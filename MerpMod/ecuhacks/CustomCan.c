/*
	Copyright (C) 2017-2017 Johnny Lloyd Wall jlwall@gmail.com
	
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
#if CAN_HACKS

void setupMailBoxStruct(CanMessageSetupStruct* cs)
{
	unsigned short* ptr;	
	ptr = (unsigned short*)(0xFFFFD100+ 0x800*(unsigned short)(cs->bus&0x01) + 0x20*(unsigned short)(cs->mailBox&0x1F));
	if(cs->ext == 0) //11-bit, not extended
		{
		ptr[0] = ((unsigned short)cs->id<<4)&0x7FF0;
		ptr[1] = 0;
		}
	else if(cs->ext == 1)
		{
		ptr[0]  = (unsigned short)(((unsigned long)cs->id>>16)&0x0003);
		ptr[0] += (unsigned short)(0x0004);
		ptr[0] += (unsigned short)(((unsigned long)cs->id>>14)&0x7FF0);
		ptr[1] = ((unsigned short)cs->id)&0xFFFF;
		}		
	ptr[2] = (((unsigned short)cs->mcs<<8)&0x700) + ((unsigned short)cs->dlc&0x0F);	
}

void updateCanDT(unsigned char dt)
{
	unsigned long addrtemp;
	CanMessageSetupStruct *ccmGroup = (CanMessageSetupStruct *)(&ccm00);
	if(cmDTaddr[dt] >= 0xFFFF0000)
	{		
		addrtemp = 0xFFFFD100;
		addrtemp += 0x800*(unsigned long)(ccmGroup[cmDTccm[dt]].bus&0x01);		
		addrtemp += 0x020*(unsigned long)(ccmGroup[cmDTccm[dt]].mailBox&0x1F);
		addrtemp += 0x08;
		addrtemp += (unsigned long)cmDTpos[dt]&0x07;	
		switch(cmDTtypeIn[dt])
		{
		case 1: 
			{
			unsigned char* ptrSource = (unsigned char*)cmDTaddr[dt];
			unsigned char* ptrSink = (unsigned char*)addrtemp;		
			ptrSink[0] = ptrSource[0];			
			}
			break;
		case 2: 
			{			
			if(((addrtemp%2) ==0) && ((cmDTaddr[dt]%2) ==0))
				{
				unsigned short* ptrSource = (unsigned short*)cmDTaddr[dt];
				unsigned short* ptrSink = (unsigned short*)addrtemp;	
				ptrSink[0] = ptrSource[0];
				}
			}
			break;		
		case 3: 
			{				
			if(((addrtemp%4) ==0) && ((cmDTaddr[dt]%4) ==0))
				{
				unsigned long* ptrSource = (unsigned long*)cmDTaddr[dt];
				unsigned long* ptrSink = (unsigned long*)addrtemp;
				ptrSink[0] = ptrSource[0];
				}
			}
			break;	
		case 4:
			switch(cmDTtypeOut[dt])
			{
				case 1: 
				{
					float var = *(float*)cmDTaddr[dt];
					if(cmDToffset[dt] != 0)
						var += cmDToffset[dt];
					if(cmDTscale[dt] != 0)
						var *= cmDTscale[dt];
					//unsigned char* ptrSource = (unsigned cha*)cmDTaddr[dt];
					unsigned char* ptrSink = (unsigned char*)addrtemp;		
					ptrSink[0] = limit_u8(var+0.5f);//ptrSource[0];			
				}
				break;
				case 2: 
				{			
					if(((addrtemp%2) ==0) && ((cmDTaddr[dt]%2) ==0))
					{
						float var = *(float*)cmDTaddr[dt];
						if(cmDToffset[dt] != 0)
							var += cmDToffset[dt];
						if(cmDTscale[dt] != 0)
							var *= cmDTscale[dt];
						//unsigned char* ptrSource = (unsigned cha*)cmDTaddr[dt];
						unsigned short* ptrSink = (unsigned short*)addrtemp;		
						ptrSink[0] = limit_u16(var+0.5f);//ptrSource[0];		
					}
				}
				break;		
				case 3: 
				{				
					if(((addrtemp%4) ==0) && ((cmDTaddr[dt]%4) ==0))
					{
						float var = *(float*)cmDTaddr[dt];
						if(cmDToffset[dt] != 0)
							var += cmDToffset[dt];
						if(cmDTscale[dt] != 0)
							var *= cmDTscale[dt];
						//unsigned char* ptrSource = (unsigned cha*)cmDTaddr[dt];
						unsigned long* ptrSink = (unsigned long*)addrtemp;		
						ptrSink[0] = limit_u32(var+0.5f);//ptrSource[0];		
					}
				}
				break;
				case 4: 
				{				
					if(((addrtemp%4) ==0) && ((cmDTaddr[dt]%4) ==0))
					{
						float* ptrSource = (float*)cmDTaddr[dt];
						float* ptrSink = (float*)addrtemp;
						ptrSink[0] = ptrSource[0];
						if(cmDToffset[0] != 0)
							ptrSink[0] += cmDToffset[0];
						if(cmDTscale[0] != 0)
							ptrSink[0] *= cmDTscale[0];
					}
				}
				break;
			}
			break;		
		default: 
			break;	
		}		
	}
}

void updateCanRaw(unsigned long addr, unsigned char type, unsigned char ccm, unsigned char bytePos)
{
	unsigned long addrtemp;
	CanMessageSetupStruct *ccmGroup = (CanMessageSetupStruct *)(&ccm00);
	if(addr >= 0xFFFF0000 || addr < 0x000FFFFF)
	{		
		addrtemp = 0xFFFFD100;
		addrtemp += 0x800*(unsigned long)(ccmGroup[ccm].bus&0x01);
		addrtemp += 0x020*(unsigned long)(ccmGroup[ccm].mailBox&0x1F);
		addrtemp += 0x08; //Move to Data Field
		addrtemp += (unsigned long)bytePos&0x07;	//Offset in Data Field
		switch(type)
		{
		case 1: 
			if(((addrtemp%1) ==0) && ((addr%1) ==0))
			{
				unsigned char* ptrSource = (unsigned char*)addr;
				unsigned char* ptrSink = (unsigned char*)addrtemp;		
				ptrSink[0] = ptrSource[0];			
			}
			break;
		case 2: 
			{				
			if(((addrtemp%2) ==0) && ((addr%2) ==0))
				{
				unsigned short* ptrSource = (unsigned short*)addr;
				unsigned short* ptrSink = (unsigned short*)addrtemp;
				ptrSink[0] = ptrSource[0];
				}
			}
			break;		
		case 3: 
			{			
			if(((addrtemp%4) ==0) && ((addr%4) ==0))
				{
				unsigned long* ptrSource = (unsigned long*)addr;
				unsigned long* ptrSink = (unsigned long*)addrtemp;	
				ptrSink[0] = ptrSource[0];
				}
			}
			break;				
		default: 
			break;	
		}		
	}
}

void sendCanMessage(unsigned char ccm)
{
	unsigned short* ptr;
	unsigned char* ptrMB;	
	unsigned short tmp;
	CanMessageSetupStruct *ccmGroup = (CanMessageSetupStruct *)(&ccm00);
	ptrMB = (unsigned char*)(0xFFFFD100 + 0x800*(ccmGroup[ccm].bus&0x01) + 0x20*(ccmGroup[ccm].mailBox&0x1f) + 0x04);			
	if((ptrMB[0]&0x07) == 0x00) //Check if Mailbox is a TX
	{		
		if(ccmGroup[ccm].mailBox>=16)
			{
			tmp = (unsigned short)ccmGroup[ccm].mailBox-16;
			ptr = (unsigned short*)(0xFFFFD000 + 0x800*(ccmGroup[ccm].bus&0x01) + 0x20);	//This is 	TXPR1
			}
		else
			{
			tmp = (unsigned short)ccmGroup[ccm].mailBox;
			ptr = (unsigned short*)(0xFFFFD000 + 0x800*(ccmGroup[ccm].bus&0x01) + 0x22);	//This is 	TXPR0	
			}
		switch(tmp)
		{
			case  0: ptr[0] = 0x001; break;
			case  1: ptr[0] = 0x002; break;
			case  2: ptr[0] = 0x004; break;
			case  3: ptr[0] = 0x008; break;
			case  4: ptr[0] = 0x010; break;
			case  5: ptr[0] = 0x020; break;
			case  6: ptr[0] = 0x040; break;
			case  7: ptr[0] = 0x080; break;
			case  8: ptr[0] = 0x100; break;
			case  9: ptr[0] = 0x200; break;
			case 10: ptr[0] = 0x400; break;
			case 11: ptr[0] = 0x800; break;
			case 12: ptr[0] = 0x1000; break;
			case 13: ptr[0] = 0x2000; break;
			case 14: ptr[0] = 0x4000; break;
			case 15: ptr[0] = 0x8000; break;
			default: break;
		}
	}
}

unsigned short returnShifter(unsigned char c)
{	
	switch(c)
		{
		case  0: return 0x001; break;
		case  1: return 0x002; break;
		case  2: return 0x004; break;
		case  3: return 0x008; break;
		case  4: return 0x010; break;
		case  5: return 0x020; break;
		case  6: return 0x040; break;
		case  7: return 0x080; break;
		case  8: return 0x100; break;
		case  9: return 0x200; break;
		case 10: return 0x400; break;
		case 11: return 0x800; break;
		case 12: return 0x1000; break;
		case 13: return 0x2000; break;
		case 14: return 0x4000; break;
		case 15: return 0x8000; break;
		default: return 0;break;
		}
}

void recieveCanMessage(unsigned char ccm)
{
	unsigned short* ptr;
	unsigned char* ptrMB;	
	unsigned short tmp;
	CanMessageSetupStruct *ccmGroup = (CanMessageSetupStruct *)(&ccm00);
	ptrMB = (unsigned char*)(0xFFFFD100 + 0x800*(ccmGroup[ccm].bus&0x01) + 0x20*(ccmGroup[ccm].mailBox&0x1f) + 0x04);			
	if((ptrMB[0]&0x07) == 0x03) //Check if Mailbox is a TX
	{		
		if(ccmGroup[ccm].mailBox>=16)
		{
			tmp = (unsigned short)ccmGroup[ccm].mailBox-16;
			ptr = (unsigned short*)(0xFFFFD000 + 0x800*(ccmGroup[ccm].bus&0x01) + 0x40);	//This is 	RXPR1
		}
		else
		{
			tmp = (unsigned short)ccmGroup[ccm].mailBox;
			ptr = (unsigned short*)(0xFFFFD000 + 0x800*(ccmGroup[ccm].bus&0x01) + 0x42);	//This is 	RXPR0	
		}	
		if((ptr[0] & returnShifter(tmp)) >0)
		{		
			switch(tmp)
			{
				case  0: ptr[0] = 0x001; break;
				case  1: ptr[0] = 0x002; break;
				case  2: ptr[0] = 0x004; break;
				case  3: ptr[0] = 0x008; break;
				case  4: ptr[0] = 0x010; break;
				case  5: ptr[0] = 0x020; break;
				case  6: ptr[0] = 0x040; break;
				case  7: ptr[0] = 0x080; break;
				case  8: ptr[0] = 0x100; break;
				case  9: ptr[0] = 0x200; break;
				case 10: ptr[0] = 0x400; break;
				case 11: ptr[0] = 0x800; break;
				case 12: ptr[0] = 0x1000; break;
				case 13: ptr[0] = 0x2000; break;
				case 14: ptr[0] = 0x4000; break;
				case 15: ptr[0] = 0x8000; break;
				default: return; break;
			}
				
			if(ccmGroup[ccm].callback >0)
			{
				ptrMB = (unsigned char*)(0xFFFFD100 + 0x800*(ccmGroup[ccm].bus&0x01) + 0x20*(ccmGroup[ccm].mailBox&0x1f) + 0x08);		
				if(ccmGroup[ccm].callback%4 == 0) //Only call it if its U32 alligned
				{
					void (*callbackPtr)(unsigned char*) = (void*)ccmGroup[ccm].callback;
					(*callbackPtr)(ptrMB);					
				}
			}			
		}		
	}
}

unsigned long shC[24] CANDATA = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4192304,8388608};

void canCallbackECA2Packet(unsigned char* data)
{
	if(!data[7])
	{
		pRamVariables.ECA2EthanolContentCAN = data[0];
		pRamVariables.ECA2FuelTemperatureCAN = data[1]-40;	//0 to 165 for -40 to 125C
		pRamVariables.ethanolSensorFault = 0x00;
	}
	else
	{
		pRamVariables.ethanolSensorFault = 0x01;		
	}
	
	pRamVariables.CANBusECAUpdateCounter = CANBusECAUpdateCount;
}

void CANBusECAFailSafeCount()
{
	if(pRamVariables.CANBusECAUpdateCounter > 0) 
	{
		pRamVariables.CANBusECAUpdateCounter--;
		pRamVariables.FailSafeCANBusECAUpdateSwitch = 0;
	}
	else pRamVariables.FailSafeCANBusECAUpdateSwitch = 1;
}

void canCallbackZT3Packet(unsigned char* data)
{
	if(!data[7])
	{
		pRamVariables.ZT3LambdaCAN = (float)data[2]*0.01;
		pRamVariables.ZT3AFRCAN = (float)(data[3])*0.1;
		pRamVariables.ZT3StatusCAN = (unsigned char)data[7];
	}
	else
	{
		pRamVariables.ZT3StatusCAN = (unsigned char)data[7];
	}
}


/*
void canCallbackAEMwideband(unsigned char* data)
{
	pRamVariables.aemLambda = (float)(data[0]*256 + data[1])*0.0001;
	pRamVariables.aemOxygen = (float)(data[2]*256 + data[3])*0.001;
	pRamVariables.aemDataValid = (unsigned char)(data[6])>>7&0x01;
	pRamVariables.aemSensorFault = (unsigned char)(data[7])>>6&0x01;	
}


*/

////////////////////
// *** Setup Function to load Mailbox settings to CPU Can Mailboxes
//////////////////// 
void CanSetup()
{
	unsigned char i = 0;
	CanMessageSetupStruct *ccmGroup = (CanMessageSetupStruct *)(&ccm00);	
	while(i< ccmCount)
	{
		if(ccmGroup[i].mcs < 7)
		{
			setupMailBoxStruct(&ccmGroup[i]);
		}	
		i++;
	}
	pRamVariables.initFunctionRun = 1;	
}


////////////////////
// *** needs to be called every 1mSec
// Checks each Transmit slot to see if it needs to be sent
// Check every Receive slot to see if there is new data
// Calls the RX Callback in case it is configured to run
////////////////////
void CustomCanService()
{
	unsigned char i = 0;
	CanMessageSetupStruct *ccmGroup = (CanMessageSetupStruct *)(&ccm00);
	unsigned char* ptrMB = (unsigned char*)(0xFFFFD100 + 0x800*(ccmGroup[0].bus&0x01) + 0x20*(ccmGroup[0].mailBox&0x1f) + 0x04);		
	
	//Run Can Setup in Case the Init has not run, in case the first mailbox is not setup
	if((pRamVariables.initFunctionRun != 1) || (ccmGroup[0].mcs != (ptrMB[0]&0x07)))
	{
		CanSetup();
	}


	
	//Update all possible DataTransfers, stop when list is seen to be not configured	
	while(i<cmDTCount)
	{
		if(cmDTtypeIn[i] > 0) //update if a Type is defined
		{
			updateCanDT(i);
		}
		i++;
	}
	
	//Send all Possible Messages
	i=0;
	while(i<ccmCount)
	{
		if((ccmGroup[i].mcs == mcsTrans) && (ccmGroup[i].rate>0)) //Send if MCS is set to 0, and has a periodic rate greater than 0
		{
			if(++pRamVariables.ccmSendTimers[i] >= ccmGroup[i].rate) //Send message once 1mSec timer has rolled up
			{
				sendCanMessage(i);
				pRamVariables.ccmSendTimers[i] = 0; //rest timer
			}
		}			
		else if(ccmGroup[i].mcs == mcsReceive) //recieve
		{
			recieveCanMessage(i);	
		}
		i++;
	}
}
#endif
