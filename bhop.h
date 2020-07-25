#pragma once

#include "base de tudo.h"

bool bhopligar = true;

void bhop()
{
    //val.flag = MemClass.readMem<BYTE>(val.localPlayer + offset.m_fFlags);

    if (GetAsyncKeyState(VK_SPACE) && val.flag & (1 << 0))

        MemClass.writeMem<DWORD>(val.gameModule + offset.dwForceJump, 6);
}

