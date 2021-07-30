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

#if SWITCH_HACKS && INJECTOR_HACKS

void InjectorHack(){

pRamVariables.InjectorScalingMultiplier = Pull2DHooked(&InjectorScalingMultiplierTable,pRamVariables.MapBlendRatio);

if(pRamVariables.PolfHackEnabled == HackEnabled)
	pRamVariables.InjectorScaling = pRamVariables.InjectorScalingMultiplier * *dInjectorScaling;
else 
	pRamVariables.InjectorScaling = *dInjectorScaling;
}

#endif

#if POLF_HOOK_DEFINED
	void (*PolfHooked)() __attribute__ ((section ("RomHole_Functions"))) = (void(*)()) sPolf;

void POLFHack()
{		

#if POLF_MAIN_HOOK
EcuHacksMain();
#endif

#if POLF_HACKS
	float OutputValue;
	float fuelingLookup;

		if(pRamVariables.FuelingLookupMAPLoad==LoadLookup)	
		{
			fuelingLookup = *pEngineLoad;
		}
		else
		{
			fuelingLookup = (*pManifoldAbsolutePressure - 760)*.01933677;	
		}
		

	
		OutputValue	= BlendAndSwitchCurve(FuelTableGroup, fuelingLookup, *pEngineSpeed, OpenLoopFuelingBlendCurveSwitch);	
		
		pRamVariables.LCFuelEnrich = Pull3DHooked(&LCFuelEnrichTable, *pVehicleSpeed, *pEngineSpeed) * pRamVariables.LCFuelEnrichMultiplier;

		if(pRamVariables.LCFuelMode == LCFuelModeCompensated)
		{
			OutputValue += pRamVariables.LCFuelEnrich;
		}
		//Now run existing code!

		if(pRamVariables.FailSafeFuelAdditiveSwitch == 1)
		{
			OutputValue += (FailSafeFuelAdditive * 0.0078125);
		}
	
		pRamVariables.PolfTarget = OutputValue;
		
		if(pRamVariables.PolfHackEnabled == HackEnabled)
			pRamVariables.PolfOutput = OutputValue;
		else
			pRamVariables.PolfOutput = Pull3DHooked((void*)PrimaryOEMPolfTable, *pEngineLoad, *pEngineSpeed);	
#endif
		
	PolfHooked();
}
#endif
