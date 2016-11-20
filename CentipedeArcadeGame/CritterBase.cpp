#include "CritterBase.h"

void CritterBase::ResetFrameCount()
{
	frameCounter = (spriteSize / speed) -1;
}
