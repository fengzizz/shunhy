set (PROJECTNAME ShanHaiWin)

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
include_directories("${SOLUTION_DIR}/include/IWindow")
include_directories("${SOLUTION_DIR}/include/IDrawDrv")

add_definitions(-D_USRDLL)
add_definitions(-DSHANHAIWIN_EXPORTS)

# setup ShanHaiWin target
add_library(${PROJECTNAME} SHARED 
						${HEADER_FILES} 
						${SOURCE_FILES}
						${DLLMAIN_FILES}
						${INTERFACE_FILES}
						${CMAKE_FILES}
						)
set_target_properties(${PROJECTNAME} PROPERTIES FOLDER ${ADDON_FOLDER_NAME})

#target_link_libraries(${PROJECTNAME}
#  ${DirectX_D3D11_LIBRARIES}
#)



#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${DirectX_INCLUDE_DIR})
#link_directories(${DirectX_LIBRARY_DIR})

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

