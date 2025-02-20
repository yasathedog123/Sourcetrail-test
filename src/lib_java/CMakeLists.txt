add_library(Sourcetrail_lib_java
	data/indexer/IndexerCommandJava.cpp
	data/indexer/IndexerCommandJava.h
	data/indexer/IndexerJava.cpp
	data/indexer/IndexerJava.h

	data/parser/java/JavaParser.cpp
	data/parser/java/JavaParser.h
	data/parser/java/JavaEnvironment.cpp
	data/parser/java/JavaEnvironment.h
	data/parser/java/JavaEnvironmentFactory.cpp
	data/parser/java/JavaEnvironmentFactory.h

	project/SourceGroupFactoryModuleJava.cpp
	project/SourceGroupFactoryModuleJava.h
	project/SourceGroupJava.cpp
	project/SourceGroupJava.h
	project/SourceGroupJavaEmpty.cpp
	project/SourceGroupJavaEmpty.h
	project/SourceGroupJavaGradle.cpp
	project/SourceGroupJavaGradle.h
	project/SourceGroupJavaMaven.cpp
	project/SourceGroupJavaMaven.h

	utility/utilityJava.cpp
	utility/utilityJava.h
	utility/utilityGradle.cpp
	utility/utilityGradle.h
	utility/utilityMaven.cpp
	utility/utilityMaven.h

	LanguagePackageJava.cpp
	LanguagePackageJava.h
)
setDefaultTargetOptions(Sourcetrail_lib_java)

target_include_directories(Sourcetrail_lib_java
	PUBLIC
		data/indexer
		data/parser/java
		project
		utility
		.
)

target_link_libraries(Sourcetrail_lib_java
	PUBLIC
		Sourcetrail_lib
		JNI::JNI
)

#
# Maven build (java-indexer.jar)
#
# TODO: Try to build the jar also in the CMAKE_BINARY_DIR

if (NOT CMAKE_VERBOSE_MAKEFILE)
	set(quietSwitch "--quiet")
endif()

if (NOT BUILD_UNIT_TESTS_PACKAGE)
	set(skipTestsSwitch "-Dmaven.test.skip=true")
endif()

add_custom_command(
	COMMAND ${CMAKE_COMMAND} -E echo "Maven: Building Java indexer"
	
	TARGET Sourcetrail_lib_java
	PRE_BUILD
	WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/java_indexer/"
	COMMAND "${MVN_COMMAND}" package ${quietSwitch} ${skipTestsSwitch}
	BYPRODUCTS "./target/java-indexer.jar"
)
# Copy java indexer jars
# TODO: This also copies unneeded maven directories (classes, generated-sources, ...)
add_custom_command(
	TARGET Sourcetrail_lib_java
	POST_BUILD
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "java_indexer/target/"  "${CMAKE_BINARY_DIR}/app/data/java/lib/"
)

# Delete unneeded/unwanted maven directories as a workaround for the above copy problem:
add_custom_command(
	TARGET Sourcetrail_lib_java
	POST_BUILD
	WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/app/data/java/lib/"
	COMMAND ${CMAKE_COMMAND} -E rm -rf "classes" "generated-sources" "maven-archiver" "maven-status" "test-classes"
)
