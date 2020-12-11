@echo off

set TCDIR=%cd%
set PROJDIR=%1%
set CONFIGNAME=%2%
set PROJNAME=%3%

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
@REM echo %TCDIR% >> %BUILDDIR%\libgen.log
@REM echo %TARGETROM% >> %BUILDDIR%\libgen.log
@REM echo %PROJNAME% >> %BUILDDIR%\libgen.log
@REM echo %CONFIGNAME% >> %BUILDDIR%\libgen.log
@REM echo %TEMPDIR% >> %BUILDDIR%\libgen.log
@REM echo %PROJDIR% >> %BUILDDIR%\libgen.log
@REM echo %WORKSPDIR% >> %BUILDDIR%\libgen.log

set FLAGS=^
--compiler-options=-m2e,-mrenesas,-mieee,-Os,-fdata-sections,-ffunction-sections,-falign-jumps,-fno-function-cse,-funit-at-a-time ^
    --output="%BUILDDIR%\lib%PROJNAME%.a" ^
    --select-lib=optlib ^
    --header-files=math

sh-elf-libgen-wrapper %FLAGS%
