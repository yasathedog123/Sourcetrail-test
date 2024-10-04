add_library(AidKit_lib
	aidkit/enum_class.hpp
	aidkit/enum_class.cpp

	aidkit/shared_data.hpp
	aidkit/shared_data.cpp
)
setDefaultTargetOptions(AidKit_lib)

target_include_directories(AidKit_lib
	PUBLIC
		.
)
