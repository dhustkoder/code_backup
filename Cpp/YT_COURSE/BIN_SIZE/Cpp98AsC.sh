g++ Cpp98AsC.cpp -o Cpp98AsC.exe -Os -std=c++98 -pedantic-errors -Wall -Wextra -fno-exceptions -fno-rtti \
	-s  -Wl,--gc-sections -ffunction-sections -fdata-sections \
	-fno-stack-protector -fomit-frame-pointer -fno-unwind-tables -fno-asynchronous-unwind-tables \
	-nodefaultlibs -lc
