


INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

contains(DEFINES,APP_WINDOWS_X64) {
LIBS +=\
  -L$$PWD/windows/x64/mingw/lib -llibopencv_world401.dll
}
contains(DEFINES,APP_LINUX_X64) {


 unix: LIBS += -L$$PWD/linux/x64/lib/libopencv_world.so.4.0
}








