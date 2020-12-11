@echo off
set TARGETROM=%1

if not exist build\%TARGETROM%\work mkdir build\%TARGETROM%\work
if not exist TestRom mkdir TestRom
