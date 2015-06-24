set (PROJECTNAME ${DRAWDRV_LIB_NAME})

project( ${PROJECTNAME} )

include(${PROJECTNAME}.list)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${DirectX_INCLUDE_DIR})
include_directories(include)
include_directories("${SOLUTION_DIR}/include/DrawDrv")

link_directories(${DirectX_LIBRARY_DIR})
add_definitions(-D_USRDLL)
ADD_DEFINITIONS(-DSHH_DRV_EXPORTS)



# setup DrawDrv target
add_library(${PROJECTNAME} STATIC
						${HEADER_FILES} 
						${SOURCE_FILES}
						${DLLMAIN_FILES}
						${CMAKE_FILES}
						)
set_target_properties(${PROJECTNAME} PROPERTIES FOLDER ${RENDER_CORE_FOLDER_NAME})

target_link_libraries(${PROJECTNAME} 
						${DirectX_LIBRARIES} 
						${MATHCORE_LIB_NAME} 
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