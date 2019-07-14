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

//Tests for Switch code

#include "EcuHacks.h"

void RamTuningTests() __attribute__ ((section ("Misc")));
void RamTuningTests()
{
	TestVETable();
	// TestAvcsTable();
}

void RamTuningTests() __attribute__ ((section ("Misc")));
void TestVETable()
{
	PopulateRamVariables();

	// Idle
	SPEEDDENSITYDATA.tableCells = VE_DATA1;
	float romVE = Pull3DHooked(SPEEDDENSITYDATA, 0.3f, 800);
	
	SPEEDDENSITYDATA.tableCells = pRamVariables.VERamData;
	float ramVE = Pull3DHooked(SPEEDDENSITYDATA, 0.3f, 800);
	
	Assert(AreCloseEnough(romVE, ramVE), "VE at idle");

	// Low RPM, high load.
	SPEEDDENSITYDATA.tableCells = VE_DATA1;
	float romVE = Pull3DHooked(SPEEDDENSITYDATA, 2.0f, 2000);
	
	SPEEDDENSITYDATA.tableCells = pRamVariables.VERamData;
	float ramVE = Pull3DHooked(SPEEDDENSITYDATA, 2.0f, 2000);
	
	Assert(AreCloseEnough(romVE, ramVE), "VE at high load, low RPM");

	// High RPM, high load.
	SPEEDDENSITYDATA.tableCells = VE_DATA1;
	float romVE = Pull3DHooked(SPEEDDENSITYDATA, 2.0f, 6500);
	
	SPEEDDENSITYDATA.tableCells = pRamVariables.VERamData;
	float ramVE = Pull3DHooked(SPEEDDENSITYDATA, 2.0f, 6500);
	
	Assert(AreCloseEnough(romVE, ramVE), "VE at high load, high RPM");
}	
	
