@echo off

set TCDIR=%cd%
set FILEPATH=%1
set FILENAME=%2
set FILEDIR=%3
set PROJDIR=%4
set CONFIGNAME=%5

REM set environment
set TARGET_LIB=%TCDIR%\Sh-elf\sh-elf\lib
set PATH=%TCDIR%\Sh-elf\bin;%TCDIR%\sh-elf\sh-elf\bin;%TCDIR%\sh-elf\libexec\gcc\sh-elf\4.7-GNUSH_v13.01;C:\Windows\System32
set TARGET_M2_LIB=%TCDIR%\Sh-elf\sh-elf\lib\m2
set TEMPDIR=%TEMPDIR%
set LIB_TARGET_INCLUDE=%TCDIR%\Sh-elf\lib\gcc\sh-elf\4.7-GNUSH_v13.01\include
set TARGET_INCLUDE=%TCDIR%\Sh-elf\sh-elf\include
set LIB_M2_LIB=%TCDIR%\Sh-elf\lib\gcc\sh-elf\4.7-GNUSH_v13.01\m2
set INCLUDE=%TCDIR%\Sh-elf\include

set BUILDDIR=%PROJDIR%\build\%CONFIGNAME%\work

@REM REM Debug environment
@REM echo %TCDIR% >> %BUILDDIR%\compile.log
@REM echo %TARGETROM% >> %BUILDDIR%\compile.log
@REM echo %PROJNAME% >> %BUILDDIR%\compile.log
@REM echo %CONFIGNAME% >> %BUILDDIR%\compile.log
@REM echo %TEMPDIR% >> %BUILDDIR%\compile.log
@REM echo %PROJDIR% >> %BUILDDIR%\compile.log
@REM echo %WORKSPDIR% >> %BUILDDIR%\compile.log

REM check for a custom flags file for the current file and use those
if exist %FILEDIR%\%FILENAME%.flags (
    set /P FLAGS=<%FILEDIR%\%FILENAME%.flags
) ELSE (
REM use default flags
    set FLAGS=^
    -Wall ^
    -c ^
    -x c ^
    -m2e ^
    -mrenesas ^
    -mieee ^
    -I "%TCDIR%\sh-elf\sh-elf\optlibinc" ^
    -I "%TCDIR%\sh-elf\lib\gcc\sh-elf\4.7-GNUSH_v13.01\optlibinc" ^
    -I "%PROJDIR%\include" ^
    -I "%PROJDIR%\Targets\%CONFIGNAME%" ^
    -D _TARGET_HEADER_=%CONFIGNAME%.h ^
    -D _TARGET_CONFIG_=%CONFIGNAME%Config.h ^
    -nostdinc ^
    -g ^
    -g2 ^
    -o ^
    "%BUILDDIR%\%FILENAME%.o"
)

REM use CALL here to force expansion of %FLAGS% when read in from input file
CALL sh-elf-gcc %FLAGS% %FILEPATH%
