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

#ifndef __RAM_VARIABLES__
#define __RAM_VARIABLES__

//////////////////////////
//RAM VARIABLES STRUCTURE
//////////////////////////
typedef struct
{
	unsigned char RamVariableStart;
	unsigned char VinAuth;
	unsigned char CruiseCoastLast;
	unsigned char CruiseResumeLast;
	unsigned long ECUIdentifier;
	unsigned char HardResetFlag;
	unsigned char blank0;
	unsigned char blank1;
	unsigned char blank2;

#if VIN_HACKS
	unsigned char VehicleIdent[20];
#endif

#if INJECTOR_HACKS
	float InjectorScaling;
	float InjectorScalingMultiplier;
#endif

#if CAN_HACKS	
	unsigned short ccmSendTimers[ccmCount];
	unsigned short sdTimer;
	
	unsigned short initFunctionRun;
	unsigned char randomTimer;
	
	unsigned char rgBackLight;
	
	unsigned char ecuHacksMainCtr;

	unsigned char ECA2EthanolContentCAN;
	unsigned char ethanolSensorFault;
	
	unsigned short CANBusECAUpdateCounter;
	unsigned char FailSafeCANBusECAUpdateSwitch;
	
	float ZT3LambdaCAN;
	float ZT3AFRCAN;
	unsigned char ZT3StatusCAN;	
	
/*	
	float aemLambda;
	float aemOxygen;
	unsigned char aemDataValid;
	unsigned char aemSensorFault;
	unsigned char aemn1;
	unsigned char aemn2;
*/	
	unsigned char ECA2FuelTemperatureCAN;		
		
#endif



#if SPARK_CUT
	unsigned char SparkEventsX;
	unsigned char se;
	unsigned char se1;
	unsigned char se2;
	unsigned char SparkEventsY;
	unsigned char se3;
	unsigned char se4;
	unsigned char se5;
#endif

#if SWITCH_HACKS
	unsigned char MapSwitch;
	unsigned char MapBlendingInputMode;
	unsigned char MapSwitchingInputMode;
	unsigned char WideBandLambdaInputMode;
	unsigned char FuelPressureInputMode;
	unsigned char OilPressureInputMode;
	unsigned char OilTemperatureInputMode;
	unsigned char swblank;
	float MapBlendRatio;
	float TGVLeftVolts;
	float TGVRightVolts;
	float WideBandLambda;
	float FuelPressure;
	float OilPressure;	
	float OilTemperature;
	float FuelPressureDifferential;
	float RearO2Volts;
	float MAFSensorVolts;
	float MapSwitchInputVoltage;
	unsigned short MapBlendOutOfRangeCounter;
	unsigned char FailSafeMapBlendSwitch;
	unsigned char SIDriveMode;
	unsigned short LeanBoostCounter;
	unsigned char FailSafeLeanBoostSwitch;
	unsigned short FuelPressureDeltaCounter;
	unsigned char FailSafeFuelPressureDeltaSwitch;
	unsigned char FailSafeFuelAdditiveSwitch;
	unsigned short OilPressureCounter;
	unsigned char FailSafeOilPressureSwitch;
	unsigned short OilTemperatureCounter;
	unsigned char FailSafeOilTemperatureSwitch;
	float InjectorDutyCycle;
	unsigned char FailSafeInjectorDutyCycleSwitch;
	unsigned char FuelingLookupMAPLoad;
	unsigned char TimingLookupMAPLoad;
	unsigned char AVCSLookupMAPLoad;
	
	unsigned short exhaustCutoutCounter;
	unsigned char exhaustCutoutOutput;
	
	
#endif

#if SD_HACKS
	//MAF/SD params
	unsigned char SDInitFlag;		//96d
	unsigned char MafMode;
	unsigned char SDempty;
	unsigned char sdempty1;
	float VolumetricEfficiency;	//	96d
	float MafFromSpeedDensity;
	float MafFromSensor;
	float AtmosphericCompensation; //96
	float DeltaMapCompensation;
	float SDMafBlendRatio;
	float SDMafFromBlend;

#if DUALMAF_HACKS
	float MafFromDualSensorScaling;
#endif
#endif

#if REVLIM_HACKS
	//Rev Limiter params
	unsigned char  	RevLimInitFlag;  //96
	unsigned char  	RevLimMode;
	unsigned char	FlatFootShiftMode;
	unsigned char	LCEngaged;
	unsigned char	FFSEngaged;
	unsigned char	ClutchSwitchLast;
	unsigned char FFSGear;
//	char	eleemee2;
	float 	RevLimCut;	//96
	float 	RevLimResume;
  	float  	RedLineCut;
	float	RedLineHyst;	//9
	float	LaunchControlSpeedMax;
  	float  	LaunchControlCut;
	float  	LaunchControlHyst;
 	float  	FFSRPM;
	float 	FlatFootShiftRpmThreshold;
	float	FlatFootShiftAutoDelta;
	float	FlatFootShiftStaticDelta;
	float  	FlatFootShiftHyst;	//9
  	float  	FlatFootShiftSpeedThreshold; //97
#endif

#if CEL_HACKS
	// New variables needed for the CEL Flash Hack
	unsigned char CelSignal;
	unsigned char CelSignalLast;
	unsigned char CruiseSignal;
	unsigned char CruiseSignalLast;

	unsigned char CelFlashSpeed;
	unsigned char CelFlashSpeedCounter;
	unsigned char CelFlashCount;
	unsigned char CelFlashCounter;

	unsigned char CelRepeatSwitch;
	unsigned char CelFlashStatus;
	unsigned char CelFlashDelay;
	unsigned char celunused;

	unsigned char FailSafeFBKCHiSwitch;
	unsigned char FailSafeFBKCLoSwitch;
#if !defined(NOAF1RES)
	unsigned char FailSafeEGTSwitch;
#endif
	unsigned char FailSafeCoolantTempSwitch;
	unsigned char FailSafeIAMSwitch;
#endif

#if PROG_MODE
	unsigned char ProgModeStatus;
	unsigned char ProgModeCurrentMode;
	unsigned char ProgModeValueFlashes;
	unsigned char ValetMode;
	unsigned char asdf3;
	float ProgModeValue;
#endif

#if TIMING_HACKS
	//Timing Hack params
	unsigned char 	TimingHackInitFlag;		//97
	unsigned char 	LCTimingMode;
	unsigned char	TimingHackEnabled;
	unsigned char	Tempty1;
	float	BaseTimingTarget;
	float 	BaseTimingOutput;	//97
	float 	LCTimingRetard;		//97
	float 	LCTimingLock;		//97
	float	LCTimingLockRPM;
	float	LCTimingRetardMultiplier;
	float	SubtractiveKCA;
	float	MaxSubtractiveKCA;
	float	FBKCRetardValue;
	float	FBKCRetardValueAlternate;
#endif

#if POLF_HACKS
	//Fuel Hack params
	unsigned char 	POLFuelHackInitFlag;	//97
	unsigned char 	LCFuelMode;
	unsigned char	PolfHackEnabled;
	unsigned char	Fempty1;
	float PolfTarget;
	float PolfOutput;		//97
	float LCFuelEnrich;			//97
	float LCFuelLock;			//97
	float LCFuelEnrichMultiplier;
#endif

#if BOOST_HACKS
	unsigned char BoostHackEnabled;
	unsigned char bhempty;
	unsigned char bhempty1;
	unsigned char bhempty2;
	//Target Boost Params
	float TargetBoostTarget;
	float TargetBoostOutput;

	//PGWG Params
	float PGWGInitialComp;
	float PGWGMaxComp;
	float PGTBComp;

	//WGDC Params
	float WGDCInitialTarget;
	float WGDCInitialOutput;
	float WGDCMaxTarget;
	float WGDCMaxOutput;
#endif

#if PORT_LOGGER
	unsigned char testchar1;
	unsigned char testchar2;
	unsigned char testchar3;
	unsigned char testchar4;
	unsigned short PortParameters[20];
	unsigned short ADCParameters[40];

#endif

#if RAM_HOLE_SCANNER
	unsigned short ScannedAddress;
	unsigned short ScannedValue;
	unsigned long ScannedStackPointer;
#endif

long	RamHoleSpace;
char	RamHoleEndMarker; //end of static RAM variables

//Dynamic RAM tuning should be at the end of the RAM hole to not have to
//worry about collisions with other RAM variables
//the RAM tune memory section is organized as follows:
//
// ---------------------START OF RAMTUNE SECTION-------------------------------
// ulong indicating the offset used to jump from ROM to RAM array (4 bytes)
// ulong indicating the maximum number of RAM tables (4 bytes)
// array of ulong storing ROM table addresses to intercept (dynamic sized)
// array of ulong storing RAM table addresses to inject (dynamic sized)
// array of bytes storing RAM table data (dynamic sized)
// -----------END OF RAMTUNE SECTION (assumed to be end of RAMHole)------------
//
// Because the number of tables is dynamically set by the controlling PC,
// there is no way to statically/compile-time store a marker to the end
// of the RAMhole, so this needs to be at the end of the RAM hole, and
// the PC uses `pRamHoleEnd` to determine how much space is available
// for RAM tuning
#if DYN_RAMTUNING
    //ROMtoRAMArrayOffset should always be set to MaxDynRAMTables-1 by the PC
    unsigned long ROMtoRAMArrayOffset;

    //MaxDynRAMTables **must** be the last variable before the arrays
    unsigned long MaxDynRAMTables;

    //no need to have pointers to rest of sections
#endif

} RamVariables;

#endif
