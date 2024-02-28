target_sources(Sourcetrail_lib_external
	PRIVATE
		sqlite/CppSQLite3.cpp
		sqlite/CppSQLite3.h
)
target_include_directories(Sourcetrail_lib_external SYSTEM
	PUBLIC
		sqlite
)
