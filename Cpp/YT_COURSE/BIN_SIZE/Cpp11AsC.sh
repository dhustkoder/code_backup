g++ Cpp11AsC.cpp -o Cpp11AsC.exe -Os -std=c++11 -pedantic-errors -Wall -Wextra -fno-exceptions -fno-rtti \
	-s  -Wl,--gc-sections -ffunction-sections -fdata-sections \
	-fno-stack-protector -fomit-frame-pointer -fno-unwind-tables -fno-asynchronous-unwind-tables \
	-nodefaultlibs -lc
