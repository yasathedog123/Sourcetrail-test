target_sources(External_lib_cxx
	PRIVATE
		sqlite/CppSQLite3.cpp
		sqlite/CppSQLite3.h

		tinyxml/tinystr.cpp
		tinyxml/tinystr.h
		tinyxml/tinyxml.cpp
		tinyxml/tinyxml.h
		tinyxml/tinyxmlerror.cpp
		tinyxml/tinyxmlparser.cpp
)
target_include_directories(External_lib_cxx SYSTEM
	PUBLIC
		sqlite
		tinyxml
)
