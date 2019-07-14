#define MOD_IDENTIFIER STRI(AZ1G701V.MeRpMoD.Switch.Testing.v01.40.d17.2.20.0828)
#define MOD_ECUID 9E7A014023
#define MOD_DATE 17.2.20.0828
#include "Switch.h"
#define MOD_CONFIG Switch
#define MOD_BUILD Testing
#define MOD_RELEASE 0
#define ECU_CALIBRATION_ID AZ1G701V
#define ECU_IDENTIFIER 6E12786007
/////////////////////
// NonSpecific Rom Info and Routines
/////////////////////

#define dCalId (0x00002004)
#define dEcuId (0x000D61A0)
#define dRomHoleStart (0x000E1400)
#define pRamHoleStart (0xFFFFA788)
#define pRamHoleEnd (0xFFFFAA4A)
#define sPull2DFloat (0x000BE844)
#define sPull3DFloat (0x000BE8F8)

/////////////////////
// Switch Hacks
/////////////////////

#define pSiDrive ((unsigned char*)0xFFFF6116)
#define pTGVLeftVoltage ((unsigned short*)0xFFFF4046)
#define pTGVRightVoltage ((unsigned short*)0xFFFF403A)
#define pRearO2Voltage ((float*)0xFFFF43FC)
#define sShortToFloat (0x000BE5AC)
#define hPull2DTipInEnrich (0x00038454)
#define tTipInEnrich (0x0009B4C4)
#define tTipInEnrich2 (0x0009B4D8)
#define hPull2DCrankingFuel (0x0002E268)
#define tCrankingFuelA (0x0009AA38)
#define tCrankingFuelB (0x0009AA4C)
#define tCrankingFuelC (0x0009AA60)
#define tCrankingFuelD (0x0009AA74)
#define tCrankingFuelE (0x0009AA88)
#define tCrankingFuelF (0x0009AA9C)
#define hPull3DStartupEnrich1 (0x0002F0E0)
#define tStartupEnrich1Cruise (0x0009B754)
#define tStartupEnrich1NonCruise (0x0009B738)
#define hPull2DStartupEnrich2 (0x0002EF70)
#define tStartupEnrich2_1A (0x0009AB0C)
#define tStartupEnrich2_1B (0x0009AB48)
#define tStartupEnrich2_2A (0x0009AB70)
#define tStartupEnrich2_2B (0x0009ABAC)
#define hPull2DStartupEnrich3 (0x0002EBF8)
#define tStartupEnrich3_1A (0x0009AAB0)
#define tStartupEnrich3_1B (0x0009AAC4)
#define tStartupEnrich3_2A (0x0009AAD8)
#define tStartupEnrich3_2B (0x0009AAEC)
#define hPull2DFrontO2Scaling (0x00054438)
#define tFrontO2Scaling (0x0009D324)

/////////////////////
// Rev Limit Hack
/////////////////////

#define hRevLimDelete (0x00046F70)
#define sRevLimStart (0x00039040)
#define sRevLimEnd (0x00039080)
#define pFlagsRevLim ((unsigned char*)0xFFFF7A70)
#define RevLimBitMask (0x01)

/////////////////////
// Speed Density Hack
/////////////////////

#define hMafCalc (0x000049E8)
#define sMafCalc (0x0000498C)

/////////////////////
// Injector Hack
/////////////////////

#define dInjectorScaling ((float*)0x000C8E54)
#define hInjectorScaling (0x0002E930)

/////////////////////
// Cel Hacks
/////////////////////

#define sCelTrigger (0x0008E210)
#define hCelSignal (0x0008E294)
#define pCelSignalOem ((unsigned char*)0xFFFFA1F2)

/////////////////////
// Boost Hacks
/////////////////////

#define hPullTargetBoost (0x00013684)
#define hTableTargetBoost (0x00013680)
#define tTargetBoost (0x000990B4)

/////////////////////
// WGDC Hacks
/////////////////////

#define hPullWgdc (0x00013B68)
#define hWgdc (0x00046954)
#define sWgdc (0x000133D0)
#define hTableWgdcInitial (0x00013B64)
#define tWgdcInitial (0x00099098)
#define hTableWgdcMax (0x00013B84)
#define tWgdcMax (0x0009907C)

/////////////////////
// Primary Open Loop Fueling Hacks
/////////////////////

#define pPolf4Byte (0xFFFF7760)
#define hPull3DPolf (0x00034144)
#define tPolf (0x0009B7C4)
#define hTablePolf (0x00034140)
#define hPolf (0x00046F94)
#define sPolf (0x00033EF0)
#define pPolfEnrich (0xFFFF7760)

/////////////////////
// Timing Hacks
/////////////////////

#define hBaseTiming (0x00047058)
#define pBaseTiming (0xFFFF7C90)
#define sBaseTiming (0x0003D06A)
#define hPull3DTiming (0x0003D37C)
#define tBaseTimingPCruise (0x0009C370)
#define hTableBaseTimingPCruise (0x0003D378)
#define tBaseTimingPNonCruise (0x0009C38C)
#define hTableBaseTimingPNonCruise (0x0003D384)
#define tBaseTimingRCruiseAvcs (0x0009C3A8)
#define hTableBaseTimingRCruiseAvcs (0x0003D380)
#define tBaseTimingRNonCruiseAvcs (0x0009C3C4)
#define hTableBaseTimingRNonCruiseAvcs (0x0003D388)
#define pKcaIam (0xFFFF7FB8)
#define hFBKCRetardValue (0x00041164)
#define dFBKCRetardValue ((float*)0x000CFC54)
#define hFBKCRetardValueAlternate (0x00040EF4)
#define dFBKCRetardValueAlternate ((float*)0x000CFC64)

/////////////////////
// Spark Cut
/////////////////////


/////////////////////
// Flags-Signals
/////////////////////

#define pResumeFlags ((unsigned char*)0xFFFF61A3)
#define ResumeBitMask ((unsigned char)0x01)
#define pCoastFlags ((unsigned char*)0xFFFF61A2)
#define CoastBitMask ((unsigned char)0x01)
#define pBrakeFlags ((unsigned char*)0xFFFF61A4)
#define BrakeBitMask ((unsigned char)0x01)
#define pClutchFlags ((unsigned char*)0xFFFF679B)
#define ClutchBitMask ((unsigned char)0x01)
#define pTestModeFlags ((unsigned char*)0xFFFF6778)
#define TestModeBitMask ((unsigned char)0x01)
#define pDefogFlags ((unsigned char*)0xFFFF6793)
#define DefogBitMask ((unsigned char)0x01)

/////////////////////
// NonSpecific Engine params
/////////////////////

#define pFbkc1 ((unsigned char*)0xFFFF6A2C)
#define pFbkc4 ((float*)0xFFFF7F48)
#define pIam1 ((unsigned char*)0xFFFF6A2E)
#define pIam4 ((float*)0xFFFF3048)
#define pEngineSpeed ((float*)0xFFFF67EC)
#define pVehicleSpeed ((float*)0xFFFF67C8)
#define pCoolantTemp ((float*)0xFFFF4140)
#define pAtmoPress ((float*)0xFFFF6A4C)
#define pManifoldAbsolutePressure ((float*)0xFFFF63E8)
#define pManifoldRelativePressure ((float*)0xFFFF63EC)
#define pInjectorPulseWidth ((float*)0xFFFF7B44)
#define pInjectorLatency ((float*)0xFFFF71F0)
#define pIntakeAirTemp ((float*)0xFFFF4128)
#define pMassAirFlow ((float*)0xFFFF40B4)
#define pMafSensorVoltage ((short*)0xFFFF4042)
#define pEngineLoad ((float*)0xFFFF65D0)
#define pReqTorque ((float*)0xFFFF82AC)
#define pThrottlePlate ((float*)0xFFFF64B0)
#define pCurrentGear ((unsigned char*)0xFFFF69D9)
#define pAf1Res ((float*)0xFFFF40C8)

/////////////////////
// OBD Experimental stuff
/////////////////////

#define pObdVinDirect ((unsigned char*)0xFFFF2004)

/////////////////////
// New Definitions
/////////////////////

#define dLoadSmoothingA (0x000C2C78)
#define dLoadSmoothingB (0x000C2C74)
#define dLoadSmoothingAlt (0x000C2C70)
#define dLoadSmoothingFinal (0x000C2C84)

/////////////////////
// Memory Reset
/////////////////////

#define sMemoryReset (0x000100C0)
#define hMemoryReset (0x0000FB18)
#define pMemoryResetLimit (0xFFFFBF9F)
#define hMemoryResetLimit (0x00011A64)

