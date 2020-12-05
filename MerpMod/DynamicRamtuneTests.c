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

//the test below assumes:
// - the `MerpMod.x` patch file is downloaded into HEW first,
// - the patched ROM is downloaded immediately after
// - the PC is manually set to the first line of the function manually

void Pull2DFloatTests() __attribute__ ((section ("Misc")));
void Pull3DFloatTests() __attribute__ ((section ("Misc")));

//-----------------------------------------------------------------------------
//  Check Pull2DFloat
//-----------------------------------------------------------------------------
void Pull2DFloatTests()
{
    ClearRam();
    PopulateRamVariables();

    int i;
    float returned = 0.0f;
    float expected = 0.0f;

    TwoDTable *table;
    int tableType;
    short numCols;
    short numRows;
    float *TableCols;
    float *TableRows;
    float mult;
    float offs;

    //uncomment the type of table you're checking
    //e.g. Base Timing is a 1-byte table, so uncomment the `char` table

    // char *Table_Y_ROM;
    // short *Table_Y_ROM;
    float *Table_Y_ROM;

    // unsigned char *testTable;
    // unsigned short *testTable;
    float *testTable;

    // unsigned char Table_Y_RAM_1[numCols];
    // unsigned char Table_Y_RAM_2[numCols];
    // unsigned short Table_Y_RAM_1[numCols];
    // unsigned short Table_Y_RAM_2[numCols];
    float Table_Y_RAM_1[numCols];
    float Table_Y_RAM_2[numCols];

    //Verify Pull2DFloat using values directly from ROM
    table = (TwoDTable*) tFrontO2Scaling;
    tableType = table->tableType;
    numCols = table->columnCount;
    TableCols = table->columnHeaderArray;
    Table_Y_ROM = (float*) table->tableCells;
    mult = table->multiplier;
    offs = table->offset;

    //arbitrary tables to populate in RAM, generated with different values
    //calculated from the original ROM tables
    for(i = 0; i < numCols; i++){
        Table_Y_RAM_1[i] = Table_Y_ROM[i]*2.0;
        Table_Y_RAM_2[i] = Table_Y_ROM[i]*0.5;
    }

    //Check that Pull2D pulls from regular ROM table when no RAM table defined
    for(i = 0; i < numCols; i++){
        returned = Pull2DHooked(table, TableCols[i]);
        expected = Table_Y_ROM[i];
        if(tableType){
            expected *= mult;
            expected += offs;
        }
        Assert(
            AreCloseEnough(returned, expected),
            "Pull2DHooked: Incorrect value, 4-byte table, ROM Table"
        );
    }

    //allocate a corresponding table in RAM with arbitrary values
    testTable = (float*) &(pRamVariables.RAMTableArrayMarker);
    for(i = 0; i < numCols; i++){
        testTable[i] = Table_Y_RAM_1[i];
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
    pRamVariables.RAMTableHeaderROMAddr[0] = (long) Table_Y_ROM;
    pRamVariables.RAMTableHeaderRAMAddr[_MAX_RAM_TABLES_ - 1] = (long) testTable & 0xAAAAFFFF; //arbitrary, non-valid flag bytes

    //ensure values still pulled from ROM with the invalid table header
    for(i = 0; i < numCols; i++){
        returned = Pull2DHooked(table, TableCols[i]);
        expected = Table_Y_ROM[i];
        if(tableType){
            expected *= mult;
            expected += offs;
        }
        Assert(
            AreCloseEnough(returned, expected),
            "Pull2DHooked: Incorrect value, 4-byte table, ROM Table (invalid RAM table header)"
        );
    }

    //mark table as valid, ensure values now pulled from RAM
    pRamVariables.RAMTableHeaderRAMAddr[_MAX_RAM_TABLES_ - 1] |= 0xFFFF0000;
    for(i = 0; i < numCols; i++){
        returned = Pull2DHooked(table, TableCols[i]);
        expected = Table_Y_RAM_1[i];
        if(tableType){
            expected *= mult;
            expected += offs;
        }
        Assert(
            AreCloseEnough(returned, expected),
            "Pull2DHooked: Incorrect value, 4-byte table, RAM Table (first header)"
        );
    }

    //check final header case
    testTable += numCols; //move to next free spot in RAM
    for(i = 0; i < numCols; i++){
        testTable[i] = Table_Y_RAM_2[i];
    }
    //clear original header
    pRamVariables.RAMTableHeaderROMAddr[0] = DefaultRAMTableRomAddr;
    pRamVariables.RAMTableHeaderRAMAddr[_MAX_RAM_TABLES_ - 1] = DefaultRAMTableRamAddr;

    //create new header
    pRamVariables.RAMTableHeaderROMAddr[_MAX_RAM_TABLES_ - 1] = (long) Table_Y_ROM;
    pRamVariables.RAMTableHeaderRAMAddr[0] = (long) testTable; //initialized valid
    for(i = 0; i < numCols; i++){
        returned = Pull2DHooked(table, TableCols[i]);
        expected = Table_Y_RAM_2[i];
        if(tableType){
            expected *= mult;
            expected += offs;
        }
        Assert(
            AreCloseEnough(returned, expected),
            "Pull2DHooked: Incorrect value, 4-byte table, RAM Table (last header)"
        );
    }

    asm("nop"); //breakpoint handle to check Pull2DFloat Patch
}

//-----------------------------------------------------------------------------
//  Check Pull3DFloat
//-----------------------------------------------------------------------------
void Pull3DFloatTests(){

    ClearRam();
    PopulateRamVariables();

    int i, j;
    float returned = 0.0f;
    float expected = 0.0f;

    ThreeDTable *table;
    int tableType;
    short numCols;
    short numRows;
    float *TableCols;
    float *TableRows;
    float mult;
    float offs;

    //uncomment the type of table you're checking
    //e.g. Base Timing is a 1-byte table, so uncomment the `char` table

    unsigned char *Table_Z_ROM;
    // unsigned short *Table_Z_ROM;
    // float *Table_Z_ROM;

    unsigned char *testTable;
    // unsigned short *testTable;
    // float *testTable;

    unsigned char Table_Z_RAM_1[numCols*numRows];
    unsigned char Table_Z_RAM_2[numCols*numRows];
    // unsigned short Table_Z_RAM_1[numCols*numRows];
    // unsigned short Table_Z_RAM_2[numCols*numRows];
    // float Table_Z_RAM_1[numCols*numRows];
    // float Table_Z_RAM_2[numCols*numRows];

    table = (ThreeDTable*) tBaseTimingPNonCruise;
    tableType = table->tableType;
    numCols = table->columnCount;
    numRows = table->rowCount;
    TableCols = table->columnHeaderArray;
    TableRows = table->rowHeaderArray;
    Table_Z_ROM = (char*) (table->tableCells);
    mult = table->multiplier;
    offs = table->offset;

    //arbitrary tables to populate in RAM, generated with different values
    //calculated from the original ROM tables
    for(i = 0; i < numRows; i++){
        for(j = 0; j < numCols; j++){
            if(tableType){
                Table_Z_RAM_1[i*numCols + j] = Table_Z_ROM[i*numCols + j] << 1;
                Table_Z_RAM_2[i*numCols + j] = Table_Z_ROM[i*numCols + j] << 2;
            }
            else{
                Table_Z_RAM_1[i*numCols + j] = Table_Z_ROM[i*numCols + j]*2.0;
                Table_Z_RAM_2[i*numCols + j] = Table_Z_ROM[i*numCols + j]*4.0;
            }
        }
    }

    //Check that Pull3D pulls from regular ROM table when no RAM table defined
    for(i = 0; i < numRows; i++){
        for(j = 0; j < numCols; j++){
            returned = Pull3DHooked(table, TableCols[j], TableRows[i]);
            expected = Table_Z_ROM[i*numCols + j];
            if(tableType){
                expected *= mult;
                expected += offs;
            }
            Assert(AreCloseEnough(returned, expected), "Pull3DHooked: Incorrect value, ROM Table");
        }
    }

    //allocate a corresponding table in RAM with arbitrary values
    testTable = (char*) &(pRamVariables.RAMTableArrayMarker);
    for(i = 0; i < numRows; i++){
        for(j = 0; j < numCols; j++){;
            testTable[i*numCols + j] = Table_Z_RAM_1[i*numCols + j];
        }
    }

    pRamVariables.RAMTableHeaderROMAddr[0] = (long) Table_Z_ROM;
    pRamVariables.RAMTableHeaderRAMAddr[_MAX_RAM_TABLES_ - 1] = (long) testTable & 0xAAAAFFFF; //arbitrary, non-valid flag bytes

    //ensure values still pulled from ROM with the invalid table header
    for(i = 0; i < numRows; i++){
        for(j = 0; j < numCols; j++){
            returned = Pull3DHooked(table, TableCols[j], TableRows[i]);
            expected = Table_Z_ROM[i*numCols + j];
            if(tableType){
                expected *= mult;
                expected += offs;
            }
            Assert(AreCloseEnough(returned, expected), "Pull3DHooked: Incorrect value, ROM Table (Invalid RAM Header)");
        }
    }

    //mark table as valid, ensure values now pulled from RAM
    pRamVariables.RAMTableHeaderRAMAddr[_MAX_RAM_TABLES_ - 1] |= 0xFFFF0000;
    for(i = 0; i < numRows; i++){
        for(j = 0; j < numCols; j++){
            returned = Pull3DHooked(table, TableCols[j], TableRows[i]);
            expected = Table_Z_RAM_1[i*numCols + j];
            if(tableType){
                expected *= mult;
                expected += offs;
            }
            Assert(AreCloseEnough(returned, expected), "Pull3DHooked: Incorrect value, RAM Table (first header)");
        }
    }

    //check final header case
    testTable += numCols*numRows; //move to next free spot in RAM
    for(i = 0; i < numRows; i++){
        for(j = 0; j < numCols; j++){
            testTable[i*numCols + j] = Table_Z_RAM_2[i*numCols + j];
        }
    }
    //clear original header
    pRamVariables.RAMTableHeaderROMAddr[0] = DefaultRAMTableRomAddr;
    pRamVariables.RAMTableHeaderRAMAddr[_MAX_RAM_TABLES_ - 1] = DefaultRAMTableRamAddr;

    //create new header
    pRamVariables.RAMTableHeaderROMAddr[_MAX_RAM_TABLES_ - 1] = (long) Table_Z_ROM;
    pRamVariables.RAMTableHeaderRAMAddr[0] = (long) testTable; //initialized valid
    for(i = 0; i < numRows; i++){
        for(j = 0; j < numCols; j++){
            returned = Pull3DHooked(table, TableCols[j], TableRows[i]);
            expected = Table_Z_RAM_2[i*numCols + j];
            if(tableType){
                expected *= mult;
                expected += offs;
            }
            Assert(AreCloseEnough(returned, expected), "Pull3DHooked: Incorrect value, RAM Table (last header)");
        }
    }

    asm("nop"); //breakpoint handle to check Pull3DFloat patch
}

#endif
