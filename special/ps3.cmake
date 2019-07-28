# This Toolchain file is used to cross compile the ps3
# version of Hatari under linux using powerpc64-ps3
# Now it's used for frivolous shit:
# use : cd build; ccmake -DCMAKE_TOOLCHAIN_FILE=../special/ps3.cmake -DCMAKE_INSTALL_PREFIX=/opt/ps3dev/ppu -DCMAKE_MAKE_PROGRAM=/usr/bin/make ..
# TODO: fix this so CMAKE_MAKE_PROGRAM detects correctly

# this one is important
SET(CMAKE_SYSTEM_NAME Generic)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

SET(CMAKE_SYSTEM_PROCESSOR powerpc64)

SET(CMAKE_MAKE_PROGRAM /usr/bin/make)

SET(PS3DEV /opt/ps3dev)
SET(PSL1GHT ${PS3DEV})

# specify the cross compiler
SET(CMAKE_C_COMPILER powerpc64-ps3-elf-gcc)
SET(CMAKE_CXX_COMPILER powerpc64-ps3-elf-g++)
#SET(CMAKE_C_FLAGS "-mcpu=cell -I${PSL1GHT}/ppu/include -I${PS3DEV}/portlibs/ppu/include -DCLAB_PS3")
#SET(CMAKE_CXX_FLAGS "-mcpu=cell -I${PSL1GHT}/ppu/include -I${PS3DEV}/portlibs/ppu/include -DCLAB_PS3")
SET(SPECIAL_INCLUDES "-I${PSL1GHT}/ppu/include -I${PS3DEV}/portlibs/ppu/include")
SET(SPECIAL_DEFS "-DCLAB_PS3")
SET(SPECIAL_MCPU "-mcpu=cell")

# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH ${PS3DEV}/ppu ${PSL1GHT}/ppu ${PS3DEV}/portlibs/ppu )

# FindSDL.cmake doesn't search correctly in CMAKE_FIND_ROOT_PATH
# so we force SDLDIR here
#set ( ENV{SDLDIR} ${PS3DEV}/portlibs/ppu )

set(ENV{PKG_CONFIG_LIBDIR} "${PS3DEV}/ppu/lib/pkgconfig:${PS3DEV}/portlibs/ppu/lib/pkgconfig")


SET(ZLIB_INCLUDE_DIRS "${PS3DEV}/portlibs/ppu/include")
SET(ZLIB_LIBRARIES    "${PS3DEV}/portlibs/ppu/lib")

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
