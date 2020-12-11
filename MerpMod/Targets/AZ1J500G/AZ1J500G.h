#define MOD_IDENTIFIER STRI(AZ1J500G.MeRpMoD.Switch.Testing.v01.40.d17.2.18.1749)
#define MOD_ECUID 28D8014023
#define MOD_DATE 17.2.18.1749
#include "Switch.h"
#define MOD_CONFIG Switch
#define MOD_BUILD Testing
#define MOD_RELEASE 0
#define ECU_CALIBRATION_ID AZ1J500G
#define ECU_IDENTIFIER 7442594007
/////////////////////
// NonSpecific Rom Info and Routines
/////////////////////

#define dCalId (0x00002004)
#define dEcuId (0x000D5310)
#define dRomHoleStart (0x000E1000)
#define pRamHoleStart (0xFFFFA7E0)
#define sPull2DFloat (0x000BE774)
#define sPull3DFloat (0x000BE828)

/////////////////////
// Switch Hacks
/////////////////////

#define pSiDrive ((unsigned char*)0xFFFF6186)
#define pTGVLeftVoltage ((unsigned short*)0xFFFF4046)
#define pTGVRightVoltage ((unsigned short*)0xFFFF403A)
#define pRearO2Voltage ((float*)0xFFFF43FC)
#define sShortToFloat (0x000BE4DC)
#define hPull2DTipInEnrich (0x35650)
#define tTipInEnrich (0x8C388)
#define tTipInEnrich2 (0x8C39C)
#define hPull2DCrankingFuel (0x2C03C)
#define tCrankingFuelA (0x8B924)
#define tCrankingFuelB (0x8B938)
#define tCrankingFuelC (0x8B94C)
#define tCrankingFuelD (0x8B960)
#define tCrankingFuelE (0x8B974)
#define tCrankingFuelF (0x8B988)
#define hPull3DStartupEnrich1 (0x2CEB4)
#define tStartupEnrich1Cruise (0x8C618)
#define tStartupEnrich1NonCruise (0x8C5FC)
#define hPull2DStartupEnrich2 (0x2CD44)
#define tStartupEnrich2_1A (0x8B9F8)
#define tStartupEnrich2_1B (0x8BA34)
#define tStartupEnrich2_2A (0x8BA5C)
#define tStartupEnrich2_2B (0x8BA98)
#define hPull2DStartupEnrich3 (0x2C9CC)
#define tStartupEnrich3_1A (0x8B99C)
#define tStartupEnrich3_1B (0x8B9B0)
#define tStartupEnrich3_2A (0x8B9C4)
#define tStartupEnrich3_2B (0x8B9D8)
#define hPull2DFrontO2Scaling (0x51BC8)
#define tFrontO2Scaling (0x8E1E8)

/////////////////////
// Rev Limit Hack
/////////////////////

#define hRevLimDelete (0x000440F8)
#define sRevLimStart (0x000363E0)
#define sRevLimEnd (0x00036420)
#define pFlagsRevLim ((unsigned char*)0xFFFF76FC)
#define RevLimBitMask (0x01)

/////////////////////
// Speed Density Hack
/////////////////////

#define hMafCalc (0x000049E8)
#define sMafCalc (0x0000498C)

/////////////////////
// Injector Hack
/////////////////////

#define dInjectorScaling ((float*)0x000C7DDC)
#define hInjectorScaling (0x0002C704)

/////////////////////
// Cel Hacks
/////////////////////

#define sCelTrigger (0x0007FA40)
#define hCelSignal (0x0007FAC4)
#define pCelSignalOem ((unsigned char*)0xFFFF9C12)

/////////////////////
// Boost Hacks
/////////////////////

#define hPullTargetBoost (0x00013F48)
#define hTableTargetBoost (0x00013F44)
#define tTargetBoost (0x0008A208)

/////////////////////
// WGDC Hacks
/////////////////////

#define hPullWgdc (0x0001440C)
#define hWgdc (0x00043BF8)
#define sWgdc (0x00013C94)
#define hTableWgdcInitial (0x00014408)
#define tWgdcInitial (0x0008A1EC)
#define hTableWgdcMax (0x00014428)
#define tWgdcMax (0x0008A1D0)

/////////////////////
// Primary Open Loop Fueling Hacks
/////////////////////

#define pPolf4Byte (0xFFFF73EC)
#define hPull3DPolf (0x00031658)
#define hPolf (0x00042C98)
#define sPolf (0x000313F2)
#define pPolfEnrich (0xFFFF73EC)
#define tPolfKcaAlt (0x0008C688)
#define hTablePolfKcaAlt (0x00031654)
#define tPolfKcaBLo (0x0008C6DC)
#define hTablePolfKcaBLo (0x0003166C)
#define tPolfKcaBHi (0x0008C6F8)
#define hTablePolfKcaBHi (0x00031670)

/////////////////////
// Timing Hacks
/////////////////////

#define hBaseTiming (0x000441E0)
#define pBaseTiming (0xFFFF791C)
#define sBaseTiming (0x0003A444)
#define hPull3DTiming (0x0003A6E4)
#define tBaseTimingPCruise (0x0008D204)
#define hTableBaseTimingPCruise (0x0003A6E0)
#define tBaseTimingPNonCruise (0x0008D220)
#define hTableBaseTimingPNonCruise (0x0003A6EC)
#define tBaseTimingRCruiseAvcs (0x0008D23C)
#define hTableBaseTimingRCruiseAvcs (0x0003A6E8)
#define tBaseTimingRNonCruiseAvcs (0x0008D258)
#define hTableBaseTimingRNonCruiseAvcs (0x0003A6F0)
#define pKcaIam (0xFFFF7C44)
#define hFBKCRetardValue (0x3E4B0)
#define dFBKCRetardValue ((float*)0xCE790)
#define hFBKCRetardValueAlternate (0x3E240)
#define dFBKCRetardValueAlternate ((float*)0xCE7A0)

/////////////////////
// Spark Cut
/////////////////////


/////////////////////
// Flags-Signals
/////////////////////

#define pResumeFlags ((unsigned char*)0xFFFF622B)
#define ResumeBitMask ((unsigned char)0x01)
#define pCoastFlags ((unsigned char*)0xFFFF622A)
#define CoastBitMask ((unsigned char)0x01)
#define pBrakeFlags ((unsigned char*)0xFFFF622C)
#define BrakeBitMask ((unsigned char)0x01)
#define pClutchFlags ((unsigned char*)0xFFFF683B)
#define ClutchBitMask ((unsigned char)0x01)
#define pTestModeFlags ((unsigned char*)0xFFFF6818)
#define TestModeBitMask ((unsigned char)0x01)
#define pDefogFlags ((unsigned char*)0xFFFF6833)
#define DefogBitMask ((unsigned char)0x01)

/////////////////////
// NonSpecific Engine params
/////////////////////

#define pFbkc1 ((unsigned char*)0xFFFF6ADD)
#define pFbkc4 ((float*)0xFFFF7BD4)
#define pIam1 ((unsigned char*)0xFFFF6ADF)
#define pIam4 ((float*)0xFFFF2DE4)
#define pEngineSpeed ((float*)0xFFFF688C)
#define pVehicleSpeed ((float*)0xFFFF6868)
#define pCoolantTemp ((float*)0xFFFF4140)
#define pAtmoPress ((float*)0xFFFF6B00)
#define pManifoldAbsolutePressure ((float*)0xFFFF6470)
#define pManifoldRelativePressure ((float*)0xFFFF6474)
#define pInjectorPulseWidth ((float*)0xFFFF77D0)
#define pInjectorLatency ((float*)0xFFFF6E68)
#define pIntakeAirTemp ((float*)0xFFFF4128)
#define pMassAirFlow ((float*)0xFFFF40B4)
#define pMafSensorVoltage ((short*)0xFFFF4042)
#define pEngineLoad ((float*)0xFFFF664C)
#define pReqTorque ((float*)0xFFFF7F38)
#define pThrottlePlate ((float*)0xFFFF6540)
#define pCurrentGear ((unsigned char*)0xFFFF6A79)
#define pAf1Res ((float*)0xFFFF40C8)

/////////////////////
// OBD Experimental stuff
/////////////////////

#define pObdVinDirect ((unsigned char*)0xFFFF2004)

/////////////////////
// New Definitions
/////////////////////

#define dLoadSmoothingA (0x000C2A1C)
#define dLoadSmoothingB (0x000C2A18)
#define dLoadSmoothingAlt (0x000C2A14)
#define dLoadSmoothingFinal (0x000C2A28)

/////////////////////
// Memory Reset
/////////////////////

#define sMemoryReset (0x000100C0)
#define hMemoryReset (0x0000FB18)
#define pMemoryResetLimit (0xFFFFBF9F)
#define hMemoryResetLimit (0x00011A64)

