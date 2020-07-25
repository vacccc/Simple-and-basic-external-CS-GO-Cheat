#pragma once
#include "base de tudo.h"

bool ligarthirdperson = true;

void thirdperson()
{

    if (GetKeyState(VK_NUMPAD4))
    {
        MemClass.writeMem<DWORD>(val.localPlayer + offset.m_iObserverMode, 1);
    }
     
    
    else
    {
        MemClass.writeMem<DWORD>(val.localPlayer + offset.m_iObserverMode, 0);
    }
}