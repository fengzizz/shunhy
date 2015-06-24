set (PROJECTNAME ${DRAWDRV11_LIB_NAME})

project( ${PROJECTNAME} )

include(${PROJECTNAME}.list)


set (CMAKE_FILES
  CMakeLists.txt
  ${PROJECTNAME}.list
)
SOURCE_GROUP("config" FILES
	${CMAKE_FILES}
)
if(MSVC10)
	include_directories(${DirectX_INCLUDE_DIR})
endif(MSVC10)

include_directories("${SOLUTION_DIR}/include/DrawDrv")
include_directories(include)




# setup DrawDrv11 target
add_library(${PROJECTNAME} STATIC 
						${HEADER_FILES} 
						${SOURCE_FILES}
						${DLLMAIN_FILES}
						${CMAKE_FILES}
						)
set_target_properties(${PROJECTNAME} PROPERTIES FOLDER ${RENDER_CORE_FOLDER_NAME})



target_link_libraries(${PROJECTNAME} 
						${DirectX_D3D11_LIBRARIES}						
						${MATHCORE_LIB_NAME} 
						${CORE_LIB_NAME}
						${DRAWDRV_LIB_NAME}
)

link_directories(${DirectX_LIBRARY_DIR})
