set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE static)

# Try to prevent msvc rebuilds (See https://github.com/microsoft/vcpkg/issues/26346):
set(VCPKG_DISABLE_COMPILER_TRACKING ON)
