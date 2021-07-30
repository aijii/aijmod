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


/*

create table for exhaustCutoutDelay


*/

#include "EcuHacks.h"

#if AUXOUT_HACKS

void UpdateAuxilliaryOutputs()
{
		pRamVariables.exhaustCutoutOutput = SwitchSelect(ExhaustCutoutTableSet, *pManifoldRelativePressure, *pEngineSpeed);	
}

#endif