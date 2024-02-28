# Copy data:
get_property(isMultiConfigGenerator GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if (isMultiConfigGenerator)
	message(FATAL_ERROR "TODO: Multi config generator support is missing!")
	foreach(CONFIGURATION_TYPE ${CMAKE_CONFIGURATION_TYPES})
		file(COPY "bin/app/data/"  DESTINATION "${CONFIGURATION_TYPE}/app/data/")
		file(COPY "bin/app/user/"  DESTINATION "${CONFIGURATION_TYPE}/app/user/")
		file(COPY "bin/test/data/" DESTINATION "${CONFIGURATION_TYPE}/test/data/")
	endforeach()
else()
	message(STATUS "Copying: ${CMAKE_SOURCE_DIR}/bin/app/ -> ${CMAKE_BINARY_DIR}/app/")
	file(COPY "${CMAKE_SOURCE_DIR}/bin/app/" DESTINATION "${CMAKE_BINARY_DIR}/app/")

	# The test data must be 'linked' because the 'FilePathTestSuite' and 'FileSystemTestSuite'
	# contain symlinks and of this writing (2024-02-23) there is no cmake command which copies symlinks
	# correctly. See https://gitlab.kitware.com/cmake/cmake/-/issues/14609
	message(STATUS "Linking: ${CMAKE_SOURCE_DIR}/bin/test/data/ -> ${CMAKE_BINARY_DIR}/test/data")
	file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/test")
	file(CREATE_LINK "${CMAKE_SOURCE_DIR}/bin/test/data/" "${CMAKE_BINARY_DIR}/test/data" SYMBOLIC)
endif()

add_executable(Sourcetrail_test
	helper/TestFileRegister.cpp
	helper/TestFileRegister.h
	helper/TestStorage.h

	Catch2.hpp
	test_main.cpp

	CommandlineTestSuite.cpp
	ConfigManagerTestSuite.cpp
	CxxIncludeProcessingTestSuite.cpp
	CxxParserTestSuite.cpp
	CxxTypeNameTestSuite.cpp
	FileManagerTestSuite.cpp
	FilePathFilterTestSuite.cpp
	FilePathTestSuite.cpp
	FileSystemTestSuite.cpp
	GraphTestSuite.cpp
	HierarchyCacheTestSuite.cpp
	JavaIndexSampleProjectsTestSuite.cpp
	JavaParserTestSuite.cpp
	LogManagerTestSuite.cpp
	LowMemoryStringMapTestSuite.cpp
	MatrixBaseTestSuite.cpp
	MatrixDynamicBaseTestSuite.cpp
	MessageQueueTestSuite.cpp
	NetworkProtocolHelperTestSuite.cpp
	PythonIndexerTestSuite.cpp
	RefreshInfoGeneratorTestSuite.cpp
	SearchIndexTestSuite.cpp
	SettingsMigratorTestSuite.cpp
	SettingsTestSuite.cpp
	SharedMemoryTestSuite.cpp
	SourceGroupTestSuite.cpp
	SourceLocationCollectionTestSuite.cpp
	SqliteBookmarkStorageTestSuite.cpp
	SqliteIndexStorageTestSuite.cpp
	StorageTestSuite.cpp
	TaskSchedulerTestSuite.cpp
	TextAccessTestSuite.cpp
	UtilityGradleTestSuite.cpp
	UtilityMavenTestSuite.cpp
	UtilityStringTestSuite.cpp
	UtilityTestSuite.cpp
	Vector2TestSuite.cpp
)

target_include_directories(Sourcetrail_test
	PRIVATE
		helper
)

set_target_properties(Sourcetrail_test
	PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test/"
		PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/test/"
)

target_link_libraries(Sourcetrail_test
	PRIVATE
		Sourcetrail_lib
		Catch2::Catch2
)

if (WIN32)
	target_compile_options(Sourcetrail_test
		PRIVATE
			/bigobj
	)
	set_target_properties(Sourcetrail_test
		PROPERTIES
			VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/test"
	)
endif ()

catch_discover_tests(Sourcetrail_test)
