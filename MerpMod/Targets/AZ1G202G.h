#define MOD_IDENTIFIER STRI(AZ1G202G.MeRpMoD.Switch.Debug.v01.60.d19.7.14.1214)
#define MOD_ECUID 9964016013
#define MOD_DATE 19.7.14.1214
#include "Switch.h"
#define MOD_CONFIG Switch
#define MOD_BUILD Debug
#define MOD_RELEASE 0
#define ECU_CALIBRATION_ID AZ1G202G
#define ECU_IDENTIFIER 5A42784207
/////////////////////
// NonSpecific Rom Info and Routines
/////////////////////

#define dCalId (0x00002004)
#define dEcuId (0x000D4C4C)
#define dRomHoleStart (0x000E1400)
#define pRamHoleStart (0xFFFFA840)
#define pRamHoleEnd (0xFFFFBF50)
#define sPull2DFloat (0x000BE804)
#define sPull3DFloat (0x000BE8B8)

/////////////////////
// Switch Hacks
/////////////////////

#define pSiDrive ((unsigned char*)0xFFFF611E)
#define pTGVLeftVoltage ((unsigned short*)0xFFFF404A)
#define pTGVRightVoltage ((unsigned short*)0xFFFF403E)
#define pRearO2Voltage ((float*)0xFFFF43F8)
#define sShortToFloat (0x000BE56C)
#define hPull2DTipInEnrich (0x33FC0)
#define tTipInEnrich (0x88D24)
#define tTipInEnrich2 (0x88D38)
#define hPull2DCrankingFuel (0x2A98C)
#define tCrankingFuelA (0x000882D4)
#define tCrankingFuelB (0x000882E8)
#define tCrankingFuelC (0x000882FC)
#define tCrankingFuelD (0x00088310)
#define tCrankingFuelE (0x00088324)
#define tCrankingFuelF (0x00088338)
#define hPull3DStartupEnrich1 (0x2B804)
#define tStartupEnrich1Cruise (0x88FB4)
#define tStartupEnrich1NonCruise (0x88F98)
#define hPull2DStartupEnrich2 (0x2B694)
#define tStartupEnrich2_1A (0x883A8)
#define tStartupEnrich2_1B (0x883E4)
#define tStartupEnrich2_2A (0x8840C)
#define tStartupEnrich2_2B (0x88448)
#define hPull2DStartupEnrich3 (0x2B31C)
#define tStartupEnrich3_1A (0x8834C)
#define tStartupEnrich3_1B (0x88360)
#define tStartupEnrich3_2A (0x88374)
#define tStartupEnrich3_2B (0x88388)
#define hPull2DFrontO2Scaling (0x4FF64)
#define tFrontO2Scaling (0x8AB70)
#define tIntakeTempCompensation (0x89564)
#define hPull2DIntakeTempCompensation (0x38F4C)

/////////////////////
// Rev Limit Hack
/////////////////////

#define hRevLimDelete (0x00042684)
#define sRevLimStart (0x00034B28)
#define sRevLimEnd (0x00034B68)
#define pFlagsRevLim ((unsigned char*)0xFFFF7768)
#define RevLimBitMask (0x01)

/////////////////////
// Speed Density Hack
/////////////////////

#define hMafCalc (0x00004B10)
#define sMafCalc (0x00004AB4)

/////////////////////
// Injector Hack
/////////////////////

#define dInjectorScaling ((float*)0x000C78A8)
#define hInjectorScaling (0x0002B054)

/////////////////////
// Cel Hacks
/////////////////////

#define sCelTrigger (0x0007CA94)
#define hCelSignal (0x0007CB6C)
#define pCelSignalOem ((unsigned char*)0xFFFF9B3A)

/////////////////////
// Boost Hacks
/////////////////////

#define hPullTargetBoost (0x00014134)
#define hTableTargetBoost (0x00014130)
#define tTargetBoost (0x00086C50)

/////////////////////
// WGDC Hacks
/////////////////////

#define hPullWgdc (0x000145F8)
#define hWgdc (0x000421A4)
#define sWgdc (0x00013E80)
#define hTableWgdcInitial (0x000145F4)
#define tWgdcInitial (0x00086C34)
#define hTableWgdcMax (0x00014614)
#define tWgdcMax (0x00086C18)

/////////////////////
// Primary Open Loop Fueling Hacks
/////////////////////

#define pPolf4Byte (0xFFFF7458)
#define hPull3DPolf (0x0002FDA0)
#define hPolf (0x000426A8)
#define sPolf (0x0002FB4C)
#define pPolfEnrich (0xFFFF7458)
#define tPolfKcaAlt (0x00089024)
#define hTablePolfKcaAlt (0x0002FD9C)
#define tPolfKcaBLo (0x00089078)
#define hTablePolfKcaBLo (0x0002FDB4)
#define tPolfKcaBHi (0x00089094)
#define hTablePolfKcaBHi (0x0002FDB8)

/////////////////////
// Timing Hacks
/////////////////////

#define hBaseTiming (0x0004276C)
#define pBaseTiming (0xFFFF7988)
#define sBaseTiming (0x00038B98)
#define hPull3DTiming (0x00038E38)
#define tBaseTimingPCruise (0x00089BA0)
#define hTableBaseTimingPCruise (0x00038E34)
#define tBaseTimingPNonCruise (0x00089BBC)
#define hTableBaseTimingPNonCruise (0x00038E40)
#define tBaseTimingRCruiseAvcs (0x00089BD8)
#define hTableBaseTimingRCruiseAvcs (0x00038E3C)
#define tBaseTimingRNonCruiseAvcs (0x00089BF4)
#define hTableBaseTimingRNonCruiseAvcs (0x00038E44)
#define pKcaIam (0xFFFF7CB0)
#define hFBKCRetardValue (0x3CB70)
#define dFBKCRetardValue ((float*)0xCE0E0)
#define hFBKCRetardValueAlternate (0x3C900)
#define dFBKCRetardValueAlternate ((float*)0xCE0F0)

/////////////////////
// AVCS Hacks
/////////////////////

#define tIntakeAVCSCruise (0x0008B0F8)
#define tIntakeAVCSNonCruise (0x0008B114)
#define tExhaustAVCSCruise (0x0008B1BC)
#define tExhaustAVCSNonCruise (0x0008B1D8)
#define hPull3DIntakeAVCS (0x00057BE8)
#define hPull3DExhaustAVCS (0x00059534)
#define tIntakeAVCSNonCruiseCols (0x000D66B0)
#define tIntakeAVCSNonCruiseRows (0x000D66FC)
#define tIntakeAVCSNonCruiseData (0x000D6744)

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

#define pFbkc1 ((unsigned char*)0xFFFF6A4D)
#define pFbkc4 ((float*)0xFFFF7C40)
#define pIam1 ((unsigned char*)0xFFFF6A4F)
#define pIam4 ((float*)0xFFFF2D34)
#define pEngineSpeed ((float*)0xFFFF6810)
#define pVehicleSpeed ((float*)0xFFFF67EC)
#define pCoolantTemp ((float*)0xFFFF413C)
#define pAtmoPress ((float*)0xFFFF6A70)
#define pManifoldAbsolutePressure ((float*)0xFFFF63FC)
#define pManifoldRelativePressure ((float*)0xFFFF6400)
#define pInjectorPulseWidth ((float*)0xFFFF783C)
#define pInjectorLatency ((float*)0xFFFF6F44)
#define pIntakeAirTemp ((float*)0xFFFF4124)
#define pMassAirFlow ((float*)0xFFFF40B4)
#define pMafSensorVoltage ((short*)0xFFFF4046)
#define pEngineLoad ((float*)0xFFFF65D4)
#define pReqTorque ((float*)0xFFFF7FA4)
#define pThrottlePlate ((float*)0xFFFF64C4)
#define pCurrentGear ((unsigned char*)0xFFFF69FD)
#define pAf1Res ((float*)0xFFFF40C8)

/////////////////////
// OBD Experimental stuff
/////////////////////

#define pObdVinDirect ((unsigned char*)0xFFFF2004)

/////////////////////
// New Definitions
/////////////////////

#define dLoadSmoothingA (0x000C29C0)
#define dLoadSmoothingB (0x000C29BC)
#define dLoadSmoothingAlt (0x000C29B8)
#define dLoadSmoothingFinal (0x000C29CC)

/////////////////////
// Memory Reset
/////////////////////

#define sMemoryReset (0x000102A4)
#define hMemoryReset (0x0000FC04)
#define pMemoryResetLimit (0xFFFFBF9F)
#define hMemoryResetLimit (0x00011C58)

