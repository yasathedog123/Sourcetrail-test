add_library(AidKit_lib
	enum_class.hpp
	enum_class.cpp

	shared_data.hpp
	shared_data.cpp
)
setDefaultTargetOptions(AidKit_lib)

target_include_directories(AidKit_lib
	PUBLIC
		.
)
