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
	ClearRamVariables((long*)&pRamVariables,(long*)&pRamVariables.RamHoleEndMarker);
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

#if RAMTUNE_AUTOCOPY
	AutoPopulateRamTables();
#endif

#if DYN_RAMTUNING
    TableDefRAM *p = &(pRamVariables.RAMTableHeaders[_MAX_RAM_TABLES_ - 1]);
    while(p >= pRamVariables.RAMTableHeaders){
        p->romaddress = DefaultRAMTableRomAddr;
        p->ramaddress = DefaultRAMTableRamAddr;
        p--;
    }
#endif

pRamVariables.ECUIdentifier = *(long*)dEcuId;
pRamVariables.HardResetFlag = HardResetFlagDisabled;

}

#if RAMTUNE_AUTOCOPY

void AutoPopulateRamTables()
{
short* spoint;
unsigned char* ucpoint;
int i=0;

#if VE_RAMTUNING

	spoint = pRamVariables.VERamData;
	
	for (i=0; i < 576; i++)
	{
		if(DefaultRamTuneTableBlend == 0)
			*spoint = VE_DATA1[i];
		else
			*spoint = VE_DATA2[i];
	spoint += 0x1;
	}

#endif

#if POLF_RAMTUNING

	ucpoint = pRamVariables.POLFRamData;

	for (i=0; i < 576; i++)
	{
		if(DefaultRamTuneTableBlend == 0)
		{
			switch(DefaultRamTuneTableSwitch)
			{
				case MapSwitch3:
					*ucpoint = F1SS_DATA[i];
				break;
			
				case MapSwitch2:
					*ucpoint = F1S_DATA[i];
				break;
			
				default:
					*ucpoint = F1I_DATA[i];
				break;
			}
			
		}	
		else
		{
			switch(DefaultRamTuneTableSwitch)
			{
				case MapSwitch3:
					*ucpoint = F2SS_DATA[i];
				break;
			
				case MapSwitch2:
					*ucpoint = F2S_DATA[i];
				break;
			
				default:
					*ucpoint = F2I_DATA[i];
				break;
			}			
		}
	ucpoint += 0x1;
	}	
	
#endif

#if TIMING_RAMTUNING

	ucpoint = pRamVariables.TimingRamData;

	for (i=0; i < 576; i++)
	{
		if(DefaultRamTuneTableBlend == 0)
		{
			switch(DefaultRamTuneTableSwitch)
			{
				case MapSwitch3:
					*ucpoint = T1ss_DATA[i];
				break;
			
				case MapSwitch2:
					*ucpoint = T1s_DATA[i];
				break;
			
				default:
					*ucpoint = T1i_DATA[i];
				break;
			}
			
		}	
		else
		{
			switch(DefaultRamTuneTableSwitch)
			{
				case MapSwitch3:
					*ucpoint = T2ss_DATA[i];
				break;
			
				case MapSwitch2:
					*ucpoint = T2s_DATA[i];
				break;
			
				default:
					*ucpoint = T2i_DATA[i];
				break;
			}			
		}
	ucpoint += 0x1;
	}	
#endif

#if PGWG_RAMTUNING

	spoint = pRamVariables.PGWGRamData;

	for (i=0; i < 96; i++)
	{
		if(DefaultRamTuneTableBlend == 0)
		{
			switch(DefaultRamTuneTableSwitch)
			{
				case MapSwitch3:
					*spoint = PGWGData1ss[i];
				break;
			
				case MapSwitch2:
					*spoint = PGWGData1s[i];
				break;
			
				default:
					*spoint = PGWGData1i[i];
				break;
			}
			
		}	
		else
		{
			switch(DefaultRamTuneTableSwitch)
			{
				case MapSwitch3:
					*spoint = PGWGData2ss[i];
				break;
			
				case MapSwitch2:
					*spoint = PGWGData2s[i];
				break;
			
				default:
					*spoint = PGWGData2i[i];
				break;
			}			
		}
	spoint += 0x1;
	}	


	spoint = pRamVariables.PGTBRamData;

	for (i=0; i < 96; i++)
	{
		if(DefaultRamTuneTableBlend == 0)
		{
			switch(DefaultRamTuneTableSwitch)
			{
				case MapSwitch3:
					*spoint = PGTBData1ss[i];
				break;
			
				case MapSwitch2:
					*spoint = PGTBData1s[i];
				break;
			
				default:
					*spoint = PGTBData1i[i];
				break;
			}
			
		}	
		else
		{
			switch(DefaultRamTuneTableSwitch)
			{
				case MapSwitch3:
					*spoint = PGTBData2ss[i];
				break;
			
				case MapSwitch2:
					*spoint = PGTBData2s[i];
				break;
			
				default:
					*spoint = PGTBData2i[i];
				break;
			}			
		}
	spoint += 0x1;
	}

#endif

#if WGDC_RAMTUNING

	spoint = pRamVariables.WGDCInitialRamData;

	for (i=0; i < 256; i++)
	{
		if(DefaultRamTuneTableBlend == 0)
		{
			switch(DefaultRamTuneTableSwitch)
			{
				case MapSwitch3:
					*spoint = WGDCInitialData1ss[i];
				break;
			
				case MapSwitch2:
					*spoint = WGDCInitialData1s[i];
				break;
			
				default:
					*spoint = WGDCInitialData1i[i];
				break;
			}
			
		}	
		else
		{
			switch(DefaultRamTuneTableSwitch)
			{
				case MapSwitch3:
					*spoint = WGDCInitialData2ss[i];
				break;
			
				case MapSwitch2:
					*spoint = WGDCInitialData2s[i];
				break;
			
				default:
					*spoint = WGDCInitialData2i[i];
				break;
			}			
		}
	spoint += 0x1;
	}
	
	spoint = pRamVariables.WGDCMaxRamData;

	for (i=0; i < 256; i++)
	{
		if(DefaultRamTuneTableBlend == 0)
		{
			switch(DefaultRamTuneTableSwitch)
			{
				case MapSwitch3:
					*spoint = WGDCMaxData1ss[i];
				break;
			
				case MapSwitch2:
					*spoint = WGDCMaxData1s[i];
				break;
			
				default:
					*spoint = WGDCMaxData1i[i];
				break;
			}
			
		}	
		else
		{
			switch(DefaultRamTuneTableSwitch)
			{
				case MapSwitch3:
					*spoint = WGDCMaxData2ss[i];
				break;
			
				case MapSwitch2:
					*spoint = WGDCMaxData2s[i];
				break;
			
				default:
					*spoint = WGDCMaxData2i[i];
				break;
			}			
		}
	spoint += 0x1;
	}
#endif

#if AVCS_RAMTUNING

	spoint = pRamVariables.AVCSRamData;


	for (i=0; i < 342; i++)
	{
	//	short* tempSpoint = (short*)(tIntakeAVCSNonCruiseData+i);

		*spoint = ((short*)(tIntakeAVCSNonCruiseData))[i];
		spoint += 0x1;
	}

#endif

#if MAF_RAMTUNING
#endif

#if TIPIN_RAMTUNING
#endif

}

#endif


#if VIN_HACKS

void VinCheck()
{
	//Init VIN	
}

#endif