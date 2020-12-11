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

//Tests for Dynamic RAM Tuning
#include "EcuHacks.h"

#if DYN_RAMTUNING

// float (*Pull2DHooked)(TwoDTable *table, float xval) = (float(*)(TwoDTable*, float)) sPull2DFloat;

//this test assumes the patched ROM is downloaded into HEW first, followed by the
//MerpMod.x file immediately after
void Pull2DFloatUnitTests() __attribute__ ((section ("Misc")));
void Pull2DFloatUnitTests()
{
    ClearRam();
    PopulateRamVariables();

    short i;

    //Verify Pull2DFloat with 4-byte values directly from ROM (Front O2 Scaling Table)
    TwoDTable *FrontO2Scaling = (TwoDTable*) tFrontO2Scaling;
    short numCells = FrontO2Scaling->columnCount;
    float *FrontO2_X = FrontO2Scaling->columnHeaderArray;
    float *FrontO2_Y_ROM = (float*) FrontO2Scaling->tableCells;

    //arbitrary tables to populate in RAM, generated with different values
    //calculated from the original ROM tables
    float FrontO2_Y_RAM_1[numCells];
    float FrontO2_Y_RAM_2[numCells];
    for(i = 0; i < numCells; i++){
        FrontO2_Y_RAM_1[i] = FrontO2_Y_ROM[i]*2.0;
        FrontO2_Y_RAM_2[i] = FrontO2_Y_ROM[i]*0.5;
    }

    //Check that Pull2D pulls from regular ROM table when no RAM table defined
    for(i = 0; i < numCells; i++){
        Assert(
            AreCloseEnough(Pull2DHooked(FrontO2Scaling, FrontO2_X[i]), FrontO2_Y_ROM[i]),
            "Pull2DHooked: Incorrect value, 4-byte table, ROM Table"
        );
    }

    //allocate a corresponding table in RAM with arbitrary values
    float *test4ByteTable = (float*) &(pRamVariables.RAMTableArrayMarker);
    for(i = 0; i < numCells; i++){
        test4ByteTable[i] = FrontO2_Y_RAM_1[i];
    }

    //create an INVALID header for the allocated RAM table
    //
    //ROM table is indexed increasing from base (0th element is _first_ in array)
    //RAM table is addressed decreasing from end (0th element is _last_ in array)
    //
    //RAM table entry looks like 0xLLLLOOOO where "OOOO" is the lower 2 bytes
    //of the table's base address, "LLLL" are flags. The RAM table is considered
    //valid when the most-significant byte is set equal to 0xFF. Both upper
    //bytes can be used by a connected PC for any desired flags when table is
    //invalid, however since the ECU only checks the MSB for validity, it must
    //be ensured that the lower byte is set to 0xFF ONLY if ALL of the upper flag
    //bytes are also set to 0xFF, otherwise an undefined address will be used to
    //pull data from, which is obviously not good.
    //
    //When valid, the full dword is just the RAM address to be used. This makes
    //for a very efficient way for the ECU to check table validity without wasting
    //precious ECU cycles, and it makes the organization of the dynamic RAM tables
    //nearly trivial.
    pRamVariables.RAMTableHeaderROMAddr[0] = (long) FrontO2_Y_ROM;
    pRamVariables.RAMTableHeaderRAMAddr[_MAX_RAM_TABLES_ - 1] = (long) test4ByteTable & 0xAAAAFFFF; //arbitrary, non-valid flag bytes

    //ensure values still pulled from ROM with the invalid table header
    for(i = 0; i < numCells; i++){
        Assert(
            AreCloseEnough(Pull2DHooked(FrontO2Scaling, FrontO2_X[i]), FrontO2_Y_ROM[i]),
            "Pull2DHooked: Incorrect value, 4-byte table, Invalid RAM table at 0th header"
        );
    }

    //mark table as valid, ensure values now pulled from RAM
    pRamVariables.RAMTableHeaderRAMAddr[_MAX_RAM_TABLES_ - 1] |= 0xFFFF0000;
    for(i = 0; i < numCells; i++){
        Assert(
            AreCloseEnough(Pull2DHooked(FrontO2Scaling, FrontO2_X[i]), FrontO2_Y_RAM_1[i]),
            "Pull2DHooked: Incorrect value, 4-byte table, RAM Table at 0th header"
        );
    }

    //check final header case
    test4ByteTable += numCells; //move to next free spot in RAM
    for(i = 0; i < numCells; i++){
        test4ByteTable[i] = FrontO2_Y_RAM_2[i];
    }
    //clear original header
    pRamVariables.RAMTableHeaderROMAddr[0] = DefaultRAMTableRomAddr;
    pRamVariables.RAMTableHeaderRAMAddr[_MAX_RAM_TABLES_ - 1] = DefaultRAMTableRamAddr;

    //create new header
    pRamVariables.RAMTableHeaderROMAddr[_MAX_RAM_TABLES_ - 1] = (long) FrontO2_Y_ROM;
    pRamVariables.RAMTableHeaderRAMAddr[0] = (long) test4ByteTable; //initialized valid
    for(i = 0; i < numCells; i++){
        Assert(
            AreCloseEnough(Pull2DHooked(FrontO2Scaling, FrontO2_X[i]), FrontO2_Y_RAM_2[i]),
            "Pull2DHooked: Incorrect value, 4-byte table, RAM Table at last header"
        );
    }

    asm("nop"); //breakpoint handle
}

#endif
