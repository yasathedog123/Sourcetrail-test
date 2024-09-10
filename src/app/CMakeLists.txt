configure_file("${CMAKE_SOURCE_DIR}/setup/Sourcetrail.sh"  "${CMAKE_BINARY_DIR}/app/Sourcetrail.sh" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/setup/Sourcetrail.ico" "${CMAKE_BINARY_DIR}/app/Sourcetrail.ico" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/script/_gdbinit"       "${CMAKE_BINARY_DIR}/app/.gdbinit" COPYONLY)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/Sourcetrail.rc
	"// Icon with lowest ID value placed first to ensure application icon\n"
	"// remains consistent on all systems.\n"
	"IDI_ICON1 ICON \"${CMAKE_BINARY_DIR}/app/Sourcetrail.ico\"\n"
)

add_executable(Sourcetrail
	main.cpp
	${CMAKE_CURRENT_BINARY_DIR}/Sourcetrail.rc
)
setDefaultTargetOptions(Sourcetrail)

set_target_properties(Sourcetrail
	PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/app/"
		PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/app/"
)

target_link_libraries(Sourcetrail
	PRIVATE
		Sourcetrail_lib
)
