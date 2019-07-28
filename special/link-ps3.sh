mv clabtest clabtest.elf
sprxlinker clabtest.elf
make_self clabtest.elf clabtest.self
fself.py clabtest.elf clabtest.fake.self
