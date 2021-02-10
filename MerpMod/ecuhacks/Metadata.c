/*
	Copyright (C) 2012-2013 Merrill A. Myers III merrillamyersiii@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#include "EcuHacks.h"

const long HERPDERP __attribute__ ((section ("TestSection1"),aligned(4))) =	0x12345678;

//extern float ComputeMassAirFlow();
typedef struct
{
	long op;
	long startaddress;
	long endaddress;
	char name[];

} MetaPatch;

typedef struct
{
	long op;
	long hewaddress;
	long startaddress;
	long endaddress;
	char name[];
} MetaCopyPatch;

typedef struct
{
	long op;
	long address;
	long oldval;
	long newval;
	char name[];
} MetaReplace;

/*
typedef struct
{
	long op;
	long address;

} MetaJSRHook;
*/

enum MetaOps
{
OpRequireVersion= 0x12340000,
OpCalibrationId=  0x12340001,
OpPatch=          0x12340002,
OpCopyPatch=	  0x12340012,
OpReplace4Bytes=  0x12340003,
OpReplaceLast2Of4Bytes = 0x12340013,
OpNewPatch=		0x12340004,
OpCopyNewPatch=	0x12340014,
OpModAuthor=		0x12340008,
OpModBuild=		0x12340009,
OpJSRHook=			0x1234000A,
OpECUID=			0x1234000B,
OpNewECUID=			0x1234000C,
OpModInfo=		0x1234000D,
OpModAuth=		0x1234000E,
OpModId=		0x1234000F
};

#define OpDelim STRI(\0\0\0\0\0\0)

typedef struct
{
long reqversionop;
long reqversion;
long calidop;
long calidoffset;
long calidchars;
unsigned char calid[ECU_CALIBRATION_CHARS];
unsigned char pad1[8];
unsigned char newcalid[ECU_CALIBRATION_CHARS];
unsigned char pad2[8];
//MODID
long modidop;
long modidoffset;
unsigned char modid[60];
unsigned char padmod[8];
//ECUID
long ecuidop;
long ecuidoffset;
long ecuidbytes;
unsigned char ecuid[ECU_IDENTIFIER_CHARS];
unsigned char pad3[8];
long newecuidop;
unsigned char newecuid[ECU_IDENTIFIER_CHARS];
unsigned char pad4[8];

//Mod Information
long modauthorop;
unsigned char authname[16];
long modbuildop;
unsigned char modbuild[16];
char	pad5[8];
long modinfoop;
unsigned char modinfo[];
} MetaHeader;

const MetaHeader metadataheader __attribute__ ((section ("MetaDataHeader"),aligned(4))) =
{
reqversionop:  	OpRequireVersion,
#if VIN_HACKS
reqversion:   	10009,
#else
reqversion:		9,
#endif
calidop:   OpCalibrationId,
calidoffset:   dCalId,
calidchars:  ECU_CALIBRATION_CHARS,
calid: STRI(ECU_CALIBRATION_ID),
pad1:   OpDelim,
newcalid:  STRI(MOD_CALIBRATION_ID),
pad2:  OpDelim,

//Alternate Identifier (in ROM HOLE, uniquely identifies this rom!)
modidop:	OpModId,
modidoffset: (int)&(ModIdentifier),
modid:		MOD_IDENTIFIER,
padmod:		OpDelim,

//ECU ID
ecuidop:	OpECUID,
ecuidoffset: dEcuId,
ecuidbytes: ECU_IDENTIFIER_CHARS,
ecuid:		STRI(ECU_IDENTIFIER),
pad3:   OpDelim,
newecuidop:	OpNewECUID,
#ifdef MOD_ECUID
newecuid:	STRI(MOD_ECUID),
#else
newecuid:	STRI(MOD_ECU_IDENTIFIER),
#endif
pad4:   OpDelim,

//Mod Information
modauthorop :  OpModAuthor,
authname :  "Adrian Pistritto",
modbuildop : OpModBuild,
modbuild :  STRI(MOD_BUILD),
pad5	:	OpDelim,

modinfoop : OpModInfo,
modinfo	:	ModInfo OpDelim
};

#if SPARK_HACKS
//////////////////////
//					//
//SPARK HACKS		//
//					//
//////////////////////
	const MetaPatch SparkCutHookPatchOCR METADATA =
	{
		op: OpPatch,
		startaddress: sSparkCutOcrStart,
		endaddress:	sSparkCutOcrEnd + 1,
	};
	const MetaPatch SparkCutHookGR METADATA =
	{
		op: OpPatch,
		startaddress: sSparkCutGrStart,
		endaddress: sSparkCutGrEnd + 1,
	};
#endif

#if DYN_RAMTUNING
//////////////////////
//					//
//DYNAMIC RAMTUNING	//
//					//
//////////////////////
	const MetaPatch Pull2DFloatRamInjectStart METADATA =
	{
		op: OpPatch,
		startaddress: hPull2DFloatRamInjectStart,
		endaddress: hPull2DFloatRamInjectEnd - 1,
		name: STRI(Pull2DFloat Dynamic RAM Tuning)
	};
	const MetaPatch Pull3DFloatRamInjectStart METADATA =
	{
		op: OpPatch,
		startaddress: hPull3DFloatRamInjectStart,
		endaddress: hPull3DFloatRamInjectEnd + 3,
		name: STRI(Pull3DFloat Dynamic RAM Tuning)
	};
#endif

#if REVLIM_HACKS
//////////////////////
//					//
//REVLIM HACKS		//
//					//
//////////////////////

	const MetaReplace RevLimitDelete METADATA =
	{
		op: OpReplace4Bytes,
		address: hRevLimDelete,
		oldval: sRevLimStart,
		newval: (int)RevLimHook,
		name: STRI(Rev Limit Subroutine Hook)
	};

#endif

#if MEMORY_HACKS
//////////////////////
//					//
//MEMORY HACKS		//
//					//
//////////////////////
	const MetaReplace MemResetSubHook METADATA =
	{
		op: OpReplace4Bytes,
		address: hMemoryReset,
		oldval: sMemoryReset,
		newval: (int)Initializer,
		name: STRI(Memory Reset Subroutine Hook)
	};
#if RAM_PERSIST
	const MetaReplace MemResetLimHook METADATA =
	{
		op: OpReplace4Bytes,
		address: hMemoryResetLimit,
		oldval: pMemoryResetLimit,
		newval: (int)((char*)(pRamHoleStart)) - 1,
		name: STRI(Memory Reset Limit Hook)
	};
#endif
#endif

#if SD_HACKS
//////////////////////
//					//
//SD HACKS			//
//					//
//////////////////////
	const MetaReplace SDHookPatch METADATA =
	{
		op: OpReplace4Bytes,
		address: hMafCalc,
		oldval: sPull2DFloat,
		newval: (int)ComputeMassAirFlow,
		name: STRI(Speed Density Maf Subroutine Hook)
	};
#endif

#if CEL_HACKS
//////////////////////
//					//
//CEL HACKS			//
//					//
//////////////////////
	const MetaReplace CelTriggerHookPatch METADATA =
		{
			op: OpReplace4Bytes,
			address: hCelSignal,
			oldval: (int)pCelSignalOem,
			newval: (int)&(pRamVariables.CelSignal),
			name: STRI(CEL Signal Hook)
		};
#endif


//////////////////////
//					//
//BOOST HACKS		//
//					//
//////////////////////
#if WGDC_MAIN_HOOK //This is currently used for the 'Main' hook, and runs on a constant clock (not rpm-based)
const MetaReplace WGDCHook METADATA =
	{
		op: OpReplace4Bytes,
		address: hWgdc,
		oldval: sWgdc,
		newval: (int)WGDCHack,
		name: STRI(Main Subroutine Hook WGDC)
	};
#elif POLF_MAIN_HOOK
const MetaReplace POLFHook METADATA =
	{
		op: OpReplace4Bytes,
		address: hPolf,
		oldval: sPolf,
		newval: (int)POLFHack,
		name: STRI(Main Subroutine Hook POLF)
	};
#endif

#if BOOST_HACKS
	const MetaReplace WGDCHookPull METADATA =
	{
		op: OpReplace4Bytes,
		address: hPullWgdc,
		oldval: sPull3DFloat,
		newval: (int)Pull3DRamHook,
		name: STRI(WGDC Pull3D Hook)
	} ;

	//TODO: make preprocessor produce an error if there aren't proper hooks!!!
	#if defined(hTableWgdcInitial) && defined (tWgdcInitial)
		const MetaReplace PGWGInitialHookTable METADATA =
		{
			op: OpReplace4Bytes,
			address: hTableWgdcInitial,
			oldval: tWgdcInitial,
			newval: (int)&(pRamVariables.WGDCInitialOutput),
			name: STRI(WGDC Initial Table Hook)
		};
	#endif

	#if defined(hTableWgdcInitialAlt) && defined(tWgdcInitialAlt)
	//TODO: NEED THIS????
	/*	const MetaReplace PGWGInitialAltHookTable METADATA =
	{
		op: OpReplace4Bytes,
		address: hTableWgdcInitialAlt,
		oldval: tWgdcInitialAlt,
		newval: (int)&(pRamVariables.WGDCInitial)
	};*/
	#endif

	#ifdef hTableWgdcInitialKcaAlt
		const MetaReplace PGWGInitialKcaAlt METADATA =
		{
			op: OpReplace4Bytes,
			address: hTableWgdcInitialKcaAlt,
			oldval: tWgdcInitialKcaAlt,
			newval: (int)&(pRamVariables.WGDCMaxOutput),
			name: STRI(WGDC Initial KCA Alt Table Hook)
		};
		const MetaReplace PGWGInitialKcaBLo METADATA =
		{
			op: OpReplace4Bytes,
			address: hTableWgdcInitialKcaBLo,
			oldval: tWgdcInitialKcaBLo,
			newval: (int)&(pRamVariables.WGDCMaxOutput),
			name: STRI(WGDC Initial KCA B Low Table Hook)
		};
		const MetaReplace PGWGInitialKcaBHi METADATA =
		{
			op: OpReplace4Bytes,
			address: hTableWgdcInitialKcaBHi,
			oldval: tWgdcInitialKcaBHi,
			newval: (int)&(pRamVariables.WGDCMaxOutput),
			name: STRI(WGDC Initial KCA B High Table Hook)
		};
	#endif

	//Max WGDC HOOKS

	#if defined(hTableWgdcMax) && defined(tWgdcMax)
		const MetaReplace PGWGMaxHookTable METADATA =
		{
			op: OpReplace4Bytes,
			address: hTableWgdcMax,
			oldval: tWgdcMax,
			newval: (int)&(pRamVariables.WGDCMaxOutput),
			name: STRI(WGDC Max Table Hook)
		};
	#endif

	#if defined(hTableWgdcMaxAlt) && defined(tWgdcMaxAlt)
	//TODO: NEED THIS???
	/*	const MetaReplace PGWGMaxAltHookTable METADATA =
	{
		op: OpReplace4Bytes,
		address: hTableWgdcMaxAlt,
		oldval: tWgdcMaxAlt,
		newval: (int)&(pRamVariables.WGDCMaxOutput),
	};*/
	#endif

	#ifdef hTableWgdcMaxKcaAlt
		const MetaReplace PGWGMaxKcaAlt METADATA =
		{
			op: OpReplace4Bytes,
			address: hTableWgdcMaxKcaAlt,
			oldval: tWgdcMaxKcaAlt,
			newval: (int)&(pRamVariables.WGDCMaxOutput),
			name: STRI(WGDC Max KCA Alt Table Hook)
		};
		const MetaReplace PGWGMaxKcaBLo METADATA =
		{
			op: OpReplace4Bytes,
			address: hTableWgdcMaxKcaBLo,
			oldval: tWgdcMaxKcaBLo,
			newval: (int)&(pRamVariables.WGDCMaxOutput),
			name: STRI(WGDC Max KCA B Low Table Hook)
		};
		const MetaReplace PGWGMaxKcaBHi METADATA =
		{
			op: OpReplace4Bytes,
			address: hTableWgdcMaxKcaBHi,
			oldval: tWgdcMaxKcaBHi,
			newval: (int)&(pRamVariables.WGDCMaxOutput),
			name: STRI(WGDC Max KCA B High Table Hook)
		};
	#endif

	///Target boost table hooks
	const MetaReplace TargetBoostHookPull METADATA =
	{
		op: OpReplace4Bytes,
		address: hPullTargetBoost,
		oldval: sPull3DFloat,
		newval: (int)Pull3DRamHook,
		name: STRI(Target Boost Pull3D Hook)
	} ;

	#if defined(hTableTargetBoost) && defined(tTargetBoost)
	const MetaReplace TargetBoostHookTable METADATA =
	{
		op: OpReplace4Bytes,
		address: hTableTargetBoost,
		oldval: tTargetBoost,
		newval: (int)&(pRamVariables.TargetBoostOutput),
		name: STRI(Target Boost Table Hook)
	};
	#endif

	#if defined(hTableTargetBoostAlt) && defined(tTargetBoostAlt)
	//TODO: NEED THIS??????
	/*	const MetaReplace TargetBoostAltHookTable METADATA =
	{
		op: OpReplace4Bytes,
		address: hTableTargetBoostAlt,
		oldval: tTargetBoosAlt,
		newval: (int)&(pRamVariables.TargetBoostOutput),
	};*/
	#endif

	#ifdef hTableTargetBoostKcaAlt
		const MetaReplace TargetBoostKcaAltHookTable METADATA =
		{
			op: OpReplace4Bytes,
			address: hTableTargetBoostKcaAlt,
			oldval: tTargetBoostKcaAlt,
			newval: (int)&(pRamVariables.TargetBoostOutput),
		name: STRI(Target Boost KCA Alt Table Hook)
		};
		const MetaReplace TargetBoostKcaBLoHookTable METADATA =
		{
			op: OpReplace4Bytes,
			address: hTableTargetBoostKcaBLo,
			oldval: tTargetBoostKcaBLo,
			newval: (int)&(pRamVariables.TargetBoostOutput),
		name: STRI(Target Boost KCA B Low Table Hook)
		};
		const MetaReplace TargetBoostKcaBHiHookTable METADATA =
		{
			op: OpReplace4Bytes,
			address: hTableTargetBoostKcaBHi,
			oldval: tTargetBoostKcaBHi,
			newval: (int)&(pRamVariables.TargetBoostOutput),
		name: STRI(Target Boost KCA B High Table Hook)
		};
	#endif

#endif

#if SUB_KCA_HACKS
//////////////////////
//					//
//SUB KCA HACKS		//
//					//
//////////////////////
//	const MetaReplace SubtractiveKCAPatch METADATA =
//	{
//		op: OpReplace4Bytes,
//		address: hSubKca,
//		oldval: pKcaIam,
//		newval: (int)&(pRamVariables.SubtractiveKCA)
//		name: STRI(Target Boost Table Hook)
//	};
#endif

#if TIMING_HACKS
//////////////////////
//					//
//TIMING HACKS		//
//					//
//////////////////////
	const MetaReplace TimingHookPatch METADATA =
	{
		op: OpReplace4Bytes,
		address: hBaseTiming,
		oldval: sBaseTiming,
		newval: (int)TimingHack,
		name: STRI(Timing Subroutine Hook)
	};
#ifdef hTableBaseTiming
	const MetaReplace TimingTablePatch METADATA =
	{
		op: OpReplace4Bytes,
		address: hTableBaseTiming,
		oldval: tBaseTiming,
		newval: (int)&(pRamVariables.BaseTimingOutput),
		name: STRI(Timing Table Hook)
	};
#else
	const MetaReplace BaseTimingPCruiseTablePatch METADATA =
	{
		op: OpReplace4Bytes,
		address: hTableBaseTimingPCruise,
		oldval: tBaseTimingPCruise,
		newval: (int)&(pRamVariables.BaseTimingOutput),
		name: STRI(Base Timing Primary Cruise Table Hook)
	};
	const MetaReplace BaseTimingPNonCruiseTablePatch METADATA =
	{
		op: OpReplace4Bytes,
		address: hTableBaseTimingPNonCruise,
		oldval: tBaseTimingPNonCruise,
		newval: (int)&(pRamVariables.BaseTimingOutput),
		name: STRI(Base Timing Primary Non Cruise Table Hook)
	};
	const MetaReplace BaseTimingRCruiseAvcsTablePatch METADATA =
	{
		op: OpReplace4Bytes,
		address:hTableBaseTimingRCruiseAvcs,
		oldval: tBaseTimingRCruiseAvcs,
		newval: (int)&(pRamVariables.BaseTimingOutput),
		name: STRI(Base Timing Reference Cruise AVCS Table Hook)
	};
	const MetaReplace BaseTimingRNonCruiseAvcsTablePatch METADATA =
	{
		op: OpReplace4Bytes,
		address:hTableBaseTimingRNonCruiseAvcs,
		oldval: tBaseTimingRNonCruiseAvcs,
		newval: (int)&(pRamVariables.BaseTimingOutput),
		name: STRI(Base Timing Reference Non Cruise AVCS Table Hook)
	};
#endif

	const MetaReplace TimingPullPatch METADATA =
	{
		op: OpReplace4Bytes,
		address: hPull3DTiming,
		oldval: sPull3DFloat,
		newval: (int)Pull3DRamHook,
		name: STRI(Timing Pull3D Hook)
	};


	const MetaReplace FBKCRetardValuePatch METADATA =
	{
		op: OpReplace4Bytes,
		address: hFBKCRetardValue,
		oldval: (long) dFBKCRetardValue,
		newval: (int)&(pRamVariables.FBKCRetardValue),
		name: STRI(Timing FBKC Retard Hook)
	};

	const MetaReplace FBKCRetardValueAlternatePatch METADATA =
	{
		op: OpReplace4Bytes,
		address: hFBKCRetardValueAlternate,
		oldval: (long) dFBKCRetardValueAlternate,
		newval: (int)&(pRamVariables.FBKCRetardValueAlternate),
		name: STRI(Timing FBKC Retard Alternate Hook)
	};



#endif

#if POLF_HACKS
//////////////////////
//					//
//POLF HACKS		//
//					//
//////////////////////
	const MetaReplace POLFHookPatch METADATA =
	{
		op: OpReplace4Bytes,
		address: hPolf,
		oldval: sPolf,
		newval: (int)POLFHack,
		name: STRI(POLF Subroutine Hook)
	};
	const MetaReplace POLFHookPull METADATA =
	{
		op: OpReplace4Bytes,
		address: hPull3DPolf,
		oldval: sPull3DFloat,
		newval: (int)Pull3DRamHook,
		name: STRI(POLF Pull3D Hook)
	};
#ifdef hTablePolf
	const MetaReplace POLFHookTable METADATA =
	{
		op: OpReplace4Bytes,
		address: hTablePolf,
		oldval: tPolf,
		newval: (int)&(pRamVariables.PolfOutput),
		name: STRI(POLF Table Hook)
	};
#endif
#ifdef hTablePolfKcaAlt
	const MetaReplace TablePolfKcaAltHook METADATA =
	{
		op: OpReplace4Bytes,
		address: hTablePolfKcaAlt,
		oldval: tPolfKcaAlt,
		newval: (int)&(pRamVariables.PolfOutput),
		name: STRI(POLF Table Hook KcaAlt)
	};
#endif
#ifdef hTablePolfKcaBLo
	const MetaReplace TablePolfKcaBLoHook METADATA =
	{
		op: OpReplace4Bytes,
		address: hTablePolfKcaBLo,
		oldval: tPolfKcaBLo,
		newval: (int)&(pRamVariables.PolfOutput),
		name: STRI(POLF Table Hook KcaBLo)
	};
#endif
#ifdef hTablePolfKcaBHi
	const MetaReplace TablePolfKcaBHiHook METADATA =
	{
		op: OpReplace4Bytes,
		address: hTablePolfKcaBHi,
		oldval: tPolfKcaBHi,
		newval: (int)&(pRamVariables.PolfOutput),
		name: STRI(POLF Table Hook KcaBHi)
	};
#endif

#endif

#if E85_HACKS
//////////////////////
//					//
//     E85 HACKS	//
//					//
//////////////////////
	const MetaReplace InjectorHook METADATA =
	{
		op: OpReplace4Bytes,
		address: hInjectorScaling,
		oldval: dInjectorScaling,
		newval: (int)&(pRamVariables.InjectorScaling),
		name: STRI(Injector Scalar Hook)
	};
	const MetaReplace TipInEnrichHookPull METADATA =
	{
		op: OpReplace4Bytes,
		address: hPull2DTipInEnrich,
		oldval: sPull2DFloat,
		newval: (int)Pull2DRamHookTipInEnrich,
		name: STRI(Tip In Enrichment Pull2D Hook)
	};
	const MetaReplace CrankingFuelHookPull METADATA =
	{
		op: OpReplace4Bytes,
		address: hPull2DCrankingFuel,
		oldval: sPull2DFloat,
		newval: (int)Pull2DRamHookCrankingFuel,
		name: STRI(Cranking Fuel Pull2D Hook)
	};
	const MetaReplace StartupEnrich2HookPull METADATA =
	{
		op: OpReplace4Bytes,
		address: hPull2DStartupEnrich2,
		oldval: sPull2DFloat,
		newval: (int)Pull2DRamHookStartupEnrich2,
		name: STRI(Startup Enrich 2 Pull2D Hook)
	};
	const MetaReplace StartupEnrich3HookPull METADATA =
	{
		op: OpReplace4Bytes,
		address: hPull2DStartupEnrich3,
		oldval: sPull2DFloat,
		newval: (int)Pull2DRamHookStartupEnrich3,
		name: STRI(Startup Enrich 3 Pull2D Hook)
	};

	const MetaReplace StartupEnrich1HookPull METADATA =
	{
		op: OpReplace4Bytes,
		address: hPull3DStartupEnrich1,
		oldval: sPull3DFloat,
		newval: (int)Pull3DRamHookStartupEnrich1,
		name: STRI(Startup Enrich 1 Pull3D Hook)
	};

#if DUAL_FRONTO2_HACKS

	const MetaReplace FrontO2ScalingHookPull METADATA =
	{
		op: OpReplace4Bytes,
		address: hPull2DFrontO2Scaling,
		oldval: sPull2DFloat,
		newval: (int)Pull2DRamHookFrontO2Scaling,
		name: STRI(Front O2 Scaling Pull2D Hook)
	};

#endif

	const MetaReplace IntakeTempCompensationHookPull METADATA =
	{
		op: OpReplace4Bytes,
		address: hPull2DIntakeTempCompensation,
		oldval: sPull2DFloat,
		newval: (int)Pull2DRamHookIntakeTempCompensation,
		name: STRI(Intake Temp Timing Compensation A Hook)
	};


#endif

#if AVCS_HACKS

	const MetaReplace IntakeAVCSHookPull METADATA =
	{
		op: OpReplace4Bytes,
		address: hPull3DIntakeAVCS,
		oldval: sPull3DFloat,
		newval: (int)Pull3DRamHookAVCSLookup,
		name: STRI(Intake AVCS Pull3D Hook)
	};

	const MetaReplace ExhaustAVCSHookPull METADATA =
	{
		op: OpReplace4Bytes,
		address: hPull3DExhaustAVCS,
		oldval: sPull3DFloat,
		newval: (int)Pull3DRamHookAVCSLookup,
		name: STRI(Exhaust AVCS Pull3D Hook)
	};

#endif

//////////////////////
//					//
//ROM HOLE			//
//					//
//////////////////////
extern char* StartOfSpeedDensityTables;
extern unsigned char ModIdentifier[];
const MetaPatch RomHoleCodePatch METADATA =
{
	op: OpNewPatch,
	startaddress: (int)&(ModIdentifier),
	endaddress: (int)( &RomHoleEndMarker ),
	name: STRI(Rom Hole Code Patch)
};

const long endoffile[2] METADATA = {0x00090009,0x00090009};


