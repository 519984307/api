# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



SOURCES += \
    $$PWD/sanecore.cpp \
    $$PWD/dtwaincore.cpp \
    $$PWD/scanner.cpp \
    $$PWD/scanner_operation.cpp \
    $$PWD/scannerapp.cpp \
    $$PWD/scannerconfig.cpp \
    $$PWD/scannerconfig_sane.cpp \
    $$PWD/scannermanager.cpp
INCLUDEPATH +=\
     $$PWD/sane/include

DEPENDPATH += $$PWD/sane/include
HEADERS += \
    $$PWD/scanner.h \
    $$PWD/scannermanager.h \
        $$PWD/scanner_operation.h \
        $$PWD/scannerapp.h \
        $$PWD/scannerconfig_sane.h \
        $$PWD/twain/twain.h \
        $$PWD/sanecore.h \
        $$PWD/dtwaincore.h \
        $$PWD/scannerconfig.h

FORMS += \
    $$PWD/scannerconfig.ui \
    $$PWD/scannerconfig_sane.ui



DISTFILES += \
    $$PWD/sane/.gitignore \
    $$PWD/sane/config.h.in \
    $$PWD/sane/include/config.h.in \
    $$PWD/sane/lib/arm/libsane.so.1 \
    $$PWD/sane/lib/linux/libsane.so.1 \
    $$PWD/sane/lib/mips/libsane.so.1

contains(DEFINES,APP_LINUX_X64){
    LIBS+=\
       $$PWD/sane/lib/linux/libsane.so.1

}
contains(DEFINES,APP_LINUX_MIPS){
    LIBS+=\
       $$PWD/sane/lib/mips/libsane.so.1

}
contains(DEFINES,APP_LINUX_ARM){
    LIBS+=\
       $$PWD/sane/lib/arm/libsane.so.1

}
