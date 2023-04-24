# Sourcetrail

*__Important Note:__ This project was archived by the original autors and maintainers of Sourcetrail by the end of 2021. If you want to know more about this decision, read more in the original [README.md](COATI_SOFTWARE_README.md)
.*
# Note
This is a fork of the Sourcetrail project and I want to keep this project at least buildable. 

# Cloning
It is important to clone the repository with the **submodules**:
```
git clone https://github.com/petermost/Sourcetrail.git --recurse-submodules
```

# Building
There are 2 ways to build the project:
1. With **vcpkg** provided packages ([Vcpkg build](#vcpkg-build-linuxwindows))
2. With the **system** provided packages ([System build](#system-build))



## Vcpkg Build (Linux/Windows)
Because **vcpkg** builds everything from source, additional packages are needed for building Qt5 on Linux. Install the additional packages with `script/install.ubuntu.qt5.dependencies.sh`.

Prepare the build:
```
$ cd Sourcetrail
$ cmake --preset=vcpkg-ninja-release
```
Note that the preparation (compilation of the packages) will take a **long** time! On my machine (AMD Ryzen 7 3700X) the Linux compilation takes about 2 hours and the Windows compilation about 3 hours!

Build:
```
$ cd ../build/vcpkg-ninja-release
$ cmake --build .
```



## System build
### Linux

To compile it under the current (K)ubuntu platform 22.10,"Kinetic Kudu", install the following packages:

**CMake (3.24.2):**
* cmake

**Ninja (1.11.0):**
* ninja-build

**Boost (1.74.0):**
* libboost-dev
* libboost-all-dev

**Qt (5.15.6):**
* qt5-qmake
* qtbase5-dev
* qtbase5-dev-tools
* qttools5-dev-tools
* libqt5svg5-dev

**Clang (15.0.6):**
* clang
* libclang-dev

**Catch2 (2.13.9)**
* catch2

Prepare the build:
```
$ cd Sourcetrail
$ cmake --preset=system-ninja-release
```

Build:
```
$ cd ../build/system-ninja-release
$ cmake --build .
```
### Windows
It's probably also possible to build with installed libraries, like the original build instructions describe, but I didn't/don't test it.
