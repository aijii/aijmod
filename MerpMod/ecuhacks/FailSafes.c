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

void UpdateFailSafes()
{
	// Call other failsafe counters
	
	

#if CAN_HACKS
	
	CANBusECAFailSafeCount();

#endif

	MapBlendFailSafeCount();
	LeanBoostCount();
	FuelPressureDeltaCount();
#if OILPRESSURE_HACKS
	OilPressureCount();
#endif
#if OILTEMP_HACKS
	OilTemperatureCount();
#endif	
	//test failsafe conditions and set switches
	pRamVariables.FailSafeFBKCHiSwitch = (*pFBKC <= FBKCHiThreshold && *pEngineLoad > FBKCLoadThreshold);
	pRamVariables.FailSafeFBKCLoSwitch = (*pFBKC <= FBKCLoThreshold && *pEngineLoad > FBKCLoadThreshold);
#if !defined(NOAF1RES)
	pRamVariables.FailSafeEGTSwitch = (*pAf1Res < EGTResistanceThreshold && *pEngineLoad > EGTCelLoadThreshold);
#endif
	pRamVariables.FailSafeCoolantTempSwitch = (*pCoolantTemp > ECTFlashThreshold);
	pRamVariables.FailSafeIAMSwitch = (IAM < IAMFlashThreshold);
	pRamVariables.FailSafeInjectorDutyCycleSwitch = (pRamVariables.InjectorDutyCycle > InjectorDutyCycleThreshold);

	//Check enables and alarm conditions for failsafe fuel additive action
	pRamVariables.FailSafeFuelAdditiveSwitch = ((pRamVariables.FailSafeEGTSwitch == 1) && (EGTFailSafeFuelAdditiveEnable == 1)) || 
												((pRamVariables.FailSafeCoolantTempSwitch == 1) && (CoolantTempFailSafeFuelAdditiveEnable == 1)) ||
												((pRamVariables.FailSafeFBKCHiSwitch == 1) && (FBKCHiFailSafeFuelAdditiveEnable == 1)) || 
												((pRamVariables.FailSafeLeanBoostSwitch == 1) && (LeanBoostFailSafeFuelAdditiveEnable == 1));

	//to-do add a WGDC limit switch ? Valet Mode.. lets see if this works
	pRamVariables.ValetMode = 	((pRamVariables.FailSafeEGTSwitch == 1) && (EGTFailSafeValetModeEnable == 1)) || 
								((pRamVariables.FailSafeCoolantTempSwitch == 1) && (CoolantTempFailSafeValetModeEnable == 1)) ||
								((pRamVariables.FailSafeFBKCHiSwitch == 1) && (FBKCHiFailSafeValetModeEnable == 1)) || 
								((pRamVariables.FailSafeLeanBoostSwitch == 1) && (LeanBoostFailSafeValetModeEnable == 1)) ||
								((pRamVariables.FailSafeFuelPressureDeltaSwitch == 1) && (FuelPressureDeltaFailSafeValetModeEnable == 1)) ||
#if OILPRESSURE_HACKS
								((pRamVariables.FailSafeOilPressureSwitch == 1) && (OilPressureFailSafeValetModeEnable == 1)) ||
#endif
#if OILTEMP_HACKS								
								((pRamVariables.FailSafeOilTemperatureSwitch == 1) && (OilTemperatureFailSafeValetModeEnable == 1)) ||
#endif								

								((pRamVariables.FailSafeInjectorDutyCycleSwitch == 1) && (InjectorDutyCycleFailSafeValetModeEnable == 1));																


	
}



#endif
