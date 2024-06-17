add_library(Sourcetrail_lib_python
	project/SourceGroupFactoryModulePython.h
	project/SourceGroupFactoryModulePython.cpp
	project/SourceGroupPythonEmpty.h
	project/SourceGroupPythonEmpty.cpp
)
setDefaultTargetOptions(Sourcetrail_lib_python)

target_include_directories(Sourcetrail_lib_python
	PUBLIC
		project
)

target_link_libraries(Sourcetrail_lib_python
	PUBLIC
		Sourcetrail_lib
)

#[[
add_custom_command(
	TARGET Sourcetrail_lib_python
	PRE_BUILD
	COMMAND ${BASH} ${PROJECT_SOURCE_DIR}/script/download_python_indexer.sh
	COMMENT "download python indexer"
)
]]
