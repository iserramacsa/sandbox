#-------------------------------------------------
#
# Project created by QtCreator 2019-07-12T12:37:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HmiUpdater
TEMPLATE = app

#Application version
VERSION_MAJOR = 0
VERSION_MINOR = 01
VERSION_REVISION = 00

VERSION_BUILD = 0 # 0 Release | 1 RC | 2 Beta

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


win32  {
	message("Compilación para win32")
	INCLUDEPATH += $$PWD/../../../TIJLibraries/x64/include
	LIBS += $$PWD/../../../TIJLibraries/x64/lib/tinyxml2.lib
	CONFIG += c++11
	DEFINES+=DESKTOP
}
else:!ARMSTONE:!LOCO:!ARM {
	message("Compilación para linux x86")
	INCLUDEPATH += $(HOME)/TIJLibraries/x64/include
	LIBS += $(HOME)/TIJLibraries/x64/lib/libtinyxml2.a
	CONFIG += c++11
	DEFINES+=DESKTOP
}
else:ARMSTONE {
	message("Compilación para ARM gnueabi (ARMSTONE A9)")
	INCLUDEPATH += $(HOME)/TIJLibraries/arm-buildroot-linux-gnueabi/include
	LIBS += $(HOME)/TIJLibraries/arm-buildroot-linux-gnueabi/lib/libtinyxml2.a
	DEFINES+=ARMSTONE
	QMAKE_CXXFLAGS += -std=c++98
	QT += gui
}
else{
	ARM{
		message("Compilación para ARM gnueabihf (IdTIJ)")
		DEFINES+=ARM
	}
	else:LOCO {
		message("Compilación para ARM gnueabihf (Engicam loco)")
		DEFINES+=LOCO
		QT += gui
	}
	INCLUDEPATH += $(HOME)/TIJLibraries/arm-linux-gnueabihf/include
	LIBS += $(HOME)/TIJLibraries/arm-linux-gnueabihf/lib/libtinyxml2.a
	QMAKE_CXXFLAGS += -std=c++11
}


SOURCES += \
        main.cpp \
        updatewindows.cpp

HEADERS += \
	updatewindows.h

# Default rules for deployment.
target.path=/tmp
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	style.qrc
