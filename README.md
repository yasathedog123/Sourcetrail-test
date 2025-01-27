# Sourcetrail

Sourcetrail is a free and open-source cross-platform source explorer that helps you get productive on unfamiliar source code. It is:
* free
* working offline
* operating on Linux, Windows (and macOS)
* supporting C, C++ and Java
* offering an SDK ([SourcetrailDB](https://github.com/CoatiSoftware/SourcetrailDB)) to write custom language extensions

# 🆕 Binary Releases

Binary releases are available for [sponsors](https://github.com/sponsors/petermost).


## __Links__
* [Quick Start Guide (Version 2021.4)](DOCUMENTATION.md#getting-started)
* [Documentation (Version 2021.4)](DOCUMENTATION.md)
* [Building](#building)

!["Sourcetrail User Interface"](docs/readme/user_interface.png "Sourcetrail User Interface")



## License

Sourcetrail is licensed under the [GNU General Public License Version 3](LICENSE.txt).

## Note

__Important:__ This project was archived by the original autors and maintainers of Sourcetrail by the end of 2021. If you want to know more about this decision, read more in the original [README.md](unused_coati_software_files/README.md)

This is a fork of the Sourcetrail project and I want to keep this project at least buildable. 

# Building

There are 2 ways to build the project:
1. With **vcpkg** provided packages ([Vcpkg build](#vcpkg-build))
2. With the **system** provided packages ([System build](#system-build))

## Cloning

It is important to clone the repository with the **submodules** and the **symlinks**:
```
git clone https://github.com/petermost/Sourcetrail.git --recurse-submodules --config core.symlinks=true
```
and get the updates with:
```
git pull --recurse-submodules
```



## Vcpkg Build

* In order to build the **java_indexer** additional software must be installed which are not provided by vcpkg:
    * [OpenJDK](https://jdk.java.net/)
    * [Maven](https://maven.apache.org/)
* **Linux:** Because **Qt6** is build from source, additional packages are needed. Install these packages with `script/install-qt6-dependencies.sh`.
* **Windows:** The build must be done in a **"x64 Native Tools Command Prompt for VS 2022"**.

Prepare the build:
```
$ cd Sourcetrail
$ cmake --preset vcpkg-ninja-release
```
Note that the initial compilation of the vcpkg packages (especially LLVM) will take a **long** time! On my machine (AMD Ryzen 7 3700X) the compilation takes about 3 hours!

Build:
```
$ cd ../build/vcpkg-ninja-release
$ cmake --build .
```



## System build

### Linux

To compile it under the current (K)ubuntu platform 24.04, "Noble Numbat", install the following packages:

**General packages:**
|Name|Version|Package|
|----|-------|-------|
|CMake|3.28.3|cmake  |
|Ninja|1.11.1|ninja-build|
|Boost|1.83.0|libboost1.83-all-dev|
|Qt|6.4.2|qt6-base-dev, qt6-svg-dev|
|SQLite|3.45.1|libsqlite3-dev|
|TinyXML|2.6.2|libtinyxml-dev|

**C++ packages:**
|Name|Version|Package|
|----|-------|-------|
|Clang|18.1.3|clang-18, libclang-18-dev|

**Java packages:**
|Name|Version|Package|
|----|-------|-------|
|Maven|3.8.7|maven|
|OpenJDK|21.0.3|openjdk-21-jdk|

**Unit test packages:**
|Name|Version|Package|
|----|-------|-------|
|Catch2|3.4.0|catch2|
|GoogleTest|1.14.0|libgtest-dev|

Prepare the build:
```
$ cd Sourcetrail
$ cmake --preset system-ninja-release
```

Build:
```
$ cd ../build/system-ninja-release
$ cmake --build .
```

### Windows
It's probably also possible to build with pre-installed libraries, like the original build instructions describe, but I didn't/don't test it.

