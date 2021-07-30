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

void (*MemoryResetHooked)() __attribute__ ((section ("RomHole_Functions"))) = (void(*)()) sMemoryReset;

void Initializer()
{
	MemoryResetHooked();
#if RAM_PERSIST
	InitRamVariables();
#else
	ResetRamVariables();
#endif

#if PROG_MODE && CRUISE_CONTROL
	//Check every init for test mode switch (entering OEM test mode)
	//If entering OEM test mode, disable programming mode to stop CEL flash
	if(TestTestModeSwitch())
	{
		pRamVariables.ProgModeStatus = ProgModeDisabled;
	}
	else
	{
		pRamVariables.ProgModeStatus = ProgModeEnabled;
	}
#endif

}

void ResetRamVariables()
{
	ClearRamVariables((long*)&pRamVariables, (long*)pRamHoleEnd);
	PopulateRamVariables();
}

void InitRamVariables()
{
	if(pRamVariables.ECUIdentifier != *(long*)dEcuId || pRamVariables.HardResetFlag == HardResetFlagEnabled)
	{
		ResetRamVariables();
	}
}

void ClearRamVariables(long *start, long *end)
{
	long *pend = end;
	long *pointy = start;
	while(pointy < pend)
	{
		*pointy = 0x00000000;
		pointy++;
	}
}

void PopulateRamVariables()
{

#if CRUISE_CONTROL
pRamVariables.CruiseResumeLast = TestCruiseResumeSwitch();
pRamVariables.CruiseCoastLast = TestCruiseCoastSwitch();
#endif

#if INJECTOR_HACKS
	//Injector Scalar init to default
	pRamVariables.InjectorScaling = *InjectorScalingOem;
#endif

#if SWITCH_HACKS
	pRamVariables.MapSwitch = DefaultMapSwitch;
	pRamVariables.MapBlendRatio = DefaultMapBlendRatio;
	pRamVariables.MapSwitchingInputMode = DefaultMapSwitchingInputMode;
	pRamVariables.MapBlendingInputMode = DefaultMapBlendingInputMode;
	pRamVariables.WideBandLambdaInputMode = WideBandLambdaInputMode;
	pRamVariables.FuelPressureInputMode = FuelPressureInputMode;
	pRamVariables.MapBlendOutOfRangeCounter = MapBlendCount;
	pRamVariables.LeanBoostCounter = LeanBoostDelay;
	pRamVariables.FuelPressureDeltaCounter = FuelPressureDeltaDelay;
	pRamVariables.WideBandLambda = 0;
	pRamVariables.FuelPressure = 0;

#if OILPRESSURE_HACKS
pRamVariables.OilPressureInputMode=OilPressureInputMode;
pRamVariables.OilPressure = 0;
#endif
#if OILTEMP_HACKS
pRamVariables.OilTemperatureInputMode=OilTemperatureInputMode;
pRamVariables.OilTemperature = 0;
#endif
	
	
#endif

#if CAN_HACKS
	pRamVariables.initFunctionRun = 0;
	pRamVariables.sdTimer = 0;
	
	pRamVariables.ECA2EthanolContentCAN = 0;
	pRamVariables.ECA2FuelTemperatureCAN = 0;
	
	pRamVariables.ZT3LambdaCAN = 0;
	pRamVariables.ZT3AFRCAN = 0;
	pRamVariables.ZT3StatusCAN = 0;
#endif 

#if PROG_MODE
	pRamVariables.ProgModeCurrentMode = 1;
	pRamVariables.ProgModeValueFlashes = 0;
	pRamVariables.ValetMode = ValetModeDisabled;
#endif

#if REVLIM_HACKS
	//Revlimit mode init
	if (pRamVariables.RevLimMode == RevLimModeUndefined)
	{
		pRamVariables.RevLimMode = DefaultRevLimMode;
	}
	//Init revlimit cuts
	pRamVariables.FlatFootShiftMode = DefaultFlatFootShiftMode;
	pRamVariables.RedLineCut = DefaultRedLineCut;
	pRamVariables.RedLineHyst = DefaultRedLineHyst;
	pRamVariables.FlatFootShiftHyst = DefaultFlatFootShiftHyst;
	pRamVariables.FlatFootShiftAutoDelta = DefaultFlatFootShiftAutoDelta;
	pRamVariables.FlatFootShiftStaticDelta = DefaultFlatFootShiftStaticDelta;
	pRamVariables.LaunchControlSpeedMax = DefaultLaunchControlSpeedMax;
	pRamVariables.LaunchControlCut = DefaultLaunchControlCut;
	pRamVariables.LaunchControlHyst = DefaultLaunchControlHyst;
	pRamVariables.FlatFootShiftSpeedThreshold = DefaultFlatFootShiftSpeedThreshold;
	pRamVariables.FlatFootShiftRpmThreshold = DefaultFlatFootShiftRpmThreshold;
	pRamVariables.ClutchSwitchLast = *pClutchFlags & ClutchBitMask;
#if !AUTO_TRANS
	RevLimReset();
#endif
#endif

#if VIN_HACKS
	VinCheck();
#endif

#if SPARK_HACKS
	//Init spark cut
	*LCSparkEventsToCut = DefaultLCSparkEventsToCut;
	*LCSparkEventsCutFrom = DefaultLCSparkEventsCutFrom;
#endif

#if POLF_HACKS
	pRamVariables.PolfHackEnabled = DefaultPolfHackEnabled;
	if (pRamVariables.LCFuelMode == LCFuelModeUndefined)
	{
		pRamVariables.LCFuelMode = DefaultLCFuelMode;
	}
	pRamVariables.LCFuelLock = DefaultLCFuelLock;
	pRamVariables.LCFuelEnrichMultiplier = DefaultLCFuelEnrichMultiplier;
	pRamVariables.FuelingLookupMAPLoad = DefaultFuelingLookupMAPLoad;
#endif

#if TIMING_HACKS
	pRamVariables.TimingHackEnabled = DefaultTimingHackEnabled;

	if (pRamVariables.LCTimingMode == LCTimingModeUndefined)
	{
		pRamVariables.LCTimingMode = DefaultLCTimingMode;
	}
	pRamVariables.LCTimingLock = DefaultLCTimingLock;
	pRamVariables.LCTimingRetardMultiplier = DefaultLCTimingRetardMultiplier;
	pRamVariables.TimingLookupMAPLoad = DefaultTimingLookupMAPLoad;
#endif

#if BOOST_HACKS
	pRamVariables.BoostHackEnabled = DefaultBoostHackEnabled;
#endif

#if SD_HACKS
	pRamVariables.MafMode = DefaultMafMode;
#endif

#if AVCS_HACKS
	pRamVariables.AVCSLookupMAPLoad = DefaultAVCSLookupMAPLoad;
#endif
#if RAM_HOLE_SCANNER
	pRamVariables.ScannedAddress = (pRamHoleStart - 0xFFFF0000);
#endif

#if DYN_RAMTUNING
    unsigned long *p;
    p = (unsigned long*) ((char*) pRamHoleEnd + 1);
    while(--p >= &(pRamVariables.MaxDynRAMTables)){
        *p = 0x00000000;
    }
    pRamVariables.ROMtoRAMArrayOffset = (pRamVariables.MaxDynRAMTables - 1)<<2; //doesn't matter for 0 case
    pRamVariables.MaxDynRAMTables = 0;
#endif

pRamVariables.ECUIdentifier = *(long*)dEcuId;
pRamVariables.HardResetFlag = HardResetFlagDisabled;

}

#if VIN_HACKS

void VinCheck()
{
	//Init VIN
}

#endif
