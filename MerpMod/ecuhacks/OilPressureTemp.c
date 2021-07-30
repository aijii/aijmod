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

#if OILPRESSURE_HACKS

void UpdateOilPressureInput(float InputVoltage)
{
	//scale
	pRamVariables.OilPressure = Smooth(OilPressureSensorSmoothingFactor,Pull2DHooked(&OilPressureScaling,InputVoltage),pRamVariables.OilPressure);

	if((pRamVariables.OilPressure < OilPressureThreshold) && (*pEngineSpeed > OilPressureTriggerMinRPM))
	{
		if(pRamVariables.OilPressureCounter == 0) pRamVariables.FailSafeOilPressureSwitch = 1;
	}
	else
	{
		pRamVariables.FailSafeOilPressureSwitch = 0;
		pRamVariables.OilPressureCounter = OilPressureDelay;
	}
}

void OilPressureCount()
{
	if(pRamVariables.OilPressureCounter > 0) pRamVariables.OilPressureCounter--;
}
#endif

#if OILTEMP_HACKS

void UpdateOilTemperatureInput(float InputVoltage)
{
	//scale
	// fix oil temperature!
	pRamVariables.OilTemperature = Smooth(OilTemperatureSensorSmoothingFactor,Pull2DHooked(&OilTemperatureScaling,InputVoltage),pRamVariables.OilTemperature);

	if((pRamVariables.OilTemperature > OilTemperatureThreshold) && (*pEngineSpeed > OilTemperatureTriggerMinRPM))
	{
		if(pRamVariables.OilTemperatureCounter == 0) pRamVariables.FailSafeOilTemperatureSwitch = 1;
	}
	else
	{
		pRamVariables.FailSafeOilTemperatureSwitch = 0;
		pRamVariables.OilTemperatureCounter = OilTemperatureDelay;
	}
}

void OilTemperatureCount()
{
	if(pRamVariables.OilTemperatureCounter > 0) pRamVariables.OilTemperatureCounter--;
}

#endif
#endif