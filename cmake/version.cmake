# Note the variable names must match the one used in productVersion.h.in!

if (EXISTS "${CMAKE_SOURCE_DIR}/.git")
	execute_process(
		COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		OUTPUT_VARIABLE branchName
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)

	execute_process(
		COMMAND ${GIT_EXECUTABLE} log -1 --format=%h
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		OUTPUT_VARIABLE commitHash
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)

	execute_process(
		COMMAND ${GIT_EXECUTABLE} log -1 --format=%ci
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		OUTPUT_VARIABLE commitTime
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)

    execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --long --match "[0-9]*" HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE versionNumber
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    string(REGEX REPLACE "^([0-9]+)\\..*" "\\1" versionYear "${versionNumber}")
    string(REGEX REPLACE "^[0-9]+\\.([0-9]+).*" "\\1" versionMonth "${versionNumber}")
    string(REGEX REPLACE "^[0-9]+\\.[0-9]+-([0-9]+).*" "\\1" versionCommit "${versionNumber}")

	set(versionString "${versionYear}.${versionMonth}.${versionCommit}")
	message(STATUS "Product version: ${versionString}")
endif()

# message(STATUS "Git current branch: ${branchName}")
# message(STATUS "Git version number: " ${versionNumber} )
# message(STATUS "Git commit hash: ${commitHash}")
# message(STATUS "Git commit time: ${commitTime}")
