set (PROJECTNAME HelloWorld)

project( ${PROJECTNAME} )

include(${PROJECTNAME}.list)

include_directories(include)


set (CMAKE_FILES
  CMakeLists.txt
  ${PROJECTNAME}.list
)
SOURCE_GROUP("config" FILES
	${CMAKE_FILES}
)

# setup HelloWorld target
ADD_EXECUTABLE(${PROJECTNAME}  WIN32
						#${HEADER_FILES} 
						${SOURCE_FILES}
						${CMAKE_FILES}
						)
set_target_properties(${PROJECTNAME} PROPERTIES FOLDER ${SAMPLE_FOLDER_NAME})

target_link_libraries(${PROJECTNAME}
  ${APPLICATION_LIB_NAME}
)