#pragma once
#include <Windows.h>
#include <iostream>
#include <cmath>
#include "MemMan.h"
#include "offsetsDoHazedumper.h"
#include <d3d9.h>
#include <tchar.h>
#include<ctime>

struct Vec3
{
    float x, y, z;
};
struct Vec4
{
    float x, y, z, w;
};
struct view
{
    float v[16];
};

#define KeyDOWN -32768
#define KeyUP 0



MemMan MemClass;



struct variables
{
    DWORD localPlayer;
    DWORD engineModule;
    BYTE flag;
    DWORD gameModule;
    DWORD Clientstate;
    int myTeam;
    int tbDelay;
    int myWeaponID;
} val;

struct vector
{
    float x, y, z;
};
