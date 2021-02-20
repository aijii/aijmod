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

#if CAN_HACKS

void UpdateMapBlendRatioCANBus(unsigned char ethanolContent, unsigned char ethanolStatus)
{
	if(ethanolStatus) //sensor error, data[7] = 0x01 if fault
	//TODO - need to also throw an error (different one?) and trigger the blend failsafe if we fail to see ECA messages on the canbus
	{
		if(pRamVariables.MapBlendOutOfRangeCounter == 0)
		{ //counter has hit 0, either fail to default blend ratio or leave the last known good(maybe?!?) value

				if(MapBlendFailSafe == FailToDefaultBlendRatio) 
					pRamVariables.MapBlendRatio = Smooth(MapBlendSmoothingFactor,DefaultMapBlendRatio,pRamVariables.MapBlendRatio);
				pRamVariables.FailSafeMapBlendSwitch = 1;
		}
		//or do nothing and let it count down
	}
	else if(pRamVariables.FailSafeCANBusECAUpdateSwitch)
	{
		if(MapBlendFailSafe == FailToDefaultBlendRatio) 
					pRamVariables.MapBlendRatio = Smooth(MapBlendSmoothingFactor,DefaultMapBlendRatio,pRamVariables.MapBlendRatio);		
					
		pRamVariables.MapBlendOutOfRangeCounter = MapBlendCount; //  reset the counter
	}
	else if(*pManifoldRelativePressure < MapBlendBoostContentLock)
	{
		//if boost is below content lock threshold, update blend ratio

			pRamVariables.MapBlendRatio = Smooth(MapBlendSmoothingFactor,((float)ethanolContent/100),pRamVariables.MapBlendRatio); 
			pRamVariables.MapBlendOutOfRangeCounter = MapBlendCount; //  reset the counter
			pRamVariables.FailSafeMapBlendSwitch = 0;
			
	}
	else
	{
		// otherwise don't udpate eca, just reset the counter. depending on how flex sensor is plumbed, we may not be able to rely on eca content
		// readings during high load (i.e. in return line, high load could starve flow back to tank)
			pRamVariables.MapBlendOutOfRangeCounter = MapBlendCount; //  reset the counter
			pRamVariables.FailSafeMapBlendSwitch = 0;
			
	}	
	
}
#endif

void UpdateMapBlendRatioAnalog(float inputVoltage)
{
	if((inputVoltage < BlendInputMinimumVolts) || (inputVoltage > BlendInputMaximumVolts))
	{
	//out of range!
		if(pRamVariables.MapBlendOutOfRangeCounter == 0)
		{
		//counter has hit zero, fall back to default mapblend and trigger cel flash
			if(MapBlendFailSafe == FailToDefaultBlendRatio) 
				pRamVariables.MapBlendRatio = Smooth(MapBlendSmoothingFactor,DefaultMapBlendRatio,pRamVariables.MapBlendRatio);
			pRamVariables.FailSafeMapBlendSwitch = 1;
		}
	
	// do nothing, leave map blend ratio at last known good value! don't reset counter, so it will count down to zero.
	}
	else if(*pManifoldRelativePressure < MapBlendBoostContentLock)
	{
		//within range, boost is under content lock value, all good. 
		pRamVariables.MapBlendRatio = Smooth(MapBlendSmoothingFactor,Pull2DHooked(&MapBlendScaling,inputVoltage),pRamVariables.MapBlendRatio); 
		pRamVariables.MapBlendOutOfRangeCounter = MapBlendCount; //  reset the counter
		pRamVariables.FailSafeMapBlendSwitch = 0;
	}
	else //within range but above content lock, don't update output
	{
		pRamVariables.MapBlendOutOfRangeCounter = MapBlendCount; //  reset the counter
		pRamVariables.FailSafeMapBlendSwitch = 0;
	}	
}

float GetBlendCurveRatio(unsigned char curve)
{
	switch(curve)
	{
		case BlendCurve1:
			return Pull2DHooked(&MapBlendCurve1,pRamVariables.MapBlendRatio);
		break;
		case BlendCurve2:
			return Pull2DHooked(&MapBlendCurve2,pRamVariables.MapBlendRatio);
		break;
		case BlendCurve3:
			return Pull2DHooked(&MapBlendCurve3,pRamVariables.MapBlendRatio);
		break;
		case BlendCurve4:
			return Pull2DHooked(&MapBlendCurve4,pRamVariables.MapBlendRatio);
		break;
		case MasterBlendCurve:
		default:
			return pRamVariables.MapBlendRatio;
		break;
	}	
}

float BlendAndSwitchCurve(TableGroup tg, float xLookup, float yLookup, unsigned char curve)
{
	float OutputValue;
	float ThisMapBlendRatio;
	
	ThisMapBlendRatio = GetBlendCurveRatio(curve);	

	if(ThisMapBlendRatio < 0.01)
	{
		OutputValue = SwitchSelect(tg.Map1, xLookup, yLookup);
		
	}
	else if(ThisMapBlendRatio > 0.99)
	{
		OutputValue = SwitchSelect(tg.Map2, xLookup, yLookup);
	}
	else
	{
		float Value1;
		
		Value1 = SwitchSelect(tg.Map1, xLookup, yLookup);

		Value1 *= (1 - ThisMapBlendRatio);

		//Pull3d for Timing Map 2

		float Value2;
		//Pull3d for Timing Map 1
		Value2 = SwitchSelect(tg.Map2, xLookup, yLookup);
		
		Value2 *= ThisMapBlendRatio;

		//Blend

		OutputValue = (Value1 + Value2);
	}
	return OutputValue;
}

float BlendCurve(float firstValue, float secondValue, unsigned char curve)
{
	float OutputValue;
	float ThisMapBlendRatio;
	
	ThisMapBlendRatio = GetBlendCurveRatio(curve);	

	if(ThisMapBlendRatio < 0.01)
	{
		OutputValue = firstValue;
		
	}
	else if(ThisMapBlendRatio > 0.99)
	{
		OutputValue = secondValue;
	}
	else
	{
		//Blend
		
		firstValue *= (1 - ThisMapBlendRatio);
		
		secondValue *= ThisMapBlendRatio;

		OutputValue = (firstValue + secondValue);
	}
	return OutputValue;	
}

float BlendAndSwitch(TableGroup tg, float xLookup, float yLookup)
{
	float OutputValue;
	if(pRamVariables.MapBlendRatio < 0.01)
	{
		OutputValue = SwitchSelect(tg.Map1, xLookup, yLookup);
		
	}
	else if(pRamVariables.MapBlendRatio > 0.99)
	{
		OutputValue = SwitchSelect(tg.Map2, xLookup, yLookup);
	}
	else
	{
		float Value1;
		
		Value1 = SwitchSelect(tg.Map1, xLookup, yLookup);

		Value1 *= (1 - pRamVariables.MapBlendRatio);

		//Pull3d for Timing Map 2

		float Value2;
		//Pull3d for Timing Map 1
		Value2 = SwitchSelect(tg.Map2, xLookup, yLookup);
		
		Value2 *= pRamVariables.MapBlendRatio;

		//Blend

		OutputValue = (Value1 + Value2);
	}
	return OutputValue;
}

float SwitchSelect(TableSubSet tss, float xLookup, float yLookup)
{
	float OutputValue;
		switch(pRamVariables.MapSwitch)
		{
			case MapSwitch3:
			OutputValue = Pull3DHooked(tss.TableSS, xLookup, yLookup);
			break;
			
			case MapSwitch2:
			OutputValue = Pull3DHooked(tss.TableS, xLookup, yLookup);
			break;
			
			default:
			OutputValue = Pull3DHooked(tss.TableI, xLookup, yLookup);
			break;
		}
	return OutputValue;
}



#ifdef pSiDrive
void MapSwitchSiDriveCheck()
{
	pRamVariables.SIDriveMode = *pSiDrive;
	
	switch(pRamVariables.SIDriveMode)
	{
			case SiDriveSS:
				pRamVariables.MapSwitch = MapSwitch3;
			break;
			
			case SiDriveSSAlt:
				pRamVariables.MapSwitch = MapSwitch3;
			break;
			
			case SiDriveS:
				pRamVariables.MapSwitch = MapSwitch2;
			break;
		
			default:
				pRamVariables.MapSwitch = MapSwitch1;
			break;
	}
}
#endif

void MapBlendFailSafeCount()
{
	if(pRamVariables.MapBlendOutOfRangeCounter > 0) pRamVariables.MapBlendOutOfRangeCounter--;
}

void MapSwitchThresholdCheck(float input)
{
	pRamVariables.MapSwitchInputVoltage = Smooth(MapSwitchSmoothingFactor,input,pRamVariables.MapSwitchInputVoltage);
	if(pRamVariables.MapSwitchInputVoltage < MapSwitchThresholdLo)
	{
		//Low, map 1
		pRamVariables.MapSwitch = MapSwitch1;
	}
	else if (pRamVariables.MapSwitchInputVoltage < MapSwitchThresholdHi)
	{
		//Mid, map 2
		pRamVariables.MapSwitch = MapSwitch2;
	}
	else
	{
		//High, map 3
		pRamVariables.MapSwitch = MapSwitch3;
	}
}

#endif