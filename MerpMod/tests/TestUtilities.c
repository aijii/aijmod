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

void TestFailed(char *message) __attribute__ ((section ("Misc")));
void TestFailed(char *message)
{
	// This just provides a place to set a breakpoint.
	asm("nop");
}

void Assert(int condition, char *message)
{

	if (condition == 0)
	{
		long shit = 0;
		pRamVariables.RamHoleSpace = shit;
		TestFailed(message);
	}
}

void DemonstrateAssertionFailure() __attribute__ ((section ("Misc")));
void DemonstrateAssertionFailure()
{
	Assert(0, "Just to prove that assertions can fail.");
}

void ClearRam() __attribute__ ((section ("Misc")));
void ClearRam()
{
	long* lpoint = (long*)pRamHoleStart;
	long* end = (long*)0xFFFFBFFF;
	for(; lpoint < end; lpoint++)
	{
		*lpoint = 0;
	}
}
// It's hard to express a floating point number with enough precision to use
// the == operator.  Or impossible: http://en.wikipedia.org/wiki/Machine_epsilon
// Should be sufficient to ensure difference of squares is less than some tolerance
// this will also work for negative numbers
// assumes any floats used anywhere in the ECU or the code are well within
// the limits where their squares will not cause multiplication overflow
int AreCloseEnough(float actual, float expected)
{
    float difference = (actual*actual - expected*expected);
    return difference < 1e-3; //tolerance
}