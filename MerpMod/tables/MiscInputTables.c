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

unsigned char WideBandLambdaInputMode SWITCHDATA = WideBandLambdaInputModeUndefined;
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

unsigned char OilPressureInputMode SWITCHDATA = OilPressureInputModeUndefined;
float OilPressureSensorSmoothingFactor SWITCHDATA = 1.0f;
float OilPressureThreshold SWITCHDATA = 700;
float OilPressureTriggerMinRPM SWITCHDATA = 3000.0f;

unsigned char OilTemperatureInputMode SWITCHDATA = OilTemperatureInputModeUndefined;
float OilTemperatureSensorSmoothingFactor SWITCHDATA = 1.0f;
float OilTemperatureThreshold SWITCHDATA = 700;
float OilTemperatureTriggerMinRPM SWITCHDATA = 3000.0f;

#if OILPRESSURE_HACKS
unsigned short OilPressureDelay SWITCHDATA = 0;
unsigned short OilTemperatureDelay SWITCHDATA = 0;
#endif
#if OILTEMP_HACKS
unsigned char OilPressureFailSafeValetModeEnable SWITCHDATA = 0; 
unsigned char OilTemperatureFailSafeValetModeEnable SWITCHDATA = 0; 
#endif

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

#if OILPRESSURE_HACKS
float OILPRESSURE_SCALING_ROWS[11] SWITCHDATA =
{0,0.5,1,1.5,2,2.5,3,3.5,4,4.5,5};

short OILPRESSURE_SCALING_DATA[11] SWITCHDATA =
{2250,2250,2250,2250,2250,2250,2250,2250,2250,2250,2250};

TwoDTable OilPressureScaling  SWITCHDATA = {
	.columnCount = 11,
	.tableType = UInt16Table2D,
	.columnHeaderArray = OILPRESSURE_SCALING_ROWS,
	.tableCells = OILPRESSURE_SCALING_DATA,
	.multiplier = 1.0f,	//todo unit test these
	.offset = 0.0 };
//! 1/65535  (0-1.00 range, 16bit precision)
#endif
#if OILTEMP_HACKS
float OILTEMPERATURE_SCALING_ROWS[11] SWITCHDATA =
{0,0.5,1,1.5,2,2.5,3,3.5,4,4.5,5};

float OILTEMPERATURE_SCALING_DATA[11] SWITCHDATA =
{-40,-22,-4,14,34,54,74,92,104,122,140,158};

TwoDTable OilTemperatureScaling  SWITCHDATA = {
	.columnCount = 11,
	.tableType = FloatTable2D,
	.columnHeaderArray = OILTEMPERATURE_SCALING_ROWS,
	.tableCells = OILTEMPERATURE_SCALING_DATA,
	.multiplier = 1.0f,	//todo unit test these
	.offset = 0.0 };
//! 1/65535  (0-1.00 range, 16bit precision)
#endif
#endif
