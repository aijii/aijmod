#define MOD_IDENTIFIER STRI(A8DH200Z.MeRpMoD.Switch.Testing.v01.40.d17.1.20.2243)
#define MOD_ECUID 9859014023
#define MOD_DATE 17.1.20.2243
#include "Switch.h"
#define MOD_CONFIG Switch
#define MOD_BUILD Testing
#define MOD_RELEASE 0
#define ECU_CALIBRATION_ID A8DH200Z
#define ECU_IDENTIFIER 4342594006
/////////////////////
// NonSpecific Rom Info and Routines
/////////////////////

#define dCalId (0x00002000)
#define dEcuId (0x000CD208)
#define dRomHoleStart (0x000E1000)
#define pRamHoleStart (0xFFFF8E00)
#define sPull2DFloat (0x0000209C)
#define sPull3DFloat (0x00002110)

/////////////////////
// Switch Hacks
/////////////////////

#define pTGVLeftVoltage ((unsigned short*)0xFFFF5C0A)
#define pTGVRightVoltage ((unsigned short*)0xFFFF5C0C)
#define pRearO2Voltage ((float*)0xFFFF5CBC)
#define sShortToFloat (0x2554)
#define hPull2DTipInEnrich (0x2BDBC)
#define tTipInEnrich (0x7B948)
#define tTipInEnrich2 (0x7B948)
#define hPull2DCrankingFuel (0x241BC)
#define tCrankingFuelA (0x7B4EC)
#define tCrankingFuelB (0x7B500)
#define tCrankingFuelC (0x7B514)
#define tCrankingFuelD (0x7B528)
#define tCrankingFuelE (0x7B53C)
#define tCrankingFuelF (0x7B550)
#define hPull3DStartupEnrich1 (0x24D34)
#define tStartupEnrich1Cruise (0x7BBAC)
#define tStartupEnrich1NonCruise (0x7BB90)
#define hPull2DStartupEnrich2 (0x24C08)
#define tStartupEnrich2_1A (0x7B5B4)
#define tStartupEnrich2_1B (0x7B5DC)
#define tStartupEnrich2_2A (0x7B5C8)
#define tStartupEnrich2_2B (0x7B5F0)
#define hPull2DStartupEnrich3 (0x24A2C)
#define tStartupEnrich3_1A (0x7B564)
#define tStartupEnrich3_1B (0x7B578)
#define tStartupEnrich3_2A (0x7B58C)
#define tStartupEnrich3_2B (0x7B5A0)
#define hPull2DFrontO2Scaling (0xBDB8)
#define tFrontO2Scaling (0x7CD58)

/////////////////////
// Rev Limit Hack
/////////////////////

#define hRevLimDelete (0x000145AC)
#define sRevLimStart (0x0002C8A8)
#define sRevLimEnd (0x0002C8DE)
#define pFlagsRevLim ((unsigned char*)0xFFFF7008)
#define RevLimBitMask (0x80)

/////////////////////
// Speed Density Hack
/////////////////////

#define hMafCalc (0x000080F4)
#define sMafCalc (0x00008098)

/////////////////////
// Injector Hack
/////////////////////

#define dInjectorScaling ((float*)0x000C5EBC)
#define hInjectorScaling (0x24808)

/////////////////////
// Cel Hacks
/////////////////////

#define sCelTrigger (0x00073048)
#define hCelSignal (0x00073160)
#define pCelSignalOem ((unsigned char*)0xFFFF89BA)

/////////////////////
// Boost Hacks
/////////////////////

#define hPullTargetBoost (0x16E38)
#define hTableTargetBoost (0x16E4C)
#define tTargetBoost (0x0007A768)

/////////////////////
// WGDC Hacks
/////////////////////

#define hPullWgdc (0x17260)
#define hWgdc (0x141E0)
#define sWgdc (0x16948)
#define hTableWgdcInitial (0x17268)
#define tWgdcInitial (0x7A6C0)
#define hTableWgdcMax (0x172A4)
#define tWgdcMax (0x7A6F8)

/////////////////////
// Primary Open Loop Fueling Hacks
/////////////////////

#define pPolf4Byte (0xFFFF6E74)
#define hPull3DPolf (0x29740)
#define tPolf (0x7BC00)
#define hPolf (0x145C8)
#define sPolf (0x2950C)
#define pPolfEnrich (0xFFFF6E74)

/////////////////////
// Timing Hacks
/////////////////////

#define hBaseTiming (0x14684)
#define hTableBaseTiming (0x2FF80)
#define tBaseTiming (0x7C3B0)
#define pBaseTiming (0xFFFF71A0)
#define sBaseTiming (0x2FE12)
#define hPull3DTiming (0x2FF7C)
#define pKcaIam (0xFFFF7320)
#define hFBKCRetardValue (0x32448)
#define dFBKCRetardValue ((float*)0xC927C)
#define hFBKCRetardValueAlternate (0x32428)
#define dFBKCRetardValueAlternate ((float*)0xC9280)

/////////////////////
// Spark Cut
/////////////////////


/////////////////////
// Flags-Signals
/////////////////////

#define pClutchFlags ((unsigned char*)0xFFFF67B5)
#define ClutchBitMask ((unsigned char)0x80)

/////////////////////
// NonSpecific Engine params
/////////////////////

#define pFbkc1 ((unsigned char*)0xFFFF6930)
#define pFbkc4 ((float*)0xFFFF72DC)
#define pIam1 ((unsigned char*)0xFFFF6935)
#define pIam4 ((float*)0xFFFF28F4)
#define pEngineSpeed ((float*)0xFFFF67DC)
#define pVehicleSpeed ((float*)0xFFFF67D4)
#define pCoolantTemp ((float*)0xFFFF5CAC)
#define pAtmoPress ((float*)0xFFFF5CD4)
#define pManifoldAbsolutePressure ((float*)0xFFFF6464)
#define pManifoldRelativePressure ((float*)0xFFFF6468)
#define pInjectorPulseWidth ((float*)0xFFFF7064)
#define pInjectorLatency ((float*)0xFFFF7078)
#define pIntakeAirTemp ((float*)0xFFFF5C9C)
#define pMassAirFlow ((float*)0xFFFF5CD0)
#define pMafSensorVoltage ((short*)0xFFFF5BFE)
#define pEngineLoad ((float*)0xFFFF660C)
#define pReqTorque ((float*)0xFFFF75D0)
#define pThrottlePlate ((float*)0xFFFF6508)
#define pCurrentGear ((unsigned char*)0xFFFF68E5)
#define pAf1Res ((float*)0xFFFF5F08)

/////////////////////
// OBD Experimental stuff
/////////////////////

#define pObdVinDirect ((unsigned char*)0xFFFF2004)

/////////////////////
// New Definitions
/////////////////////

#define dLoadSmoothingA (0x000C0FF0)
#define dLoadSmoothingB (0x000C0FF4)
#define dLoadSmoothingFinal (0x000C1000)

/////////////////////
// Memory Reset
/////////////////////

#define sMemoryReset (0x0000FA8C)
#define hMemoryReset (0x0000D9A8)
#define pMemoryResetLimit (0xFFFFBFBB)
#define hMemoryResetLimit (0x00011E18)

