:: set PATH=%PATH%;C:\mingw32\bin;
set PATH=%PATH%;C:\i686-7.2.0-release-posix-dwarf-rt_v5-rev1\mingw32\bin;
::gcc -std=c99 -DCIMGUI_DEFINE_ENUMS_AND_STRUCTS cimgui.h
::gcc  -DCIMGUI_DEFINE_ENUMS_AND_STRUCTS cimgui.h
gcc  -std=c99 -Wall -Wpedantic -DCIMGUI_DEFINE_ENUMS_AND_STRUCTS cimguitest.c
cmd /k