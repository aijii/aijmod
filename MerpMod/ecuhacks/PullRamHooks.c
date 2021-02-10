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

float (*Pull3DHooked)(ThreeDTable *table, float xLookup, float yLookup) __attribute__ ((section ("RomHole_Functions"))) = (float(*)(ThreeDTable*, float, float)) sPull3DFloat;
float (*Pull2DHooked)(TwoDTable *table, float xLookup) __attribute__ ((section ("RomHole_Functions"))) = (float(*)(TwoDTable*, float)) sPull2DFloat;

#if SWITCH_HACKS
float (*ShortToFloatHooked)(unsigned short input, float grad, float offs) __attribute__ ((section ("RomHole_Functions"))) = (float(*)(unsigned short, float, float)) sShortToFloat;
#endif

float Pull3DRamHook(ThreeDTable *table, float xLookup, float yLookup)
{
    //Check if r4 is ram or not??
    //WARNING: cannot use LOOKUP TABLES in this region (pRamVariables)!!!
    //Lookup tables must be static or this needs to change.
    if( (table > (ThreeDTable*) &(pRamVariables.RamVariableStart)) &&
        (table < (ThreeDTable*) &(pRamVariables.RamHoleEndMarker))
    ){
        return *((float*) table);
    }
    else
    {
        return Pull3DHooked((ThreeDTable*)table, xLookup, yLookup);
    }
}

float Pull2DRamHook(TwoDTable *table, float xLookup)
{
    //Check if r4 is ram or not??
    if(table > (TwoDTable*) &(pRamVariables.RamVariableStart))
    {
        return *((float*) table);
    }
    else
    {
         return Pull2DHooked((TwoDTable*)table, xLookup);
    }
}

#if SWITCH_HACKS

float Pull2DRamHookTipInEnrich(TwoDTable *table, float xLookup)
{
    // Change this to return tipinenrichlookup * injectorscalar multiplier, if switch is on
    // maybe move to fueling hacks?

    if((table == (TwoDTable*) tTipInEnrich || table == (TwoDTable*) tTipInEnrich2) &&
        (pRamVariables.PolfHackEnabled == HackEnabled))//This hook is used by other tables!!
        return Pull2DHooked(table, xLookup)
        * Pull3DHooked((ThreeDTable*)&TipInEnrichMultiplier, pRamVariables.MapBlendRatio, xLookup);
    return Pull2DHooked(table, xLookup);
}

float Pull2DRamHookCrankingFuel(TwoDTable *table, float xLookup)
{
    if((table == (TwoDTable*) tCrankingFuelA || table == (TwoDTable*) tCrankingFuelB ||
        table == (TwoDTable*) tCrankingFuelC || table == (TwoDTable*) tCrankingFuelD ||
        table == (TwoDTable*) tCrankingFuelE || table == (TwoDTable*) tCrankingFuelF) &&
        (pRamVariables.PolfHackEnabled == HackEnabled))//This hook is used by other tables!!
        return Pull2DHooked(table, xLookup)
        * Pull3DHooked((ThreeDTable*)&CrankingFuelMultiplier, pRamVariables.MapBlendRatio, xLookup);
    return Pull2DHooked(table, xLookup);

}

float Pull2DRamHookStartupEnrich2(TwoDTable *table, float xLookup)
{
    if((table == (TwoDTable*) tStartupEnrich2_1A || table == (TwoDTable*) tStartupEnrich2_1B ||
        table == (TwoDTable*) tStartupEnrich2_2A || table == (TwoDTable*) tStartupEnrich2_2B) &&
        (pRamVariables.PolfHackEnabled == HackEnabled))//This hook is used by other tables!!
        return Pull2DHooked(table, xLookup)
        * Pull3DHooked((ThreeDTable*)&StartupEnrichMultiplier, pRamVariables.MapBlendRatio, xLookup);
    return Pull2DHooked(table, xLookup);

}

float Pull2DRamHookStartupEnrich3(TwoDTable *table, float xLookup)
{
    if((table == (TwoDTable*) tStartupEnrich3_1A || table == (TwoDTable*) tStartupEnrich3_1B ||
        table == (TwoDTable*) tStartupEnrich3_2A || table == (TwoDTable*) tStartupEnrich3_2B) &&
    (pRamVariables.PolfHackEnabled == HackEnabled))//This hook is used by other tables!!
        return Pull2DHooked(table, xLookup)
        * Pull3DHooked((ThreeDTable*)&StartupEnrichMultiplier,pRamVariables.MapBlendRatio, xLookup);
    return Pull2DHooked(table, xLookup);
}

#if DUAL_FRONTO2_HACKS
float Pull2DRamHookFrontO2Scaling(TwoDTable *table, float xLookup)
{
    if((table == (TwoDTable*) tFrontO2Scaling) &&
        (pRamVariables.PolfHackEnabled == HackEnabled))//This hook is used by other tables!!
        return BlendCurve(
            Pull2DHooked(&FrontOxygenSensorScaling1,xLookup),
            Pull2DHooked(&FrontOxygenSensorScaling2,xLookup),
            ClosedLoopFuelingBlendCurveSwitch
        );
    return Pull2DHooked(table, xLookup);
}
#endif

float Pull3DRamHookStartupEnrich1(ThreeDTable *table, float xLookup, float yLookup)
{
    if((table == (ThreeDTable*) tStartupEnrich1Cruise || table == (ThreeDTable*) tStartupEnrich1NonCruise) &&
        (pRamVariables.PolfHackEnabled == HackEnabled))//This hook is used by other tables!!
        return Pull3DHooked(table, xLookup, yLookup)
        * Pull3DHooked((ThreeDTable*)&StartupEnrichMultiplier, pRamVariables.MapBlendRatio, xLookup);
    return Pull3DHooked(table, xLookup, yLookup);
}



float Pull2DRamHookIntakeTempCompensation(TwoDTable *table, float xLookup)
{
    if((table == (TwoDTable*) tIntakeTempCompensation) &&
        (pRamVariables.TimingHackEnabled == HackEnabled))//This hook is used by other tables!!
        return BlendCurve(
            Pull2DHooked(&IntakeTempCompensationTable1,xLookup),
            Pull2DHooked(&IntakeTempCompensationTable2,xLookup),
            TimingBlendCurveSwitch
        );
    return Pull2DHooked(table, xLookup);
}
//To do - define tIntakeTempCompensation, and create the two tables

#endif

#if AVCS_HACKS
float Pull3DRamHookAVCSLookup(TwoDTable *table, float xLookup, float yLookup)
{

    if((table == (TwoDTable*) tIntakeAVCSCruise ||
    table == (TwoDTable*) tIntakeAVCSNonCruise ||
    table == (TwoDTable*) tExhaustAVCSCruise ||
    table == (TwoDTable*) tExhaustAVCSNonCruise) &&
    (pRamVariables.AVCSLookupMAPLoad != LoadLookup))
        return Pull3DHooked(table, ((*pManifoldAbsolutePressure - 760)*.01933677), yLookup);
    return Pull3DHooked(table, xLookup, yLookup);

}
#endif