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

#if AUXOUT_HACKS

ThreeDTable ExhaustCutoutTable1i  SWITCHDATA;
ThreeDTable ExhaustCutoutTable1s  SWITCHDATA;
ThreeDTable ExhaustCutoutTable1ss  SWITCHDATA;

TableSubSet ExhaustCutoutTableSet SWITCHDATA =
	{&ExhaustCutoutTable1i,
	&ExhaustCutoutTable1s,
	&ExhaustCutoutTable1ss};
	
float EC_COLS[]  SWITCHDATA = 
{100,200,300,400,500,600,700,800,900,1000,1100,1200};

float EC_ROWS[]  SWITCHDATA = 
{500,1200,2000,2800,3600,4200,4600,5000,5400,5800,6400,7200};

unsigned char ECi_DATA[]  SWITCHDATA = 
{
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100
};

unsigned char ECs_DATA[]  SWITCHDATA = 
{
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100
};

unsigned char ECss_DATA[] SWITCHDATA = 
{
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100,
100,100,100,100,100,100,100,100,100,100,100,100
};

ThreeDTable ExhaustCutoutTable1i  SWITCHDATA = {
	.columnCount = 12,
	.rowCount = 12,
	.columnHeaderArray = EC_COLS,
	.rowHeaderArray = EC_ROWS,
	.tableCells = ECi_DATA,
	.tableType = UInt8Table3D,
	.multiplier = 1.0f,
	.offset = 0 };
	
ThreeDTable ExhaustCutoutTable1s  SWITCHDATA = {
	.columnCount = 12,
	.rowCount = 12,
	.columnHeaderArray = EC_COLS,
	.rowHeaderArray = EC_ROWS,
	.tableCells = ECs_DATA,
	.tableType = UInt8Table3D,
	.multiplier = 1.0f,
	.offset = 0 };
	
ThreeDTable ExhaustCutoutTable1ss  SWITCHDATA = {
	.columnCount = 12,
	.rowCount = 12,
	.columnHeaderArray = EC_COLS,
	.rowHeaderArray = EC_ROWS,
	.tableCells = ECss_DATA,
	.tableType = UInt8Table3D,
	.multiplier = 1.0f,
	.offset = 0 };

#endif