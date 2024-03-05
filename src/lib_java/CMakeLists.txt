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

add_custom_command(
	TARGET Sourcetrail_lib_java
	PRE_BUILD
	WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/java_indexer/"
	COMMAND ${MVN_COMMAND} --quiet package
	BYPRODUCTS "./target/java-indexer.jar"
	COMMENT "Building java indexer jars"
)
# TODO: This also copies unneeded maven directories (classes, generated-sources, ...)
add_custom_command(
	TARGET Sourcetrail_lib_java
	POST_BUILD
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "java_indexer/target/"  "${CMAKE_BINARY_DIR}/app/data/java/lib/"
	COMMENT "Copying java indexer jars"
)
# Workaround for above copy problem
add_custom_command(
	TARGET Sourcetrail_lib_java
	POST_BUILD
	WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/app/data/java/lib/"
	COMMAND ${CMAKE_COMMAND} -E rm -rf "classes" "generated-sources" "maven-archiver" "maven-status" "test-classes"
	COMMENT "Deleting unneeded maven directories"
)
