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

void Pull2DFloatUnitTests() __attribute__ ((section ("Misc")));
void Pull2DFloatUnitTests()
{
    ClearRam();
    PopulateRamVariables();

    int i;

    //Verify Pull2D with 4-byte values (Front O2 Scaling Table)

    //Populate the two arrays with values directly from your ROM's disassembly,
    //should be an easy copy-paste directly from IDA if you use float formatting
    //and arrays for your tables data in the disassembly
    float FrontO2_X[13] = {-1.3f,-0.86999995f,-0.47f,-0.13999999f, 0.0f, 0.099999994f, 0.23999999f, 0.38999999f, 0.52999997f, 0.63999999f, 0.73999995f, 0.73999995f, 0.73999995f};
    float FrontO2_Y[13] = {0.7586f, 0.82758617f, 0.89655167f, 0.96551722f, 1.0f, 1.0344827f, 1.1034483f, 1.1724137f, 1.2413793f, 1.3103448f, 1.3793103f, 1.3793103f, 1.3793103f};

    //arbitrary tables to populate in RAM (note the duplicated ending values,
    //which should correspond to any duplicated values in the X-axis in the ROM
    float FrontO2_YRAM[13] = {0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 1.0f, 1.0f};

    //Check that Pull2D works correctly from regular ROM tables
    for(i = 0; i < 13; i++){
        Assert(
            AreCloseEnough(
                Pull2DHooked((TwoDTable*) tFrontO2Scaling, FrontO2_X[i]), FrontO2_Y[i]),
                "Pull2DHooked: Incorrect value, 4-byte table, ROM Table"
        );
    }

    //allocate a corresponding table in RAM with some arbitrary values
    float *test4ByteTable = (float*) &(pRamVariables.RAMTableArrayMarker);
    for(i = 0; i < 13; i++){
        test4ByteTable[i] = FrontO2_YRAM[i];
    }

    //create an INVALID header for the allocated RAM table
    pRamVariables.RAMTableHeaders[0] = (TableDefRAM){
        .romaddress = (long) ((TwoDTable*) tFrontO2Scaling)->tableCells,
        .ramaddress = (long) test4ByteTable - (long) &(pRamVariables.RAMTableArrayMarker)
    };

    //ensure values still pulled from ROM with the invalid table header
    for(i = 0; i < 13; i++){
        Assert(
            AreCloseEnough(
                Pull2DHooked((TwoDTable*) tFrontO2Scaling, FrontO2_X[i]), FrontO2_Y[i]),
                "Pull2DHooked: Incorrect value, 4-byte table, Invalid RAM table"
        );
    }

    //mark table as valid, ensure values now pulled from RAM
    pRamVariables.RAMTableHeaders[0].ramaddress |= 0xFFFF0000;
    for(i = 0; i < 13; i++){
        Assert(
            AreCloseEnough(
                Pull2DHooked((TwoDTable*) tFrontO2Scaling, FrontO2_X[i]), FrontO2_YRAM[i]),
                "Pull2DHooked: Incorrect value, 4-byte table, RAM Table"
        );
    }
}
    
#endif
