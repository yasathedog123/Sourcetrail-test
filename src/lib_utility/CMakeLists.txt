add_library(Sourcetrail_lib_utility
	utility/TextCodec.cpp
	utility/TextCodec.h
	utility/utilityString.cpp
	utility/utilityString.h
)

target_include_directories(Sourcetrail_lib_utility
	PUBLIC
		utility
)

target_link_libraries(Sourcetrail_lib_utility
	PUBLIC
		Boost::locale
		Qt5::Core
)
