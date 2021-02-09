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

#if TIMING_HACKS


extern void** TimingBlendGroup;
extern void** KnockCorrectionRetardBlendGroup;

void (*BaseTimingHooked)() __attribute__ ((section ("RomHole_Functions"))) = (void(*)()) sBaseTiming;

float TimingHack()
{
	float OutputValue;
	
	float subIam;
	float iam;
	float timingLookup;
	
	subIam = HighPass(1 - IAM, 0.0f);

	if(pRamVariables.TimingLookupMAPLoad==LoadLookup)	
	{
		timingLookup = *pEngineLoad;
	}
	else
	{
		timingLookup = (*pManifoldAbsolutePressure - 760)*.01933677;
	}

//		pRamVariables.MaxSubtractiveKCA = HighPass(BlendAndSwitchCurve(KnockCorrectionRetardTableGroup, *pEngineLoad, *pEngineSpeed, KnockControlBlendCurveSwitch),0.0f);
		pRamVariables.MaxSubtractiveKCA = HighPass(BlendAndSwitchCurve(KnockCorrectionRetardTableGroup, timingLookup, *pEngineSpeed, KnockControlBlendCurveSwitch),0.0f);
	 
	pRamVariables.SubtractiveKCA = subIam *  pRamVariables.MaxSubtractiveKCA;
	

		
//			OutputValue = BlendAndSwitchCurve(TimingTableGroup, *pEngineLoad, *pEngineSpeed, TimingBlendCurveSwitch);
			OutputValue = BlendAndSwitchCurve(TimingTableGroup, timingLookup, *pEngineSpeed, TimingBlendCurveSwitch);
		


	if(pRamVariables.LCTimingMode == LCTimingModeLocked && pRamVariables.LCEngaged == 1)
	{
		OutputValue = pRamVariables.LCTimingLock;
	}
	else if(pRamVariables.LCTimingMode == LCTimingModeCompensated)
	{
		pRamVariables.LCTimingRetard = HighPass(Pull3DHooked(&LCTimingRetardTable, *pVehicleSpeed, *pEngineSpeed),0.0f);
	
		pRamVariables.LCTimingRetard *= pRamVariables.LCTimingRetardMultiplier;
		
		OutputValue -= HighPass(pRamVariables.LCTimingRetard,0.0f);
	}

	OutputValue -= Abs(pRamVariables.SubtractiveKCA);
	
	pRamVariables.BaseTimingTarget = OutputValue;
	
	if(pRamVariables.TimingHackEnabled == HackEnabled)
		{
			pRamVariables.BaseTimingOutput = OutputValue;
			pRamVariables.FBKCRetardValue = BlendCurve(FBKCRetardValue1,FBKCRetardValue2,KnockControlBlendCurveSwitch);
			pRamVariables.FBKCRetardValueAlternate = BlendCurve(FBKCRetardValueAlternate1,FBKCRetardValueAlternate2,KnockControlBlendCurveSwitch);
		}
	else
		{
			pRamVariables.BaseTimingOutput = Pull3DHooked((void*)PrimaryOEMTimingTable, *pEngineLoad, *pEngineSpeed);	
	    	pRamVariables.FBKCRetardValue = *dFBKCRetardValue;
			pRamVariables.FBKCRetardValueAlternate = *dFBKCRetardValueAlternate;
		}

	
		
	//Call existing!
	BaseTimingHooked();

}

#endif