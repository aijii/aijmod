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

//Define structures for definition output
typedef struct
{
	long op;
	long address;
	char name[];
} TableDef;

typedef struct
{
	long op;
	long coladdress;
	long dataaddress;
	char name[];
} Table2dDef;

typedef struct
{
	long op;
	long dataaddress;
	char name[];
} Table1dDef;

typedef struct
{
	long op;
	long address;
	char id[8];
	long buf;
	char storagetype[8];
	long buf2;
	char name[];
} ParamDef;

typedef struct
{
	long op;
	long address;
	char id[8];
	long buf;
	long bit;
	char name[];
} ParamBitDef;

typedef struct
{
	long op;
	long address;
	char name[];
} AxisDef;


enum DefOps
{
	OpIdent = 0x43210000,
	OpIdentAddr = 0x43210001,
	OpTable1d = 0x43210002,
	OpTable2d = 0x43210003,
	OpTable3d = 0x43210004,
	OpX = 0x43210005,
	OpY = 0x43210006,
	OpStaticY = 0x43210007,
	OpRAM = 0x43210008,
	OpRAMBit = 0x43210010,
	OpRAMAllBits = 0x43210011,
	OpEnd = 0x00090009,
};

typedef struct {
	long IdentOp;
	long IdentOffset;
	char Ident[ECU_IDENTIFIER_CHARS];
	long Identend;
	long InhOffset;
	char InhIdent[ECU_CALIBRATION_CHARS];
	long IdentIhnEnd;
	long InhEcuIdOffset;
	char InhEcuId[ECU_IDENTIFIER_CHARS];
	long EcuIdInhEnd;
} DefMetaHeader;


/*
typedef struct {


} LiveTuneBuffer;
*/

/*const DefMetaHeader defmetaheader __attribute__ ((section ("DefinitionDataHeader"),aligned(4))) =
{
	IdentOp:	OpIdent,
	IdentOffset:	DERP(dRomHoleStart),
	Ident:	STRI(MOD_ECU_IDENTIFIER),
	Identend:	OpEnd,
	InhOffset:	0x0,
	InhIdent:	STRI(ECU_CALIBRATION_ID),
	IdentIhnEnd:	OpEnd,
	InhEcuIdOffset:	0x0,
	InhEcuId:	STRI(ECU_IDENTIFIER),
	EcuIdInhEnd:	OpEnd
);*/

#define DEFNEW1D(NAME,ADDR)	const TableDef ADDR##_1DDef DEFDATA =	{op: OpTable1d , address: (int)&ADDR , name: NAME }
#define DEFNEW2D(NAME,ADDR)	const TableDef ADDR##_2DDef DEFDATA =	{op: OpTable2d , address: (int)&ADDR , name: NAME }
#define DEFNEW3D(NAME,ADDR)	const TableDef ADDR##_3DDef DEFDATA =	{op: OpTable3d , address: (int)&ADDR , name: NAME }

#define DEFIDA1D(NAME,ADDR)	const TableDef ADDR##_1DDef DEFDATA =	{op: OpTable1d , address: (int)ADDR , name: NAME }
#define DEFIDA2D(NAME,ADDR)	const TableDef ADDR##_2DDef DEFDATA =	{op: OpTable2d , address: (int)ADDR , name: NAME }
#define DEFIDA3D(NAME,ADDR)	const TableDef ADDR##_3DDef DEFDATA =	{op: OpTable3d , address: (int)ADDR , name: NAME }

#define DEFINERAM(NAME,ADDR,TYPE,EID)	const ParamDef ADDR##_ParamDef DEFDATA =	{op: OpRAM , address: (int)ADDR , id: EID , buf: OpEnd , storagetype: TYPE , buf2: OpEnd, name: NAME }
#define DEFINERAMBIT(NAME,ADDR,BIT,EID)	const ParamBitDef ADDR##_ParamBitDef DEFDATA =	{op: OpRAMBit , address: (int)ADDR , id: EID , buf: OpEnd , bit: BIT , name: NAME }
#define DEFINERAMVAR(NAME,ADDR,TYPE,EID)	const ParamDef ADDR##_ParamDef DEFDATA =	{op: OpRAM , address: (int)&pRamVariables.ADDR , id: EID , buf: OpEnd , storagetype: TYPE , buf2: OpEnd, name: NAME }//TRY TO FIX THIS??
#define DEFINERAMVARARRAY(NAME,ADDR,INDEX,TYPE,EID)	const ParamDef ADDR##INDEX##_ParamDef DEFDATA =	{op: OpRAM , address: (int)&pRamVariables.ADDR[INDEX] , id: EID , buf: OpEnd , storagetype: TYPE , buf2: OpEnd, name: NAME }//TRY TO FIX THIS??
#define DEFINERAMVARARRAYALLBITS(NAME,ADDR,INDEX,TYPE,EID)	const ParamDef ADDR##INDEX##_ParamBitsDef DEFDATA =	{op: OpRAMAllBits , address: (int)&pRamVariables.ADDR[INDEX] , id: EID , buf: OpEnd , storagetype: TYPE , buf2: OpEnd, name: NAME }//TRY TO FIX THIS??
//TODO: in sharptune, if no match is found, create a new one to read out RAWDATA!

#if PORT_LOGGER
DEFINERAMVARARRAYALLBITS("MerpMod Port Logger A",PortParameters,0,"uint16","E");
DEFINERAMVARARRAYALLBITS("MerpMod Port Logger B",PortParameters,1,"uint16","E");
DEFINERAMVARARRAYALLBITS("MerpMod Port Logger C",PortParameters,2,"uint16","E");
DEFINERAMVARARRAYALLBITS("MerpMod Port Logger D",PortParameters,3,"uint16","E");
DEFINERAMVARARRAYALLBITS("MerpMod Port Logger E",PortParameters,4,"uint16","E");
DEFINERAMVARARRAYALLBITS("MerpMod Port Logger F",PortParameters,5,"uint16","E");
DEFINERAMVARARRAYALLBITS("MerpMod Port Logger G",PortParameters,6,"uint16","E");
DEFINERAMVARARRAYALLBITS("MerpMod Port Logger H",PortParameters,7,"uint16","E");
DEFINERAMVARARRAYALLBITS("MerpMod Port Logger J",PortParameters,8,"uint16","E");
DEFINERAMVARARRAYALLBITS("MerpMod Port Logger K",PortParameters,9,"uint16","E");
DEFINERAMVARARRAYALLBITS("MerpMod Port Logger L",PortParameters,10,"uint16","E");

DEFINERAMVARARRAY("MerpMod Port Logger A",PortParameters,0,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger B",PortParameters,1,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger C",PortParameters,2,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger D",PortParameters,3,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger E",PortParameters,4,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger F",PortParameters,5,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger G",PortParameters,6,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger H",PortParameters,7,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger J",PortParameters,8,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger K",PortParameters,9,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger L",PortParameters,10,"uint16","E");


//ADC
DEFINERAMVARARRAY("MerpMod Port Logger ADC 0",ADCParameters,0,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 1",ADCParameters,1,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 2",ADCParameters,2,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 3",ADCParameters,3,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 4",ADCParameters,4,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 5",ADCParameters,5,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 6",ADCParameters,6,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 7",ADCParameters,7,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 8",ADCParameters,8,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 9",ADCParameters,9,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 10",ADCParameters,10,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 11",ADCParameters,11,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 12",ADCParameters,12,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 13",ADCParameters,13,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 14",ADCParameters,14,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 15",ADCParameters,15,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 16",ADCParameters,16,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 17",ADCParameters,17,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 18",ADCParameters,18,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 19",ADCParameters,19,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 20",ADCParameters,20,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 21",ADCParameters,21,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 22",ADCParameters,22,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 23",ADCParameters,23,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 24",ADCParameters,24,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 25",ADCParameters,25,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 26",ADCParameters,26,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 27",ADCParameters,27,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 28",ADCParameters,28,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 29",ADCParameters,29,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 30",ADCParameters,30,"uint16","E");
DEFINERAMVARARRAY("MerpMod Port Logger ADC 31",ADCParameters,31,"uint16","E");
#endif

#if RAM_HOLE_SCANNER
DEFINERAMVAR("MerpMod Ram Hole Scanner Address",ScannedAddress,"uint16","E");
DEFINERAMVAR("MerpMod Ram Hole Scanner Value",ScannedValue,"uint16","E");
//DEFINERAMVAR("MerpMod Ram Hole Scanner Composite",ScannedAddress,"uint32","E");
DEFINERAMVAR("MerpMod Ram Hole Scanner Stack Pointer",ScannedStackPointer,"uint32","E");
#endif

#if PROG_MODE
DEFINERAMVAR("MerpMod Prog Mode Status",ProgModeStatus,"uint8","E1518");
DEFINERAMVAR("MerpMod Prog Mode Current Mode",ProgModeCurrentMode,"uint8","E1519");
DEFINERAMVAR("MerpMod Prog Mode Selected Value Flash",ProgModeValueFlashes,"uint8","E1520");
DEFINERAMVAR("MerpMod Prog Mode Value",ProgModeValue,"float","E1521");
DEFINERAMVAR("MerpMod Valet Mode",ValetMode,"uint8","E1522");
DEFINERAMVAR("MerpMod Hard Reset Flag",HardResetFlag,"uint8","E1601");
#endif

DEFIDA1D("ECU Identifier",dEcuId);

//Engine load smoothing factors
DEFIDA1D("Engine Load Smoothing Factor A",dLoadSmoothingA);
DEFIDA1D("Engine Load Smoothing Factor B",dLoadSmoothingB);
#ifdef dLoadSmoothingAlt
	DEFIDA1D("Engine Load Smoothing Factor Alternate",dLoadSmoothingAlt);
#endif
#ifdef dLoadSmoothingAlt2
	DEFIDA1D("Engine Load Smoothing Factor Alternate B",dLoadSmoothingAlt2);
#endif
DEFIDA1D("Engine Load Smoothing Factor Final",dLoadSmoothingFinal);

//Switches/flags
// TODO UNCOMMENT THIS ONCE BITS ARE WORKING IN SHARPTUNE!!!
#ifdef pClutchFlags
DEFINERAMBIT("MerpMod Clutch Switch",pClutchFlags, ClutchBitMask,"E");
#endif

#ifdef pBrakeFlags
DEFINERAMBIT("MerpMod Brake Switch",pBrakeFlags, BrakeBitMask,"E");
#endif

#ifdef pDefogFlags
DEFINERAMBIT("MerpMod Defog Switch",pDefogFlags, DefogBitMask,"E");
#endif
#ifdef pTestModeFlags
DEFINERAMBIT("MerpMod TestMode Switch",pTestModeFlags, TestModeBitMask,"E");
#endif

#ifdef pResumeFlags
	DEFINERAMBIT("MerpMod Cruise Resume Switch",pResumeFlags, ResumeBitMask,"E");
#endif
#ifdef pCoastFlags
	DEFINERAMBIT("MerpMod Cruise Coast Switch",pCoastFlags, CoastBitMask,"E");
#endif
#ifdef pFlagsRevLim
	DEFINERAMBIT("MerpMod Rev Limit Fuel Cut Switch",pFlagsRevLim, RevLimBitMask,"E");
#endif

//VIN stuff
#if VIN_HACKS && VIN_TEST_LOG
DEFINERAMVAR("MerpMod Vehicle Identifier",VehicleIdent,"uint28","E");
DEFINERAMVAR("MerpMod Auth Pass/Fail",VinAuth,"uint8","E");
#endif

#if SPARK_CUT
DEFINERAM("Default LC Spark Events Cut From",DefaultLCSparkEventsCutFrom,"uint8","E");
DEFINERAMVAR("LC Spark Events Cut From",SparkEventsX,"uint8","E");
#endif

#if SD_HACKS
DEFINERAMVAR("MerpMod SD Mode Switch",MafMode,"uint8","E1100");
DEFINERAMVAR("MerpMod SD Volumetric Efficiency",VolumetricEfficiency,"float","E1101");
DEFINERAMVAR("MerpMod SD Airflow Final Output",MafFromSpeedDensity,"float","E1102");
DEFINERAMVAR("MerpMod SD Airflow Maf Sensor",MafFromSensor,"float","E1106");
DEFINERAMVAR("MerpMod SD Atmospheric Compensation",AtmosphericCompensation,"float","E1103");
DEFINERAMVAR("MerpMod SD Blending Ratio",SDMafBlendRatio,"float","E1104");
DEFINERAMVAR("MerpMod SD Airflow Blending",SDMafFromBlend,"float","E1105");
DEFNEW3D("Volumetric Efficiency Table 1",VolumetricEfficiencyTable1);

#if SWITCH_HACKS
DEFNEW3D("Volumetric Efficiency Table 2",VolumetricEfficiencyTable2);
#endif

#if DUALMAF_HACKS
DEFNEW2D("Mass Airflow Sensor Scaling Table 1",MafScalingTable1);
DEFNEW2D("Mass Airflow Sensor Scaling Table 2",MafScalingTable2);
DEFINERAMVAR("MerpMod SD Airflow Maf Sensor Dual Scaled",MafFromDualSensorScaling,"float","E");
#endif

#if SD_DMAP
DEFINE3D("Delta MAP Compensation",SDDeltaMapTable);
DEFINERAM("MerpMod Delta MAP",pDeltaMap,"float","E");
DEFINERAMVAR("MerpMod Delta MAP Compensation Direct",DeltaMapCompensation,"float","E");
#endif

DEFNEW3D("Atmospheric Pressure Compensation",AtmosphericCompensationTable);
DEFNEW3D("SD Blending Table",SDBlendingTable);
DEFNEW1D("Engine Displacement",Displacement);
DEFNEW1D("Mass Airflow Mode",DefaultMafMode);
DEFNEW1D("Speed Density Constant",SpeedDensityConstant);


#endif

#if REVLIM_HACKS
DEFNEW1D("Rev Limit (Redline)",DefaultRedLineCut);
#ifdef pCurrentGear
DEFNEW1D("Flat Foot Shift Mode",DefaultFlatFootShiftMode);
DEFNEW1D("Flat Foot Shift Delta (Automatic Limit)",DefaultFlatFootShiftAutoDelta);
#endif
DEFNEW1D("Flat Foot Shift Delta (Static Limit)",DefaultFlatFootShiftStaticDelta);
DEFNEW1D("Flat Foot Shift Minimum Speed Threshold",DefaultFlatFootShiftSpeedThreshold);
DEFNEW1D("Flat Foot Shift Minimum RPM Threshold",DefaultFlatFootShiftRpmThreshold);
DEFNEW1D("Launch Control Maximum Speed Threshold",DefaultLaunchControlSpeedMax);
DEFNEW1D("Launch Control Minimum Throttle Threshold",LCMinimumThrottle);
DEFNEW1D("Flat Foot Shift Minimum Throttle Threshold",FFSMinimumThrottle);
#ifdef pCurrentGear
DEFNEW1D("Flat Foot Shift Gear Ratios",GearRatios);
#endif
DEFNEW1D("Rev Limit (Launch Control)",DefaultLaunchControlCut);

	//PARAMS
DEFINERAMVAR("MerpMod FFS Mode",FlatFootShiftMode,"uint8","E");//TODO add to def base
DEFINERAMVAR("MerpMod LC Engaged Signal",LCEngaged,"uint8","E");
DEFINERAMVAR("MerpMod FFS Engaged Signal",FFSEngaged,"uint8","E");
DEFINERAMVAR("MerpMod FFS Gear Monitor 1-Byte",FFSGear,"uint8","E");
DEFINERAMVAR("MerpMod RevLimit Active Cut RPM",RevLimCut,"float","E");
DEFINERAMVAR("MerpMod RevLimit Active Resume RPM",RevLimResume,"float","E");
DEFINERAMVAR("MerpMod RedLine Cut RPM",RedLineCut,"float","E");
DEFINERAMVAR("MerpMod RedLine Hysteresis",RedLineHyst,"float","E");
DEFINERAMVAR("MerpMod Launch Control RPM",LaunchControlCut,"float","E");
DEFINERAMVAR("MerpMod Launch Control Hysteresis",LaunchControlHyst,"float","E");
DEFINERAMVAR("MerpMod FFS Delta (Auto)",FlatFootShiftAutoDelta,"float","E");
DEFINERAMVAR("MerpMod FFS Delta (Static)",FlatFootShiftStaticDelta,"float","E");
DEFINERAMVAR("MerpMod FFS Engagement RPM",FFSRPM,"float","E");
DEFINERAMVAR("MerpMod FFS Speed Threshold",FlatFootShiftSpeedThreshold,"float","E");
DEFINERAMVAR("MerpMod LC Speed Threshold",LaunchControlSpeedMax,"float","E");
#endif

#if LC_ADJUST
DEFNEW1D("Launch Control Adjustment Step",LCAdjustStep);
#endif

#if SWITCH_HACKS
DEFINERAMVAR("MerpMod ECU Identifier",ECUIdentifier,"uint32","E");

DEFINERAMVAR("MerpMod TGV Volts Left",TGVLeftVolts,"float","E");
DEFINERAMVAR("MerpMod TGV Volts Right",TGVRightVolts,"float","E");

DEFNEW2D("Map Blend Input Scaling",MapBlendScaling);

DEFNEW2D("Map Blend Curve 1",MapBlendCurve1);
DEFNEW2D("Map Blend Curve 2",MapBlendCurve2);
DEFNEW2D("Map Blend Curve 3",MapBlendCurve3);
DEFNEW2D("Map Blend Curve 4",MapBlendCurve4);

DEFNEW1D("Open Loop Fueling Blend Curve",OpenLoopFuelingBlendCurveSwitch);
DEFNEW1D("Closed Loop Fueling Blend Curve",ClosedLoopFuelingBlendCurveSwitch);
DEFNEW1D("Base Timing Blend Curve",TimingBlendCurveSwitch);
DEFNEW1D("Knock Control Blend Curve",KnockControlBlendCurveSwitch);
DEFNEW1D("Wastegate Duty Blend Curve",WastegateDutyBlendCurveSwitch);
DEFNEW1D("Boost Blend Curve",BoostBlendCurveSwitch);
DEFNEW1D("Mass Airflow Blend Curve",MassAirFlowScalingBlendCurveSwitch);
DEFNEW1D("Speed Density Blend Curve",SpeedDensityBlendCurveSwitch);

DEFNEW1D("Map Switch Input Threshold Low",MapSwitchThresholdLo);
DEFNEW1D("Map Switch Input Threshold High",MapSwitchThresholdHi);
DEFNEW1D("Map Switch Input Mode",DefaultMapSwitchingInputMode);
DEFNEW1D("Map Blending Input Mode",DefaultMapBlendingInputMode);

DEFINERAMVAR("MerpMod Map Switching Input Mode",MapSwitchingInputMode,"uint8","E");
DEFINERAMVAR("MerpMod Map Blending Input Mode",MapBlendingInputMode,"uint8","E");
DEFINERAMVAR("MerpMod Map Switch",MapSwitch,"uint8","E");
DEFINERAMVAR("MerpMod Map Blending Ratio",MapBlendRatio,"float","E");

DEFINERAMVAR("Merpmod Blended FBKC Retard Value",FBKCRetardValue,"float","E");
DEFINERAMVAR("Merpmod Blended FBKC Retard Value Alternate",FBKCRetardValueAlternate,"float","E");

DEFINERAMVAR("Merpmod SI Drive",SIDriveMode,"uint8","E");
DEFINERAMVAR("Merpmod Map Blend Out Of Range Counter",MapBlendOutOfRangeCounter,"uint16","E");

DEFNEW1D("Map Blend Ratio Smoothing Factor",MapBlendSmoothingFactor);
DEFNEW1D("Map Blend Ratio Boost Content Lock",MapBlendBoostContentLock);
DEFNEW1D("Default Map Blending Ratio",DefaultMapBlendRatio);
DEFNEW1D("Default Map Switch",DefaultMapSwitch);
DEFNEW1D("Map Switch Smoothing Factor",MapSwitchSmoothingFactor);
DEFNEW1D("Map Blend Failsafe Low Threshold Voltage",BlendInputMinimumVolts);
DEFNEW1D("Map Blend Failsafe High Threshold Voltage",BlendInputMaximumVolts);
DEFNEW1D("Map Blend Failsafe Delay",MapBlendCount);
DEFNEW1D("Map Blend Failsafe Action",MapBlendFailSafe);

#if CAN_HACKS
DEFNEW1D("CANBus ECA Update Failsafe Delay",CANBusECAUpdateCount);
#endif

DEFNEW2D("Wideband Sensor Scaling",WideBandScaling);
DEFNEW1D("Wideband Sensor Smoothing Factor",WidebandSensorSmoothingFactor);
DEFNEW2D("Fuel Pressure Sensor Scaling",FuelPressureScaling);
DEFNEW1D("Fuel Pressure Sensor Smoothing Factor",FuelPressureSensorSmoothingFactor);
DEFNEW1D("Wideband Sensor Input Mode",WideBandLambdaInputMode);
DEFNEW1D("Fuel Pressure Sensor Input Mode",FuelPressureInputMode);
DEFNEW1D("Base Fuel Pressure",BaseFuelPressure);


#if OILPRESSURE_HACKS
DEFNEW2D("Oil Pressure Sensor Scaling",OilPressureScaling);
DEFNEW1D("Oil Pressure Sensor Smoothing Factor",OilPressureSensorSmoothingFactor);
DEFNEW1D("Oil Pressure Sensor Input Mode",OilPressureInputMode);
DEFINERAMVAR("Merpmod Oil Pressure",OilPressure,"float","E");
DEFINERAMVAR("Merpmod Oil Temperature",OilTemperature,"float","E");
#endif 

#if OILTEMP_HACKS
DEFNEW2D("Oil Temperature Sensor Scaling",OilTemperatureScaling);
DEFNEW1D("Oil Temperature Sensor Smoothing Factor",OilTemperatureSensorSmoothingFactor);
DEFNEW1D("Oil Temperature Sensor Input Mode",OilTemperatureInputMode);
#endif

DEFINERAMVAR("Merpmod Fuel Pressure",FuelPressure,"float","E");

DEFINERAMVAR("Merpmod Rear O2 Voltage",RearO2Volts,"float","E");
DEFINERAMVAR("Merpmod Wideband",WideBandLambda,"float","E");
DEFINERAMVAR("Merpmod Lean Boost Counter",LeanBoostCounter,"uint16","E");
DEFINERAMVAR("Merpmod Fuel Pressure Delta",FuelPressureDifferential,"float","E");
DEFINERAMVAR("Merpmod Injector Duty Cycle",InjectorDutyCycle,"float","E");

#if INJECTOR_HACKS
DEFNEW2D("Map Blending Injector Scaling Multiplier",InjectorScalingMultiplierTable);
DEFINERAMVAR("MerpMod Injector Scaling",InjectorScaling,"float","E");
#endif

DEFNEW3D("Map Blending Throttle Tip-In Enrichment Multiplier",TipInEnrichMultiplier);
DEFNEW3D("Map Blending Cranking Fuel Multiplier",CrankingFuelMultiplier);
DEFNEW3D("Map Blending Startup Enrichment Multiplier",StartupEnrichMultiplier);

#endif

#if CAN_HACKS

//Zeitronix ECA-2 CAN Bus
DEFINERAMVAR("Merpmod CANBus ECA Update Counter",CANBusECAUpdateCounter,"uint16","E");
DEFINERAMVAR("Merpmod Trigger CANBus ECA Update",FailSafeCANBusECAUpdateSwitch,"uint8","E");

DEFINERAMVAR("Merpmod CANBus ECA-2 Raw Ethanol Content",ECA2EthanolContentCAN,"uint8","E");
DEFINERAMVAR("Merpmod CANBus ECA-2 Raw Fuel Temp",ECA2FuelTemperatureCAN,"uint8","E");

//Zeitronix ZT-3 Wideband CAN Bus
DEFINERAMVAR("Merpmod CANBus ZT3 Raw Lambda",ZT3LambdaCAN,"float","E");
DEFINERAMVAR("Merpmod CANBus ZT3 Raw AFR",ZT3AFRCAN,"uint8","E");
DEFINERAMVAR("Merpmod CANBus ZT3 Sensor Status",ZT3StatusCAN,"uint8","E");

#endif

#if POLF_HACKS
DEFINERAMVAR("MerpMod LC Fueling Lock Enrichment",LCFuelLock,"float","E");
DEFINERAMVAR("MerpMod LC Fueling Mode",LCFuelMode,"float","E");
DEFINERAMVAR("MerpMod LC Fueling Enrichment",LCFuelEnrich,"float","E");
DEFINERAMVAR("MerpMod LC Fueling Enrichment Multiplier",LCFuelEnrichMultiplier,"float","E");
DEFINERAMVAR("MerpMod Primary Open Loop Fueling Target",PolfTarget,"float","E");
DEFINERAMVAR("MerpMod Primary Open Loop Fueling Output",PolfOutput,"float","E");

#if SWITCH_HACKS
DEFNEW1D("Fueling Hack Enable",DefaultPolfHackEnabled);
DEFNEW1D("Fueling Lookup Load/MAP",DefaultFuelingLookupMAPLoad);
DEFNEW3D("Primary Open Loop Fueling Table 1 Intelligent(Ext)",FuelTable1i);
DEFNEW3D("Primary Open Loop Fueling Table 2 Intelligent(Ext)",FuelTable2i);
DEFNEW3D("Primary Open Loop Fueling Table 1 Sport(Ext)",FuelTable1s);
DEFNEW3D("Primary Open Loop Fueling Table 2 Sport(Ext)",FuelTable2s);
DEFNEW3D("Primary Open Loop Fueling Table 1 Sport Sharp(Ext)",FuelTable1ss);
DEFNEW3D("Primary Open Loop Fueling Table 2 Sport Sharp(Ext)",FuelTable2ss);

DEFNEW1D("Failsafe Fuel Additive",FailSafeFuelAdditive);
DEFNEW1D("Failsafe Fuel Additive Trigger - EGT",EGTFailSafeFuelAdditiveEnable);
DEFNEW1D("Failsafe Fuel Additive Trigger - ECT",CoolantTempFailSafeFuelAdditiveEnable);
DEFNEW1D("Failsafe Fuel Additive Trigger - Severe Knock",FBKCHiFailSafeFuelAdditiveEnable);
DEFNEW1D("Failsafe Fuel Additive Trigger - Lean Boost",LeanBoostFailSafeFuelAdditiveEnable);

DEFNEW1D("Failsafe Valet Mode Trigger - EGT",EGTFailSafeValetModeEnable);
DEFNEW1D("Failsafe Valet Mode Trigger - ECT",CoolantTempFailSafeValetModeEnable);
DEFNEW1D("Failsafe Valet Mode Trigger - Severe Knock",FBKCHiFailSafeValetModeEnable);
DEFNEW1D("Failsafe Valet Mode Trigger - Lean Boost",LeanBoostFailSafeValetModeEnable);
DEFNEW1D("Failsafe Valet Mode Trigger - Fuel Pressure Delta",FuelPressureDeltaFailSafeValetModeEnable);
#if OILPRESSURE_HACKS
DEFNEW1D("Failsafe Valet Mode Trigger - Oil Pressure",OilPressureFailSafeValetModeEnable);
#endif
#if OILTEMP_HACKS
DEFNEW1D("Failsafe Valet Mode Trigger - Oil Temperature",OilTemperatureFailSafeValetModeEnable);
#endif
DEFNEW1D("Failsafe Valet Mode Trigger - Injector Duty Cycle",InjectorDutyCycleFailSafeValetModeEnable);
DEFNEW1D("Injector Pulse Width Calculation",UseInjectorLatency);

#if DUAL_FRONTO2_HACKS
DEFNEW2D("Front Oxygen Sensor Scaling Table 1",FrontOxygenSensorScaling1);
DEFNEW2D("Front Oxygen Sensor Scaling Table 2",FrontOxygenSensorScaling2);
#endif

#if AUXOUT_HACKS
DEFNEW3D("Exhaust Cutout Valve Output Table Intelligent",ExhaustCutoutTable1i);
DEFNEW3D("Exhaust Cutout Valve Output Table Sport",ExhaustCutoutTable1s);
DEFNEW3D("Exhaust Cutout Valve Output Table Sport Sharp",ExhaustCutoutTable1ss);
DEFINERAMVAR("MerpMod Auxilliary Output - Exhaust Cutout",exhaustCutoutOutput,"uint8","E");
#endif

#else
DEFNEW3D("Primary Open Loop Fueling Table 1",FuelTable1i);
DEFNEW3D("Primary Open Loop Fueling Table 2",FuelTable2i);
#endif
DEFNEW3D("Launch Control Fuel Enrichment",LCFuelEnrichTable);
DEFNEW1D("Launch Control Fueling Mode",DefaultLCFuelMode);
DEFNEW1D("Launch Control Enrichment (Lock Mode)",DefaultLCFuelLock);
DEFNEW1D("Default Launch Control Fueling Compensation Multiplier",DefaultLCFuelEnrichMultiplier);

#endif

#if PROG_MODE
#endif

#if SPARK_HACKS
#endif

#if AVCS_HACKS
DEFNEW1D("AVCS Lookup Load/MAP",DefaultAVCSLookupMAPLoad);
#endif

#if CEL_HACKS
DEFNEW1D("FBKC Threshold",FBKCLoThreshold);
DEFNEW1D("FBKC Flash Speed",FBKCLoFlashSpeed);
DEFNEW1D("FBKC Flash Count",FBKCLoFlashes);
DEFNEW1D("FBKC Severe Knock Threshold",FBKCHiThreshold);
DEFNEW1D("FBKC Severe Knock Flash Speed",FBKCHiFlashSpeed);
DEFNEW1D("FBKC Severe Knock Flash Count",FBKCHiFlashes);
DEFNEW1D("FBKC Load Threshold",FBKCLoadThreshold);
DEFNEW1D("IAM Flash Threshold",IAMFlashThreshold);
DEFNEW1D("IAM Flash Count",IAMFlashes);
DEFNEW1D("IAM Flash Speed",IAMFlashSpeed);
DEFNEW1D("Map Blend Out of Range Flash Speed",MapBlendFlashSpeed);
DEFNEW1D("Map Blend Out of Range Flash Count",MapBlendFlashes);
DEFNEW1D("Lean Boost Flash Speed",LeanBoostFlashSpeed);
DEFNEW1D("Lean Boost Flash Count",LeanBoostFlashes);
DEFNEW1D("Lean Boost AFR Threshold",LeanBoostAFRThreshold);
DEFNEW1D("Lean Boost MRP Threshold",LeanBoostMRPThreshold);
DEFNEW1D("Lean Boost Delay",LeanBoostDelay);
DEFNEW1D("Differential Fuel Pressure Flash Speed",FuelPressureDeltaFlashSpeed);
DEFNEW1D("Differential Fuel Pressure Flash Count",FuelPressureDeltaFlashes);

#if OILPRESSURE_HACKS
DEFNEW1D("Oil Pressure Flash Speed",OilPressureFlashSpeed);
DEFNEW1D("Oil Pressure Flash Count",OilPressureFlashes);
#endif
#if OILTEMP_HACKS
DEFNEW1D("Oil Temperature Flash Speed",OilTemperatureFlashSpeed);
DEFNEW1D("Oil Temperature Flash Count",OilTemperatureFlashes);
#endif
DEFINERAMVAR("Merpmod Trigger Low FBKC",FailSafeFBKCLoSwitch,"uint8","E");
#if !defined(NOAF1RES)
DEFINERAMVAR("Merpmod Trigger Exhaust Gas Temperature",FailSafeEGTSwitch,"uint8","E");
#endif
DEFINERAMVAR("Merpmod Trigger Coolant Temperature",FailSafeCoolantTempSwitch,"uint8","E");
DEFINERAMVAR("Merpmod Trigger IAM",FailSafeIAMSwitch,"uint8","E");

DEFINERAMVAR("Merpmod Trigger Lean Boost",FailSafeLeanBoostSwitch,"uint8","E");
DEFINERAMVAR("Merpmod Trigger Fuel Pressure Delta",FailSafeFuelPressureDeltaSwitch,"uint8","E");
DEFINERAMVAR("Merpmod Trigger Injector Duty Cycle",FailSafeInjectorDutyCycleSwitch,"uint8","E");
DEFINERAMVAR("Merpmod Action Fuel Additive Active",FailSafeFuelAdditiveSwitch,"uint8","E");

DEFNEW1D("Fuel Pressure Delta Delay",FuelPressureDeltaDelay);
DEFNEW1D("Fuel Pressure Delta Threshold",FuelPressureDeltaThreshold);
DEFNEW1D("Fuel Pressure Delta - Minimum RPM",FuelPressureTriggerMinRPM);
#if OILPRESSURE_HACKS
DEFNEW1D("Oil Pressure Delay",OilPressureDelay);
DEFNEW1D("Oil Pressure Threshold",OilPressureThreshold);
DEFNEW1D("Oil Pressure - Minimum RPM",OilPressureTriggerMinRPM);
#endif
#if OILTEMP_HACKS
DEFNEW1D("Oil Temperature Delay",OilTemperatureDelay);
DEFNEW1D("Oil Temperature Threshold",OilTemperatureThreshold);
DEFNEW1D("Oil Temperature - Minimum RPM",OilTemperatureTriggerMinRPM);
#endif

#ifdef pAf1Res
DEFNEW1D("EGT AF1 Resistance Threshold",EGTResistanceThreshold);
DEFNEW1D("EGT Flash Speed",EGTFlashSpeed);
DEFNEW1D("EGT Flash Count",EGTFlashes);

DEFNEW1D("EGT Load Threshold",EGTCelLoadThreshold);
#endif

DEFNEW1D("ECT Flash Speed",ECTFlashSpeed);
DEFNEW1D("ECT Flash Count",ECTFlashes);
DEFNEW1D("ECT Flash Temperature Threshold",ECTFlashThreshold);

#if defined(CRUISE_FLAGS) || defined (CRUISE_RESUME_FLAGS)
DEFNEW1D("IAM Recall Flash Speed",IAMFlashSpeed);
#endif

DEFNEW1D("Injector Duty Cycle Flash Speed",InjectorDutyCycleFlashSpeed);
DEFNEW1D("Injector Duty Cycle Flash Count",InjectorDutyCycleFlashes);
DEFNEW1D("Injector Duty Cycle Threshold",InjectorDutyCycleThreshold);

//DEFINERAMVAR("MerpMod CEL Signal",CelSignal,"uint8","E");
//DEFINERAM("MerpMod CEL Signal OEM",pCelSignalOem,"uint8","E");
//DEFINERAMVAR("MerpMod CEL Flash Counter",CelFlashCounter,"uint8","E");
//DEFINERAMVAR("MerpMod CEL Speed Counter",CelFlashSpeedCounter,"uint8","E");

#endif


#if BOOST_HACKS
DEFNEW1D("Boost Hack Enable",DefaultBoostHackEnabled);
DEFINERAMVAR("MerpMod PGWG Initial Compensation",PGWGInitialComp,"float","E");
DEFINERAMVAR("MerpMod PGWG Max Compensation",PGWGMaxComp,"float","E");
#if SWITCH_HACKS
DEFNEW3D("Per Gear Wastegate Table 1 Intelligent",PGWGTable1i);
DEFNEW3D("Per Gear Wastegate Table 2 Intelligent",PGWGTable2i);
DEFNEW3D("Per Gear Wastegate Table 1 Sport",PGWGTable1s);
DEFNEW3D("Per Gear Wastegate Table 2 Sport",PGWGTable2s);
DEFNEW3D("Per Gear Wastegate Table 1 Sport Sharp",PGWGTable1ss);
DEFNEW3D("Per Gear Wastegate Table 2 Sport Sharp",PGWGTable2ss);
#else
DEFNEW3D("Per Gear Wastegate Table 1",PGWGTable1i);
DEFNEW3D("Per Gear Wastegate Table 2",PGWGTable2i);
#endif
DEFINERAMVAR("MerpMod PGTB Compensation",PGTBComp,"float","E");
#if SWITCH_HACKS
DEFNEW3D("Per Gear Target Boost Table 1 Intelligent",PGTBTable1i);
DEFNEW3D("Per Gear Target Boost Table 2 Intelligent",PGTBTable2i);
DEFNEW3D("Per Gear Target Boost Table 1 Sport",PGTBTable1s);
DEFNEW3D("Per Gear Target Boost Table 2 Sport",PGTBTable2s);
DEFNEW3D("Per Gear Target Boost Table 1 Sport Sharp",PGTBTable1ss);
DEFNEW3D("Per Gear Target Boost Table 2 Sport Sharp",PGTBTable2ss);
#else
DEFNEW3D("Per Gear Target Boost Table 1",PGTBTable1i);
DEFNEW3D("Per Gear Target Boost Table 2",PGTBTable2i);
#endif
#if PROG_MODE
DEFNEW3D("Per Gear Target Boost Table Valet Mode",PGTBTableValetMode);
DEFNEW3D("Per Gear Wastegate Table Valet Mode",PGWGTableValetMode);
#endif

DEFINERAMVAR("MerpMod Max WGDC Per Gear Target",WGDCMaxTarget,"float","E");
DEFINERAMVAR("MerpMod Max WGDC Per Gear Output",WGDCMaxOutput,"float","E");
#if SWITCH_HACKS
DEFNEW3D("Max Wastegate Duty Compensation Table 1 Intelligent",WGDCMaxTable1i);
DEFNEW3D("Max Wastegate Duty Compensation Table 2 Intelligent",WGDCMaxTable2i);
DEFNEW3D("Max Wastegate Duty Compensation Table 1 Sport",WGDCMaxTable1s);
DEFNEW3D("Max Wastegate Duty Compensation Table 2 Sport",WGDCMaxTable2s);
DEFNEW3D("Max Wastegate Duty Compensation Table 1 Sport Sharp",WGDCMaxTable1ss);
DEFNEW3D("Max Wastegate Duty Compensation Table 2 Sport Sharp",WGDCMaxTable2ss);
#else
DEFNEW3D("Max Wastegate Duty Compensation Table 1",WGDCMaxTable1i);
DEFNEW3D("Max Wastegate Duty Compensation Table 2",WGDCMaxTable2i);
#endif

DEFINERAMVAR("MerpMod Initial WGDC Per Gear Target",WGDCInitialTarget,"float","E");
DEFINERAMVAR("MerpMod Initial WGDC Per Gear Output",WGDCInitialOutput,"float","E");
#if SWITCH_HACKS
DEFNEW3D("Initial Wastegate Duty Compensation Table 1 Intelligent",WGDCInitialTable1i);
DEFNEW3D("Initial Wastegate Duty Compensation Table 2 Intelligent",WGDCInitialTable2i);
DEFNEW3D("Initial Wastegate Duty Compensation Table 1 Sport",WGDCInitialTable1s);
DEFNEW3D("Initial Wastegate Duty Compensation Table 2 Sport",WGDCInitialTable2s);
DEFNEW3D("Initial Wastegate Duty Compensation Table 1 Sport Sharp",WGDCInitialTable1ss);
DEFNEW3D("Initial Wastegate Duty Compensation Table 2 Sport Sharp",WGDCInitialTable2ss);
#else
DEFNEW3D("Initial Wastegate Duty Compensation Table 1",WGDCInitialTable1i);
DEFNEW3D("Initial Wastegate Duty Compensation Table 2",WGDCInitialTable2i);
#endif

DEFINERAMVAR("MerpMod Target Boost Target",TargetBoostTarget,"float","E");
DEFINERAMVAR("MerpMod Target Boost Output",TargetBoostOutput,"float","E");
#if SWITCH_HACKS
DEFNEW3D("Target Boost Compensation Table 1 Intelligent",TargetBoostTable1i);
DEFNEW3D("Target Boost Compensation Table 2 Intelligent",TargetBoostTable2i);
DEFNEW3D("Target Boost Compensation Table 1 Sport",TargetBoostTable1s);
DEFNEW3D("Target Boost Compensation Table 2 Sport",TargetBoostTable2s);
DEFNEW3D("Target Boost Compensation Table 1 Sport Sharp",TargetBoostTable1ss);
DEFNEW3D("Target Boost Compensation Table 2 Sport Sharp",TargetBoostTable2ss);
#else
DEFNEW3D("Target Boost Compensation Table 1",TargetBoostTable1);
DEFNEW3D("Target Boost Compensation Table 2",TargetBoostTable2);
#endif

	#if WGDC_LOCK
DEFNEW1D("WGDC Lock Maximum RPM",RPMWGDCLock);
DEFNEW1D("WGDC Lock Minimum Throttle",ThrottleLockWGDC);
	#endif
#endif

#if TIMING_HACKS
DEFINERAMVAR("MerpMod LC Timing Mode",LCTimingMode,"uint8","E");
DEFINERAMVAR("MerpMod LC Timing Lock Value",LCTimingLock,"float","E");
DEFINERAMVAR("MerpMod LC Timing Retard",LCTimingRetard,"float","E");
DEFINERAMVAR("MerpMod LC Timing Retard Multiplier",LCTimingRetardMultiplier,"float","E");
DEFINERAMVAR("MerpMod Base Timing Final Target",BaseTimingTarget,"float","E");
DEFINERAMVAR("MerpMod Base Timing Final Output",BaseTimingOutput,"float","E");

DEFNEW1D("Timing Lookup Load/MAP",DefaultTimingLookupMAPLoad);
DEFNEW1D("Launch Control Timing Mode",DefaultLCTimingMode);
DEFNEW1D("Launch Control Timing Lock",DefaultLCTimingLock);
DEFNEW1D("Default Launch Control Timing Retard Multiplier",DefaultLCTimingRetardMultiplier);
DEFNEW3D("Launch Control Timing Retard Table",LCTimingRetardTable);

DEFNEW1D("Feedback Knock Correction Blended Retard Value 1",FBKCRetardValue1);
DEFNEW1D("Feedback Knock Correction Blended Retard Value 2",FBKCRetardValue2);
DEFNEW1D("Feedback Knock Correction Blended Retard Value Alternate 1",FBKCRetardValueAlternate1);
DEFNEW1D("Feedback Knock Correction Blended Retard Value Alternate 2",FBKCRetardValueAlternate2);

#if SWITCH_HACKS
DEFNEW1D("Timing Hack Enable",DefaultTimingHackEnabled);
DEFNEW2D("Timing Compensation A (IAT) Table 1", IntakeTempCompensationTable1);
DEFNEW2D("Timing Compensation A (IAT) Table 2", IntakeTempCompensationTable2);
DEFNEW3D("Base Timing Table 1 Intelligent(Ext)",TimingTable1i);
DEFNEW3D("Base Timing Table 2 Intelligent(Ext)",TimingTable2i);
DEFNEW3D("Base Timing Table 1 Sport(Ext)",TimingTable1s);
DEFNEW3D("Base Timing Table 2 Sport(Ext)",TimingTable2s);
DEFNEW3D("Base Timing Table 1 Sport Sharp(Ext)",TimingTable1ss);
DEFNEW3D("Base Timing Table 2 Sport Sharp(Ext)",TimingTable2ss);
DEFNEW3D("Knock Correction Retard Table 1 Intelligent(Ext)",KnockCorrectionRetardTable1i);
DEFNEW3D("Knock Correction Retard Table 2 Intelligent(Ext)",KnockCorrectionRetardTable2i);
DEFNEW3D("Knock Correction Retard Table 1 Sport(Ext)",KnockCorrectionRetardTable1s);
DEFNEW3D("Knock Correction Retard Table 2 Sport(Ext)",KnockCorrectionRetardTable2s);
DEFNEW3D("Knock Correction Retard Table 1 Sport Sharp(Ext)",KnockCorrectionRetardTable1ss);
DEFNEW3D("Knock Correction Retard Table 2 Sport Sharp(Ext)",KnockCorrectionRetardTable2ss);
#else
DEFNEW3D("Base Timing Table 1",TimingTable1i);
DEFNEW3D("Base Timing Table 2",TimingTable2i);
DEFNEW3D("Knock Correction Retard Table 1",KnockCorrectionRetardTable1i);
DEFNEW3D("Knock Correction Retard Table 2",KnockCorrectionRetardTable2i);
#endif

#endif

#if SUB_KCA_HACKS
#endif

#if POLF_HACKS
#endif

#if INJECTOR_HACKS
#endif

#if MEMORY_HACKS
#endif

#if DYN_RAMTUNING
DEFINERAMVAR("aijmod RAM Tune Max Tables",MaxDynRAMTables,"uint32","E");
DEFINERAM("aijmod RAM Tune End",pRamHoleEnd,"uint32","E");
#endif



const long endofdeffile __attribute__ ((section ("DefinitionDataEnd"),aligned(4))) = 0x00090009;
const long endofdeffile1 __attribute__ ((section ("DefinitionDataEnd"),aligned(4))) = 0x00090009;
const long endofdeffile2 __attribute__ ((section ("DefinitionDataEnd"),aligned(4))) = 0x00090009;
const long endofdeffile3 __attribute__ ((section ("DefinitionDataEnd"),aligned(4))) = 0x00090009;
