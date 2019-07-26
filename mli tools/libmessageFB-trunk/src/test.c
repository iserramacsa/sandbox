#include <stdlib.h>

#include "messageFB.h"

#if !defined TEST_FONT
#define TEST_FONT "/usr/share/fonts/truetype/ttf-dejavu/DejaVuSansMono-Bold.ttf"
#endif

#if !defined TEST_COLOR
#define TEST_COLOR 0x50f05000
#endif

int _counter = 0;
const char *text = NULL;

////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
	if (argc > 1) {
		text = argv[1];
	} else {
		text = argv[0];
	}

	if (beginMessage(&argc, &argv) != 0) {
		return 1;
	}

	setMessageFont(TEST_FONT);
	setMessageColor(TEST_COLOR);

	showMessage("Starting ...");
	sleep(3);
	showMessage(text);
	sleep(3);

	stopMessage();

	return 0;
}
