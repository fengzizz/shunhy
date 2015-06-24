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
endif(SHH_LINK_AS_DLL)


#####################################################################
# add subdirectory
#####################################################################

add_subdirectory(HelloWorld)
add_subdirectory(TestConsole)

