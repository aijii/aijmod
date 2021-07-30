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

float Abs(float input)
{
	if(input > 0.0f)
		return input;
	else
		return input * -1.0f;
}

float LowPass(float input, float limit)
{
	if(input < limit)
		return input;
	else
		return limit;
}

float HighPass(float input, float limit)
{
	if(input > limit)
		return input;
	else
		return limit;
}

float BandPass(float input, float lowlim, float highlim)
{
	if(input > highlim)
		return highlim;
	else if(input < lowlim)
		return lowlim;
	else
		return input;
}

int BandPassInt(int input, int lowlim, int highlim)
{
	if(input > highlim)
		return highlim;
	else if(input < lowlim)
		return lowlim;
	else
		return input;
}

float Smooth(float smoothingFactor, float input, float previous)
{
	float output = previous;
	float diff = input - previous;
	float smooth = BandPass(smoothingFactor,0.1,1);
	output += diff * smooth;
	return output;
}

unsigned char limit_u8(float input)
{
	if(input < 0.0) return 0;
	else if(input > 255.0) return 0xFF;
	else return (unsigned char)input;	
}

unsigned short limit_u16(float input)
{
	if(input < 0.0) return 0;
	else if(input > 65535.0) return 0xFFFF;
	else return (unsigned short)input;	
}

unsigned long limit_u32(float input)
{
	if(input <0.0) return 0;
	else if(input > 4294967295.0) return 0xFFFFFFFF;
	else return (unsigned long)input;	
}
