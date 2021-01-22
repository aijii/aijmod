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


#define COMPTB1_DATA1	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB1_DATA2	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB1_DATA3	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB1_DATA4	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB1_DATA5	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB1_DATA6	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB1_DATA7	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB1_DATA8	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB1_DATA9	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB1_DATA10	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB1_DATA11	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB1_DATA12	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB1_DATA13	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB1_DATA14	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB1_DATA15	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB1_DATA16	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701
#define COMPTB1_DATA COMPTB1_DATA1 COMPTB1_DATA2 COMPTB1_DATA3 COMPTB1_DATA4 COMPTB1_DATA5 COMPTB1_DATA6 COMPTB1_DATA7 COMPTB1_DATA8 COMPTB1_DATA9 COMPTB1_DATA10 COMPTB1_DATA11 COMPTB1_DATA12 COMPTB1_DATA13 COMPTB1_DATA14 COMPTB1_DATA15 COMPTB1_DATA16

#define COMPTB2_DATA1	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB2_DATA2	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB2_DATA3	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB2_DATA4	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB2_DATA5	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB2_DATA6	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB2_DATA7	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB2_DATA8	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB2_DATA9	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB2_DATA10	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB2_DATA11	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB2_DATA12	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB2_DATA13	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB2_DATA14	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB2_DATA15	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,
#define COMPTB2_DATA16	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701,	701
#define COMPTB2_DATA COMPTB2_DATA1 COMPTB2_DATA2 COMPTB2_DATA3 COMPTB2_DATA4 COMPTB2_DATA5 COMPTB2_DATA6 COMPTB2_DATA7 COMPTB2_DATA8 COMPTB2_DATA9 COMPTB2_DATA10 COMPTB2_DATA11 COMPTB2_DATA12 COMPTB2_DATA13 COMPTB2_DATA14 COMPTB2_DATA15 COMPTB2_DATA16

#define COMPTB_COLS 50,75,100,125,150,175,200,225,250,275,300,325,350,375,400,425
#define COMPTB_ROWS 2200,2400,2800,3200,3500,4000,4200,4400,4600,4800,5000,5200,5600,6000,6400,6800

#define COMPWGDCINIT1_DATA1 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT1_DATA2	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT1_DATA3	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT1_DATA4	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT1_DATA5	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT1_DATA6	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT1_DATA7	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT1_DATA8	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT1_DATA9	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT1_DATA10 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT1_DATA11 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT1_DATA12 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT1_DATA13 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT1_DATA14 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT1_DATA15 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT1_DATA16 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0
#define COMPWGDCINIT1_DATA COMPWGDCINIT1_DATA1 COMPWGDCINIT1_DATA2 COMPWGDCINIT1_DATA3 COMPWGDCINIT1_DATA4 COMPWGDCINIT1_DATA5 COMPWGDCINIT1_DATA6 COMPWGDCINIT1_DATA7 COMPWGDCINIT1_DATA8 COMPWGDCINIT1_DATA9 COMPWGDCINIT1_DATA10 COMPWGDCINIT1_DATA11 COMPWGDCINIT1_DATA12 COMPWGDCINIT1_DATA13 COMPWGDCINIT1_DATA14 COMPWGDCINIT1_DATA15 COMPWGDCINIT1_DATA16

#define COMPWGDCMAX1_DATA1 	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX1_DATA2	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX1_DATA3	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX1_DATA4	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX1_DATA5	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX1_DATA6	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX1_DATA7	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX1_DATA8	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX1_DATA9	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX1_DATA10	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX1_DATA11	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX1_DATA12	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX1_DATA13	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX1_DATA14	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX1_DATA15	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX1_DATA16	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0
#define COMPWGDCMAX1_DATA COMPWGDCMAX1_DATA1 COMPWGDCMAX1_DATA2 COMPWGDCMAX1_DATA3 COMPWGDCMAX1_DATA4 COMPWGDCMAX1_DATA5 COMPWGDCMAX1_DATA6 COMPWGDCMAX1_DATA7 COMPWGDCMAX1_DATA8 COMPWGDCMAX1_DATA9 COMPWGDCMAX1_DATA10 COMPWGDCMAX1_DATA11 COMPWGDCMAX1_DATA12 COMPWGDCMAX1_DATA13 COMPWGDCMAX1_DATA14 COMPWGDCMAX1_DATA15 COMPWGDCMAX1_DATA16

#define COMPWGDCINIT2_DATA1 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT2_DATA2	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT2_DATA3	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT2_DATA4	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT2_DATA5	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT2_DATA6	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT2_DATA7	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT2_DATA8	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT2_DATA9	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT2_DATA10 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT2_DATA11 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT2_DATA12 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT2_DATA13 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT2_DATA14 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT2_DATA15 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCINIT2_DATA16 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0
#define COMPWGDCINIT2_DATA COMPWGDCINIT2_DATA1 COMPWGDCINIT2_DATA2 COMPWGDCINIT2_DATA3 COMPWGDCINIT2_DATA4 COMPWGDCINIT2_DATA5 COMPWGDCINIT2_DATA6 COMPWGDCINIT2_DATA7 COMPWGDCINIT2_DATA8 COMPWGDCINIT2_DATA9 COMPWGDCINIT2_DATA10 COMPWGDCINIT2_DATA11 COMPWGDCINIT2_DATA12 COMPWGDCINIT2_DATA13 COMPWGDCINIT2_DATA14 COMPWGDCINIT2_DATA15 COMPWGDCINIT2_DATA16

#define COMPWGDCMAX2_DATA1 	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX2_DATA2	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX2_DATA3	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX2_DATA4	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX2_DATA5	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX2_DATA6	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX2_DATA7	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX2_DATA8	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX2_DATA9	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX2_DATA10	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX2_DATA11	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX2_DATA12	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX2_DATA13	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX2_DATA14	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX2_DATA15	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMPWGDCMAX2_DATA16	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0
#define COMPWGDCMAX2_DATA COMPWGDCMAX2_DATA1 COMPWGDCMAX2_DATA2 COMPWGDCMAX2_DATA3 COMPWGDCMAX2_DATA4 COMPWGDCMAX2_DATA5 COMPWGDCMAX2_DATA6 COMPWGDCMAX2_DATA7 COMPWGDCMAX2_DATA8 COMPWGDCMAX2_DATA9 COMPWGDCMAX2_DATA10 COMPWGDCMAX2_DATA11 COMPWGDCMAX2_DATA12 COMPWGDCMAX2_DATA13 COMPWGDCMAX2_DATA14 COMPWGDCMAX2_DATA15 COMPWGDCMAX2_DATA16

#define COMPWGDC_COLS 50,75,100,125,150,175,200,225,250,275,300,325,350,375,400,425
#define COMPWGDC_ROWS 2200,2400,2800,3200,3500,4000,4200,4400,4600,4800,5000,5200,5600,6000,6400,6800

#define COMP80_DATA1 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMP80_DATA2 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMP80_DATA3 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMP80_DATA4 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMP80_DATA5 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMP80_DATA6 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMP80_DATA7 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMP80_DATA8 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0
#define COMP80_DATA COMP80_DATA1 COMP80_DATA2 COMP80_DATA3 COMP80_DATA4 COMP80_DATA5 COMP80_DATA6 COMP80_DATA7 COMP80_DATA8

#define COMP100_DATA1 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMP100_DATA2 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMP100_DATA3 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMP100_DATA4 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMP100_DATA5 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMP100_DATA6 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMP100_DATA7 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
#define COMP100_DATA8 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0
#define COMP100_DATA COMP100_DATA1 COMP100_DATA2 COMP100_DATA3 COMP100_DATA4 COMP100_DATA5 COMP100_DATA6 COMP100_DATA7 COMP100_DATA8

#define COMP_COLS 100,120,130,140,160,170,190,210,230,240,260,280,300,320,340,350
#define COMP_ROWS 2000,2600,3000,3400,3800,4200,4600,5000,5400,5800,6200,6600,7000,7400,7800,8200

/////////////////
//Constants
/////////////////
#if BOOST_HACKS

unsigned char DefaultBoostHackEnabled BOOSTDATA = HackDisabled;

float RPMLockWGDC BOOSTDATA = 3000.0f;
float ThrottleLockWGDC BOOSTDATA = 85.0f;

unsigned char EGTFailSafeValetModeEnable BOOSTDATA = 0;
unsigned char CoolantTempFailSafeValetModeEnable BOOSTDATA = 0;
unsigned char FBKCHiFailSafeValetModeEnable BOOSTDATA = 0;
unsigned char LeanBoostFailSafeValetModeEnable BOOSTDATA = 0;
unsigned char FuelPressureDeltaFailSafeValetModeEnable BOOSTDATA = 0; 
unsigned char InjectorDutyCycleFailSafeValetModeEnable BOOSTDATA = 0;

#if SWITCH_HACKS
TableGroup PGWGTableGroup BOOSTDATA = {
	{&PGWGTable1i,
	&PGWGTable1s,
	&PGWGTable1ss},
	{&PGWGTable2i,
	&PGWGTable2s,
	&PGWGTable2ss}
};

TableGroup PGTBTableGroup BOOSTDATA = {
	{&PGTBTable1i,
	&PGTBTable1s,
	&PGTBTable1ss},
	{&PGTBTable2i,
	&PGTBTable2s,
	&PGTBTable2ss}
};

TableGroup WGDCInitialTableGroup BOOSTDATA = {
	{&WGDCInitialTable1i,
	&WGDCInitialTable1s,
	&WGDCInitialTable1ss},
	{&WGDCInitialTable2i,
	&WGDCInitialTable2s,
	&WGDCInitialTable2ss}
};

TableGroup WGDCMaxTableGroup BOOSTDATA = {
	{&WGDCMaxTable1i,
	&WGDCMaxTable1s,
	&WGDCMaxTable1ss},
	{&WGDCMaxTable2i,
	&WGDCMaxTable2s,
	&WGDCMaxTable2ss}
};

TableGroup TargetBoostTableGroup BOOSTDATA = {
	{&TargetBoostTable1i,
	&TargetBoostTable1s,
	&TargetBoostTable1ss},
	{&TargetBoostTable2i,
	&TargetBoostTable2s,
	&TargetBoostTable2ss}
};
#endif 

///////////////
//PGWG TABLE 1 i
///////////////
float PGWGCols[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{1,2,3,4,5,6};
float PGWGRows[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{COMPWGDC_ROWS};



ThreeDTable PGWGTable1i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float PGWGCols1i[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{1,2,3,4,5,6};
//float PGWGRows1i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_ROWS};
short PGWGData1i[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600};

ThreeDTable PGWGTable1i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGWGCols,
	.rowHeaderArray = PGWGRows,
	.tableCells = PGWGData1i,
	.tableType = UInt16Table3D,
	.multiplier =  0.00390625f,//0x3B800000
	.offset = 0 };	
	
	
///////////////
//PGWG TABLE 2 i
///////////////
ThreeDTable PGWGTable2i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float PGWGCols2i[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{1,2,3,4,5,6};
//float PGWGRows2i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_ROWS};
short PGWGData2i[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600};

ThreeDTable PGWGTable2i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGWGCols,
	.rowHeaderArray = PGWGRows,
	.tableCells = PGWGData2i,
	.tableType = UInt16Table3D,
	.multiplier = 0.00390625f,//0x3B800000	
	.offset = 0 };
	
#if SWITCH_HACKS
///////////////
//PGWG TABLE 1 s
///////////////
ThreeDTable PGWGTable1s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float PGWGCols1s[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{1,2,3,4,5,6};
//float PGWGRows1s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_ROWS};
short PGWGData1s[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600};

ThreeDTable PGWGTable1s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGWGCols,
	.rowHeaderArray = PGWGRows,
	.tableCells = PGWGData1s,
	.tableType = UInt16Table3D,
	.multiplier =  0.00390625f,//0x3B800000
	.offset = 0 };	
	
	
///////////////
//PGWG TABLE 2 s
///////////////
ThreeDTable PGWGTable2s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float PGWGCols2s[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{1,2,3,4,5,6};
//float PGWGRows2s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_ROWS};
short PGWGData2s[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600};

ThreeDTable PGWGTable2s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGWGCols,
	.rowHeaderArray = PGWGRows,
	.tableCells = PGWGData2s,
	.tableType = UInt16Table3D,
	.multiplier = 0.00390625f,//0x3B800000	
	.offset = 0 };	
	
///////////////
//PGWG TABLE 1 ss
///////////////
ThreeDTable PGWGTable1ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float PGWGCols1ss[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{1,2,3,4,5,6};
//float PGWGRows1ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_ROWS};
short PGWGData1ss[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600};

ThreeDTable PGWGTable1ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGWGCols,
	.rowHeaderArray = PGWGRows,
	.tableCells = PGWGData1ss,
	.tableType = UInt16Table3D,
	.multiplier =  0.00390625f,//0x3B800000
	.offset = 0 };	
	
	
///////////////
//PGWG TABLE 2 ss
///////////////
ThreeDTable PGWGTable2ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float PGWGCols2ss[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{1,2,3,4,5,6};
//float PGWGRows2ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_ROWS};
short PGWGData2ss[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600,
25600,	25600,	25600,	25600,	25600,	25600};

ThreeDTable PGWGTable2ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGWGCols,
	.rowHeaderArray = PGWGRows,
	.tableCells = PGWGData2ss,
	.tableType = UInt16Table3D,
	.multiplier = 0.00390625f,//0x3B800000	
	.offset = 0 };	
#endif

///////////////
//PGWG TABLE VALET MODE
///////////////
ThreeDTable PGWGTableValetMode __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float PGWGColsVM[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{1,2,3,4,5,6};
//float PGWGRowsVM[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMP_ROWS};
short PGWGDataVM[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0,
0,0,0,0,0,0};

ThreeDTable PGWGTableValetMode __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGWGCols,
	.rowHeaderArray = PGWGRows,
	.tableCells = PGWGDataVM,
	.tableType = UInt16Table3D,
	.multiplier = 0.00390625f,//0x3B800000	
	.offset = 0 };
	

///////////////
//PGTB TABLE 1i
///////////////
float PGTBCols[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{1,2,3,4,5,6};
float PGTBRows[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{COMPTB_ROWS};


ThreeDTable PGTBTable1i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float PGTBCols1i[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{1,2,3,4,5,6};
//float PGTBRows1i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPTB_ROWS};
short PGTBData1i[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975};

ThreeDTable PGTBTable1i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGTBCols,
	.rowHeaderArray = PGTBRows,
	.tableCells = PGTBData1i,
	.tableType = UInt16Table3D,
	.multiplier = 1.0f,//0x3F800000 .01933677	
	.offset = 0 };	
	
	
///////////////
//PGTB TABLE 2i
///////////////
ThreeDTable PGTBTable2i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float PGTBCols2i[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{1,2,3,4,5,6};
//float PGTBRows2i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPTB_ROWS};
short PGTBData2i[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001};

ThreeDTable PGTBTable2i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGTBCols,
	.rowHeaderArray = PGTBRows,
	.tableCells = PGTBData2i,
	.tableType = UInt16Table3D,
	.multiplier = 1.0f,//0x3F800000	
	.offset = 0 };

#if SWITCH_HACKS
///////////////
//PGTB TABLE 1s
///////////////
ThreeDTable PGTBTable1s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float PGTBCols1s[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{1,2,3,4,5,6};
//float PGTBRows1s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPTB_ROWS};
short PGTBData1s[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975};

ThreeDTable PGTBTable1s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGTBCols,
	.rowHeaderArray = PGTBRows,
	.tableCells = PGTBData1s,
	.tableType = UInt16Table3D,
	.multiplier = 1.0f,//0x3F800000	
	.offset = 0 };	
	
	
///////////////
//PGTB TABLE 2s
///////////////
ThreeDTable PGTBTable2s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float PGTBCols2s[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{1,2,3,4,5,6};
//float PGTBRows2s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPTB_ROWS};
short PGTBData2s[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001};

ThreeDTable PGTBTable2s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGTBCols,
	.rowHeaderArray = PGTBRows,
	.tableCells = PGTBData2s,
	.tableType = UInt16Table3D,
	.multiplier = 1.0f,//0x3F800000	
	.offset = 0 };


///////////////
//PGTB TABLE 1ss
///////////////
ThreeDTable PGTBTable1ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float PGTBCols1ss[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{1,2,3,4,5,6};
//float PGTBRows1ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPTB_ROWS};
short PGTBData1ss[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975,
1975,	1975,	1975,	1975,	1975,	1975};

ThreeDTable PGTBTable1ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGTBCols,
	.rowHeaderArray = PGTBRows,
	.tableCells = PGTBData1ss,
	.tableType = UInt16Table3D,
	.multiplier = 1.0f,//0x3F800000	
	.offset = 0 };	
	
	
///////////////
//PGTB TABLE 2ss
///////////////
ThreeDTable PGTBTable2ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float PGTBCols2ss[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{1,2,3,4,5,6};
//float PGTBRows2ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPTB_ROWS};
short PGTBData2ss[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001,
2001,	2001,	2001,	2001,	2001,	2001};

ThreeDTable PGTBTable2ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGTBCols,
	.rowHeaderArray = PGTBRows,
	.tableCells = PGTBData2ss,
	.tableType = UInt16Table3D,
	.multiplier = 1.0f,//0x3F800000	
	.offset = 0 };
#endif

///////////////
//PGTB TABLE VALET MODE
///////////////
ThreeDTable PGTBTableValetMode __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float PGTBColsVM[6] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{1,2,3,4,5,6};
//float PGTBRowsVM[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMP_ROWS};
short PGTBDataVM[96] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{760,760,760,760,760,760,
760,760,760,760,760,760,
760,760,760,760,760,760,
760,760,760,760,760,760,
760,760,760,760,760,760,
760,760,760,760,760,760,
760,760,760,760,760,760,
760,760,760,760,760,760,
760,760,760,760,760,760,
760,760,760,760,760,760,
760,760,760,760,760,760,
760,760,760,760,760,760,
760,760,760,760,760,760,
760,760,760,760,760,760,
760,760,760,760,760,760,
760,760,760,760,760,760};

ThreeDTable PGTBTableValetMode __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 6,
	.rowCount = 16,
	.columnHeaderArray = PGTBCols,
	.rowHeaderArray = PGTBRows,
	.tableCells = PGTBDataVM,
	.tableType = UInt16Table3D,
	.multiplier = 1.0f,//0x3F800000	
	.offset = 0 };
	

///////////////////
//WGDC Initial Table 1i LUT
///////////////////
float WGDCInitialCols[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{COMPWGDC_COLS};
float WGDCInitialRows[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{COMPWGDC_ROWS};


ThreeDTable WGDCInitialTable1i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float WGDCInitialCols1i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_COLS};
//float WGDCInitialRows1i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_ROWS};
short WGDCInitialData1i[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{COMPWGDCINIT1_DATA};

ThreeDTable WGDCInitialTable1i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = WGDCInitialCols,
	.rowHeaderArray = WGDCInitialRows,
	.tableCells = WGDCInitialData1i,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)

///////////////////
//WGDC Initial Table 2 LUT
///////////////////
ThreeDTable WGDCInitialTable2i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float WGDCInitialCols2i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_COLS};
//float WGDCInitialRows2i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_ROWS};
short WGDCInitialData2i[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{COMPWGDCINIT2_DATA};

ThreeDTable WGDCInitialTable2i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = WGDCInitialCols,
	.rowHeaderArray = WGDCInitialRows,
	.tableCells = WGDCInitialData2i,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,	
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)

#if SWITCH_HACKS
///////////////////
//WGDC Initial Table 1s LUT
///////////////////
ThreeDTable WGDCInitialTable1s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float WGDCInitialCols1s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_COLS};
//float WGDCInitialRows1s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_ROWS};
short WGDCInitialData1s[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{COMPWGDCINIT1_DATA};

ThreeDTable WGDCInitialTable1s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = WGDCInitialCols,
	.rowHeaderArray = WGDCInitialRows,
	.tableCells = WGDCInitialData1s,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)

///////////////////
//WGDC Initial Table 2s LUT
///////////////////
ThreeDTable WGDCInitialTable2s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float WGDCInitialCols2s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_COLS};
//float WGDCInitialRows2s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_ROWS};
short WGDCInitialData2s[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{COMPWGDCINIT2_DATA};

ThreeDTable WGDCInitialTable2s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = WGDCInitialCols,
	.rowHeaderArray = WGDCInitialRows,
	.tableCells = WGDCInitialData2s,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,	
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)

///////////////////
//WGDC Initial Table 1ss LUT
///////////////////
ThreeDTable WGDCInitialTable1ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float WGDCInitialCols1ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_COLS};
//float WGDCInitialRows1ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_ROWS};
short WGDCInitialData1ss[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{COMPWGDCINIT1_DATA};

ThreeDTable WGDCInitialTable1ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = WGDCInitialCols,
	.rowHeaderArray = WGDCInitialRows,
	.tableCells = WGDCInitialData1ss,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)

///////////////////
//WGDC Initial Table 2ss LUT
///////////////////
ThreeDTable WGDCInitialTable2ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float WGDCInitialCols2ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_COLS};
//float WGDCInitialRows2ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_ROWS};
short WGDCInitialData2ss[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{COMPWGDCINIT2_DATA};

ThreeDTable WGDCInitialTable2ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = WGDCInitialCols,
	.rowHeaderArray = WGDCInitialRows,
	.tableCells = WGDCInitialData2ss,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,	
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)
#endif

///////////////////
//WGDC Max Table 1i LUT
///////////////////

float WGDCMaxCols[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{COMPWGDC_COLS};
float WGDCMaxRows[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{COMPWGDC_ROWS};

ThreeDTable WGDCMaxTable1i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));

//float WGDCMaxCols1i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_COLS};
//float WGDCMaxRows1i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_ROWS};

short WGDCMaxData1i[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{COMPWGDCMAX1_DATA};

ThreeDTable WGDCMaxTable1i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = WGDCMaxCols,
	.rowHeaderArray = WGDCMaxRows,
	.tableCells = WGDCMaxData1i,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)
	
///////////////////
//WGDC Max Table 2i LUT
///////////////////
ThreeDTable WGDCMaxTable2i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float WGDCMaxCols2i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_COLS};
//float WGDCMaxRows2i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_ROWS};
short WGDCMaxData2i[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{COMPWGDCMAX2_DATA};

ThreeDTable WGDCMaxTable2i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = WGDCMaxCols,
	.rowHeaderArray = WGDCMaxRows,
	.tableCells = WGDCMaxData2i,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)

#if SWITCH_HACKS
///////////////////
//WGDC Max Table 1s LUT
///////////////////
ThreeDTable WGDCMaxTable1s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float WGDCMaxCols1s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_COLS};
//float WGDCMaxRows1s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_ROWS};
short WGDCMaxData1s[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{COMPWGDCMAX1_DATA};

ThreeDTable WGDCMaxTable1s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = WGDCMaxCols,
	.rowHeaderArray = WGDCMaxRows,
	.tableCells = WGDCMaxData1s,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)
	
///////////////////
//WGDC Max Table 2s LUT
///////////////////
ThreeDTable WGDCMaxTable2s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float WGDCMaxCols2s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_COLS};
//float WGDCMaxRows2s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_ROWS};
short WGDCMaxData2s[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{COMPWGDCMAX2_DATA};

ThreeDTable WGDCMaxTable2s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = WGDCMaxCols,
	.rowHeaderArray = WGDCMaxRows,
	.tableCells = WGDCMaxData2s,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)
	
///////////////////
//WGDC Max Table 1ss LUT
///////////////////
ThreeDTable WGDCMaxTable1ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float WGDCMaxCols1ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_COLS};
//float WGDCMaxRows1ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_ROWS};
short WGDCMaxData1ss[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{COMPWGDCMAX1_DATA};

ThreeDTable WGDCMaxTable1ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = WGDCMaxCols,
	.rowHeaderArray = WGDCMaxRows,
	.tableCells = WGDCMaxData1ss,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)
	
///////////////////
//WGDC Max Table 2ss LUT
///////////////////
ThreeDTable WGDCMaxTable2ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float WGDCMaxCols2ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_COLS};
//float WGDCMaxRows2ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPWGDC_ROWS};
short WGDCMaxData2ss[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{COMPWGDCMAX2_DATA};

ThreeDTable WGDCMaxTable2ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = WGDCMaxCols,
	.rowHeaderArray = WGDCMaxRows,
	.tableCells = WGDCMaxData2ss,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)
#endif

///////////////////
//Target Boost Table 1i
///////////////////

float TBCols[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{COMPTB_COLS};
float TBRows[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
{COMPTB_ROWS};


ThreeDTable TargetBoostTable1i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float TBCols1i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPTB_COLS};
//float TBRows1i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPTB_ROWS};
short TBData1i[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{COMPTB1_DATA};

ThreeDTable TargetBoostTable1i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = TBCols,
	.rowHeaderArray = TBRows,
	.tableCells = TBData1i,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,	
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)
	
///////////////////
//Target Boost Table 2i
///////////////////
ThreeDTable TargetBoostTable2i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float TBCols2i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPTB_COLS};
//float TBRows2i[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPTB_ROWS};
short TBData2i[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{COMPTB2_DATA};

ThreeDTable TargetBoostTable2i __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = TBCols,
	.rowHeaderArray = TBRows,
	.tableCells = TBData2i,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,	
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)

#if SWITCH_HACKS
///////////////////
//Target Boost Table 1s
///////////////////
ThreeDTable TargetBoostTable1s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float TBCols1s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPTB_COLS};
//float TBRows1s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPTB_ROWS};
short TBData1s[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{COMPTB1_DATA};

ThreeDTable TargetBoostTable1s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = TBCols,
	.rowHeaderArray = TBRows,
	.tableCells = TBData1s,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,	
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)
	
///////////////////
//Target Boost Table 2s
///////////////////
ThreeDTable TargetBoostTable2s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float TBCols2s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPTB_COLS};
//float TBRows2s[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPTB_ROWS};
short TBData2s[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{COMPTB2_DATA};

ThreeDTable TargetBoostTable2s __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = TBCols,
	.rowHeaderArray = TBRows,
	.tableCells = TBData2s,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,	
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)

///////////////////
//Target Boost Table 1ss
///////////////////
ThreeDTable TargetBoostTable1ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float TBCols1ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPTB_COLS};
//float TBRows1ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPTB_ROWS};
short TBData1ss[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{COMPTB1_DATA};

ThreeDTable TargetBoostTable1ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = TBCols,
	.rowHeaderArray = TBRows,
	.tableCells = TBData1ss,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,	
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)
	
///////////////////
//Target Boost Table 2ss
///////////////////
ThreeDTable TargetBoostTable2ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4)));
//float TBCols2ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPTB_COLS};
//float TBRows2ss[16] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = 
//{COMPTB_ROWS};
short TBData2ss[256] __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) =
{COMPTB2_DATA};

ThreeDTable TargetBoostTable2ss __attribute__ ((section ("RomHole_SpeedDensityTables"),aligned(4))) = {
	.columnCount = 16,
	.rowCount = 16,
	.columnHeaderArray = TBCols,
	.rowHeaderArray = TBRows,
	.tableCells = TBData2ss,
	.tableType = UInt16Table3D,
	.multiplier = 0.000061037f,	
	.offset = 0 };				//! /32767  (0-? range, 16bit precision)

#endif
	
#endif