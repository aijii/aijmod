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

void UpdateFuelPressureInput(float InputVoltage)
{
	//scale
	pRamVariables.FuelPressure = Smooth(FuelPressureSensorSmoothingFactor,Pull2DHooked(&FuelPressureScaling,InputVoltage),pRamVariables.FuelPressure);
	pRamVariables.FuelPressureDifferential = pRamVariables.FuelPressure - *pManifoldRelativePressure;

	if((Abs(pRamVariables.FuelPressureDifferential - BaseFuelPressure) > FuelPressureDeltaThreshold) && (*pEngineSpeed > FuelPressureTriggerMinRPM))
	{
		if(pRamVariables.FuelPressureDeltaCounter == 0) pRamVariables.FailSafeFuelPressureDeltaSwitch = 1;
	}
	else
	{
		pRamVariables.FailSafeFuelPressureDeltaSwitch = 0;
		pRamVariables.FuelPressureDeltaCounter = FuelPressureDeltaDelay;
	}
}

void FuelPressureDeltaCount()
{
	if(pRamVariables.FuelPressureDeltaCounter > 0) pRamVariables.FuelPressureDeltaCounter--;
}

#endif