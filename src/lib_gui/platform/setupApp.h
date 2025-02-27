#ifndef SETUP_PLATFORM_H
#define SETUP_PLATFORM_H

#include <FilePath.h>
#include <Version.h>

Version setupAppDirectories(const FilePath &appPath);
void setupUserDirectory(const FilePath &appPath);
void setupAppEnvironment(int argc, char *argv[]);

#endif
