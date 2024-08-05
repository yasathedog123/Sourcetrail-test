### Changelog

#### 2024.8.2
* GUI: Remove `qt.conf` which seems to improve the menu font rendering under Windows

#### 2024.7.3
* GUI: Fix non-working dialogs i.e. the selected action weren't executed
* C/C++: Disabled indexing of non-trivial destructor calls. See [#7 (comment)](https://github.com/petermost/Sourcetrail/issues/7#issuecomment-2199640807) for further details.

#### 2024.7.2
* Installation: Add Debian packaging

#### 2024.7.1
* C/C++: Add indexing of the deduced type of auto variables
* C/C++: Add indexing of user defined conversion operators
* C/C++: Add indexing of non-trivial destructor calls

#### 2024.7.0
* C/C++: Update libClang/LibTooling to Clang 18

#### 2024.6.0
* C/C++: Add indexing of the deduced type of auto variables

#### 2024.05.9
* C/C++: Add indexing of user defined conversion operators
* C/C++: Update support for C++ standards C++20, C++23
* C/C++: Update detection of 'Global Include Paths' for Visual Studio 2017, 2019, 2022
* Java: Generalize detection of JRE/JVM
* Java: Generalize detection of Maven
* Java: Update support for Java Standard 16, 17, 18, 19, 20 
* Framework: Update libClang/LibTooling to Clang 16/17
* Framework: Switch from Qt5 to Qt6

#### 2021.4.19 - 0.3.0
[Coati Changelog](unused_coati_software_files/CHANGELOG.md)