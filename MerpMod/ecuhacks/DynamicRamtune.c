/*
    Copyright (C) 2020 Shamit Som shamitsom@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

/*
    NOTE:
    This file is used to define the data section of the assembly source
    file `DynamicRamtunePatch.s`. This file must be excluded from the build
    and compiled to assembly code with no debug information MANUALLY before
    building the rest of the project.

    In order to get the dynamic addresses for the RAM table headers as usable
    symbols in pure assembly code, they need to be determined in C as it is
    below, compiled with no debug information, and the resulting assembly file
    is then included in the assembly source file. Because it is included in
    the assembly source file, the compiled assembly from this file cannot
    be linked because that will result in multiply defined symbols.

    This is because there is no way (as far as I could tell...) to
    exclude HEW from linking the resulting assembly file unless it's excluded
    from the project, short of using custom makefiles.

    It is true that the assembly could be written with inline assembly in this
    file and then compiled, but it seems prudent  to avoid the extra overhead
    of the function call when using inline assembly in C. The extra cycles may
    not be a huge deal, but better to be safe when hacking time-critical
    systems...
*/

#include "EcuHacks.h"

#if DYN_RAMTUNING

unsigned long *pROMtoRAMArrayOffs ROMCODE_DATA = &(pRamVariables.ROMtoRAMArrayOffset);
unsigned long *pMaxRAMTables ROMCODE_DATA = &(pRamVariables.MaxDynRAMTables);

#endif