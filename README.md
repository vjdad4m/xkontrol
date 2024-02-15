# Xkontrol

<div align="center">
<img src="./assets/xkontrol_logo.png" width=256px>

Xkontrol: Bindings and tools for wired X input type controllers.
</div>

---

## Build

### Dependencies

Controller libraries used *(built-in)*:
* on linux: `linux/joystick.h`
* on windows: `Xinput.h`

Linux

1. Install `libzmq3-dev` and `cppzmq-dev`

Windows

1. Download [DirectX End-User Runtime](https://www.microsoft.com/en-us/download/details.aspx?id=35)
2. Download [vcpkg](https://github.com/microsoft/vcpkg)
3. Install the `cppzmq` and `zeromq` packages

### Install

Linux & windows

1. Clone this repository
```
git clone https://github.com/vjdad4m/xkontrol
```
2. Change directories
```
cd xkontrol
```
3. Run the build process
```
sh .\build.sh
```

## TODO

* Visualization
* Error handling and proper logging