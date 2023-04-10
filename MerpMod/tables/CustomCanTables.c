
#include "EcuHacks.h"

/////////////////
//Constants
/////////////////
#if CAN_HACKS

unsigned short CANBusECAUpdateCount CANDATA = 45;
//temp
//CanMessageSetupStruct ccm00 CANDATA = {.id = 0x640,	.ext = 0,	.dlc = 8,	.bus = 0,	.mailBox = 27,	.mcs = mcsTrans, 	.nmc = 0, .rate =  10, .callback = 0};


//CanMessageSetupStruct ccm00 CANDATA = {.id = 0x506, .ext = 0,	.dlc = 3,	.bus = 0,	.mailBox = 19,	.mcs = mcsReceive, 	.nmc = 1, .rate =   0, .callback = (unsigned long)&raceGradeKeyPadCallback};
//CanMessageSetupStruct ccm04 CANDATA = {.id = 0x720,	.ext = 0,	.dlc = 8,	.bus = 0,	.mailBox = 23,	.mcs = mcsReceive, 	.nmc = 1, .rate =   0, .callback = (unsigned long)&canCallbackRamTune};
//CanMessageSetupStruct ccm06 CANDATA = {.id = 0x180, .ext = 1,	.dlc = 8,	.bus = 0,	.mailBox = 25,	.mcs = mcsReceive, 	.nmc = 1, .rate =   0, .callback = (unsigned long)&canCallbackAEMwideband};
//CanMessageSetupStruct ccm07 CANDATA = {.id = 0x190,	.ext = 0,	.dlc = 4,	.bus = 0,	.mailBox = 26,	.mcs = mcsReceive, 	.nmc = 1, .rate =   0, .callback = (unsigned long)&canCallbackMK3e85Packet};
//CanMessageSetupStruct *ccmGroup[8] CANDATA;// = {&ccm00,&ccm01,&ccm02,&ccm03,&ccm04,&ccm05,&ccm06,&ccm07};
//CanMessageSetupStruct ccm01 CANDATA = {.id = 0x0EC,	.ext = 0,	.dlc = 8,	.bus = 0,	.mailBox = 20,	.mcs = mcsReceive, 	.nmc = 1, .rate =   0, .callback = (unsigned long)&canCallbackECAPacket}; 


//CanMessageSetupStruct ccm00 CANDATA = {.id = 0x640, .ext = 0,	.dlc = 8,	.bus = 0,	.mailBox = 19,	.mcs = mcsTrans, 	.nmc = 0, .rate =   100, .callback = 0};
//CanMessageSetupStruct ccm02 CANDATA = {.id = 0x641, .ext = 0,	.dlc = 5,	.bus = 0,	.mailBox = 21,	.mcs = mcsTrans, 	.nmc = 0, .rate =   100, .callback = 0}; 


CanMessageSetupStruct ccm00 CANDATA = {.id = 0x650, .ext = 0,	.dlc = 8,	.bus = 0,	.mailBox = 19,	.mcs = mcsReceive, 	.nmc = 1, .rate =   0, .callback = (unsigned long)&canCallbackECA2Packet};
CanMessageSetupStruct ccm01 CANDATA = {.id = 0x651,	.ext = 0,	.dlc = 8,	.bus = 0,	.mailBox = 20,	.mcs = mcsReceive, 	.nmc = 1, .rate =   0, .callback = (unsigned long)&canCallbackZT3Packet}; 
CanMessageSetupStruct ccm02 CANDATA = {.id = 0x000,	.ext = 0,	.dlc = 0,	.bus = 0,	.mailBox = 21,	.mcs = mcsTrans, 	.nmc = 0, .rate =   0, .callback = 0}; 
CanMessageSetupStruct ccm03 CANDATA = {.id = 0x000,	.ext = 0,	.dlc = 0,	.bus = 0,	.mailBox = 22,	.mcs = mcsTrans,    .nmc = 0, .rate =   0, .callback = 0}; 
CanMessageSetupStruct ccm04 CANDATA = {.id = 0x000,	.ext = 0,	.dlc = 0,	.bus = 0,	.mailBox = 23,	.mcs = mcsTrans, 	.nmc = 0, .rate =   0, .callback = 0};
CanMessageSetupStruct ccm05 CANDATA = {.id = 0x000,	.ext = 0,	.dlc = 0,	.bus = 0,	.mailBox = 24,	.mcs = mcsTrans, 	.nmc = 0, .rate =   0, .callback = 0};
CanMessageSetupStruct ccm06 CANDATA = {.id = 0x000, .ext = 0,	.dlc = 0,	.bus = 0,	.mailBox = 25,	.mcs = mcsTrans, 	.nmc = 0, .rate =   0, .callback = 0};
CanMessageSetupStruct ccm07 CANDATA = {.id = 0x000,	.ext = 0,	.dlc = 0,	.bus = 0,	.mailBox = 26,	.mcs = mcsTrans, 	.nmc = 0, .rate =   0, .callback = 0};
CanMessageSetupStruct ccm08 CANDATA = {.id = 0x640,	.ext = 0,	.dlc = 8,	.bus = 0,	.mailBox = 27,	.mcs = mcsTrans, 	.nmc = 0, .rate = 100, .callback = 0};
CanMessageSetupStruct ccm09 CANDATA = {.id = 0x641,	.ext = 0,	.dlc = 6,	.bus = 0,	.mailBox = 28,	.mcs = mcsTrans, 	.nmc = 0, .rate = 100, .callback = 0};
CanMessageSetupStruct ccm10 CANDATA = {.id = 0x000,	.ext = 0,	.dlc = 0,	.bus = 0,	.mailBox = 29,	.mcs = mcsTrans, 	.nmc = 0, .rate =   0, .callback = 0};
CanMessageSetupStruct ccm11 CANDATA = {.id = 0x000,	.ext = 0,	.dlc = 0,	.bus = 0,	.mailBox = 30,	.mcs = mcsTrans, 	.nmc = 0, .rate =   0, .callback = 0};

unsigned char dataLinkedInRam  __attribute__ ((section ("RamHole")));


//640: BBBB FFFF  //boost fuel press 
//641: cifo exxx //temps ethanol
//642:
//643:

/*
unsigned long cmDTaddr[cmDTCount] CANDATA = {
	(unsigned long)&pRamVariables.rgBackLight,(unsigned long)&pRamVariables.rgBackLight,
	(unsigned long)&pRamVariables.MasterInitFlag,
	(unsigned long)&pRamVariables.MapSwitch,
	(unsigned long)&pRamVariables.LCEngaged,
	(unsigned long)&pRamVariables.FFSEngaged,
	(unsigned long)&pRamVariables.TimingHackEnabled,
	(unsigned long)&pRamVariables.PolfOutputFP,
	(unsigned long)&pRamVariables.MafMode,
	(unsigned long)&pRamVariables.MapBlendRatio,
	(unsigned long)&pRamVariables.aemLambda,(unsigned long)&pRamVariables.aemOxygen,(unsigned long)&pRamVariables.aemDataValid,(unsigned long)&pRamVariables.aemSensorFault,
	(unsigned long)&pRamVariables.rEthanolCAN,(unsigned long)&pRamVariables.tFuelCAN};
*/


//640: BBBB FFFF  //boost fuel press 
//641: cifo Exhaust-ethanol-x-x //temps ethanol
//650: ECA
//651: ZT3

unsigned long cmDTaddr[cmDTCount] CANDATA = {
	(unsigned long)pManifoldRelativePressure, (unsigned long)&pRamVariables.FuelPressureDifferential,
	(unsigned long)pCoolantTemp,(unsigned long)pIntakeAirTemp,(unsigned long)&pRamVariables.ECA2FuelTemperatureCAN,(unsigned long)&pRamVariables.OilTemperature,
	(unsigned long)&pRamVariables.exhaustCutoutOutput,(unsigned long)&pRamVariables.OilPressure,0,0,
	0,0,0,0,	
	0,0};


//format conversion prior to transmitting
// this controls whether the address table cmdtaddr is checked.
// it is also the input to the format conversion	
unsigned char cmDTtypeIn[cmDTCount] CANDATA = {
	dtFloat,dtFloat,
	
	dtFloat,dtFloat,dtChar,dtFloat,	
	dtChar,dtFloat,dtUndefined,dtUndefined,
	
	dtUndefined,dtUndefined,dtUndefined,dtUndefined,
	dtUndefined,dtUndefined};

unsigned char cmDTtypeOut[cmDTCount] CANDATA = {
	dtFloat,dtFloat,
	
	dtChar,dtChar,dtChar,dtChar,		
	dtChar,dtChar,dtChar,dtChar,
	
	dtChar,dtChar,dtChar,dtChar,
	dtChar,dtChar};
	
unsigned char cmDTccm[cmDTCount] CANDATA = {
	8,8,
	9,9,9,9,
	9,9,0,0,
	0,0,0,0,
	0,0};
	
unsigned char cmDTpos[cmDTCount] CANDATA = {
	0,4,
	0,1,2,3,
	4,5,0,0,
	0,0,0,0,
	0,0};
	
	
float cmDTscale[cmDTCount] CANDATA = {
	0,0,
	0,0,0,0,
	0,0.01933677,0,0,
	0,0,0,0,0,0};
	
float cmDToffset[cmDTCount] CANDATA = {
	0,0,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,0,0};

#endif