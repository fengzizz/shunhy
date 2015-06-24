#-------------------------------------------------------------------
# This file is part of the CMake build system for ShanHai
#     (Object-oriented Graphics Rendering Engine)
# 
#
# 
# 
#-------------------------------------------------------------------


if(SHH_LINK_AS_DLL)
	add_definitions(-D__SHH_LINK_AS_DLL__)
	add_definitions(-D__SHH_EXPORT_API__)

	if(SHH_PLATFROM_WIN32)
		add_definitions(-D__SHH_WIN32__)
	endif()
endif()

if (SHH_LINK_AS_DLL)
	set(APP_LINK_TYPE SHARED)
else()
	set(APP_LINK_TYPE STATIC)
endif ()


#####################################################################
# add subdirectory
#####################################################################
add_subdirectory(DrawDrv)
add_subdirectory(DrawDrv9)
add_subdirectory(DrawDrv11)
add_subdirectory(Core)
add_subdirectory(MathCore)
add_subdirectory(RTShaderSystem)
add_subdirectory(Application)
add_subdirectory(Graphics)
add_subdirectory(Renderer)
add_subdirectory(Resource)