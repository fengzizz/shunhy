#-------------------------------------------------------------------
# This file is part of the CMake build system for ShanHai
#     (Object-oriented Graphics Rendering Engine)
# 
#
# 
# 
#-------------------------------------------------------------------


cmake_minimum_required(VERSION 2.8)

# Use relative paths
# This is mostly to reduce path size for command-line limits on windows
if(WIN32)
  # This seems to break Xcode projects so definitely don't enable on Apple builds
  set(CMAKE_USE_RELATIVE_PATHS true)
  set(CMAKE_SUPPRESS_REGENERATION true)
endif()

#####################################################################
# global configs
#####################################################################
set(SOLUTION_NANE shunhy)
MESSAGE(STATUS "${SOLUTION_NANE} root begin.")
project(${SOLUTION_NANE})

set(SOLUTION_DIR ${PROJECT_SOURCE_DIR})

# Include necessary submodules
set(CMAKE_MODULE_PATH
	"${PROJECT_SOURCE_DIR}/CMake"
	"${PROJECT_SOURCE_DIR}/CMake/Utils"
	"${PROJECT_SOURCE_DIR}/CMake/Packages"
)
set(PROJECT_TEMPLATES_DIR "${PROJECT_SOURCE_DIR}/CMake/Templates")
set(PROJECT_WORK_DIR ${PROJECT_BINARY_DIR})

include(CMakeDependentOption)

if(WIN32)
	include(WindowsBuildConfig)
endif()


include(FindOpenGLES)

######################################################################
# Provide user options to customise the build process
######################################################################
# Find dependencies
#include("../Dependencies")

# Customise what to build


option(SHANHAI_STATIC "Static build" FALSE)
cmake_dependent_option(SHANHAI_BUILD_RENDERSYSTEM_D3D9 "Build Direct3D9 RenderSystem" TRUE "WIN32;DirectX_FOUND" FALSE)
cmake_dependent_option(SHANHAI_BUILD_RENDERSYSTEM_D3D11 "Build Direct3D11 RenderSystem [EXPERIMENTAL]" TRUE "WIN32;DirectX_D3D11_FOUND" FALSE)
cmake_dependent_option(SHANHAI_BUILD_RENDERSYSTEM_GL "Build OpenGL RenderSystem" FALSE "OPENGL_FOUND;NOT OGRE_BUILD_PLATFORM_IPHONE" FALSE)

# Specify build paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)


###################################################################
# global setting
###################################################################
set(CORE_FOLDER_NAME "1.Core")
set(RENDER_CORE_FOLDER_NAME "2.RenderCore")
#set(ADDON_FOLDER_NAME "3.AddOn")
set(GRAPHICS_FOLDER_NAME "3.Graphics")
set(APPLICATION_FOLDER_NAME "4.Application")
set(SAMPLE_FOLDER_NAME "5.Demos")

set(CMAKE_SCRIPTS_NAME "CMakeScripts")
set(CORE_LIB_NAME "Core")
set(MATHCORE_LIB_NAME "MathCore")
set(GRAPHICS_LIB_NAME "Graphics")
set(RENDERER_LIB_NAME "Renderer")
set(RESOURCE_LIB_NAME "Resource")
set(RESOURCESERVICE_LIB_NAME "ResourceService")
set(FILESYSTEM_LIB_NAME "FileSystem")
set(RTSHADERSYSTEM_LIB_NAME "RTShaderSystem")
set(APPLICATION_LIB_NAME "Application")
set(DRAWDRV_LIB_NAME "DrawDrv")
set(DRAWDRV9_LIB_NAME "DrawDrv9")
set(DRAWDRV11_LIB_NAME "DrawDrv11")

set(APP_LINK_TYPE SHARED)


#--------------- force setting --------------------------
# MESSAGE(STATUS "force set.")
# set(SHH_LINK_AS_DLL TRUE)
#--------------------------------------------------------

add_definitions(-D__PRINT_ALL_DEBUG_LOG__) # for debug engine logic.

add_definitions(-D_UNICODE)
add_definitions(-DUNICODE)

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/include/Core")

###################################################################
# global setting end
###################################################################




#####################################################################
# add subdirectory
#####################################################################
add_subdirectory(source)

add_subdirectory(include)

add_subdirectory(demos)

add_subdirectory(CMake)
