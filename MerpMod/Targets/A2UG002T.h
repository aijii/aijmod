#define MOD_IDENTIFIER STRI(A2UG002T.MeRpMoD.Switch.Testing.v00.60.d16.11.17.1514)
#define MOD_ECUID 05BD006023
#define MOD_DATE 16.11.17.1514
#include "Switch.h"
#define MOD_CONFIG Switch
#define MOD_BUILD Testing
#define MOD_RELEASE 0
#define ECU_CALIBRATION_ID A2UG002T
#define ECU_IDENTIFIER 4B52584207
/////////////////////
// NonSpecific Rom Info and Routines
/////////////////////

#define dCalId (0x00002000)
#define dEcuId (0x000D1528)
#define dRomHoleStart (0x000E1000)
#define pRamHoleStart (0xFFFFA570)
#define pRamHoleEnd (0xFFFFBF7F)
#define sPull2DFloat (0x000020AC)
#define sPull3DFloat (0x00002160)

/////////////////////
// Switch Hacks
/////////////////////

#define pSiDrive ((unsigned char*)0xFFFF6666)
#define pTGVLeftVoltage ((unsigned short*)0xFFFF5C0E)
#define pTGVRightVoltage ((unsigned short*)0xFFFF5C10)
#define pRearO2Voltage ((float*)0xFFFF5CC4)
#define sShortToFloat (0x25A4)
#define hPull2DTipInEnrich (0x3633C)
#define tTipInEnrich (0x8C978)
#define tTipInEnrich2 (0x8C978)
#define hPull2DCrankingFuel (0x2DF58)
#define tCrankingFuelA (0x0008C28C)
#define tCrankingFuelB (0x0008C2A0)
#define tCrankingFuelC (0x0008C2B4)
#define tCrankingFuelD (0x0008C2C8)
#define tCrankingFuelE (0x0008C2DC)
#define tCrankingFuelF (0x0008C2F0)
#define hPull3DStartupEnrich1 (0x2EB1C)
#define tStartupEnrich1Cruise (0x8CB18)
#define tStartupEnrich1NonCruise (0x8CAFC)
#define hPull2DStartupEnrich2 (0x2E9F8)
#define tStartupEnrich2_1A (0x8C360)
#define tStartupEnrich2_1B (0x8C374)
#define tStartupEnrich2_2A (0x8C388)
#define tStartupEnrich2_2B (0x8C39c)
#define hPull2DStartupEnrich3 (0x2E828)
#define tStartupEnrich3_1A (0x8C310)
#define tStartupEnrich3_1B (0x8C324)
#define tStartupEnrich3_2A (0x8C338)
#define tStartupEnrich3_2B (0x8C34C)
#define hPull2DFrontO2Scaling (0xC0FC)
#define tFrontO2Scaling (0x8E0FC)

/////////////////////
// Rev Limit Hack
/////////////////////

#define hRevLimDelete (0x00015398)
#define sRevLimStart (0x00037174)
#define sRevLimEnd (0x000371A4)
#define pFlagsRevLim ((unsigned char*)0xFFFF7890)
#define RevLimBitMask (0x01)

/////////////////////
// Speed Density Hack
/////////////////////

#define hMafCalc (0x0000842C)
#define sMafCalc (0x000083D0)

/////////////////////
// Injector Hack
/////////////////////

#define dInjectorScaling ((float*)0x000C7A08)
#define hInjectorScaling (0x0002E638)

/////////////////////
// Cel Hacks
/////////////////////

#define sCelTrigger (0x0007EA90)
#define hCelSignal (0x0007EBA8)
#define pCelSignalOem ((unsigned char*)0xFFFF981E)

/////////////////////
// Boost Hacks
/////////////////////

#define hPullTargetBoost (0x00017B14)
#define hTableTargetBoost (0x00017B1C)
#define tTargetBoost (0x0008B014)

/////////////////////
// WGDC Hacks
/////////////////////

#define hPullWgdc (0x00017E68)
#define hWgdc (0x00014F24)
#define sWgdc (0x00017658)
#define hTableWgdcInitial (0x00017E6C)
#define tWgdcInitial (0x0008AFDC)
#define hTableWgdcMax (0x00017E9C)
#define tWgdcMax (0x0008AFA4)

/////////////////////
// Primary Open Loop Fueling Hacks
/////////////////////

#define pPolf4Byte (0xFFFF7690)
#define hPull3DPolf (0x00033430)
#define tPolf (0x0008CBDC)
#define hPolf (0x000153CC)
#define sPolf (0x000331E0)
#define pPolfEnrich (0xFFFF7690)

/////////////////////
// Timing Hacks
/////////////////////

#define hBaseTiming (0x1548C)
#define pBaseTiming (0xFFFF7A8C)
#define sBaseTiming (0x3B6CE)
#define hPull3DTiming (0x3B894)
#define tBaseTimingPCruise (0x0008D40C)
#define hTableBaseTimingPCruise (0x3B898)
#define tBaseTimingPNonCruise (0x0008D428)
#define hTableBaseTimingPNonCruise (0x3B8A0)
#define tBaseTimingRCruiseAvcs (0x0008D444)
#define hTableBaseTimingRCruiseAvcs (0x3B89C)
#define tBaseTimingRNonCruiseAvcs (0x0008D460)
#define hTableBaseTimingRNonCruiseAvcs (0x3B8A4)
#define pKcaIam (0xFFFF7CA4)
#define hFBKCRetardValue (0x3E3B0)
#define dFBKCRetardValue ((float*)0xCC134)
#define hFBKCRetardValueAlternate (0x3E158)
#define dFBKCRetardValueAlternate ((float*)0xCC144)

/////////////////////
// Spark Cut
/////////////////////


/////////////////////
// Flags-Signals
/////////////////////

#define pResumeFlags ((unsigned char*)0xFFFF66F7)
#define ResumeBitMask ((unsigned char)0x01)
#define pCoastFlags ((unsigned char*)0xFFFF66F6)
#define CoastBitMask ((unsigned char)0x01)
#define pBrakeFlags ((unsigned char*)0xFFFF66F8)
#define BrakeBitMask ((unsigned char)0x01)
#define pClutchFlags ((unsigned char*)0xFFFF6CE5)
#define ClutchBitMask ((unsigned char)0x01)
#define pTestModeFlags ((unsigned char*)0xFFFF6CCA)
#define TestModeBitMask ((unsigned char)0x01)
#define pDefogFlags ((unsigned char*)0xFFFF6CDE)
#define DefogBitMask ((unsigned char)0x01)

/////////////////////
// NonSpecific Engine params
/////////////////////

#define pFbkc1 ((unsigned char*)0xFFFF6F56)
#define pFbkc4 ((float*)0xFFFF7C40)
#define pIam1 ((unsigned char*)0xFFFF6F5B)
#define pIam4 ((float*)0xFFFF2C30)
#define pEngineSpeed ((float*)0xFFFF6D34)
#define pVehicleSpeed ((float*)0xFFFF6D08)
#define pCoolantTemp ((float*)0xFFFF5CB4)
#define pAtmoPress ((float*)0xFFFF6F70)
#define pManifoldAbsolutePressure ((float*)0xFFFF6970)
#define pManifoldRelativePressure ((float*)0xFFFF6974)
#define pInjectorPulseWidth ((float*)0xFFFF793C)
#define pInjectorLatency ((float*)0xFFFF7950)
#define pIntakeAirTemp ((float*)0xFFFF5CA4)
#define pMassAirFlow ((float*)0xFFFF5CD8)
#define pMafSensorVoltage ((short*)0xFFFF5C02)
#define pEngineLoad ((float*)0xFFFF6B30)
#define pReqTorque ((float*)0xFFFF7F4C)
#define pThrottlePlate ((float*)0xFFFF6A10)
#define pCurrentGear ((unsigned char*)0xFFFF6F09)
#define pAf1Res ((float*)0xFFFF5F10)

/////////////////////
// OBD Experimental stuff
/////////////////////

#define pObdVinDirect ((unsigned char*)0xFFFF2004)

/////////////////////
// New Definitions
/////////////////////

#define dLoadSmoothingA (0x000C2DD8)
#define dLoadSmoothingB (0x000C2DD4)
#define dLoadSmoothingAlt (0x000C2DD0)
#define dLoadSmoothingFinal (0x000C2DE4)

/////////////////////
// Memory Reset
/////////////////////

#define sMemoryReset (0x0000FA30)
#define hMemoryReset (0x0000DCEC)
#define pMemoryResetLimit (0xFFFFBFBB)
#define hMemoryResetLimit (0x00012454)

