# Xkontrol

bindings for the gxtrust wired muta controller

Controller libraries used (built-in):
* on linux: `linux/joystick.h`
* on windows: `Xinput.h` (might need to download https://www.microsoft.com/en-us/download/details.aspx?id=35)

## Build

### Dependencies

windows

1. install [vcpkg](https://github.com/microsoft/vcpkg)
2. install `cppzmq` and `zeromq` packages

### Install

linux & windows
```
sh .\build.sh
```

## TODO

* python bindings
* visualization
* error handling and proper logging