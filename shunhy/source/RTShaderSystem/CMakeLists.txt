set (PROJECTNAME ${RTSHADERSYSTEM_LIB_NAME})

project( ${PROJECTNAME} )

include(${PROJECTNAME}.list)


if (MSVC)
	# disable: "no suitable definition provided for explicit template instantiation request"
	# Occurs for no justifiable reason on all #includes of Singleton
	add_definitions(/wd4661)
endif ()

set (CMAKE_FILES
  CMakeLists.txt
  ${PROJECTNAME}.list
)
SOURCE_GROUP("config" FILES
	${CMAKE_FILES}
)

include_directories("${SOLUTION_DIR}/include/${PROJECTNAME}")
include_directories("${SOLUTION_DIR}/tools/yacc-parser/win32-linux")

# setup RTShaderSystem target
add_library(${PROJECTNAME} STATIC
						${HEADER_FILES} 
						${SOURCE_FILES}
						${DLLMAIN_FILES}
						${CMAKE_FILES}
						)
set_target_properties(${PROJECTNAME} PROPERTIES FOLDER ${GRAPHICS_FOLDER_NAME})

target_link_libraries(${PROJECTNAME}
  ${CORE_LIB_NAME}
  ${MATHCORE_LIB_NAME})

