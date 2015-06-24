set (PROJECTNAME ${APPLICATION_LIB_NAME})

project( ${PROJECTNAME} )

include(${PROJECTNAME}.list)


add_definitions(-D_USRDLL)
add_definitions(-DAPPLICATION_EXPORTS)

include_directories("${SOLUTION_DIR}/include/${PROJECTNAME}")

# setup Application target
add_library(${PROJECTNAME} ${APP_LINK_TYPE}
						${PUBLIC_HEADER_FILES} 
						${HEADER_FILES} 
						${SOURCE_FILES}
						${DLLMAIN_FILES}
						${CMAKE_FILES}
						)
set_target_properties(${PROJECTNAME} PROPERTIES FOLDER ${APPLICATION_FOLDER_NAME})

target_link_libraries(${PROJECTNAME}
  ${CORE_LIB_NAME}
  ${MATHCORE_LIB_NAME}
  ${GRAPHICS_LIB_NAME}
  ${RENDERER_LIB_NAME}
  ${RESOURCE_LIB_NAME}
  ${RTSHADERSYSTEM_LIB_NAME}
)

