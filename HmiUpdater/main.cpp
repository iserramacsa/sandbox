#include "updatewindows.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	UpdateWindow w;
#if defined (ARMSTONE) || defined (LOCO)
	a.setOverrideCursor(Qt::BlankCursor);
	w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint) ;
	w.setWindowState(Qt::WindowFullScreen) ;
	w.showFullScreen();
#else
	w.show();
#endif
	return a.exec();
}
