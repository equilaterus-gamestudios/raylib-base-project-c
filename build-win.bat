@echo off
mkdir "bin/win" 2>NUL
copy "C:\raylib\lib\raylib.dll" "bin/win" >NUL
gcc src/main.c -IC:\raylib\include -Lbuild/win -g -ggdb -lraylib -lgdi32 -lwinmm -lm -o build/win/main.exe -std=c99 -pedantic