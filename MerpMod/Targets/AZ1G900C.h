#define MOD_IDENTIFIER STRI(AZ1G900C.MeRpMoD.Switch.Testing.v01.40.d17.2.19.0809)
#define MOD_ECUID AB29014023
#define MOD_DATE 17.2.19.0809
#include "Switch.h"
#define MOD_CONFIG Switch
#define MOD_BUILD Testing
#define MOD_RELEASE 0
#define ECU_CALIBRATION_ID AZ1G900C
#define ECU_IDENTIFIER 7452584007
/////////////////////
// NonSpecific Rom Info and Routines
/////////////////////

#define dCalId (0x00002004)
#define dEcuId (0x000D47A0)
#define dRomHoleStart (0x000E2000)
#define pRamHoleStart (0xFFFFA6C0)
#define pRamHoleEnd (0xFFFFBF70)
#define sPull2DFloat (0x000BE844)
#define sPull3DFloat (0x000BE8F8)

/////////////////////
// Switch Hacks
/////////////////////

#define pSiDrive ((unsigned char*)0xFFFF617E)
#define pTGVLeftVoltage ((unsigned short*)0xFFFF4046)
#define pTGVRightVoltage ((unsigned short*)0xFFFF403A)
#define pRearO2Voltage ((float*)0xFFFF43FC)
#define sShortToFloat (0x000BE5AC)
#define hPull2DTipInEnrich (0x343E0)
#define tTipInEnrich (0x86CBC)
#define tTipInEnrich2 (0x86CD0)
#define hPull2DCrankingFuel (0x2ACF8)
#define tCrankingFuelA (0x86244)
#define tCrankingFuelB (0x86258)
#define tCrankingFuelC (0x8626C)
#define tCrankingFuelD (0x86280)
#define tCrankingFuelE (0x86294)
#define tCrankingFuelF (0x862A8)
#define hPull3DStartupEnrich1 (0x2BB70)
#define tStartupEnrich1Cruise (0x86F4C)
#define tStartupEnrich1NonCruise (0x86F30)
#define hPull2DStartupEnrich2 (0x2BA00)
#define tStartupEnrich2_1A (0x86318)
#define tStartupEnrich2_1B (0x86354)
#define tStartupEnrich2_2A (0x8637C)
#define tStartupEnrich2_2B (0x863B8)
#define hPull2DStartupEnrich3 (0x2B688)
#define tStartupEnrich3_1A (0x862BC)
#define tStartupEnrich3_1B (0x862D0)
#define tStartupEnrich3_2A (0x862E4)
#define tStartupEnrich3_2B (0x862F8)
#define hPull2DFrontO2Scaling (0x504A8)
#define tFrontO2Scaling (0x88B38)

/////////////////////
// Rev Limit Hack
/////////////////////

#define hRevLimDelete (0x00042B28)
#define sRevLimStart (0x00034FCC)
#define sRevLimEnd (0x0003500C)
#define pFlagsRevLim ((unsigned char*)0xFFFF77A0)
#define RevLimBitMask (0x01)

/////////////////////
// Speed Density Hack
/////////////////////

#define hMafCalc (0x000049E8)
#define sMafCalc (0x0000498C)

/////////////////////
// Injector Hack
/////////////////////

#define dInjectorScaling ((float*)0x000C7688)
#define hInjectorScaling (0x0002B3C0)

/////////////////////
// Cel Hacks
/////////////////////

#define sCelTrigger (0x0007AA04)
#define hCelSignal (0x0007AADC)
#define pCelSignalOem ((unsigned char*)0xFFFF9996)

/////////////////////
// Boost Hacks
/////////////////////

#define hPullTargetBoost (0x00014024)
#define hTableTargetBoost (0x00014020)
#define tTargetBoost (0x00084BC0)

/////////////////////
// WGDC Hacks
/////////////////////

#define hPullWgdc (0x00014508)
#define hWgdc (0x00042654)
#define sWgdc (0x00013D70)
#define hTableWgdcInitial (0x00014504)
#define tWgdcInitial (0x00084BA4)
#define hTableWgdcMax (0x00014524)
#define tWgdcMax (0x00084B88)

/////////////////////
// Primary Open Loop Fueling Hacks
/////////////////////

#define pPolf4Byte (0xFFFF7490)
#define hPull3DPolf (0x0003010C)
#define hPolf (0x00042B4C)
#define sPolf (0x0002FEB8)
#define pPolfEnrich (0xFFFF7490)
#define tPolfKcaAlt (0x00086FBC)
#define hTablePolfKcaAlt (0x00030108)
#define tPolfKcaBLo (0x00087010)
#define hTablePolfKcaBLo (0x00030120)
#define tPolfKcaBHi (0x0008702C)
#define hTablePolfKcaBHi (0x00030124)

/////////////////////
// Timing Hacks
/////////////////////

#define hBaseTiming (0x00042C10)
#define pBaseTiming (0xFFFF79C0)
#define sBaseTiming (0x00038FBE)
#define hPull3DTiming (0x000392D0)
#define tBaseTimingPCruise (0x00087B68)
#define hTableBaseTimingPCruise (0x000392CC)
#define tBaseTimingPNonCruise (0x00087BBC)
#define hTableBaseTimingPNonCruise (0x000392DC)
#define tBaseTimingRCruiseAvcs (0x00087BA0)
#define hTableBaseTimingRCruiseAvcs (0x000392D4)
#define tBaseTimingRNonCruiseAvcs (0x00087B84)
#define hTableBaseTimingRNonCruiseAvcs (0x000392D8)
#define pKcaIam (0xFFFF7CE8)
#define hFBKCRetardValue (0x3D0B8)
#define dFBKCRetardValue ((float*)0xCE334)
#define hFBKCRetardValueAlternate (0x3CE48)
#define dFBKCRetardValueAlternate ((float*)0xCE344)

/////////////////////
// Spark Cut
/////////////////////


/////////////////////
// Flags-Signals
/////////////////////

#define pResumeFlags ((unsigned char*)0xFFFF620B)
#define ResumeBitMask ((unsigned char)0x01)
#define pCoastFlags ((unsigned char*)0xFFFF620A)
#define CoastBitMask ((unsigned char)0x01)
#define pBrakeFlags ((unsigned char*)0xFFFF620C)
#define BrakeBitMask ((unsigned char)0x01)
#define pClutchFlags ((unsigned char*)0xFFFF67F3)
#define ClutchBitMask ((unsigned char)0x01)
#define pTestModeFlags ((unsigned char*)0xFFFF67D0)
#define TestModeBitMask ((unsigned char)0x01)
#define pDefogFlags ((unsigned char*)0xFFFF67EB)
#define DefogBitMask ((unsigned char)0x01)

/////////////////////
// NonSpecific Engine params
/////////////////////

#define pFbkc1 ((unsigned char*)0xFFFF6A81)
#define pFbkc4 ((float*)0xFFFF7C78)
#define pIam1 ((unsigned char*)0xFFFF6A883)
#define pIam4 ((float*)0xFFFF2D28)
#define pEngineSpeed ((float*)0xFFFF6844)
#define pVehicleSpeed ((float*)0xFFFF6820)
#define pCoolantTemp ((float*)0xFFFF4140)
#define pAtmoPress ((float*)0xFFFF6AA0)
#define pManifoldAbsolutePressure ((float*)0xFFFF6450)
#define pManifoldRelativePressure ((float*)0xFFFF6454)
#define pInjectorPulseWidth ((float*)0xFFFF7874)
#define pInjectorLatency ((float*)0xFFFF6F7C)
#define pIntakeAirTemp ((float*)0xFFFF4128)
#define pMassAirFlow ((float*)0xFFFF40B4)
#define pMafSensorVoltage ((short*)0xFFFF4042)
#define pEngineLoad ((float*)0xFFFF6628)
#define pReqTorque ((float*)0xFFFF7FDC)
#define pThrottlePlate ((float*)0xFFFF6518)
#define pCurrentGear ((unsigned char*)0xFFFF6A31)
#define pAf1Res ((float*)0xFFFF40C8)

/////////////////////
// OBD Experimental stuff
/////////////////////

#define pObdVinDirect ((unsigned char*)0xFFFF2004)

/////////////////////
// New Definitions
/////////////////////

#define dLoadSmoothingA (0x000C2C34)
#define dLoadSmoothingB (0x000C2C30)
#define dLoadSmoothingAlt (0x000C2C2C)
#define dLoadSmoothingFinal (0x000C2C40)

/////////////////////
// Memory Reset
/////////////////////

#define sMemoryReset (0x000100C0)
#define hMemoryReset (0x0000FB18)
#define pMemoryResetLimit (0xFFFFBF9F)
#define hMemoryResetLimit (0x00011A64)

