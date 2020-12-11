@echo off

set "TCDIR=%cd%"
set PROJDIR=%1
set CONFIGNAME=%2
set PROJNAME=%3

REM set environment
set TARGET_LIB=%TCDIR%\Sh-elf\sh-elf\lib
set PATH=%TCDIR%\Sh-elf\bin;%TCDIR%\sh-elf\sh-elf\bin;%TCDIR%\sh-elf\libexec\gcc\sh-elf\4.7-GNUSH_v13.01;C:\Windows\System32
set TARGET_M2_LIB=%TCDIR%\Sh-elf\sh-elf\lib\m2
set TEMPDIR=%TEMPDIR%
set LIB_TARGET_INCLUDE=%TCDIR%\Sh-elf\lib\gcc\sh-elf\4.7-GNUSH_v13.01\include
set TARGET_INCLUDE=%TCDIR%\Sh-elf\sh-elf\include
set LIB_M2_LIB=%TCDIR%\Sh-elf\lib\gcc\sh-elf\4.7-GNUSH_v13.01\m2
set INCLUDE=%TCDIR%\Sh-elf\include

set BUILDDIR=%PROJDIR%\build\%CONFIGNAME%

@REM REM Debug environment
@REM echo %TCDIR% >> %BUILDDIR%\link.log
@REM echo %TARGETROM% >> %BUILDDIR%\link.log
@REM echo %PROJNAME% >> %BUILDDIR%\link.log
@REM echo %CONFIGNAME% >> %BUILDDIR%\link.log
@REM echo %TEMPDIR% >> %BUILDDIR%\link.log
@REM echo %PROJDIR% >> %BUILDDIR%\link.log
@REM echo %WORKSPDIR% >> %BUILDDIR%\link.log

set FLAGS=^
-L ".\sh-elf\lib\gcc\sh-elf\4.7-GNUSH_v13.01\mrenesas\m2e" ^
-L "%BUILDDIR%\work" ^
-renesas ^
--start-group ^
-l "%PROJNAME%" ^
-l "gcc-Os-4-200" ^
-l "gcc" ^
--end-group ^
-e _ResetHandler ^
-T "%PROJDIR%\include\LinkerScript.txt" ^
-T "%PROJDIR%\Targets\%CONFIGNAME%\%CONFIGNAME%.txt"

sh-elf-ld-wrapper "%BUILDDIR%\work\*.o" %FLAGS% -o "%BUILDDIR%\%PROJNAME%.x"
sh-elf-ld-wrapper "%BUILDDIR%\work\*.o" %FLAGS% --oformat srec -o "%BUILDDIR%\%PROJNAME%.mot"

if exist "%PROJDIR%\%CONFIGNAME%" rmdir /S /Q "%PROJDIR%\%CONFIGNAME%"