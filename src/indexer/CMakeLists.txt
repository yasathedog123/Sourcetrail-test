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

target_link_libraries(Sourcetrail_indexer
	PRIVATE
		Sourcetrail_lib
)
