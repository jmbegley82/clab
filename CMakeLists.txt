cmake_minimum_required (VERSION 2.6)
project (Clab)
set (Clab_VERSION_MAJOR 0)
set (Clab_VERSION_MINOR 3)
set (DEST_DIR "${CMAKE_INSTALL_PREFIX}")
set (prefix "${DEST_DIR}")
set (exec_prefix "${prefix}")
set (libdir "${prefix}/lib")
set (PACKAGE_NAME "${CMAKE_PROJECT_NAME}")
set (PACKAGE_VERSION "${Clab_VERSION_MAJOR}.${Clab_VERSION_MINOR}")
set (API_VERSION "${Clab_VERSION_MAJOR}")
set (includedir "${prefix}/include")

configure_file(
	"${PROJECT_SOURCE_DIR}/src/config.h.in"
	"${PROJECT_BINARY_DIR}/src/config.h"
	)
configure_file(
	"${PROJECT_SOURCE_DIR}/Clab.pc.in"
	"${PROJECT_BINARY_DIR}/Clab-${API_VERSION}.pc"
	@ONLY
	)
configure_file(
	"${PROJECT_SOURCE_DIR}/src/Clab.h.in"
	"${PROJECT_BINARY_DIR}/src/Clab.h"
	@ONLY
	)
include_directories("${PROJECT_BINARY_DIR}/src")

#find_package (PkgConfig REQUIRED)

#TODO:  make this conditional upon detection of Windows platform!
#set(CLAB_PLATFORM_SPECIFIC "src/msvs_dirent.cpp")

add_library(Clab SHARED src/Atom.cpp src/Clock.cpp src/Float.cpp src/Integer.cpp src/Node.cpp src/Notype.cpp src/ShadowInteger.cpp src/String.cpp src/StringStuff.cpp src/Time.cpp src/Types.cpp src/FileOps.cpp ${CLAB_PLATFORM_SPECIFIC} src/Log.cpp src/Clab.cpp)
set_target_properties(Clab PROPERTIES OUTPUT_NAME "${CMAKE_PROJECT_NAME}-${API_VERSION}")
set_target_properties(Clab PROPERTIES SOVERSION "${PACKAGE_VERSION}")
target_compile_options(Clab PUBLIC ${SPECIAL_MCPU} ${SPECIAL_INCLUDES})
target_compile_definitions(Clab PUBLIC ${SPECIAL_DEFS})

add_executable(clabtest EXCLUDE_FROM_ALL src/main.cpp)
target_link_libraries(clabtest Clab)
target_compile_options(clabtest PUBLIC ${SPECIAL_MCPU} ${SPECIAL_INCLUDES})
target_compile_definitions(clabtest PUBLIC ${SPECIAL_DEFS})

install(TARGETS Clab
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib)
install(FILES ${PROJECT_BINARY_DIR}/src/Clab.h src/Atom.h src/Node.h src/Notype.h src/Integer.h src/Float.h src/String.h src/ShadowInteger.h src/Types.h src/Time.h src/Clock.h src/StringStuff.h src/Log.h
	DESTINATION include/Clab-${API_VERSION})
install(FILES "${PROJECT_BINARY_DIR}/Clab-${API_VERSION}.pc"
	DESTINATION lib/pkgconfig)

set(CPACK_PACKAGE_VERSION ${PACKAGE_VERSION})
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "jmb")
set(CPACK_PACKAGING_INSTALL_PREFIX "/usr/local")
include(CPack)
