#!/bin/sh

# Extracted from https://wiki.qt.io/Building_Qt_5_from_Git

# Linux/X11
sudo apt-get install build-dep qtbase5-dev

# Build essentials
sudo apt-get install build-essential perl python3 git

# Libxcb
sudo apt-get install '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev

# Qt WebKit
sudo apt-get install flex bison gperf libicu-dev libxslt-dev ruby

# Qt WebEngine
sudo apt-get install libxcursor-dev libxcomposite-dev libxdamage-dev libxrandr-dev libxtst-dev libxss-dev libdbus-1-dev libevent-dev libfontconfig1-dev libcap-dev libpulse-dev libudev-dev libpci-dev libnss3-dev libasound2-dev libegl1-mesa-dev gperf bison nodejs

# Qt Multimedia
sudo apt-get install libasound2-dev libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-good1.0-dev libgstreamer-plugins-bad1.0-dev

# QDoc Documentation Generator Tool
sudo apt install clang libclang-dev
