gcc c99.c -o c99.exe -Os -std=c99 -pedantic-errors -Wall -Wextra -fno-exceptions -fno-rtti \
	-s  -Wl,--gc-sections -ffunction-sections -fdata-sections \
	-fno-stack-protector -fomit-frame-pointer -fno-unwind-tables -fno-asynchronous-unwind-tables \
	-nodefaultlibs -lc
