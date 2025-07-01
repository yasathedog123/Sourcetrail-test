#!/bin/sh

gcovr --no-color --root ../../Sourcetrail .  --html-details --output coverage/coverage.html
xdg-open coverage/coverage.html
