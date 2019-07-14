/*
	Copyright (C) 2012-2013 Merrill A. Myers III merrillamyersiii@gmail.com
	
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


#if RAMTUNE_AUTOCOPY
// These Variables define where the autopopulate function 
// sources table data from for blendable/switchable tables
unsigned char DefaultRamTuneTableBlend RAMTUNEDATA = 1; //Todo, create RAMTABLEDATA section
unsigned char DefaultRamTuneTableSwitch RAMTUNEDATA = 1;

#endif

#if AVCS_RAMTUNING

ThreeDTable AVCSRamTable RAMTUNEDATA = {
	.columnCount = 18,
	.rowCount = 19,
	.tableType = UInt16Table3D,
	.columnHeaderArray = tIntakeAVCSNonCruiseCols,
	.rowHeaderArray = tIntakeAVCSNonCruiseRows,
	.tableCells = &(pRamVariables.AVCSRamData),
	.multiplier = 0.0054931641f,	//todo unit test these
	.offset = 0.0 };


#endif

#if MAF_RAMTUNING

#endif

#if TIPIN_RAMTUNING

#endif


