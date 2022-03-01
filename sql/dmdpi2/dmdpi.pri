
INCLUDEPATH+= \
              $$PWD/include

contains(DEFINES,APP_WINDOWS_X64) {
LIBS+= -L$$PWD/windows/x64/lib/ -ldmdpi
}
contains(DEFINES,APP_LINUX_X64) {
LIBS+= -L$$PWD/linux/x64/lib/ -ldmdpi

}


HEADERS += \
    $$PWD/dmsqldb.h \
    $$PWD/dmsqlquery.h

SOURCES += \
    $$PWD/dmsqldb.cpp \
    $$PWD/dmsqlquery.cpp
