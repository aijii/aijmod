#define MOD_ECUID 5C83F9D199
#define MOD_DATE 29.11.20.20.49
#include "Switch.h"
#define MOD_CONFIG Switch
#define MOD_BUILD Debug
#define MOD_RELEASE 0
#define ECU_CALIBRATION_ID A2UI001L
#define ECU_IDENTIFIER 4B12785207
/////////////////////
// NonSpecific Rom Info and Routines
/////////////////////

#define dCalId (0x00002000)
#define dEcuId (0x000D2658)
#define dRomHoleStart (0x000DF810)
#define pRamHoleStart (0xFFFFB500)
#define pRamHoleEnd (0xFFFFBCFF)
#define sPull2DFloat (0x000020AC)
#define sPull3DFloat (0x00002160)

/////////////////////
// Switch Hacks
/////////////////////

#define pSiDrive ((unsigned char*)0xFFFF65FE)
#define pTGVLeftVoltage ((unsigned short*)0xFFFF5C0E)
#define pTGVRightVoltage ((unsigned short*)0xFFFF5C10)
#define pRearO2Voltage ((float*)0xFFFF5CC4)
#define sShortToFloat (0x000025A4)
#define hPull2DTipInEnrich (0x00037A4C)
#define tTipInEnrich (0x000A13BC)
#define tTipInEnrich2 (0x000A13BC)
#define hPull2DCrankingFuel (0x0002EF64)
#define tCrankingFuelA (0x000A0CD0)
#define tCrankingFuelB (0x000A0CE4)
#define tCrankingFuelC (0x000A0CF8)
#define tCrankingFuelD (0x000A0D0C)
#define tCrankingFuelE (0x000A0D20)
#define tCrankingFuelF (0x000A0D34)
#define hPull3DStartupEnrich1 (0x0002FB34)
#define tStartupEnrich1Cruise (0x000A1568)
#define tStartupEnrich1NonCruise (0x000A154C)
#define hPull2DStartupEnrich2 (0x0002FA10)
#define tStartupEnrich2_1A (0x000A0DA4)
#define tStartupEnrich2_1B (0x000A0DCC)
#define tStartupEnrich2_2A (0x000A0DB8)
#define tStartupEnrich2_2B (0x000A0DE0)
#define hPull2DStartupEnrich3 (0x0002F840)
#define tStartupEnrich3_1A (0x000A0D54)
#define tStartupEnrich3_1B (0x000A0D68)
#define tStartupEnrich3_2A (0x000A0D7C)
#define tStartupEnrich3_2B (0x000A0D90)
#define hPull2DFrontO2Scaling (0x0000C12C)
#define tFrontO2Scaling (0x000A2B68)
#define tIntakeTempCompensation (0x000A1A84)

/////////////////////
// Rev Limit Hack
/////////////////////

#define hRevLimDelete (0x000156F4)
#define sRevLimStart (0x00038884)
#define sRevLimEnd (0x000388B4)
#define pFlagsRevLim ((unsigned char*)0xFFFF7AF0)
#define RevLimBitMask (0x01)

/////////////////////
// Speed Density Hack
/////////////////////

#define hMafCalc (0x0000845C)
#define sMafCalc (0x00008400)

/////////////////////
// Injector Hack
/////////////////////

#define dInjectorScaling ((float*)0x000C8918)
#define hInjectorScaling (0x0002F650)

/////////////////////
// Cel Hacks
/////////////////////

#define sCelTrigger (0x0009320C)
#define hCelSignal (0x00093324)
#define pCelSignalOem ((unsigned char*)0xFFFFA026)

/////////////////////
// Boost Hacks
/////////////////////

#define hPullTargetBoost (0x000174D8)
#define hTableTargetBoost (0x000174E0)
#define tTargetBoost (0x0009F8A0)
#define hTableTargetBoostAlt (0x000174D4)
#define tTargetBoostAlt (0x0009F884)

/////////////////////
// WGDC Hacks
/////////////////////

#define hPullWgdc (0x0001782C)
#define hWgdc (0x00015088)
#define sWgdc (0x0001701C)
#define sJsrWgdcInitial (0x000176F6)
#define hTableWgdcInitial (0x00017830)
#define tWgdcInitial (0x0009F868)
#define tTableWgdcInitialAlt (0x00017834)
#define tWgdcInitialAlt (0x0009F84C)
#define hJsrWgdcMax (0x00017738)
#define hTableWgdcMax (0x00017860)
#define tWgdcMax (0x0009F830)
#define tWgdcMaxAlt (0x0009F814)

/////////////////////
// Primary Open Loop Fueling Hacks
/////////////////////

#define pPolf4Byte (0xFFFF78AC)
#define hPull3DPolf (0x00034528)
#define tPolf (0x000A162C)
#define hTablePolf (0x00034534)
#define hJsrPolf (0x00034398)
#define hPolf (0x00015728)
#define sPolf (0x000342D8)
#define pPolfEnrich (0xFFFF78AC)

/////////////////////
// Timing Hacks
/////////////////////

#define hBaseTiming (0x000157E8)
#define pBaseTiming (0xFFFF7CEC)
#define sBaseTiming (0x0003CDDE)
#define hPull3DTiming (0x0003CFA4)
#define tBaseTimingPCruise (0x000A1E78)
#define hTableBaseTimingPCruise (0x0003CFA8)
#define tBaseTimingPNonCruise (0x000A1E94)
#define hTableBaseTimingPNonCruise (0x0003CFB0)
#define tBaseTimingRCruiseAvcs (0x000A1EB0)
#define hTableBaseTimingRCruiseAvcs (0x0003CFAC)
#define tBaseTimingRNonCruiseAvcs (0x000A1ECC)
#define hTableBaseTimingRNonCruiseAvcs (0x0003CFB4)
#define hSubKca (0x0003C6AC)
#define pKcaIam (0xFFFF7F04)
#define hFBKCRetardValue (0x0003FAC0)
#define dFBKCRetardValue ((float*)0x000CD290)
#define hFBKCRetardValueAlternate (0x0003F868)
#define dFBKCRetardValueAlternate ((float*)0x000CD2A0)

/////////////////////
// AVCS Hacks
/////////////////////


/////////////////////
// Spark Cut
/////////////////////

#define sSparkCutOcrStart (0x0000A892)
#define sSparkCutOcrEnd (0x0000A8A8)
#define sSparkCutGrStart (0x0000A902)
#define sSparkCutGrEnd (0x0000A90A)

/////////////////////
// Flags-Signals
/////////////////////

#define pResumeFlags ((unsigned char*)0xFFFF668F)
#define ResumeBitMask ((unsigned char)0x01)
#define pCoastFlags ((unsigned char*)0xFFFF668E)
#define CoastBitMask ((unsigned char)0x01)
#define pBrakeFlags ((unsigned char*)0xFFFF6690)
#define BrakeBitMask ((unsigned char)0x01)
#define pClutchFlags ((unsigned char*)0xFFFF6C89)
#define ClutchBitMask ((unsigned char)0x01)
#define pTestModeFlags ((unsigned char*)0xFFFF6C6E)
#define TestModeBitMask ((unsigned char)0x01)
#define pDefogFlags ((unsigned char*)0xFFFF6C82)
#define DefogBitMask ((unsigned char)0x01)

/////////////////////
// NonSpecific Engine params
/////////////////////

#define pFbkc1 ((unsigned char*)0xFFFF6EFA)
#define pFbkc4 ((float*)0xFFFF7EA0)
#define pIam1 ((unsigned char*)0xFFFF6EFF)
#define pIam4 ((float*)0xFFFF2F5C)
#define pEngineSpeed ((float*)0xFFFF6CD8)
#define pVehicleSpeed ((float*)0xFFFF6CAC)
#define pCoolantTemp ((float*)0xFFFF5CB4)
#define pAtmoPress ((float*)0xFFFF6F14)
#define pManifoldAbsolutePressure ((float*)0xFFFF6908)
#define pManifoldRelativePressure ((float*)0xFFFF690C)
#define pInjectorPulseWidth ((float*)0xFFFF7B9C)
#define pInjectorLatency ((float*)0xFFFF7BB0)
#define pIntakeAirTemp ((float*)0xFFFF5CA4)
#define pMassAirFlow ((float*)0xFFFF5CD8)
#define pMafSensorVoltage ((short*)0xFFFF5C02)
#define pEngineLoad ((float*)0xFFFF6AD4)
#define pReqTorque ((float*)0xFFFF81AC)
#define pThrottlePlate ((float*)0xFFFF69B0)
#define pWgdc4 ((float*)0xFFFF63B8)
#define pCurrentGear ((unsigned char*)0xFFFF6EAD)
#define pAf1Res ((float*)0xFFFF5F10)
#define pDeltaMap ((float*)0xFFFF68FC)

/////////////////////
// OBD Experimental stuff
/////////////////////


/////////////////////
// New Definitions
/////////////////////

#define dLoadSmoothingA (0x000C2D38)
#define dLoadSmoothingB (0x000C2D34)
#define dLoadSmoothingAlt (0x000C2D30)
#define dLoadSmoothingFinal (0x000C2D44)

/////////////////////
// Memory Reset
/////////////////////

#define sMemoryReset (0x0000FA60)
#define hMemoryReset (0x0000DD1C)
#define pMemoryResetLimit (0xFFFFBFBB)
#define hMemoryResetLimit (0x00012484)

/////////////////////
// Dynamic RAM Tuning
/////////////////////

#define hPull2DFloatRamInjectStart (0x000020B4)
#define hPull2DFloatRamInjectEnd (0x000020DC)
#define hPull3DFloatRamInjectStart (0x00002168)
#define hPull3DFloatRamInjectEnd (0x0000218C)

