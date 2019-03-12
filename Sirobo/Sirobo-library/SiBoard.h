#ifndef SiBoard_H
#define SiBoard_H

#include "SiPort.h"

#define NC (0)

/*********************  SiBoard GPIO Map *********************************/

SiPin SiPort[9] = 
{
	{A7,NC},
	{1,0},
	{3,11},
	{9,10},
	{12,A6},
	{A4,A5},
	{A2,A3},
	{7,5},
	{8,6}
};

#endif

