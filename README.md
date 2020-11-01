# Maya Plugin Adapter

A Maya plugin abstraction designed to act as an interop between the Maya native API and a separate executable that serves as the true plugin.
The intent is to allow plugins to be created using langauges that previously would have proved difficult to integrate, provide a clean API, and not require experience with C++ to take advantage of.

> STATUS: ABANDONED
>
> I started this project intending to build extensions for Maya LT, discovering that the LT edition does not support custom plugins (WHY!? It prevents people from automating processes and devs like myself from building an ecosystem of plugins around the product). In light of this, the project is effectively dead for me. It may have value as a plugin starter kit however, as the tooling is relatively self contained (the Maya devkit for example is automatically downloaded, xplat support is in place or at least very close).

## Building

You'll need CMake version 3.18 or higher.

### Windows

```sh
# Configure
mkdir ./out
mkdir ./out/win
cd ./out/win
cmake ../../
cd ../../
# Build
cmake --build ./out/win
```

### MacOS

You'll need 7zip installed and on PATH.

```sh
# Configure
mkdir ./out
mkdir ./out/macos
cd ./out/macos
cmake ../../
cd ../../
# Build
cmake --build ./out/macos
```

### Linux

```sh
# Configure
mkdir ./out
mkdir ./out/linux
cd ./out/linux
cmake ../../
cd ../../
# Build
cmake --build ./out/linux
```

## Planning

* Have plugin compiled for all platforms, made available via Github releaes.
* Integration with native executable achieved via configuration file.
