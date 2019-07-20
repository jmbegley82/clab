cmake_minimum_required (VERSION 2.6)
project (Clab)
set (Clab_VERSION_MAJOR 0)
set (Clab_VERSION_MINOR 1)
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

#include_directories (src)
#find_package (PkgConfig REQUIRED)
#pkg_check_modules(SDL2 REQUIRED sdl2)
#pkg_check_modules(SDL2_image REQUIRED SDL2_image)
#pkg_check_modules(SDL2_mixer REQUIRED SDL2_mixer)
#pkg_check_modules(SDL2_ttf REQUIRED SDL2_ttf)

add_library(Clab SHARED src/Atom.cpp src/Clock.cpp src/Float.cpp src/Integer.cpp src/Node.cpp src/Notype.cpp src/ShadowInteger.cpp src/String.cpp src/StringStuff.cpp src/Time.cpp src/Types.cpp src/Clab.cpp)
set_target_properties(Clab PROPERTIES OUTPUT_NAME "${CMAKE_PROJECT_NAME}-${API_VERSION}")
set_target_properties(Clab PROPERTIES SOVERSION "${PACKAGE_VERSION}")
#target_link_libraries(clab ${SDL2_LIBRARIES} ${SDL2_image_LIBRARIES} ${SDL2_mixer_LIBRARIES} ${SDL2_ttf_LIBRARIES})
#target_include_directories(clab PUBLIC ${SDL2_INCLUDE_DIRS} ${SDL2_image_INCLUDE_DIRS} ${SDL2_mixer_INCLUDE_DIRS} ${SDL2_ttf_INCLUDE_DIRS})
#target_compile_options(clab PUBLIC ${SDL2_CFLAGS_OTHER} ${SDL2_image_CFLAGS_OTHER} ${SDL2_mixer_CFLAGS_OTHER} ${SDL2_ttf_CFLAGS_OTHER})

add_executable(clabtest EXCLUDE_FROM_ALL src/main.cpp)
target_link_libraries(clabtest Clab)

install(TARGETS Clab LIBRARY DESTINATION lib)
install(FILES ${PROJECT_BINARY_DIR}/src/Clab.h src/Atom.h src/Node.h src/Notype.h src/Integer.h src/Float.h src/String.h src/ShadowInteger.h src/Types.h src/Time.h src/Clock.h src/StringStuff.h DESTINATION include/Clab-${API_VERSION})
install(FILES "${PROJECT_BINARY_DIR}/Clab-${API_VERSION}.pc" DESTINATION lib/pkgconfig)

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "jmb")
set(CPACK_PACKAGING_INSTALL_PREFIX "/usr/local")
include(CPack)
