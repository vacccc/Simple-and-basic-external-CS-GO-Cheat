#pragma once

#include "base de tudo.h"

bool glowligar = true;


DWORD glowObject = MemClass.readMem<DWORD>(val.gameModule + offset.dwGlowObjectManager);
int myTeam = MemClass.readMem<int>(val.localPlayer + offset.m_iTeamNum);

void glow()
{
    DWORD glowObject = MemClass.readMem<DWORD>(val.gameModule + offset.dwGlowObjectManager);
    int myTeam = MemClass.readMem<int>(val.localPlayer + offset.m_iTeamNum);

    for (short int i = 0; i < 64; i++)
    {
        DWORD entity = MemClass.readMem<DWORD>(val.gameModule + offset.dwEntityList + i * 0x10);
        if (entity != NULL)
        {
            int glowIndx = MemClass.readMem<int>(entity + offset.m_iGlowIndex);
            int entityTeam = MemClass.readMem<int>(entity + offset.m_iTeamNum);

            if (myTeam == entityTeam)
            {
                MemClass.writeMem<float>(glowObject + ((glowIndx * 0x38) + 0x4), 0.0f);
                MemClass.writeMem<float>(glowObject + ((glowIndx * 0x38) + 0x8), 0.0f);
                MemClass.writeMem<float>(glowObject + ((glowIndx * 0x38) + 0xC), 2.0f);
                MemClass.writeMem<float>(glowObject + ((glowIndx * 0x38) + 0x10), 0.0f);
            }
            else
            {
                MemClass.writeMem<float>(glowObject + ((glowIndx * 0x38) + 0x4), 1.0f);
                MemClass.writeMem<float>(glowObject + ((glowIndx * 0x38) + 0x8), 0.0f);
                MemClass.writeMem<float>(glowObject + ((glowIndx * 0x38) + 0xC), 2.5f);
                MemClass.writeMem<float>(glowObject + ((glowIndx * 0x38) + 0x10), 0.3f);
            }
            MemClass.writeMem<bool>(glowObject + ((glowIndx * 0x38) + 0x24), true);
            MemClass.writeMem<bool>(glowObject + ((glowIndx * 0x38) + 0x25), false);
        }
    }


}