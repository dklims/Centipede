//CritterBase.cpp
//David Klimavich, November 2016

#include "CritterBase.h"

void CritterBase::ResetFrameCount()
{
	frameCounter = (spriteSize / speed) -1;
}
