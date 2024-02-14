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

Windows

1. Download [DirectX End-User Runtime](https://www.microsoft.com/en-us/download/details.aspx?id=35)
2. Download [vcpkg](https://github.com/microsoft/vcpkg)
3. Install the `cppzmq` and `zeromq` packages

### Install

Linux & windows
```
git clone https://github.com/vjdad4m/xkontrol
cd xkontrol
sh .\build.sh
```

## TODO

* Visualization
* Error handling and proper logging