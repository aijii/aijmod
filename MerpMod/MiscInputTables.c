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

#if SWITCH_HACKS

//unsigned char WideBandLambdaInputMode SWITCHDATA = WideBandLambdaInputModeUndefined;
unsigned char WideBandLambdaInputMode SWITCHDATA = 3;
float WidebandSensorSmoothingFactor SWITCHDATA = 1.0f;
unsigned short LeanBoostDelay SWITCHDATA = 25;
float LeanBoostAFRThreshold SWITCHDATA = 0.85f;
float LeanBoostMRPThreshold SWITCHDATA = 220.0;

unsigned char FuelPressureInputMode SWITCHDATA = FuelPressureInputModeUndefined;
float FuelPressureSensorSmoothingFactor SWITCHDATA = 1.0f;
float BaseFuelPressure SWITCHDATA = 2250;
unsigned short FuelPressureDeltaDelay SWITCHDATA = 25;
float FuelPressureDeltaThreshold SWITCHDATA = 700;
float FuelPressureTriggerMinRPM SWITCHDATA = 3000.0f;

unsigned char UseInjectorLatency SWITCHDATA = 0x01;

unsigned char DefaultAVCSLookupMAPLoad SWITCHDATA = 0x00;

float WIDEBAND_SCALING_ROWS[11] SWITCHDATA =
{0,0.5,1,1.5,2,2.5,3,3.5,4,4.5,5};

short WIDEBAND_SCALING_DATA[11] SWITCHDATA =
{9634,9634,9634,9634,9634,9634,9634,9634,9634,9634,9634};

TwoDTable WideBandScaling  SWITCHDATA = {
	.columnCount = 11,
	.tableType = UInt16Table2D,
	.columnHeaderArray = WIDEBAND_SCALING_ROWS,
	.tableCells = WIDEBAND_SCALING_DATA,
	.multiplier = 0.00152590218966964217593652246891f,	//todo unit test these
	.offset = 0.0 };
//! 1/65535  (0-1.00 range, 16bit precision)


float FUELPRESSURE_SCALING_ROWS[11] SWITCHDATA =
{0,0.5,1,1.5,2,2.5,3,3.5,4,4.5,5};

short FUELPRESSURE_SCALING_DATA[11] SWITCHDATA =
{2250,2250,2250,2250,2250,2250,2250,2250,2250,2250,2250};

TwoDTable FuelPressureScaling  SWITCHDATA = {
	.columnCount = 11,
	.tableType = UInt16Table2D,
	.columnHeaderArray = FUELPRESSURE_SCALING_ROWS,
	.tableCells = FUELPRESSURE_SCALING_DATA,
	.multiplier = 1.0f,	//todo unit test these
	.offset = 0.0 };
//! 1/65535  (0-1.00 range, 16bit precision)



#endif