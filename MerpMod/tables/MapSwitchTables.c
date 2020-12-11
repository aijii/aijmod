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

unsigned char DefaultMapSwitch SWITCHDATA = MapSwitch1;
float DefaultMapBlendRatio SWITCHDATA = 0.0f;

float MapSwitchThresholdLo SWITCHDATA = 1.5f;
float MapSwitchThresholdHi SWITCHDATA = 3.5f;

float BlendInputMinimumVolts SWITCHDATA = 0.50f;
float BlendInputMaximumVolts SWITCHDATA = 4.50f;

unsigned char MapBlendFailSafe SWITCHDATA = FailToDefaultBlendRatio;
unsigned short MapBlendCount SWITCHDATA = 45;

float MapBlendSmoothingFactor SWITCHDATA = 0.05f;
float MapSwitchSmoothingFactor SWITCHDATA = 1.0f;
float MapBlendBoostContentLock SWITCHDATA = 760;

unsigned char DefaultMapBlendingInputMode SWITCHDATA = MapBlendingInputModeTGVLeft;
unsigned char DefaultMapSwitchingInputMode  SWITCHDATA = MapSwitchingInputModeSiDrive;

unsigned char OpenLoopFuelingBlendCurveSwitch SWITCHDATA = BlendCurve1;
unsigned char ClosedLoopFuelingBlendCurveSwitch SWITCHDATA = BlendCurve1;
unsigned char TimingBlendCurveSwitch SWITCHDATA = BlendCurve2;
unsigned char KnockControlBlendCurveSwitch SWITCHDATA = BlendCurve2;
unsigned char WastegateDutyBlendCurveSwitch SWITCHDATA = BlendCurve3;
unsigned char BoostBlendCurveSwitch SWITCHDATA = BlendCurve3;
unsigned char MassAirFlowScalingBlendCurveSwitch SWITCHDATA = BlendCurve4;
unsigned char SpeedDensityBlendCurveSwitch SWITCHDATA = BlendCurve4;

//TODO TEST pull2d function here!
/*
float INPUT1_SCALING_ROWS[11] SWITCHDATA =
{0,0.5,1,1.5,2,2.5,3,3.5,4,4.5,5};

short INPUT1_SCALING_DATA[11] SWITCHDATA =
{0,6554,13107,19661,26214,32768,39321,45875,52428,58982,65535};

TwoDTable TGVLeftScaling  SWITCHDATA = {
	.columnCount = 11,
	.tableType = UInt16Table2D,
	.columnHeaderArray = INPUT1_SCALING_ROWS,
	.tableCells = INPUT1_SCALING_DATA,
	.multiplier = 0.00001525902f,	//todo unit test these
	.offset = 0.0 };
//! 1/65535  (0-1.00 range, 16bit precision)

float INPUT2_SCALING_ROWS[11] SWITCHDATA =
{0,0.5,1,1.5,2,2.5,3,3.5,4,4.5,5};

short INPUT2_SCALING_DATA[11] SWITCHDATA =
{0,6554,13107,19661,26214,32768,39321,45875,52428,58982,65535};

TwoDTable TGVRightScaling  SWITCHDATA = {
	.columnCount = 11,
	.tableType = UInt16Table2D,//TODO: CHECK that these are consistent between 2d/3d tables!
	.columnHeaderArray = INPUT2_SCALING_ROWS,
	.tableCells = INPUT2_SCALING_DATA,
	.multiplier = 0.00001525902f,	//todo unit test these
	.offset = 0.0 };
//! 1/65535  (0-1.00 range, 16bit precision)
*/
float MAP_BLEND_SCALING_ROWS[11] SWITCHDATA =
{0,0.5,1,1.5,2,2.5,3,3.5,4,4.5,5};

short MAP_BLEND_SCALING_DATA[11] SWITCHDATA =
{0,6554,13107,19661,26214,32768,39321,45875,52428,58982,65535};

TwoDTable MapBlendScaling  SWITCHDATA = {
	.columnCount = 11,
	.tableType = UInt16Table2D,//TODO: CHECK that these are consistent between 2d/3d tables!
	.columnHeaderArray = MAP_BLEND_SCALING_ROWS,
	.tableCells = MAP_BLEND_SCALING_DATA,
	.multiplier = 0.00001525902f,	//todo unit test these
	.offset = 0.0 };
//! 1/65535  (0-1.00 range, 16bit precision)


float MAP_BLEND_CURVE_1_ROWS[11] SWITCHDATA =
{0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1};

short MAP_BLEND_CURVE_1_DATA[11] SWITCHDATA =
{0,6554,13107,19661,26214,32768,39321,45875,52428,58982,65535};

TwoDTable MapBlendCurve1  SWITCHDATA = {
	.columnCount = 11,
	.tableType = UInt16Table2D,//TODO: CHECK that these are consistent between 2d/3d tables!
	.columnHeaderArray = MAP_BLEND_CURVE_1_ROWS,
	.tableCells = MAP_BLEND_CURVE_1_DATA,
	.multiplier = 0.00001525902f,	//todo unit test these
	.offset = 0.0 };
//! 1/65535  (0-1.00 range, 16bit precision)

float MAP_BLEND_CURVE_2_ROWS[11] SWITCHDATA =
{0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1};

short MAP_BLEND_CURVE_2_DATA[11] SWITCHDATA =
{0,6554,13107,19661,26214,32768,39321,45875,52428,58982,65535};

TwoDTable MapBlendCurve2  SWITCHDATA = {
	.columnCount = 11,
	.tableType = UInt16Table2D,//TODO: CHECK that these are consistent between 2d/3d tables!
	.columnHeaderArray = MAP_BLEND_CURVE_2_ROWS,
	.tableCells = MAP_BLEND_CURVE_2_DATA,
	.multiplier = 0.00001525902f,	//todo unit test these
	.offset = 0.0 };
//! 1/65535  (0-1.00 range, 16bit precision)

float MAP_BLEND_CURVE_3_ROWS[11] SWITCHDATA =
{0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1};

short MAP_BLEND_CURVE_3_DATA[11] SWITCHDATA =
{0,6554,13107,19661,26214,32768,39321,45875,52428,58982,65535};

TwoDTable MapBlendCurve3 SWITCHDATA = {
	.columnCount = 11,
	.tableType = UInt16Table2D,//TODO: CHECK that these are consistent between 2d/3d tables!
	.columnHeaderArray = MAP_BLEND_CURVE_3_ROWS,
	.tableCells = MAP_BLEND_CURVE_3_DATA,
	.multiplier = 0.00001525902f,	//todo unit test these
	.offset = 0.0 };
//! 1/65535  (0-1.00 range, 16bit precision)

float MAP_BLEND_CURVE_4_ROWS[11] SWITCHDATA =
{0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1};

short MAP_BLEND_CURVE_4_DATA[11] SWITCHDATA =
{0,6554,13107,19661,26214,32768,39321,45875,52428,58982,65535};

TwoDTable MapBlendCurve4  SWITCHDATA = {
	.columnCount = 11,
	.tableType = UInt16Table2D,//TODO: CHECK that these are consistent between 2d/3d tables!
	.columnHeaderArray = MAP_BLEND_CURVE_4_ROWS,
	.tableCells = MAP_BLEND_CURVE_4_DATA,
	.multiplier = 0.00001525902f,	//todo unit test these
	.offset = 0.0 };
//! 1/65535  (0-1.00 range, 16bit precision)


#endif