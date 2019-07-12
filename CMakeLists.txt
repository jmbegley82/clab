cmake_minimum_required (VERSION 2.6)
project (CLab)
set (CLab_VERSION_MAJOR 0)
set (CLab_VERSION_MINOR 1)

configure_file(
	"${PROJECT_SOURCE_DIR}/src/config.h.in"
	"${PROJECT_SOURCE_DIR}/src/config.h"
	)
include_directories("${PROJECT_BINARY_DIR}")

#include_directories (src)
find_package (PkgConfig REQUIRED)
#pkg_check_modules(RTMIDI REQUIRED rtmidi)
#pkg_check_modules(EVDEV REQUIRED libevdev)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_image REQUIRED SDL2_image)
pkg_check_modules(SDL2_mixer REQUIRED SDL2_mixer)
pkg_check_modules(SDL2_ttf REQUIRED SDL2_ttf)

add_library(clab SHARED src/Atom.cpp src/Clock.cpp src/Float.cpp src/Integer.cpp src/Manager.cpp src/Node.cpp src/Notype.cpp src/ShadowInteger.cpp src/String.cpp src/StringStuff.cpp src/Time.cpp src/Video.cpp)
target_link_libraries(clab ${SDL2_LIBRARIES} ${SDL2_image_LIBRARIES} ${SDL2_mixer_LIBRARIES} ${SDL2_ttf_LIBRARIES})
target_include_directories(clab PUBLIC ${SDL2_INCLUDE_DIRS} ${SDL2_image_INCLUDE_DIRS} ${SDL2_mixer_INCLUDE_DIRS} ${SDL2_ttf_INCLUDE_DIRS})
target_compile_options(clab PUBLIC ${SDL2_CFLAGS_OTHER} ${SDL2_image_CFLAGS_OTHER} ${SDL2_mixer_CFLAGS_OTHER} ${SDL2_ttf_CFLAGS_OTHER})

add_executable(clabtest EXCLUDE_FROM_ALL src/main.cpp)
target_link_libraries(clabtest clab)

#add_executable (brometheus src/Brometheus.cpp src/main.cpp)
#target_link_libraries(brometheus JMB ${RTMIDI_LIBRARIES} ${EVDEV_LIBRARIES})
#target_include_directories(brometheus PUBLIC ${RTMIDI_INCLUDE_DIRS} ${EVDEV_INCLUDE_DIRS})
#target_compile_options(brometheus PUBLIC ${RTMIDI_CFLAGS_OTHER} ${EVDEV_CFLAGS_OTHER})
