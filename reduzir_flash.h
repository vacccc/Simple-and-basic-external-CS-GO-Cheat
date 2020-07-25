#pragma once
#include "base de tudo.h"

bool ligar_reduzirF = true;

void reduzirF()
{
	int flashDur = 0;

    while (true)
    {
        flashDur = MemClass.readMem<int>(val.localPlayer + offset.m_flFlashDuration);
        if (flashDur > 0)
            MemClass.writeMem<int>(val.localPlayer + offset.m_flFlashDuration, 0);

        Sleep(1);
    }
}
