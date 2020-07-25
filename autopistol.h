#pragma once
#include "base de tudo.h"

bool ligarautopistol = true;

void autopistol()
{
	while ((GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
		// Write "attacking" value to attack.
		MemClass.writeMem<DWORD>(val.gameModule + offset.dwForceAttack, 5);
		Sleep(15);

		// Write "not attacking" value to attack.
		MemClass.writeMem<DWORD>(val.gameModule + offset.dwForceAttack, 4);
		Sleep(15);
	}
}
