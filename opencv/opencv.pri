
contains(DEFINES,APP_LINUX_MIPS) {
   DEFINES += _GLIBCXX_USE_CXX11_ABI=0
}

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

contains(DEFINES,APP_WINDOWS_X64) {
LIBS +=\
  -L$$PWD/windows/x64/mingw/lib -llibopencv_world401.dll
}
contains(DEFINES,APP_LINUX_X64) {
LIBS +=\
   -L$$PWD/linux/x64/lib -lopencv_world
}
contains(DEFINES,APP_LINUX_ARM) {
LIBS +=\
   -L$$PWD/linux/arm/lib -lopencv_world
}
contains(DEFINES,APP_LINUX_MIPS) {
LIBS +=\
    $$PWD/linux/mips/lib/libopencv_world.so.4.0


}








