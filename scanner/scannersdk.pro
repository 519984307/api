#-------------------------------------------------
#
# Project created by QtCreator 2019-05-22T14:15:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = scannersdk
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    sanecore.cpp \
    dtwaincore.cpp \
    scannerconfig.cpp

HEADERS += \
    sane/sane.h \
    sane/sanei.h \
    sane/sanei_ab306.h \
    sane/sanei_access.h \
    sane/sanei_auth.h \
    sane/sanei_backend.h \
    sane/sanei_cderror.h \
    sane/sanei_codec_ascii.h \
    sane/sanei_codec_bin.h \
    sane/sanei_config.h \
    sane/sanei_debug.h \
    sane/sanei_ir.h \
    sane/sanei_jinclude.h \
    sane/sanei_jpeg.h \
    sane/sanei_lm983x.h \
    sane/sanei_magic.h \
    sane/sanei_net.h \
    sane/sanei_pa4s2.h \
    sane/sanei_pio.h \
    sane/sanei_pp.h \
    sane/sanei_pv8630.h \
    sane/sanei_scsi.h \
    sane/sanei_tcp.h \
    sane/sanei_thread.h \
    sane/sanei_udp.h \
    sane/sanei_usb.h \
    sane/sanei_wire.h \
    sane/saneopts.h \
    twain/twain.h \
    sanecore.h \
    dtwaincore.h \
    scannerconfig.h

FORMS += \
    scannerconfig.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    sane/.gitignore \
    sane/config.h.in
