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

void UpdateWideBandLambdaInput(float InputVoltage)
{
	pRamVariables.WideBandLambda = Smooth(WidebandSensorSmoothingFactor,Pull2DHooked(&WideBandScaling,InputVoltage),pRamVariables.WideBandLambda);
	
	if((pRamVariables.WideBandLambda > (LeanBoostAFRThreshold*14.7)) && (*pManifoldRelativePressure > LeanBoostMRPThreshold))
	{
		if(pRamVariables.LeanBoostCounter == 0) pRamVariables.FailSafeLeanBoostSwitch = 1;
	}
	else
	{
		pRamVariables.FailSafeLeanBoostSwitch = 0;
		pRamVariables.LeanBoostCounter = LeanBoostDelay;
	}
}

void UpdateWideBandLambdaZT3CAN(float sensorLambda, unsigned char sensorStatus)
{

	pRamVariables.WideBandLambda = sensorLambda;

	if((!sensorStatus) && (pRamVariables.WideBandLambda > (LeanBoostAFRThreshold*14.7)) && (*pManifoldRelativePressure > LeanBoostMRPThreshold))
	{
		if(pRamVariables.LeanBoostCounter == 0) pRamVariables.FailSafeLeanBoostSwitch = 1;
	}
	else
	{
		pRamVariables.FailSafeLeanBoostSwitch = 0;
		pRamVariables.LeanBoostCounter = LeanBoostDelay;
	}		
}

void LeanBoostCount()
{
	if(pRamVariables.LeanBoostCounter > 0) pRamVariables.LeanBoostCounter--;
}

#endif
