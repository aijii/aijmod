@ECHO OFF

set TARGETROM=%1
set BUILDCONFIG=%2
set MMVERSION=%3

REM Use map file to generate/update ECU header file and linker script file
..\SharpTune.exe ecumaptool ".\Targets\idatohew.xml" ".\Targets\%TARGETROM%\%TARGETROM%.map" ".\Targets\%TARGETROM%\%TARGETROM%.h" ".\Targets\%TARGETROM%\%TARGETROM%.txt" %TARGETROM% %BUILDCONFIG% %MMVERSION%

REM Copy a template config to the target ROM folder if necessary
IF NOT EXIST ".\Targets\%TARGETROM%\%TARGETROM%Config.h" (
    Copy ".\Targets\TemplateConfig.h" ".\Targets\%TARGETROM%\%TARGETROM%Config.h"
)