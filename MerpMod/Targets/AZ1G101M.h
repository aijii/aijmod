#define MOD_IDENTIFIER STRI(AZ1G101M.MeRpMoD.Switch.Testing.v00.60.d16.5.22.2146)
#define MOD_ECUID F9A5006023
#define MOD_DATE 16.5.22.2146
#include "Switch.h"
#define MOD_CONFIG Switch
#define MOD_BUILD Testing
#define MOD_RELEASE 0
#define ECU_CALIBRATION_ID AZ1G101M
#define ECU_IDENTIFIER 5C42584007
/////////////////////
// NonSpecific Rom Info and Routines
/////////////////////

#define dCalId (0x00002004)
#define dEcuId (0x000D44F0)
#define dRomHoleStart (0x000E1200)
#define pRamHoleStart (0xFFFFA700)
#define pRamHoleEnd (0xFFFFBF70)
#define sPull2DFloat (0x000BE844)
#define sPull3DFloat (0x000BE8F8)

/////////////////////
// Switch Hacks
/////////////////////

#define pSiDrive ((unsigned char*)0xFFFF6166)
#define pTGVLeftVoltage ((unsigned short*)0xFFFF404A)
#define pTGVRightVoltage ((unsigned short*)0xFFFF403E)
#define pRearO2Voltage ((float*)0xFFFF43F8)
#define sShortToFloat (0x000BE5AC)
#define hPull2DTipInEnrich (0x343AC)
#define tTipInEnrich (0x86D6C)
#define tTipInEnrich2 (0x86D80)
#define hPull2DCrankingFuel (0x2AEEC)
#define tCrankingFuelA (0x000862F4)
#define tCrankingFuelB (0x00086308)
#define tCrankingFuelC (0x0008631C)
#define tCrankingFuelD (0x00086330)
#define tCrankingFuelE (0x00086344)
#define tCrankingFuelF (0x00086358)
#define hPull3DStartupEnrich1 (0x2BD64)
#define tStartupEnrich1Cruise (0x86FFC)
#define tStartupEnrich1NonCruise (0x86FE0)
#define hPull2DStartupEnrich2 (0x2BBF4)
#define tStartupEnrich2_1A (0x863C8)
#define tStartupEnrich2_1B (0x86404)
#define tStartupEnrich2_2A (0x8642C)
#define tStartupEnrich2_2B (0x86468)
#define hPull2DStartupEnrich3 (0x2B87C)
#define tStartupEnrich3_1A (0x8636C)
#define tStartupEnrich3_1B (0x86380)
#define tStartupEnrich3_2A (0x86394)
#define tStartupEnrich3_2B (0x863A8)
#define hPull2DFrontO2Scaling (0x506B0)
#define tFrontO2Scaling (0x88BE8)

/////////////////////
// Rev Limit Hack
/////////////////////

#define hRevLimDelete (0x00042D1C)
#define sRevLimStart (0x000351C0)
#define sRevLimEnd (0x00035200)
#define pFlagsRevLim ((unsigned char*)0xFFFF7788)
#define RevLimBitMask (0x01)

/////////////////////
// Speed Density Hack
/////////////////////

#define hMafCalc (0x00004B10)
#define sMafCalc (0x00004AB4)

/////////////////////
// Injector Hack
/////////////////////

#define dInjectorScaling ((float*)0x000C76C8)
#define hInjectorScaling (0x0002B5B4)

/////////////////////
// Cel Hacks
/////////////////////

#define sCelTrigger (0x0007AAB4)
#define hCelSignal (0x0007AB8C)
#define pCelSignalOem ((unsigned char*)0xFFFF997E)

/////////////////////
// Boost Hacks
/////////////////////

#define hPullTargetBoost (0x00014218)
#define hTableTargetBoost (0x00014214)
#define tTargetBoost (0x00084C70)

/////////////////////
// WGDC Hacks
/////////////////////

#define hPullWgdc (0x000146FC)
#define hWgdc (0x00042848)
#define sWgdc (0x00013F64)
#define hTableWgdcInitial (0x000146F8)
#define tWgdcInitial (0x00084C54)
#define hTableWgdcMax (0x00014718)
#define tWgdcMax (0x00084C38)

/////////////////////
// Primary Open Loop Fueling Hacks
/////////////////////

#define pPolf4Byte (0xFFFF7478)
#define hPull3DPolf (0x00030300)
#define hPolf (0x00042D40)
#define sPolf (0x000300AC)
#define pPolfEnrich (0xFFFF7478)
#define tPolfKcaAlt (0x0008706C)
#define hTablePolfKcaAlt (0x000302FC)
#define tPolfKcaBLo (0x000870C0)
#define hTablePolfKcaBLo (0x00030314)
#define tPolfKcaBHi (0x000870DC)
#define hTablePolfKcaBHi (0x00030318)

/////////////////////
// Timing Hacks
/////////////////////

#define hBaseTiming (0x0042E04)
#define pBaseTiming (0xFFFF79A8)
#define sBaseTiming (0x000391B2)
#define hPull3DTiming (0x000394C4)
#define tBaseTimingPCruise (0x00087D14)
#define hTableBaseTimingPCruise (0x000394C0)
#define tBaseTimingPNonCruise (0x00087D30)
#define hTableBaseTimingPNonCruise (0x000394CC)
#define tBaseTimingRCruiseAvcs (0x00087D4C)
#define hTableBaseTimingRCruiseAvcs (0x000394C8)
#define tBaseTimingRNonCruiseAvcs (0x00087D68)
#define hTableBaseTimingRNonCruiseAvcs (0x000394D0)
#define pKcaIam (0xFFFF7CD0)
#define hFBKCRetardValue (0x3D2AC)
#define dFBKCRetardValue ((float*)0xCDE0C)
#define hFBKCRetardValueAlternate (0x3D03C)
#define dFBKCRetardValueAlternate ((float*)0xCDE1C)

/////////////////////
// Spark Cut
/////////////////////


/////////////////////
// Flags-Signals
/////////////////////

#define pResumeFlags ((unsigned char*)0xFFFF61F4)
#define ResumeBitMask ((unsigned char)0x01)
#define pCoastFlags ((unsigned char*)0xFFFF61F3)
#define CoastBitMask ((unsigned char)0x01)
#define pBrakeFlags ((unsigned char*)0xFFFF61F8)
#define BrakeBitMask ((unsigned char)0x01)
#define pClutchFlags ((unsigned char*)0xFFFF67DB)
#define ClutchBitMask ((unsigned char)0x01)
#define pTestModeFlags ((unsigned char*)0xFFFF67B8)
#define TestModeBitMask ((unsigned char)0x01)
#define pDefogFlags ((unsigned char*)0xFFFF67D3)
#define DefogBitMask ((unsigned char)0x01)

/////////////////////
// NonSpecific Engine params
/////////////////////

#define pFbkc1 ((unsigned char*)0xFFFF6A69)
#define pFbkc4 ((float*)0xFFFF7C60)
#define pIam1 ((unsigned char*)0xFFFF6A6B)
#define pIam4 ((float*)0xFFFF2D1C)
#define pEngineSpeed ((float*)0xFFFF682C)
#define pVehicleSpeed ((float*)0xFFFF6808)
#define pCoolantTemp ((float*)0xFFFF413C)
#define pAtmoPress ((float*)0xFFFF6A88)
#define pManifoldAbsolutePressure ((float*)0xFFFF6438)
#define pManifoldRelativePressure ((float*)0xFFFF643C)
#define pInjectorPulseWidth ((float*)0xFFFF785C)
#define pInjectorLatency ((float*)0xFFFF6F64)
#define pIntakeAirTemp ((float*)0xFFFF4124)
#define pMassAirFlow ((float*)0xFFFF40B4)
#define pMafSensorVoltage ((short*)0xFFFF4046)
#define pEngineLoad ((float*)0xFFFF6610)
#define pReqTorque ((float*)0xFFFF7FC4)
#define pThrottlePlate ((float*)0xFFFF6500)
#define pCurrentGear ((unsigned char*)0xFFFF6A19)
#define pAf1Res ((float*)0xFFFF40C8)

/////////////////////
// OBD Experimental stuff
/////////////////////

#define pObdVinDirect ((unsigned char*)0xFFFF2004)

/////////////////////
// New Definitions
/////////////////////

#define dLoadSmoothingA (0x000C2D7C)
#define dLoadSmoothingB (0x000C2D78)
#define dLoadSmoothingAlt (0x000C2D74)
#define dLoadSmoothingFinal (0x000C2D88)

/////////////////////
// Memory Reset
/////////////////////

#define sMemoryReset (0x000102A4)
#define hMemoryReset (0x0000FC04)
#define pMemoryResetLimit (0xFFFFBF9F)
#define hMemoryResetLimit (0x00011C58)

