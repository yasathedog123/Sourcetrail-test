# Sourcetrail

*__Important Note:__ This project was archived by the original autors and maintainers of Sourcetrail by the end of 2021. If you want to know more about this decision, read more in the original [README.md](COATI_SOFTWARE_README.md)
.*
# Fork

This is a fork of the Sourcetrail project and I want to keep this project at least buildable.

To compile it under the current (K)ubuntu platform 22.10,"Kinetic Kudu", install the following packages:

__CMake (3.24.2):__
* cmake

__Ninja (1.11.0):__
* ninja-build

__Boost (1.74.0):__
* libboost-dev
* libboost-all-dev

__Qt (5.15.6):__
* qt5-qmake
* qtbase5-dev
* qtbase5-dev-tools
* qttools5-dev-tools
* libqt5svg5-dev

__Clang (15.0.6):__
* clang
* libclang-dev

Please let me know when I missed a package.
# Building

* To prepare your build environment run:
    ```
    $ cd Sourcetrail
    $ cmake --preset=Release
    ```
* Now start the build with:
    ```
    $ cd ../build/Release
    $ cmake --build .
    ```
# Future plans
* Use a C++ package manager for the dependencies
* Check/Update Windows build
