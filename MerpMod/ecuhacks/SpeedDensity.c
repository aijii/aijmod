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

#if SD_HACKS

float ComputeMassAirFlow(TwoDTable* MafScalingTable, float MafVoltage)
{

#if CAN_HACKS
	CustomCanService();
#endif	
	
	pRamVariables.MafFromSensor = Pull2DHooked(MafScalingTable,MafVoltage);	

#if DUALMAF_HACKS	
	pRamVariables.MafFromDualSensorScaling = BlendCurve(Pull2DHooked(&MafScalingTable1,MafVoltage),Pull2DHooked(&MafScalingTable2,MafVoltage),MassAirFlowScalingBlendCurveSwitch);
#endif

#if SWITCH_HACKS
	pRamVariables.VolumetricEfficiency = BlendAndSwitchCurve(VETableGroup, *pManifoldAbsolutePressure, *pEngineSpeed, SpeedDensityBlendCurveSwitch);
#else
	pRamVariables.VolumetricEfficiency = Pull3DHooked(&VolumetricEfficiencyTable1, *pManifoldAbsolutePressure, *pEngineSpeed);
#endif
		
	float intakeAirTempInKelvin = (*pIntakeAirTemp) + CelsiusToKelvin;
		
	pRamVariables.AtmosphericCompensation = Pull3DHooked(&AtmosphericCompensationTable, *pManifoldAbsolutePressure, *pAtmoPress);
#if SD_DMAP
	pRamVariables.DeltaMapCompensation = Pull3DHooked(&SDDeltaMapTable, *pDeltaMap, *pEngineSpeed);
#endif

	pRamVariables.MafFromSpeedDensity = 
		Displacement * 
		(*pEngineSpeed) * 
		(*pManifoldAbsolutePressure) * 
		pRamVariables.VolumetricEfficiency * 
		pRamVariables.AtmosphericCompensation *
#if SD_DMAP
		pRamVariables.DeltaMapCompensation *
#endif
		SpeedDensityConstant / intakeAirTempInKelvin;

	if (pRamVariables.MafMode == MafModeSpeedDensity)
	{
		return pRamVariables.MafFromSpeedDensity;
	}
	else if (pRamVariables.MafMode == MafModeSDBlending)
	{
		pRamVariables.SDMafBlendRatio = Pull3DHooked(&SDBlendingTable, *pManifoldAbsolutePressure, *pEngineSpeed);
		
		pRamVariables.SDMafFromBlend = 
		((pRamVariables.MafFromSpeedDensity * pRamVariables.SDMafBlendRatio) +
		(pRamVariables.MafFromSensor * 
		(1 - pRamVariables.SDMafBlendRatio)));
		
		return pRamVariables.SDMafFromBlend;
	}
#if DUALMAF_HACKS	
	else if (pRamVariables.MafMode == MafModeDualSDBlending)
	{
		pRamVariables.SDMafBlendRatio = Pull3DHooked(&SDBlendingTable, *pManifoldAbsolutePressure, *pEngineSpeed);
		
		pRamVariables.SDMafFromBlend = 
		((pRamVariables.MafFromSpeedDensity * pRamVariables.SDMafBlendRatio) +
		(pRamVariables.MafFromDualSensorScaling * 
		(1 - pRamVariables.SDMafBlendRatio)));
		
		return pRamVariables.SDMafFromBlend;		
	}
	else if (pRamVariables.MafMode == MafModeSensorDualScaling)
	{
		return pRamVariables.MafFromDualSensorScaling;	
	}
#endif
	
	else
	{
		return pRamVariables.MafFromSensor;
	}
}
#endif