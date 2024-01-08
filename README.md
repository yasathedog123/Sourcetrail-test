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
and get the updates with:
```
git pull --recurse-submodules
```

# Building
There are 2 ways to build the project:
1. With **vcpkg** provided packages ([Vcpkg build](#vcpkg-build-linuxwindows))
2. With the **system** provided packages ([System build](#system-build))



## Vcpkg Build (Linux/Windows)
* Linux: Because **vcpkg** builds everything from source, additional packages are needed for building Qt5 on Linux. Install these packages with `script/install.ubuntu.qt5.dependencies.sh`.
* Linux/Windows: In order to build the **java_indexer** additional software must be installed (they are not provided by vcpkg):
    * [OpenJDK](https://jdk.java.net/)
    * [Maven](https://maven.apache.org/)


Prepare the build:
```
$ cd Sourcetrail
$ cmake --preset vcpkg-ninja-release
```
Note that the preparation (compilation of the packages) will take a **long** time! On my machine (AMD Ryzen 7 3700X) the Linux compilation takes about 2 hours and the Windows compilation about 3 hours!

Build:
```
$ cd ../build/vcpkg-ninja-release
$ cmake --build .
```



## System build
### Linux

To compile it under the current (K)ubuntu platform 23.10, "Mantic Minotaur", install the following packages:

**General packages:**

*CMake (3.27.4):*
* cmake

*Ninja (1.11.1):*
* ninja-build

*Boost (1.74.0):*
* libboost-all-dev

*Qt (5.15.10):*
* qtbase5-dev
* libqt5svg5-dev

*SQLite3 (3.42.0):*
* libsqlite3-dev

*TinyXml (2.6.2):*
* libtinyxml-dev

**C++ packages:**

*Clang (16.0.6):*
* clang
* libclang-dev

*Catch2 (2.13.10)*
* catch2

**Java packages:**

*Maven (3.8.7)
* maven

*OpenJDK (21.0.1)*
* openjdk-21-jdk

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
It's probably also possible to build with installed libraries, like the original build instructions describe, but I didn't/don't test it.
