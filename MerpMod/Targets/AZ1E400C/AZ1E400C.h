#define MOD_IDENTIFIER STRI(AZ1E400C.MeRpMoD.Switch.Testing.v00.60.d16.5.17.1134)
#define MOD_ECUID DFE6006023
#define MOD_DATE 16.5.17.1134
#include "Switch.h"
#define MOD_CONFIG Switch
#define MOD_BUILD Testing
#define MOD_RELEASE 0
#define ECU_CALIBRATION_ID AZ1E400C
#define ECU_IDENTIFIER 5152584007
/////////////////////
// NonSpecific Rom Info and Routines
/////////////////////

#define dCalId (0x00002004)
#define dEcuId (0x000D391C)
#define dRomHoleStart (0x000E2000)
#define pRamHoleStart (0xFFFFA610)
#define pRamHoleEnd (0xFFFFBF70)
#define sPull2DFloat (0x000BE764)
#define sPull3DFloat (0x000BE818)

/////////////////////
// Switch Hacks
/////////////////////

#define pSiDrive ((unsigned char*)0xFFFF6162)
#define pTGVLeftVoltage ((unsigned short*)0xFFFF404A)
#define pTGVRightVoltage ((unsigned short*)0xFFFF403E)
#define pRearO2Voltage ((float*)0xFFFF43F8)
#define sShortToFloat (0x000BE4CC)
#define hPull2DTipInEnrich (0x3429C)
#define tTipInEnrich (0x85CE8)
#define tTipInEnrich2 (0x85CFC)
#define hPull2DCrankingFuel (0x2AC3C)
#define tCrankingFuelA (0x85284)
#define tCrankingFuelB (0x85298)
#define tCrankingFuelC (0x852AC)
#define tCrankingFuelD (0x852C0)
#define tCrankingFuelE (0x852D4)
#define tCrankingFuelF (0x852E8)
#define hPull3DStartupEnrich1 (0x2BAB4)
#define tStartupEnrich1Cruise (0x85F78)
#define tStartupEnrich1NonCruise (0x85F5C)
#define hPull2DStartupEnrich2 (0x2B944)
#define tStartupEnrich2_1A (0x85358)
#define tStartupEnrich2_1B (0x85394)
#define tStartupEnrich2_2A (0x853BC)
#define tStartupEnrich2_2B (0x853F8)
#define hPull2DStartupEnrich3 (0x2B5CC)
#define tStartupEnrich3_1A (0x852FC)
#define tStartupEnrich3_1B (0x85310)
#define tStartupEnrich3_2A (0x85324)
#define tStartupEnrich3_2B (0x85338)
#define hPull2DFrontO2Scaling (0x4F800)
#define tFrontO2Scaling (0x87A00)

/////////////////////
// Rev Limit Hack
/////////////////////

#define hRevLimDelete (0x0004210C)
#define sRevLimStart (0x00034E88)
#define sRevLimEnd (0x00034EC8)
#define pFlagsRevLim ((unsigned char*)0xFFFF7760)
#define RevLimBitMask (0x01)

/////////////////////
// Speed Density Hack
/////////////////////

#define hMafCalc (0x00004B10)
#define sMafCalc (0x00004AB4)

/////////////////////
// Injector Hack
/////////////////////

#define dInjectorScaling ((float*)0x000C7130)
#define hInjectorScaling (0x0002B304)

/////////////////////
// Cel Hacks
/////////////////////

#define sCelTrigger (0x00079AF0)
#define hCelSignal (0x00079BC8)
#define pCelSignalOem ((unsigned char*)0xFFFF98EA)

/////////////////////
// Boost Hacks
/////////////////////

#define hPullTargetBoost (0x00014218)
#define hTableTargetBoost (0x00014214)
#define tTargetBoost (0x00083C68)

/////////////////////
// WGDC Hacks
/////////////////////

#define hPullWgdc (0x000146F0)
#define hWgdc (0x00041C4C)
#define sWgdc (0x00013F64)
#define hTableWgdcInitial (0x000146EC)
#define tWgdcInitial (0x00083C4C)
#define hTableWgdcMax (0x0001470C)
#define tWgdcMax (0x00083C30)

/////////////////////
// Primary Open Loop Fueling Hacks
/////////////////////

#define pPolf4Byte (0xFFFF745C)
#define hPull3DPolf (0x00030054)
#define hPolf (0x00042130)
#define sPolf (0x0002FDFC)
#define pPolfEnrich (0xFFFF745C)
#define tPolfKcaAlt (0x00085FE8)
#define hTablePolfKcaAlt (0x00030050)
#define tPolfKcaBLo (0x00086020)
#define hTablePolfKcaBLo (0x00030058)
#define tPolfKcaBHi (0x0008603C)
#define hTablePolfKcaBHi (0x0003005C)

/////////////////////
// Timing Hacks
/////////////////////

#define hBaseTiming (0x000421E4)
#define pBaseTiming (0xFFFF7980)
#define sBaseTiming (0x00038E66)
#define hPull3DTiming (0x00039178)
#define tBaseTimingPCruise (0x00086C74)
#define hTableBaseTimingPCruise (0x00039174)
#define tBaseTimingPNonCruise (0x00086C90)
#define hTableBaseTimingPNonCruise (0x00039180)
#define tBaseTimingRCruiseAvcs (0x00086CAC)
#define hTableBaseTimingRCruiseAvcs (0x0003917C)
#define tBaseTimingRNonCruiseAvcs (0x00086CC8)
#define hTableBaseTimingRNonCruiseAvcs (0x00039184)
#define pKcaIam (0xFFFF7C7C)
#define hFBKCRetardValue (0x3CCA0)
#define dFBKCRetardValue ((float*)0xCD8AC)
#define hFBKCRetardValueAlternate (0x3CA0C)
#define dFBKCRetardValueAlternate ((float*)0xCD8BC)

/////////////////////
// Spark Cut
/////////////////////


/////////////////////
// Flags-Signals
/////////////////////

#define pResumeFlags ((unsigned char*)0xFFFF61DB)
#define ResumeBitMask ((unsigned char)0x01)
#define pCoastFlags ((unsigned char*)0xFFFF61DA)
#define CoastBitMask ((unsigned char)0x01)
#define pBrakeFlags ((unsigned char*)0xFFFF61DC)
#define BrakeBitMask ((unsigned char)0x01)
#define pClutchFlags ((unsigned char*)0xFFFF67C3)
#define ClutchBitMask ((unsigned char)0x01)
#define pTestModeFlags ((unsigned char*)0xFFFF67A0)
#define TestModeBitMask ((unsigned char)0x01)
#define pDefogFlags ((unsigned char*)0xFFFF67BB)
#define DefogBitMask ((unsigned char)0x01)

/////////////////////
// NonSpecific Engine params
/////////////////////

#define pFbkc1 ((unsigned char*)0xFFFF6A51)
#define pFbkc4 ((float*)0xFFFF7C18)
#define pIam1 ((unsigned char*)0xFFFF6A53)
#define pIam4 ((float*)0xFFFF2D10)
#define pEngineSpeed ((float*)0xFFFF6814)
#define pVehicleSpeed ((float*)0xFFFF67F0)
#define pCoolantTemp ((float*)0xFFFF413C)
#define pAtmoPress ((float*)0xFFFF6A70)
#define pManifoldAbsolutePressure ((float*)0xFFFF6420)
#define pManifoldRelativePressure ((float*)0xFFFF6424)
#define pInjectorPulseWidth ((float*)0xFFFF7824)
#define pInjectorLatency ((float*)0xFFFF6F48)
#define pIntakeAirTemp ((float*)0xFFFF4124)
#define pMassAirFlow ((float*)0xFFFF40B4)
#define pMafSensorVoltage ((short*)0xFFFF4046)
#define pEngineLoad ((float*)0xFFFF79E0)
#define pReqTorque ((float*)0xFFFF7F58)
#define pThrottlePlate ((float*)0xFFFF64E8)
#define pCurrentGear ((unsigned char*)0xFFFF6A01)
#define pAf1Res ((float*)0xFFFF40C8)

/////////////////////
// OBD Experimental stuff
/////////////////////

#define pObdVinDirect ((unsigned char*)0xFFFF2004)

/////////////////////
// New Definitions
/////////////////////

#define dLoadSmoothingA (0x000C2834)
#define dLoadSmoothingB (0x000C2830)
#define dLoadSmoothingAlt (0x000C282C)
#define dLoadSmoothingFinal (0x000C2840)

/////////////////////
// Memory Reset
/////////////////////

#define sMemoryReset (0x000102A4)
#define hMemoryReset (0x0000FC04)
#define pMemoryResetLimit (0xFFFFBF9F)
#define hMemoryResetLimit (0x00011C58)

