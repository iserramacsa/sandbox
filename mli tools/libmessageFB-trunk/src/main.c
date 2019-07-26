/**
messageFB reads commands from a FIFO and show a message using the messageFB library.

ARGUMENTS
   -d            daemonize process
   -f <fifo>     set FIFO file
   -h            show help

The FIFO commands format is:
   COMMAND[VALUE]
where COMMAND might be:
   c    set text color using HEX notation
   d    show VALUE
   f    set text font in file VALUE
   h    set text height (DEC value)
   q    quit (VALUE ignored)
   z    clear screen (VALUE ignored)

EXAMPLE
   dHello World!   --> prints "Hello World!"
   cf05020         --> set text color to 0xf05020
  */

#include <assert.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "messageFB.h"

#if !defined FONT
#define FONT "/usr/share/fonts/truetype/ttf-dejavu/DejaVuSansMono-Bold.ttf"
#endif

#if !defined FONT_HEIGHT
#define FONT_HEIGHT 22
#endif

#if !defined COLOR
#define COLOR 0xf05020
#endif

#define DEFAULT_FIFO_FILE "/tmp/messageFB-fifo"
#define MAX_LINE 256

volatile int _parentRunning = 1;
int _parentPid = -1;

////////////////////////////////////////////////////////////////////////////////////////////////////
void panic(const char *desc) {
	fprintf(stderr, "ERROR: %s\n", desc);
	fflush(stderr);
	exit(1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void usage(const char *prog) {
	assert(prog != NULL);

	fprintf(stdout,
			"Usage: %s [-d] [-f FILE]\n"
			"OPTIONS:\n"
			"    -d          daemonize process\n"
			"    -f FILE     set FIFO file FILE\n"
			"    -h          show this help\n"
			, prog);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void killParent() {
	if (_parentPid > 0) {
		kill(_parentPid, SIGUSR1);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void stopParent(int sig) {
	switch (sig) {
		case SIGUSR1:
			_parentRunning = 0;
			break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void waitBeforeExit() {
	while (_parentRunning) {
		pause();
	}
	exit(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int daemonize() {
	signal(SIGUSR1, stopParent);

	int pid = fork();
	if (pid < 0) {
		return -1;
	} else if (pid != 0) {
		// Parent code
		waitBeforeExit();
	}

	_parentPid = getppid();
	umask(0);
	if (setsid() < 0) {
		return -1;
	}
	if (chdir("/") < 0) {
		return -1;
	}

	close(2);
	close(1);
	close(0);

	open("/dev/null", O_RDWR);
	dup(0);
	dup(0);

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int createFifo(const char *filename) {
	remove(filename);

	if (mkfifo(filename, 0644) < 0) {
		return -1;
	}

	int ret = open(filename, O_RDWR, 0);
	if (ret >= 0) {
		fcntl(ret, F_SETFL, O_NONBLOCK);
	}

	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int readCommand(int fd, char *command) {
	assert(command != NULL);

	return read(fd, command, 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int readLine(int fd, void *buff, int maxlen) {
	char *ptr = (char *) buff;
	while (maxlen > 0) {
		int r = read(fd, ptr, 1);
		if (r < 0) {
			return -1;
		} else if (r == 0) {
			usleep(1000);
		} else if (*ptr == '\n') {
			*ptr = '\0';
			break;
		} else {
			maxlen--;
			ptr++;
		}
	}
	return (int) ((unsigned int) ptr - (unsigned int) buff);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int processCommand(int fd) {
	assert(fd >= 0);

	char command;
	if (readCommand(fd, &command) != 1) {
		return -1;
	}

	if (command == 'q' || command == 'Q') {
		close(fd);
		exit(0);
	}

	char line[MAX_LINE + 1];
	int n = readLine(fd, line, MAX_LINE);
	if (n < 0) {
		return -1;
	}

	switch (command) {
		case 'c':
		case 'C':
			setMessageColor(strtol(line, NULL, 16));
			break;

		case 'd':
		case 'D':
			showMessage(line);
			break;

		case 'f':
		case 'F':
			setMessageFont(line);
			break;

		case 'h':
		case 'H':
			setMessageFontHeight(strtol(line, NULL, 10));
			break;

		case 'z':
		case 'Z':
			clearMessage();
			break;
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void mainLoop(int fd) {
	assert(fd >= 0);

	fd_set rfds;
	FD_ZERO(&rfds);

	FD_SET(fd, &rfds);
	int maxfd = fd;

	int running = 1;
	while (running) {
		int s = select(maxfd + 1, &rfds, NULL, NULL, NULL);
		if (s < 0) {
			break;
		} else if (s == 0) {
			continue;
		}

		if (FD_ISSET(fd, &rfds)) {
			if (processCommand(fd) != 0) {
				break;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
	int asDaemon = 0;
	const char *fifoFile = NULL;

	// Parse arguments
	int opt;
	while ((opt = getopt(argc, argv, "df:h")) != -1) {
		switch (opt) {
			case 'd':
				asDaemon = 1;
				break;

			case 'f':
				fifoFile = optarg;
				break;

			case 'h':
				usage(argv[0]);
				exit(0);

			default:
				usage(argv[0]);
				panic("Unknown argument");
		}
	}

	// Daemonize if required
	if (asDaemon) {
		if (daemonize() < 0) {
			panic("Impossible to daemonize");
		}
	}

	// Create FIFO
	int fifo;
	if (!fifoFile) {
		fifo = createFifo(DEFAULT_FIFO_FILE);
	} else {
		fifo = createFifo(fifoFile);
	}
	if (fifo < 0) {
		panic("Impossible to create FIFO");
	}

	// Kill parent
	killParent();

	// Begin libmessageFB
	if (beginMessage(&argc, &argv) != 0) {
		close(fifo);
		panic("Impossible to start libmessageFB");
	}

	setMessageFont(FONT);
	setMessageColor(COLOR);
	setMessageFontHeight(FONT_HEIGHT);

	// Read
	mainLoop(fifo);

	// Stop everything
	stopMessage();
	close(fifo);

	return 0;
}
