set (PROJECTNAME TestConsole)

project( ${PROJECTNAME} )

include(${PROJECTNAME}.list)

include_directories(include)

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

# setup test target
ADD_EXECUTABLE(${PROJECTNAME}
						#${HEADER_FILES} 
						${SOURCE_FILES}
						${CMAKE_FILES}
						)

set_target_properties(${PROJECTNAME} PROPERTIES FOLDER ${SAMPLE_FOLDER_NAME})

target_link_libraries(${PROJECTNAME}
  ${MATHCORE_LIB_NAME}
)