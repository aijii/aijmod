@echo off
set TARGETROM=%1
set BUILDCONFIG=%2
set PROJNAME=%3

if not exist ".\%TARGETROM%\%BUILDCONFIG%" mkdir ".\%TARGETROM%\%BUILDCONFIG%"

for %%P in (".\*.patch") do del %%P
copy "..\build\%TARGETROM%\%PROJNAME%.mot" ".\%TARGETROM%\%BUILDCONFIG%\partial-patch.mot"
Copy "..\..\..\SubaruRoms\OEM\%TARGETROM%.bin" ".\%TARGETROM%\%BUILDCONFIG%\patched.bin"
..\..\SharpTune.exe rommod hewbuild ".\%TARGETROM%\%BUILDCONFIG%\partial-patch.mot" ".\%TARGETROM%\%BUILDCONFIG%\patched.bin" %BUILDCONFIG%

move oem.bin .\%TARGETROM%\%BUILDCONFIG%\
move reverted.bin .\%TARGETROM%\%BUILDCONFIG%\
move *.patch .\%TARGETROM%\%BUILDCONFIG%\
rmdir /s /q %BUILDCONFIG%
