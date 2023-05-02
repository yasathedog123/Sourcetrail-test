target_sources(External_lib_cxx
	PRIVATE
		sqlite/CppSQLite3.cpp
		sqlite/CppSQLite3.h
)
target_include_directories(External_lib_cxx SYSTEM
	PUBLIC
		sqlite
)
