CXX=ppu-c++

SOURCES="../src/Atom.cpp ../src/Clab.cpp ../src/Clock.cpp ../src/Float.cpp ../src/Integer.cpp ../src/Node.cpp ../src/Notype.cpp ../src/ShadowInteger.cpp ../src/String.cpp ../src/StringStuff.cpp ../src/Time.cpp ../src/Types.cpp ./ps3main.cpp"

${CXX} -I../src -I./src -I/opt/ps3dev/ppu/include -I/opt/ps3dev/portlibs/ppu/include -L/opt/ps3dev/ppu/lib -L/opt/ps3dev/portlibs/ppu/lib ${SOURCES} -llv2 -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -o clabtest.elf
ppu-strip clabtest.elf
sprxlinker clabtest.elf
make_self clabtest.elf clabtest.self
fself.py clabtest.elf clabtest.fake.self
