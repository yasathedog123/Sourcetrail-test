add_executable(Sourcetrail_indexer
	main.cpp
)
setDefaultTargetOptions(Sourcetrail_indexer)

set_target_properties(Sourcetrail_indexer
	PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/app/"
		PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/app/"
		OUTPUT_NAME              sourcetrail_indexer
)

if (WIN32)
	# hide the console when running a release build.
	set_target_properties(Sourcetrail_indexer PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
	set_target_properties(Sourcetrail_indexer PROPERTIES COMPILE_DEFINITIONS_DEBUG "_CONSOLE")
	set_target_properties(Sourcetrail_indexer PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
	set_target_properties(Sourcetrail_indexer PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO "_CONSOLE")
	set_target_properties(Sourcetrail_indexer PROPERTIES LINK_FLAGS_RELEASE "/ENTRY:\"mainCRTStartup\" /SUBSYSTEM:WINDOWS")
	set_target_properties(Sourcetrail_indexer PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")
endif ()

target_link_libraries(Sourcetrail_indexer
	PRIVATE
		Sourcetrail_lib
)
