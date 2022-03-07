
DEFINES+=DM64

INCLUDEPATH+= \
              $$PWD/include
DEPENDPATH+= \
            $$PWD/include
contains(DEFINES,APP_WINDOWS_X64) {
LIBS+= -L$$PWD/windows/x64/lib/ -ldmdpi
}
contains(DEFINES,APP_LINUX_X64) {
LIBS+= -L$$PWD/linux/x64/lib/ -ldmdpi

}
contains(DEFINES,APP_LINUX_ARM) {
LIBS+= -L$$PWD/linux/arm/lib/ -ldmdpi

}
contains(DEFINES,APP_LINUX_MIPS) {
LIBS+= -L$$PWD/linux/mips/lib/ -ldmdpi

}

HEADERS += \
    $$PWD/dmsqldb.h \
    $$PWD/dmsqlquery.h

SOURCES += \
    $$PWD/dmsqldb.cpp \
    $$PWD/dmsqlquery.cpp
