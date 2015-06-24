
set(SHH_PLATFROM_WIN32)

if(MSVC10)
	set(GENERAGER_NAME "Visual Studio 2010")
endif(MSVC10)

if(MSVC11)
	set(GENERAGER_NAME "Visual Studio 2012")
endif(MSVC11)

if(MSVC12)
	set(GENERAGER_NAME "Visual Studio 2013")
endif(MSVC12)

if(MSVC14)
	set(GENERAGER_NAME "Visual Studio 2015")
endif(MSVC14)

message(STATUS "Platfrom: Win32")
if(MSVC)
	message(STATUS "MSVC version: ${MSVC_VERSION}")
endif(MSVC)

if(GENERAGER_NAME)
	message(STATUS "Generager: ${GENERAGER_NAME}")
else(GENERAGER_NAME)
	message(STATUS "Unknown Generager.")
endif(GENERAGER_NAME)

if(MSVC10)
	include(FindDirectX11)
else()
	MESSAGE(STATUS "Use Windows SDK instead of DirectX11 SDK")
endif(MSVC10)

include(FindDirectX)


if (MSVC)
	# disable: "no suitable definition provided for explicit template instantiation request"
	# Occurs for no justifiable reason on all #includes of Singleton
	add_definitions(/wd4661)
	add_definitions(/DEBUG)
endif ()


#set postfix
set(CMAKE_DEBUG_POSTFIX "_d")

# let releae build typed generate debug information 
set( RELEASE_BUILD_TYPE_GENERATE_DEBUG_INFORMATION ON )

#Setting build type, make Debug Editor_debug build in debug mode
set_property( GLOBAL PROPERTY DEBUG_CONFIGURATIONS "Debug" )
 
###set the configuration types
if ( CMAKE_CONFIGURATION_TYPES )
	set( CMAKE_CONFIGURATION_TYPES Debug Release)
	set( CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING
	"Reset the configurations to what we need"
	FORCE )
endif( CMAKE_CONFIGURATION_TYPES )

##################################################################################
###multi thread
foreach( flag_var
		CMAKE_CXX_FLAGS
		CMAKE_CXX_FLAGS_DEBUG
		CMAKE_CXX_FLAGS_RELEASE
)

if( ${flag_var} MATCHES "/MD" )
	STRING( REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}" )
	#force update this on the CMAKE GUI
	set(${flag_var} "${${flag_var}}" CACHE STRING
	"Reset the configurations to what we need"
	FORCE )

endif( ${flag_var} MATCHES "/MD" )

if( ${flag_var} MATCHES "/MDd" )
	STRING( REGEX REPLACE "/MDd" "/MTd" ${flag_var} "${${flag_var}}" )
	#force update this on the CMAKE GUI
	set(${flag_var} "${${flag_var}}" CACHE STRING
	"Reset the configurations to what we need"
	FORCE )

endif( ${flag_var} MATCHES "/MDd" )

endforeach( flag_var )

### let release build type generate debug information
if ( ${RELEASE_BUILD_TYPE_GENERATE_DEBUG_INFORMATION} )

	foreach( flag_var
			CMAKE_CXX_FLAGS_RELEASE
	)

	if( NOT ${flag_var} MATCHES "/Zi" )
		
		set( ${flag_var} "${${flag_var}} /Zi" CACHE STRING 
		"Let release build type generate debug info"
		FORCE )
		
	endif( NOT ${flag_var} MATCHES "/Zi" )
	endforeach( flag_var )
	
endif ( ${RELEASE_BUILD_TYPE_GENERATE_DEBUG_INFORMATION} )

foreach( flag_var
		CMAKE_EXE_LINKER_FLAGS
		CMAKE_EXE_LINKER_FLAGS_DEBUG
		CMAKE_EXE_LINKER_FLAGS_RELEASE
		
		CMAKE_SHARED_LINKER_FLAGS
		CMAKE_SHARED_LINKER_FLAGS_DEBUG
		CMAKE_SHARED_LINKER_FLAGS_RELEASE
)

if( NOT ${flag_var} MATCHES "/DEBUG" )	
	#force update this on the CMAKE GUI
	set( ${flag_var} "${${flag_var}} /DEBUG" CACHE STRING "" FORCE)	
endif( NOT ${flag_var} MATCHES "/DEBUG" )
endforeach( flag_var )



#Organize projects into folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

