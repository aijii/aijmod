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


#ifndef __ECU_HACKS__
#define __ECU_HACKS__

#define CONCAT(x,y) CONCAT_DO(x,y)
#define CONCAT_DO(x,y) x y
#define CONCAT_THREE(x,y,z) CONCAT(CONCAT(x,y),z)
#define STRINGIFY(x) #x
#define STRI(x) STRINGIFY(x)


//Section Macros
#define ROMCODE  __attribute__ ((section ("RomHole_Code"),aligned(4)))
#define DEFDATA __attribute__ ((section ("DefinitionData"),aligned(4)))
#define METADATA  __attribute__ ((section ("MetaData"),aligned(4)))
#define CELFLASHDATA  __attribute__ ((section ("RomHole_CelFlashTables"),aligned(4)))
#define PROGMODEDATA __attribute__ ((section ("RomHole_ProgModeTables"),aligned(4)))
#define REVLIMDATA __attribute__ ((section ("RomHole_RevLimTables"),aligned(4)))
#define SPEEDDENSITYDATA __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)))
#define TIMINGDATA __attribute__ ((section ("RomHole_TimingHackTables"),aligned(4)))
#define SWITCHDATA __attribute__ ((section ("RomHole_MapSwitchTables"),aligned(4)))
#define RAMTUNEDATA __attribute__ ((section ("RomHole_MapSwitchTables"),aligned(4)))
#define FUELDATA __attribute__ ((section ("RomHole_POLFHackTables"),aligned(4)))
#define BOOSTDATA __attribute__ ((section ("RomHole_BoostHackTables"),aligned(4)))
#define CANDATA __attribute__ ((section ("RomHole_BoostHackTables"),aligned(4)))
#define PORTDATA __attribute__ ((section ("RomHole_PortLoggerTables"),aligned(4)))

/*
    Below is a kind of klugy way to eliminate the warnings emitted by the
    assembler when compiling C code with only data to be used in the
    `RomHole_Code` section. By default, the compiler will translate a C section
    attribute directive into something like `.section <name>,"ax",@progbits`
    or similar. If you compile C code only with data to be linked with raw
    assembly source code in the same section, then the section flags that the
    compiler generates will likely conflict with the section directive in
    the assembly source, which will generate warnings.

    To eliminate this, suffixing the section name with a `!` will cause
    the assembler to disregard everything after the section name as a comment,
    eliminating the compiler warning.
*/
#define ROMCODE_DATA __attribute__((section("RomHole_Code!")))

//Select ECU Target!!
#include STRI(_TARGET_HEADER_)
#include STRI(_TARGET_CONFIG_)

#if defined(pResumeFlags) && defined(pCoastFlags)
#if LC_ADJUST || CEL_HACKS || PROG_MODE
#define CRUISE_CONTROL 1
#endif
#endif

#if defined hWgdc && defined sWgdc
#define WGDC_HOOK_DEFINED 1
#endif

#if defined hPolf && defined sPolf
#define POLF_HOOK_DEFINED 1
#endif

#if defined hWgdc && defined sWgdc
#define WGDC_MAIN_HOOK 1
#elif defined hPolf && defined sPolf
#define POLF_MAIN_HOOK 1
#endif

#if LC_ADJ_HACKS && defined pResumeFlags && defined pCoastFlags
#define LC_ADJUST 1
#endif
#if VIN_HACKS
#define VinInfo Vin based authentication__
#define VinLabel .VA
#else
#define VinInfo
#define VinLabel
#endif
#if SWITCH_HACKS
#define BlendInfo	Map switching with blending__
#define BlendLabel	.MS
#else
#define BlendInfo
#define BlendLabel
#endif
#if REVLIM_HACKS
#define RevLimInfo	Launch control and flat foot shifting (static or gear based calculation)__
#define RevLimLabel .RL
#else
#define RevLimInfo
#define RevLimLabel
#endif
#if LC_ADJ_HACKS
#define	LcAdjInfo	Launch control live adjust using cruise control resume/accel__
#define LcAdjLabel .LCA
#else
#define	LcAdjInfo
#define LcAdjLabel
#endif
#if PROG_HACKS
#define ProgModeInfo	Programming Mode__
#define ProgModeLabel
#else
#define ProgModeInfo
#define ProgModeLabel
#endif
#if SPARK_HACKS
#define SparkCutInfo	Advanced spark cut features__
#define SparkCutLabel
#else
#define SparkCutInfo
#define SparkCutLabel
#endif
#if CEL_HACKS
#define CelInfo		CEL Flash (FBKC, EGT from Front O2 resistance, Coolant Temp)__
#define CelLabel	.CEL
#else
#define CelInfo
#define CelLabel
#endif
#if BOOST_HACKS
#define BoostInfo	Per Gear WGDC & Target Boost__
#define BoostLabel	.PGBW
#else
#define BoostInfo
#define BoostLabel
#endif
#if TIMING_HACKS
#define SWITCH_HACKS 1
#define TimingInfo	Timing map switching with launch control timing retard and knock correction retard__
#define TimingLabel
#else
#define TimingInfo
#define TimingLabel
#endif
#if POLF_HACKS
#define SWITCH_HACKS 1
#define PolfInfo	Primary open loop fuel hacks__
#define PolfLabel	.POLF
#else
#define PolfInfo
#define PolfLabel
#endif
#if INJ_HACKS
#define InjectorInfo	Injector scaling hacks__
#define InjectorLabel
#else
#define InjectorInfo
#define InjectorLabel
#endif
#if MEMORY_HACKS
#define MemoryInfo	Memory reset hack__
#define MemoryLabel
#else
#define MemoryInfo
#define MemoryLabel
#endif
#define VeRamTuningInfo
#define VeRamTuningLabel
#define PolfRamTuningInfo
#define PolfRamTuningLabel
#define TimingRamTuningInfo
#define TimingRamTuningLabel
#define PgwgRamTuningInfo
#define PgwgRamTuningLabel
#define WgdcRamTuningInfo
#define WgdcRamTuningLabel
#if DYN_RAMTUNING
#define DynRamTuningInfo Dynamic RAM Tuning
#define DynRamTuningLabel
#else
#define DynRamTuningInfo
#define DynRamTuningLabel
#endif
#if SD_HACKS
#if SWITCH_HACKS
#define SdInfo	Speed Density load calculation with MAF blending and VE map switching__
#define SdLabel .SDS
#else
#define SdInfo	Speed Density load calculation with MAF blending__
#define SdLabel .SD
#endif
#else
#define SdInfo
#define SdLabel
#endif

#if MOD_RELEASE
#define MOD_CONFIG_ID STRI(MOD_CONFIG)
#else
#define MOD_CONFIG_ID CONCAT(STRI(MOD_CONFIG),STRI(.MOD_BUILD))
#endif

// #define MOD_IDENTIFIER CONCAT_THREE(   CONCAT(  STRI(ECU_CALIBRATION_ID)  ,  STRI(.MeRpMoD.)  )   ,   CONCAT( MOD_CONFIG_ID , STRI(.v) )   ,   STRI(MOD_DATE)    )
#define ModInfo CONCAT_THREE(STRI(VinInfo ),STRI(SdInfo ),CONCAT_THREE(STRI(BlendInfo ),STRI(RevLimInfo ),CONCAT_THREE(STRI(LcAdjInfo ),STRI(CelInfo ),CONCAT_THREE(STRI(PolfInfo ),STRI(BoostInfo ),STRI(DynRamTuningInfo))))) //ProgInfo SparkCutInfo  BoostInfo Timingfo SubKcaInfo PolfInfo PgwgInfo InjectorInfo MemoryInfo VeRamTuningInfo PolfRamTuningInfo TimingRamTuningInfo PgwgRamTuningInfo WgdcRamTuningInfo
#define ModLabel CONCAT_THREE(STRI(VinLabel),STRI(SdLabel),CONCAT_THREE(STRI(BlendLabel),STRI(RevLimLabel),CONCAT_THREE(STRI(LcAdjLabel),STRI(CelLabel),CONCAT_THREE(STRI(PolfLabel),STRI(BoostLabel),STRI(DynRamTuningLabel))))) //ProgLabel SparkCutLabel  BoostLabel Timingfo SubKcaLabel PgwgLabel InjectorLabel MemoryLabel VeRamTuningLabel PolfRamTuningLabel TimingRamTuningLabel PgwgRamTuningLabel WgdcRamTuningLabel

#include "IDATranslation.h"
#include "Externs.h"
#include "RamVariables.h"

extern RamVariables pRamVariables;

#endif