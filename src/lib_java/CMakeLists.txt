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
set(JAR_DIRECTORY "${CMAKE_BINARY_DIR}/app/data/java/lib/")

if (NOT CMAKE_VERBOSE_MAKEFILE)
	set(quietSwitch "--quiet")
endif()

if (NOT BUILD_UNIT_TESTS_PACKAGE)
	set(skipTestsSwitch "-Dmaven.test.skip=true")
endif()


add_custom_target(Sourcetrail_lib_jar ALL
	COMMAND ${CMAKE_COMMAND} -E echo "[Maven]: Building Java indexer to: ${JAR_DIRECTORY}"
	
	WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/java_indexer/"
	COMMAND "${MVN_COMMAND}" package ${quietSwitch} ${skipTestsSwitch} "-Dsourcetrail.jar.directory=${JAR_DIRECTORY}"
	BYPRODUCTS "./target/java-indexer.jar"
)
