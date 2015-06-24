set (PROJECTNAME ${RENDERER_LIB_NAME})
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



include_directories(include)
include_directories("${SOLUTION_DIR}/include/${PROJECTNAME}")

# setup Application target
add_library(${PROJECTNAME} STATIC
						${PUBLIC_HEADER_FILES} 
						${HEADER_FILES} 
						${SOURCE_FILES}
						${DLLMAIN_FILES}
						${CMAKE_FILES}
						)
set_target_properties(${PROJECTNAME} PROPERTIES FOLDER ${RENDER_CORE_FOLDER_NAME})

target_link_libraries(${PROJECTNAME}
  ${CORE_LIB_NAME}
  ${MATHCORE_LIB_NAME}
  ${DRAWDRV9_LIB_NAME}
  ${DRAWDRV11_LIB_NAME})
