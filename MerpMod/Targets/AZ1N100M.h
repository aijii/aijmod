#define MOD_IDENTIFIER STRI(AZ1N100M.MeRpMoD.Switch.Testing.v00.60.d16.4.28.0807)
#define MOD_ECUID EB99006023
#define MOD_DATE 16.4.28.0807
#include "Switch.h"
#define MOD_CONFIG Switch
#define MOD_BUILD Testing
#define MOD_RELEASE 0
#define ECU_CALIBRATION_ID AZ1N100M
#define ECU_IDENTIFIER 8B32783107
/////////////////////
// NonSpecific Rom Info and Routines
/////////////////////

#define dCalId (0x00002004)
#define dEcuId (0xD9860)
#define dRomHoleStart (0x000DC193)
#define pRamHoleStart (0xFFFFA840)
#define pRamHoleEnd (0xFFFFBF50)
#define sPull2DFloat (0x000BE9E8)
#define sPull3DFloat (0x000BEA9C)

/////////////////////
// Switch Hacks
/////////////////////

#define pSiDrive ((unsigned char*)0xFFFF60C2)
#define pTGVLeftVoltage ((unsigned short*)0xFFFF4046)
#define pTGVRightVoltage ((unsigned short*)0xFFFF403A)
#define pRearO2Voltage ((float*)0xFFFF4404)
#define sShortToFloat (0x000BE750)
#define hPull2DTipInEnrich (0x3DEE0)
#define tTipInEnrich (0x98DC8)
#define tTipInEnrich2 (0x98DDC)
#define hPull2DCrankingFuel (0x34494)
#define tCrankingFuelA (0x98364)
#define tCrankingFuelB (0x98378)
#define tCrankingFuelC (0x9838C)
#define tCrankingFuelD (0x983A0)
#define tCrankingFuelE (0x983B4)
#define tCrankingFuelF (0x983C8)
#define hPull3DStartupEnrich1 (0x3530C)
#define tStartupEnrich1Cruise (0x99058)
#define tStartupEnrich1NonCruise (0x9903C)
#define hPull2DStartupEnrich2 (0x3519C)
#define tStartupEnrich2_1A (0x98438)
#define tStartupEnrich2_1B (0x98474)
#define tStartupEnrich2_2A (0x9849C)
#define tStartupEnrich2_2B (0x984D8)
#define hPull2DStartupEnrich3 (0x34E24)
#define tStartupEnrich3_1A (0x983DC)
#define tStartupEnrich3_1B (0x983F0)
#define tStartupEnrich3_2A (0x98404)
#define tStartupEnrich3_2B (0x98418)
#define hPull2DFrontO2Scaling (0x5B7F8)
#define tFrontO2Scaling (0x9AD78)

/////////////////////
// Rev Limit Hack
/////////////////////

#define hRevLimDelete (0x4CBD4)
#define sRevLimStart (0x3EAC8)
#define sRevLimEnd (0x3EB0C)
#define pFlagsRevLim ((unsigned char*)0xFFFF7B18)
#define RevLimBitMask (0x01)

/////////////////////
// Speed Density Hack
/////////////////////

#define hMafCalc (0x4800)
#define sMafCalc (0x47A4)

/////////////////////
// Injector Hack
/////////////////////

#define dInjectorScaling ((float*)0xCB440)
#define hInjectorScaling (0x34B5C)

/////////////////////
// Cel Hacks
/////////////////////

#define sCelTrigger (0x8B954)
#define hCelSignal (0x8B9D8)
#define pCelSignalOem ((unsigned char*)0xFFFFA0CA)

/////////////////////
// Boost Hacks
/////////////////////

#define hPullTargetBoost (0x00014318)
#define hTableTargetBoost (0x00014314)
#define tTargetBoost (0x9644C)

/////////////////////
// WGDC Hacks
/////////////////////

#define hPullWgdc (0x14628)
#define hWgdc (0x4C678)
#define sWgdc (0x13E50)
#define hTableWgdcInitial (0x14624)
#define tWgdcInitial (0x96430)
#define hTableWgdcMax (0x14644)
#define tWgdcMax (0x96414)

/////////////////////
// Primary Open Loop Fueling Hacks
/////////////////////

#define pPolf4Byte (0xFFFF7800)
#define hPull3DPolf (0x39AD0)
#define hPolf (0x4CBF8)
#define sPolf (0x3987C)
#define pPolfEnrich (0xFFFF7800)
#define tPolfKcaAlt (0x990C8)
#define hTablePolfKcaAlt (0x39ACC)
#define tPolfKcaBLo (0x9911C)
#define hTablePolfKcaBLo (0x39AE4)
#define tPolfKcaBHi (0x99138)
#define hTablePolfKcaBHi (0x39AE8)

/////////////////////
// Timing Hacks
/////////////////////

#define hBaseTiming (0x4CCBC)
#define pBaseTiming (0xFFFF7D3C)
#define sBaseTiming (0x42C10)
#define hPull3DTiming (0x42EB0)
#define tBaseTimingPCruise (0x99C44)
#define hTableBaseTimingPCruise (0x42EAC)
#define tBaseTimingPNonCruise (0x99C60)
#define hTableBaseTimingPNonCruise (0x42EB8)
#define tBaseTimingRCruiseAvcs (0x99C7C)
#define hTableBaseTimingRCruiseAvcs (0x42EB4)
#define tBaseTimingRNonCruiseAvcs (0x99C98)
#define hTableBaseTimingRNonCruiseAvcs (0x42EBC)
#define pKcaIam (0xFFFF8068)
#define hFBKCRetardValue (0x46D54)
#define dFBKCRetardValue ((float*)0xD1EB8)
#define hFBKCRetardValueAlternate (0x46AE4)
#define dFBKCRetardValueAlternate ((float*)0xD1EC8)

/////////////////////
// Spark Cut
/////////////////////


/////////////////////
// Flags-Signals
/////////////////////

#define pResumeFlags ((unsigned char*)0xFFFF61B7)
#define ResumeBitMask ((unsigned char)0x01)
#define pCoastFlags ((unsigned char*)0xFFFF61B6)
#define CoastBitMask ((unsigned char)0x01)
#define pBrakeFlags ((unsigned char*)0xFFFF61B8)
#define BrakeBitMask ((unsigned char)0x01)
#define pClutchFlags ((unsigned char*)0xFFFF67BF)
#define ClutchBitMask ((unsigned char)0x01)
#define pTestModeFlags ((unsigned char*)0xFFFF679C)
#define TestModeBitMask ((unsigned char)0x01)
#define pDefogFlags ((unsigned char*)0xFFFF67B7)
#define DefogBitMask ((unsigned char)0x01)

/////////////////////
// NonSpecific Engine params
/////////////////////

#define pFbkc1 ((unsigned char*)0xFFFF6F15)
#define pFbkc4 ((float*)0xFFFF7FF8)
#define pIam1 ((unsigned char*)0xFFFF6F17)
#define pIam4 ((float*)0xFFFF2E70)
#define pEngineSpeed ((float*)0xFFFF6CB0)
#define pVehicleSpeed ((float*)0xFFFF6C8C)
#define pCoolantTemp ((float*)0xFFFF4144)
#define pAtmoPress ((float*)0xFFFF6F38)
#define pManifoldAbsolutePressure ((float*)0xFFFF67F0)
#define pManifoldRelativePressure ((float*)0xFFFF67F4)
#define pInjectorPulseWidth ((float*)0xFFFF7BF0)
#define pInjectorLatency ((float*)0xFFFF72DC)
#define pIntakeAirTemp ((float*)0xFFFF4128)
#define pMassAirFlow ((float*)0xFFFF40B4)
#define pMafSensorVoltage ((short*)0xFFFF4042)
#define pEngineLoad ((float*)0xFFFF69D8)
#define pReqTorque ((float*)0xFFFF8374)
#define pThrottlePlate ((float*)0xFFFF68B8)
#define pCurrentGear ((unsigned char*)0xFFFF6EA3)
#define pAf1Res ((float*)0xFFFF40C8)

/////////////////////
// OBD Experimental stuff
/////////////////////

#define pObdVinDirect ((unsigned char*)0xFFFF2004)

/////////////////////
// New Definitions
/////////////////////

#define dLoadSmoothingA (0xC4D6C)
#define dLoadSmoothingB (0xC4D68)
#define dLoadSmoothingAlt (0xC4D64)
#define dLoadSmoothingFinal (0xC4D78)

/////////////////////
// Memory Reset
/////////////////////

#define sMemoryReset (0xFFEC)
#define hMemoryReset (0xFA44)
#define pMemoryResetLimit (0xFFFFBF9F)
#define hMemoryResetLimit (0x00011C58)

