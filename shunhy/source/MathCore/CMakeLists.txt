set (PROJECTNAME ${MATHCORE_LIB_NAME})

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

add_definitions(-D_USRDLL)
add_definitions(-DSHH_3DMATH_EXPORTS)
# setup Shh3dMath target
add_library(${PROJECTNAME} STATIC
						${HEADER_FILES} 
						${SOURCE_FILES}
						${DLLMAIN_FILES}
						${MODELING_HEADER_FILES}
						${MODELING_SOURCE_FILES}
						${CMAKE_FILES}
						)
set_target_properties(${PROJECTNAME} PROPERTIES FOLDER ${CORE_FOLDER_NAME})

target_link_libraries(${PROJECTNAME}
  ${CORE_LIB_NAME}
)

# platform specific dependencies
if (APPLE)
	include_directories(/usr/local/include /usr/include)
	target_link_libraries(${PROJECTNAME} ${Carbon_LIBRARY})
endif ()

# specify a precompiled header to use
# no precompiled header


# link Carbon on Mac OS X
if (APPLE)
	find_library(CARBON_LIBRARY Carbon)
	target_link_libraries(${PROJECTNAME} ${CARBON_LIBRARY})
endif ()

