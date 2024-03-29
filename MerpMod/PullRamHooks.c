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

float (*Pull3DHooked)(ThreeDTable* table, float xLookup, float yLookup) __attribute__ ((section ("RomHole_Functions"))) = (float(*)()) sPull3DFloat;
float (*Pull2DHooked)(TwoDTable* table, float xLookup) __attribute__ ((section ("RomHole_Functions"))) = (float(*)()) sPull2DFloat;

#if SWITCH_HACKS
float (*ShortToFloatHooked)(unsigned short input, float grad, float offs) __attribute__ ((section ("RomHole_Functions"))) = (float(*)()) sShortToFloat;
#endif

float Pull3DRamHook(float* table, float xLookup, float yLookup)
{
	//Check if r4 is ram or not??
	//WARNING: cannot use LOOKUP TABLES in this region (pRamVariables)!!!
	//Lookup tables must be static or this needs to change.
	if(((void*)table > (void*)&(pRamVariables.RamVariableStart)) && ((void*)table < (void*)&(pRamVariables.RamHoleEndMarker)))
	{
		return *table;
	}
	else
	{
		return Pull3DHooked((ThreeDTable*)table, xLookup, yLookup);
	}
}

float Pull2DRamHook(float* table, float xLookup)
{
	//Check if r4 is ram or not??
	if(table > (float*)&(pRamVariables.RamVariableStart))
	{
		return *table;
	}
	else
	{
		 return Pull2DHooked((TwoDTable*)table, xLookup);
	}
}

#if SWITCH_HACKS

float Pull2DRamHookTipInEnrich(float* table, float xLookup)
{
	// Change this to return tipinenrichlookup * injectorscalar multiplier, if switch is on 
	// maybe move to fueling hacks?

	if((table == tTipInEnrich
		|| table == tTipInEnrich2)  && (pRamVariables.PolfHackEnabled == HackEnabled))//This hook is used by other tables!!
		return Pull2DHooked((TwoDTable*)table, xLookup)
		* Pull3DHooked((ThreeDTable*)&TipInEnrichMultiplier, pRamVariables.MapBlendRatio, xLookup);
	return Pull2DHooked((TwoDTable*)table, xLookup);
}

float Pull2DRamHookCrankingFuel(float* table, float xLookup)
{
	if((table == tCrankingFuelA ||
	table == tCrankingFuelB ||
	table == tCrankingFuelC ||
	table == tCrankingFuelD ||
	table == tCrankingFuelE ||
	table == tCrankingFuelF) && (pRamVariables.PolfHackEnabled == HackEnabled))//This hook is used by other tables!!
		return Pull2DHooked((TwoDTable*)table, xLookup) 
		* Pull3DHooked((ThreeDTable*)&CrankingFuelMultiplier, pRamVariables.MapBlendRatio, xLookup);
	return Pull2DHooked((TwoDTable*)table, xLookup);	

}

float Pull2DRamHookStartupEnrich2(float* table, float xLookup)
{
	if((table == tStartupEnrich2_1A ||
	table == tStartupEnrich2_1B ||
	table == tStartupEnrich2_2A ||
	table == tStartupEnrich2_2B) && (pRamVariables.PolfHackEnabled == HackEnabled))//This hook is used by other tables!!
		return Pull2DHooked((TwoDTable*)table, xLookup)
		* Pull3DHooked((ThreeDTable*)&StartupEnrichMultiplier, pRamVariables.MapBlendRatio, xLookup);
	return Pull2DHooked((TwoDTable*)table, xLookup);

}

float Pull2DRamHookStartupEnrich3(float* table, float xLookup)
{
	if((table == tStartupEnrich3_1A ||
	table == tStartupEnrich3_1B ||
	table == tStartupEnrich3_2A ||
	table == tStartupEnrich3_2B) && (pRamVariables.PolfHackEnabled == HackEnabled))//This hook is used by other tables!!
		return Pull2DHooked((TwoDTable*)table, xLookup) 
		* Pull3DHooked((ThreeDTable*)&StartupEnrichMultiplier,pRamVariables.MapBlendRatio, xLookup);
	return Pull2DHooked((TwoDTable*)table, xLookup);
}

float Pull2DRamHookFrontO2Scaling(float* table, float xLookup)
{
	if((table == tFrontO2Scaling) && (pRamVariables.PolfHackEnabled == HackEnabled))//This hook is used by other tables!!
		return BlendCurve(Pull2DHooked(&FrontOxygenSensorScaling1,xLookup),Pull2DHooked(&FrontOxygenSensorScaling2,xLookup),ClosedLoopFuelingBlendCurveSwitch);
	return Pull2DHooked((TwoDTable*)table, xLookup);
}

float Pull3DRamHookStartupEnrich1(float* table, float xLookup, float yLookup)
{
	if((table == tStartupEnrich1Cruise ||
	table == tStartupEnrich1NonCruise)
	&& (pRamVariables.PolfHackEnabled == HackEnabled))//This hook is used by other tables!!
		return Pull3DHooked((ThreeDTable*)table, xLookup, yLookup) 
		* Pull3DHooked((ThreeDTable*)&StartupEnrichMultiplier, pRamVariables.MapBlendRatio, xLookup);
	return Pull3DHooked((ThreeDTable*)table, xLookup, yLookup);	
}



float Pull2DRamHookIntakeTempCompensation(float* table, float xLookup)
{
	if((table == tIntakeTempCompensation) && (pRamVariables.TimingHackEnabled == HackEnabled))//This hook is used by other tables!!
		return BlendCurve(Pull2DHooked(&IntakeTempCompensationTable1,xLookup),Pull2DHooked(&IntakeTempCompensationTable2,xLookup),TimingBlendCurveSwitch);
	return Pull2DHooked((TwoDTable*)table, xLookup);
}
//To do - define tIntakeTempCompensation, and create the two tables



#endif

#if AVCS_HACKS
float Pull3DRamHookAVCSLookup(float* table, float xLookup, float yLookup)
{

#if AVCS_RAMTUNING
	if (table == tIntakeAVCSNonCruise &&
		pRamVariables.AVCSRamFlag == 0x01)
		{
			if(pRamVariables.AVCSLookupMAPLoad == LoadLookup)
			{
				return Pull3DHooked(&AVCSRamTable, xLookup, yLookup);
			}
			else
			{
				return Pull3DHooked(&AVCSRamTable, ((*pManifoldAbsolutePressure - 760)*.01933677), yLookup);
			}
		}
	else if((table == tIntakeAVCSCruise ||
			table == tIntakeAVCSNonCruise ||
			table == tExhaustAVCSCruise ||
			table == tExhaustAVCSNonCruise) &&
			(pRamVariables.AVCSLookupMAPLoad != LoadLookup))
				return Pull3DHooked((ThreeDTable*)table, ((*pManifoldAbsolutePressure - 760)*.01933677), yLookup); 	
	else 
		return Pull3DHooked((ThreeDTable*)table, xLookup, yLookup);	

#else
	if((table == tIntakeAVCSCruise ||
	table == tIntakeAVCSNonCruise ||
	table == tExhaustAVCSCruise ||
	table == tExhaustAVCSNonCruise) &&
	(pRamVariables.AVCSLookupMAPLoad != LoadLookup))
		return Pull3DHooked((ThreeDTable*)table, ((*pManifoldAbsolutePressure - 760)*.01933677), yLookup); 	
	return Pull3DHooked((ThreeDTable*)table, xLookup, yLookup);	
#endif	
// To-do, create OEMRamTuneTables.c, create AVCS Ramtune table, 
	
}
#endif