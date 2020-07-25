#pragma once

#include "base de tudo.h"

bool ligartriggerbot = true;

bool checkIfScoped()
{
    return MemClass.readMem<bool>(val.localPlayer + offset.m_bIsScoped);
}

void setTBDelay(float distance)
{
    float delay;
    switch (val.myWeaponID)
    {
    case 262204: delay = 3; break;
    case 7: delay = 3.3; break;
    case 40: delay = 0.15; break;
    case 9: delay = 0.15; break;
    default: delay = 0;
    }
    val.tbDelay = delay * distance;
}

void getMyWeapon()
{
    int weapon = MemClass.readMem<int>(val.localPlayer + offset.m_hActiveWeapon);
    int weaponEntity = MemClass.readMem<int>(val.gameModule + offset.dwEntityList + ((weapon & 0xFFF) - 1) * 0x10);
    if (weaponEntity != NULL)
        val.myWeaponID = MemClass.readMem<int>(weaponEntity + offset.m_iItemDefinitionIndex);
}

float getDistance(DWORD entity)
{
    vector myLocation = MemClass.readMem<vector>(val.localPlayer + offset.m_vecOrigin);
    vector enemyLocation = MemClass.readMem<vector>(entity + offset.m_vecOrigin);

    return sqrt(pow(myLocation.x - enemyLocation.x, 2) + pow(myLocation.y - enemyLocation.y, 2) + pow(myLocation.z - enemyLocation.z, 2)) * 0.0254;
}

void shoot()
{
    Sleep(val.tbDelay);
    MemClass.writeMem<int>(val.gameModule + offset.dwForceAttack, 5);
    Sleep(20);
    MemClass.writeMem<int>(val.gameModule + offset.dwForceAttack, 4);
    
    //  std::cout << "triggerbot: shoot" << std::endl;

}

bool checkTBot()
{
    int crosshair = MemClass.readMem<int>(val.localPlayer + offset.m_iCrosshairId);
    if (crosshair != 0 && crosshair < 64)
    {
        DWORD entity = MemClass.readMem<DWORD>(val.gameModule + offset.dwEntityList + ((crosshair - 1) * 0x10));
        int eTeam = MemClass.readMem<int>(entity + offset.m_iTeamNum);
        int eHealth = MemClass.readMem<int>(entity + offset.m_iHealth);
        if (eTeam != val.myTeam && eHealth > 0)
        {
            float distance = getDistance(entity);
            getMyWeapon();
            setTBDelay(distance);
            if (val.myWeaponID == 40 || val.myWeaponID == 9)
                return checkIfScoped();
            else
                return true;
        }
        else
            return false;
    }
    else
        return false;
}

void handleTBot()
{
    
    if (checkTBot())
        shoot();
}

void triggerbot()
{
    val.flag = MemClass.readMem<BYTE>(val.localPlayer + offset.m_fFlags);
    bool canTBot = false, keyHeld = false;

    if (GetAsyncKeyState(VK_F2) & 1)
    {
        //std::cout << "triggerbot: ON / OFF" << std::endl;

        val.myTeam = MemClass.readMem<int>(val.localPlayer + offset.m_iTeamNum);
        canTBot = !canTBot;

    }

    if (GetAsyncKeyState(VK_MENU) == KeyDOWN && !keyHeld)
    {

        //std::cout <<  "triggerbot: precionando" << std::endl;
        keyHeld = true;
        canTBot = true;
    }
    if (GetAsyncKeyState(VK_MENU) == KeyUP && keyHeld)
    {
        //std::cout << "triggerbot: botao solto" << std::endl;
        keyHeld = false;
        canTBot = false;
    }

    if (canTBot)
        handleTBot();

   
}
