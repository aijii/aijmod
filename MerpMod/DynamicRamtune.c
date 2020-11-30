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

#include "EcuHacks.h"

#if DYN_RAMTUNING

void Pull2DFloatDynRamHook(TwoDTable* table) ROMCODE;
void Pull2DFloatDynRamHook(TwoDTable* table){

    //push x index (in r6) to stack
    __asm__(
        "mov.l r6, @-r15\n\t"
    );

    TableDefRAM *header = &(pRamVariables.RAMTableHeaders[_MAX_RAM_TABLES_ - 1]);
    while(header >= pRamVariables.RAMTableHeaders){
        if(
            //check if a RAMTable for the given table has been allocated
            table->tableCells == (long *) header->romaddress

            //if so, check if allocated table is valid
            && (header->ramaddress & 0xFFFF0000)
        ){
            //swap address in r1 with RAM table address
            unsigned long addr= (
                (unsigned long) &(pRamVariables.RAMTableArrayMarker)
                + (unsigned short) header->ramaddress
            );
            asm("mov %0, r1"::"r"(addr));
            //short-circuit loop
            goto exit;
        }
        else
        {
            header -= 1;
        }
    }

    //put original ROM table address into r1 if no RAM table allocated
    asm("mov %0, r1"::"r"(table->tableCells));

    //Put datatype into r0 before returning back into original function
    //and restore x index into r6 from stack
    exit:
    __asm__(
        "mov.l @r15+, r6\n\t"
        "mov.b @(0x2,r4), r0\n\t"
        "extu.b  r0, r3\n\t"
    );
}

#endif