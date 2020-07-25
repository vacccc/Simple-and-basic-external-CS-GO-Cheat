#include "base de tudo.h"

bool ligaraimbot = true;

void VectorAngles(const float* forward, float* angles)
{
	float	tmp, yaw, pitch;

	if (forward[1] == 0 && forward[0] == 0)
	{
		yaw = 0;
		if (forward[2] > 0)
			pitch = 270;
		else
			pitch = 90;
	}
	else
	{
		yaw = (atan2(forward[1], forward[0]) * 180 / 3.14f);
		if (yaw < 0)
			yaw += 360;

		tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = (atan2(-forward[2], tmp) * 180 / 3.14f);
		if (pitch < 0)
			pitch += 360;
	}

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}
Vec3 calangle(Vec3 src, Vec3 dir, float xp, float yp)
{
	float output[3];
	float input[3] = { dir.x - src.x , dir.y - src.y, dir.z - src.z };
	VectorAngles(input, output);
	if (output[0] > 180) output[0] -= 360;
	if (output[0] < -180) output[0] += 360;
	if (output[1] > 180) output[1] -= 360;
	if (output[1] < -180) output[1] += 360;
	return { output[0] - xp * 2.f, output[1] - yp * 2.f, 0.f };
}


void aim_bot(DWORD entity, int aim_choice, int aim_smooth)
{
		Vec3 MyEyeLoc;
		Vec3 EnemyBones;
		DWORD Bonebase = MemClass.readMem<DWORD>(entity + offset.m_dwBoneMatrix);
		Vec3 MyLoc = MemClass.readMem<Vec3>(val.localPlayer + offset.m_vecOrigin);
		Vec3 Origin = MemClass.readMem <Vec3>(val.localPlayer + offset.m_vecViewOffset);
		int health = MemClass.readMem<int>(entity + offset.m_iHealth);
		float x = MemClass.readMem<float>(val.Clientstate + offset.dwClientState_ViewAngles);
		float y = MemClass.readMem<float>(val.Clientstate + offset.dwClientState_ViewAngles + 0x4);
		MyEyeLoc.x = MyLoc.x + Origin.x;
		MyEyeLoc.y = MyLoc.y + Origin.y;
		MyEyeLoc.z = MyLoc.z + Origin.z;
		if (aim_choice == 0)
		{
			EnemyBones.x = MemClass.readMem<float>(Bonebase + 0x30 * 8 + 0x0C);
			EnemyBones.y = MemClass.readMem<float>(Bonebase + 0x30 * 8 + 0x1C);
			EnemyBones.z = MemClass.readMem<float>(Bonebase + 0x30 * 8 + 0x2C);
		}
		else if (aim_choice == 1)
		{
			EnemyBones.x = MemClass.readMem<float>(Bonebase + 0x30 * 8 + 0x0C);
			EnemyBones.y = MemClass.readMem<float>(Bonebase + 0x30 * 7 + 0x1C);
			EnemyBones.z = MemClass.readMem<float>(Bonebase + 0x30 * 7 + 0x2C);
		}
		else
		{
			EnemyBones.x = MemClass.readMem<float>(Bonebase + 0x30 * 8 + 0x0C);
			EnemyBones.y = MemClass.readMem<float>(Bonebase + 0x30 * 6 + 0x1C);
			EnemyBones.z = MemClass.readMem<float>(Bonebase + 0x30 * 6 + 0x2C);
		}

		Vec3 Punch = MemClass.readMem<Vec3>(val.localPlayer + offset.m_aimPunchAngle);
		Vec3 Target = calangle(MyEyeLoc, EnemyBones, Punch.x, Punch.y);
		if (health > 0)
		{
			x = x + (Target.x - x) / aim_smooth;
			if (y > 0 && Target.y < 0)
			{
				if (y > 150)
				{
					y = y + ((Target.y + 360) - y) / aim_smooth;
				}
				else
				{
					y = y + (Target.y - y) / aim_smooth;
				}
			}
			else if (y < 0 && Target.y > 0)
			{
				if (y < -150)
				{
					y = y - ((y + 360) - Target.y) / aim_smooth;
				}
				else
				{
					y = y + (Target.y - y) / aim_smooth;
				}
			}
			else
			{
				y = y + (Target.y - y) / aim_smooth;
			}
			if (y > 180)
			{
				y -= 360;
			}
			else if (y < -180)
			{
				y += 360;
			}
			MemClass.writeMem<DWORD>(val.Clientstate + offset.dwClientState_ViewAngles, x);
			MemClass.writeMem<DWORD>(val.Clientstate + offset.dwClientState_ViewAngles + 0x4, y);
		}

}