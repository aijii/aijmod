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

#include "enums.h"

//////////////////////////
//Function Prototypes
//////////////////////////

#if PORT_LOGGER
void PortLogger() ROMCODE;
void ADCLogger() ROMCODE;
#endif

#if RAM_HOLE_SCANNER
void RamHoleScanner() ROMCODE;
#endif

void MapSwitchSiDriveCheck() ROMCODE;
unsigned char TestTestModeSwitch() ROMCODE;
unsigned char TestDefogSwitch() ROMCODE;
unsigned char TestBrakeSwitch()	ROMCODE;
unsigned char TestClutchSwitch() ROMCODE;
unsigned char TestClutchSwitchDepressedEvent() ROMCODE;
unsigned char TestCruiseResumeSwitch() ROMCODE;
unsigned char TestCruiseCoastSwitch() ROMCODE;
void TestCruiseControlToggles() ROMCODE;

void Initializer()	ROMCODE;
void ClearRamVariables()	ROMCODE;
void PopulateRamVariables()	ROMCODE;
void ResetRamVariables() ROMCODE;
void InitRamVariables() ROMCODE;

void EcuHacksMain() ROMCODE;
void RevLimHook() ROMCODE;

float ComputeMassAirFlow(TwoDTable* MafScalingTable, float MafVoltage)  ROMCODE;
float CallSpeedDensityHook()  ROMCODE;
void CelDoubleRepeat(unsigned char * CelFlashes1, unsigned char Speed1, unsigned char * CelFlashes2, unsigned char Speed2, unsigned char Delay1, unsigned char Delay2)  ROMCODE;
void CelFlashStart(unsigned char CelFlashes, unsigned char Speed, unsigned char Delay, unsigned char Interrupt)  ROMCODE;
void CelFlash()	ROMCODE;
void WGDCHack(void) ROMCODE;
void TargetBoostHack(void) ROMCODE;
void InjectorHack() ROMCODE;
void POLFHack()  ROMCODE;
float TimingHack()  ROMCODE;
float Pull2DRamHook(float* table, float xLookup) ROMCODE;
float Pull2DRamHookTipInEnrich(float* table, float xLookup) ROMCODE;
float Pull2DRamHookCrankingFuel(float* table, float xLookup) ROMCODE;
float Pull2DRamHookStartupEnrich2(float* table, float xLookup) ROMCODE;
float Pull2DRamHookStartupEnrich3(float* table, float xLookup) ROMCODE;
float Pull2DRamHookFrontO2Scaling(float* table, float xLookup) ROMCODE;
float Pull3DRamHook(float* table, float xLookup, float yLookup) ROMCODE;
float Pull3DRamHookStartupEnrich1(float* table, float xLookup, float yLookup) ROMCODE;
float Pull2DRamHookIntakeTempCompensation(float* table, float xLookup) ROMCODE;
float Pull3DRamHookAVCSLookup(float* table, float xLookup, float yLookup) ROMCODE;
void VinCheck() ROMCODE;
void AutoPopulateRamTables() ROMCODE;

void ProgModeListener()  ROMCODE;
void ProgModeMain()  ROMCODE;
void ProgModeCruiseToggled(unsigned char) ROMCODE;

void LCAdjustCruiseToggled(unsigned char) ROMCODE;

#if !AUTO_TRANS
void SetClutch(int value) __attribute__ ((section ("Misc")));
#endif
void SetBrake(int value) __attribute__ ((section ("Misc")));

float Abs(float input) ROMCODE;
float LowPass(float input, float limit) ROMCODE;
float HighPass(float input, float limit) ROMCODE;
float BandPass(float input, float lowlim, float highlim) ROMCODE;
int BandPassInt(int input, int lowlim, int highlim) ROMCODE;
float Smooth(float smoothingFactor, float input, float previous) ROMCODE;

void RevLimCode() ROMCODE;
void RevLimReset() ROMCODE;

float GetBlendCurveRatio(unsigned char curve) ROMCODE;
float BlendAndSwitch(TableGroup tg, float xLookup, float yLookup) ROMCODE;
float BlendCurve(float xLookup, float yLookup,unsigned char curve) ROMCODE;
float BlendAndSwitchCurve(TableGroup tg, float xLookup, float yLookup, unsigned char curve) ROMCODE;
float SwitchSelect(TableSubSet tss, float xLookup, float yLookup) ROMCODE;
void InputUpdate() ROMCODE;
void MapBlendFailSafeCount() ROMCODE;
void UpdateMapBlendRatio(float inputVoltage) ROMCODE;
void MapSwitchThresholdCheck(float input) ROMCODE;
void UpdateFuelPressureInput(float InputVoltage) ROMCODE;
void FuelPressureDeltaCount() ROMCODE;
void UpdateWideBandLambdaInput(float InputVoltage) ROMCODE;
void LeanBoostCount() ROMCODE;
void UpdateFailSafes() ROMCODE;

//////////////////////////
//Extern Function Pointers
//////////////////////////
extern float (*Pull3DHooked)(ThreeDTable* table, float xLookup, float yLookup);
extern float (*Pull2DHooked)(TwoDTable* table, float xLookup);
extern float (*ShortToFloatHooked)(unsigned short input, float grad, float offs);
extern void (*RevLimDeleteHooked) ();

#define MafVoltageToInternalUnits 13107.20005368709

// Test utility functions.
void TestFailed(unsigned char *message) __attribute__ ((section ("Misc")));
void Assert(int condition, unsigned char *message) __attribute__ ((section ("Misc")));
int AreCloseEnough(float actual, float expected) __attribute__ ((section ("Misc")));


////////////////////
//TABLES
////////////////////

extern TableGroup VETableGroup;
extern ThreeDTable VolumetricEfficiencyTable1;
extern ThreeDTable VolumetricEfficiencyTable2;
extern ThreeDTable VolumetricEfficiencyRamTable;
extern ThreeDTable TemperatureCompensationTable;
extern ThreeDTable AtmosphericCompensationTable;
extern ThreeDTable SDBlendingTable;

extern short VE_DATA1[];
extern short VE_DATA2[];

extern TwoDTable MafScalingTable1;
extern TwoDTable MafScalingTable2;

extern TwoDTable InjectorScalingMultiplierTable;

extern unsigned char DefaultPolfHackEnabled;
extern TableGroup FuelTableGroup;
extern ThreeDTable FuelTable1i;
extern ThreeDTable FuelTable2i;
extern ThreeDTable FuelTable1s;
extern ThreeDTable FuelTable2s;
extern ThreeDTable FuelTable1ss;
extern ThreeDTable FuelTable2ss;
extern ThreeDTable LCFuelEnrichTable;

extern unsigned char F1SS_DATA[];
extern unsigned char F1S_DATA[];
extern unsigned char F1I_DATA[];
extern unsigned char F2SS_DATA[];
extern unsigned char F2S_DATA[];
extern unsigned char F2I_DATA[];

extern unsigned char DefaultLCFuelMode;
extern float DefaultLCFuelLock;
extern float DefaultLCFuelEnrichMultiplier;

extern TwoDTable FrontOxygenSensorScaling1;
extern TwoDTable FrontOxygenSensorScaling2;

extern unsigned char DefaultBoostHackEnabled;
extern TableGroup PGWGTableGroup;
extern ThreeDTable PGWGTable1i;
extern ThreeDTable PGWGTable2i;
extern ThreeDTable PGTBTable1s;
extern ThreeDTable PGTBTable2s;
extern ThreeDTable PGWGTable1ss;
extern ThreeDTable PGWGTable2ss;
extern ThreeDTable PGWGTableValetMode;

extern short PGWGData1ss[];
extern short PGWGData1s[];
extern short PGWGData1i[];
extern short PGWGData2ss[];
extern short PGWGData2s[];
extern short PGWGData2i[];

extern short PGTBData1ss[];
extern short PGTBData1s[];
extern short PGTBData1i[];
extern short PGTBData2ss[];
extern short PGTBData2s[];
extern short PGTBData2i[];


extern TableGroup PGTBTableGroup;
extern ThreeDTable PGTBTable1i;
extern ThreeDTable PGTBTable2i;
extern ThreeDTable PGWGTable1s;
extern ThreeDTable PGWGTable2s;
extern ThreeDTable PGTBTable1ss;
extern ThreeDTable PGTBTable2ss;
extern ThreeDTable PGTBTableValetMode;

extern TableGroup TargetBoostTableGroup;
extern ThreeDTable TargetBoostTable1i;
extern ThreeDTable TargetBoostTable2i;
extern ThreeDTable TargetBoostTable1s;
extern ThreeDTable TargetBoostTable2s;
extern ThreeDTable TargetBoostTable1ss;
extern ThreeDTable TargetBoostTable2ss;

extern TableGroup WGDCInitialTableGroup;
extern ThreeDTable WGDCInitialTable1i;
extern ThreeDTable WGDCInitialTable2i;
extern ThreeDTable WGDCInitialTable1s;
extern ThreeDTable WGDCInitialTable2s;
extern ThreeDTable WGDCInitialTable1ss;
extern ThreeDTable WGDCInitialTable2ss;

extern short WGDCInitialData1ss[];
extern short WGDCInitialData1s[];
extern short WGDCInitialData1i[];
extern short WGDCInitialData2ss[];
extern short WGDCInitialData2s[];
extern short WGDCInitialData2i[];

extern TableGroup WGDCMaxTableGroup;
extern ThreeDTable WGDCMaxTable1i;
extern ThreeDTable WGDCMaxTable2i;
extern ThreeDTable WGDCMaxTable1s;
extern ThreeDTable WGDCMaxTable2s;
extern ThreeDTable WGDCMaxTable1ss;
extern ThreeDTable WGDCMaxTable2ss;

extern short WGDCMaxData1ss[];
extern short WGDCMaxData1s[];
extern short WGDCMaxData1i[];
extern short WGDCMaxData2ss[];
extern short WGDCMaxData2s[];
extern short WGDCMaxData2i[];

extern ThreeDTable PGWGRamTable;
extern ThreeDTable PGTBRamTable;
extern ThreeDTable WGDCInitialRamTable;
extern ThreeDTable WGDCMaxRamTable;

extern ThreeDTable AVCSRamTable;

extern unsigned char DefaultTimingHackEnabled;

extern TwoDTable IntakeTempCompensationTable1;
extern TwoDTable IntakeTempCompensationTable2;
extern TableGroup TimingTableGroup;
extern ThreeDTable TimingTable1i;
extern ThreeDTable TimingTable2i;
extern ThreeDTable TimingTable1s;
extern ThreeDTable TimingTable2s;
extern ThreeDTable TimingTable1ss;
extern ThreeDTable TimingTable2ss;

extern unsigned char T1ss_DATA[];
extern unsigned char T1s_DATA[];
extern unsigned char T1i_DATA[];
extern unsigned char T2ss_DATA[];
extern unsigned char T2s_DATA[];
extern unsigned char T2i_DATA[];

extern TableGroup KnockCorrectionRetardTableGroup;
extern ThreeDTable KnockCorrectionRetardTable1i;
extern ThreeDTable KnockCorrectionRetardTable2i;
extern ThreeDTable KnockCorrectionRetardTable1s;
extern ThreeDTable KnockCorrectionRetardTable2s;
extern ThreeDTable KnockCorrectionRetardTable1ss;
extern ThreeDTable KnockCorrectionRetardTable2ss;

extern ThreeDTable LCTimingRetardTable;

extern float FBKCRetardValue1;
extern float FBKCRetardValue2;

extern float FBKCRetardValueAlternate1;
extern float FBKCRetardValueAlternate2;

extern unsigned char FailSafeFuelAdditive;
extern unsigned char FailSafeFuelAdditive;
extern unsigned char EGTFailSafeFuelAdditiveEnable;
extern unsigned char CoolantTempFailSafeFuelAdditiveEnable;
extern unsigned char FBKCHiFailSafeFuelAdditiveEnable;
extern unsigned char LeanBoostFailSafeFuelAdditiveEnable;

extern unsigned char EGTFailSafeValetModeEnable;
extern unsigned char CoolantTempFailSafeValetModeEnable;
extern unsigned char FBKCHiFailSafeValetModeEnable;
extern unsigned char LeanBoostFailSafeValetModeEnable;
extern unsigned char FuelPressureDeltaFailSafeValetModeEnable;
extern unsigned char InjectorDutyCycleFailSafeValetModeEnable;

extern unsigned char UseInjectorLatency;

extern float RPMLockWGDC;
extern float ThrottleLockWGDC;

extern float GearRatios[6];

extern float FFSMinimumThrottle;
extern float LCMinimumThrottle;

#if SD_DMAP
extern ThreeDTable SDDeltaMapTable;
#endif

extern float CelsiusToKelvin;
extern float Displacement;
extern float SpeedDensityConstant;
extern unsigned char DefaultMafMode;

extern unsigned char DefaultTimingLookupMAPLoad;
extern unsigned char DefaultFuelingLookupMAPLoad;
extern unsigned char DefaultAVCSLookupMAPLoad;
extern unsigned char DefaultLCTimingMode;
extern float DefaultLCTimingLock;
extern float DefaultLCTimingRetardMultiplier;
extern float DefaultMaxSubtractiveKCA;

extern float DefaultInjectorScaling;

extern float RPMLockWGDC;
extern float ThrottleLockWGDC;

extern float DefaultBlend;
extern int IAMFailSafe;

//Spark Cut defaults
extern char* LCSparkCutFlag;
extern char* LCSparkEventsToCut;
extern char* LCSparkEventsCutFrom;
extern unsigned char DefaultLCSparkEventsToCut;
extern unsigned char DefaultLCSparkEventsCutFrom;

//CEL flahs defaults
extern unsigned char FBKCLoFlashes;
extern unsigned char FBKCLoFlashSpeed;
extern unsigned char FBKCHiFlashes;
extern unsigned char FBKCHiFlashSpeed;
extern unsigned char EGTFlashes;
extern unsigned char EGTFlashSpeed;
extern unsigned char IAMFlashSpeed;
extern unsigned char IAMFlashes;
extern unsigned char MapBlendFlashSpeed;
extern unsigned char MapBlendFlashes;
extern unsigned char LeanBoostFlashSpeed;
extern unsigned char LeanBoostFlashes;
extern unsigned char FuelPressureDeltaFlashSpeed;
extern unsigned char FuelPressureDeltaFlashes;
extern float FuelPressureTriggerMinRPM;
extern unsigned char InjectorDutyCycleFlashSpeed;
extern unsigned char InjectorDutyCycleFlashes;

extern float IAMFlashThreshold;
extern unsigned char ECTFlashes;
extern unsigned char ECTFlashSpeed;
extern float ECTFlashThreshold;
extern float FBKCLoThreshold;
extern float FBKCHiThreshold;
extern float FBKCLoadThreshold;
extern float EGTCelLoadThreshold;
extern float EGTResistanceThreshold;


//Rev Limiter Defaults
extern unsigned char DefaultRevLimMode;
extern unsigned char DefaultFlatFootShiftMode;
extern float DefaultRedLineCut;
extern float DefaultRedLineHyst;
extern float DefaultLaunchControlSpeedMax;
extern float DefaultLaunchControlCut;
extern float DefaultLaunchControlHyst;
extern float DefaultFlatFootShiftAutoDelta;
extern float DefaultFlatFootShiftStaticDelta;
extern float DefaultFlatFootShiftHyst;
extern float DefaultFlatFootShiftSpeedThreshold;
extern float DefaultFlatFootShiftRpmThreshold;
extern float LCAdjustStep;

extern float ValetModeRevLim;

extern unsigned char DefaultRamTuneTableBlend;
extern unsigned char DefaultRamTuneTableSwitch;
extern ThreeDTable AVCSRamTable;



#if VIN_HACKS
extern const VinBlockStruct VinBlock;
extern unsigned char Licensee[];
#endif

#if SWITCH_HACKS
extern unsigned char DefaultMapSwitch;
extern float DefaultMapBlendRatio;



/*
extern float LeftTGVInputSmoothingFactor;
extern float RightTGVInputSmoothingFactor;

extern float LeftTGVInputMultiplier;
extern float RightTGVInputMultiplier;
extern float RearO2InputMultiplier;

extern float LeftTGVInputOffset;
extern float RightTGVInputOffset;
extern float RearO2InputOffset;

extern float LeftTGVInputThreshold;
extern float RightTGVInputThreshold;
*/
extern float BlendInputMinimumVolts;
extern float BlendInputMaximumVolts;
extern unsigned char MapBlendFailSafe;
extern unsigned short MapBlendCount;
extern float MapBlendSmoothingFactor;
extern float MapSwitchSmoothingFactor;
extern float MapBlendBoostContentLock;
extern float BaseFuelPressure;

unsigned char OpenLoopFuelingBlendCurveSwitch;
unsigned char ClosedLoopFuelingBlendCurveSwitch;
unsigned char TimingBlendCurveSwitch;
unsigned char KnockControlBlendCurveSwitch;
unsigned char WastegateDutyBlendCurveSwitch;
unsigned char BoostBlendCurveSwitch;
unsigned char MassAirFlowScalingBlendCurveSwitch;
unsigned char SpeedDensityBlendCurveSwitch;

extern TwoDTable MapBlendScaling;
extern float MapSwitchThresholdLo;
extern float MapSwitchThresholdHi;

extern unsigned char DefaultMapBlendingInputMode;
extern unsigned char DefaultMapSwitchingInputMode;

extern TwoDTable MapBlendCurve1;
extern TwoDTable MapBlendCurve2;
extern TwoDTable MapBlendCurve3;
extern TwoDTable MapBlendCurve4;

extern ThreeDTable TipInEnrichMultiplier;
extern ThreeDTable CrankingFuelMultiplier;
extern ThreeDTable StartupEnrichMultiplier;

extern unsigned char WideBandLambdaInputMode;
extern unsigned char FuelPressureInputMode;
extern float WidebandSensorSmoothingFactor;
extern float FuelPressureSensorSmoothingFactor;

extern unsigned short LeanBoostDelay;
extern float LeanBoostAFRThreshold;
extern float LeanBoostMRPThreshold;
extern float InjectorDutyCycleThreshold;

extern unsigned short FuelPressureDeltaDelay;
extern float FuelPressureDeltaThreshold;


extern TwoDTable WideBandScaling;
extern TwoDTable FuelPressureScaling;



#endif

extern long RomHoleEndMarker;
extern unsigned char ModIdentifier[];