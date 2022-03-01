INCLUDEPATH +=\
  $$PWD/include

contains(DEFINES,APP_WINDOWS_X64) {
LIBS +=\
  -L$$PWD/windows/x64/mingw/lib -llibopencv_world451.dll
}
contains(DEFINES,APP_LINUX_X64) {
LIBS +=\
  -L$$PWD/linux/x64/lib -lopencv_world
}

