


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
   -L$$PWD/linux/mips/lib -lopencv_world
}








