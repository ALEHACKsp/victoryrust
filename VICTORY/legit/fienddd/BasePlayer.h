//CLASS BASEPLAYER
#include <Windows.h>
#include <iostream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <stdlib.h>
//#include "xor.h"
//#include "lw_http.hpp"
#include <ostream>
#include <regex>

//#include "hwid.h"
#include <chrono>
//#include "crypto.h"
#include <sstream>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <iostream>

#include <fstream>
#include <filesystem>
#include <string>
#include <Windows.h>
#include <fstream>
#include <iostream>
#include<iostream>
#include<string.h>
#include<string>
#include <iostream>
#include <sstream>
#include <limits>

#include <future>

#include <Windows.h>
#include <iostream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <stdlib.h>

#include <ostream>
#include <regex>
#include "Math.h"
#include "driver.h"
#include "offsets.h"
#include "Vars.h"

using namespace std;

#define safe_write(Addr, Data, Type) driver::write<Type>(Addr, Data)

Vector3 GetPrefabPos(UINT64 PrefabBase) {
	UINT64 Object = driver::read<UINT64>(PrefabBase + 0x10);
	UINT64 ObjectClass = driver::read<UINT64>(Object + 0x30);
	UINT64 GameObject = driver::read<UINT64>(ObjectClass + 0x30);
	UINT64 Transform = driver::read<UINT64>(GameObject + 0x8);
	UINT64 Vec = driver::read<UINT64>(Transform + 0x38);

	return driver::read<Vector3>(Vec + 0x90);
}

UINT64 TodCycle;


std::string GetPrefabName(std::string output) {
	//ORES
	if (output == "assets/bundled/prefabs/autospawn/resource/ores/sulfur-ore.prefab" && Vars::Visuals::WORLD::Nodes) {
		return "NSulfur Ore";
	}
	if (output == "assets/bundled/prefabs/autospawn/collectable/stone/sulfur-collectable.prefab" && Vars::Visuals::WORLD::NodesCollectable) {
		return "NSulfur Collectable";
	}
	if (output == "assets/bundled/prefabs/autospawn/resource/ores/stone-ore.prefab" && Vars::Visuals::WORLD::Nodes) {
		return "NStone Ore";
	}
	if (output == "assets/bundled/prefabs/autospawn/collectable/stone/stone-collectable.prefab" && Vars::Visuals::WORLD::NodesCollectable) {
		return "NStone Collectable";
	}
	if (output == "assets/bundled/prefabs/autospawn/resource/ores/metal-ore.prefab" && Vars::Visuals::WORLD::Nodes) {
		return "NMetal Ore";
	}
	if (output == "assets/bundled/prefabs/autospawn/collectable/stone/metal-collectable.prefab" && Vars::Visuals::WORLD::NodesCollectable) {
		return "NMetal Collectable";
	}
	if (output == "assets/bundled/prefabs/autospawn/collectable/hemp/hemp-collectable.prefab" && Vars::Visuals::WORLD::Hemp) {
		return "HHemp";
	}
	if (output == "assets/content/vehicles/boats/rhib/rhib.prefab" && Vars::Visuals::WORLD::Other) {
		return "ORHIB";
	}
	if (output == "assets/bundled/prefabs/autospawn/collectable/wood/wood-collectable.prefab" && Vars::Visuals::WORLD::NodesCollectable) {
		return "NWood Collectable";
	}
	if (output == "assets/prefabs/misc/item drop/item_drop_backpack.prefab" && Vars::Visuals::WORLD::Bags) {
		return "BBackpack";
	}


	//MISC
	if (output == "assets/prefabs/deployable/small stash/small_stash_deployed.prefab" && Vars::Visuals::WORLD::Stash) {
		return "SStash";
	}
	if (output == "assets/prefabs/player/player_corpse.prefab" && Vars::Visuals::WORLD::Corpse) {
		return "CPLAYER CORPSE";
	}
	if (output == "syringe.medical (world)" && Vars::Visuals::WORLD::Other) {
		return "OMED SYRINGE";
	}
	if (output == "keycard_green (world)" && Vars::Visuals::WORLD::Other) {
		return "OGREEN KEYCARD";
	}


	//GUNS
	if (output == "rifle.ak (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GAK47";
	}
	if (output == "syringe.medical (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GSEMI RIFLE";
	}
	if (output == "lmg.m249 (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GM249";
	}
	if (output == "rifle.lr300 (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GLR-300";
	}
	if (output == "rifle.lr300 (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GLR-300";
	}
	if (output == "pistol.semiauto (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GSEMI PISTOL";
	}
	if (output == "rifle.l96 (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GL96";
	}
	if (output == "rifle.m39 (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GM39";
	}
	if (output == "pistol.m92 (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GM92";
	}
	if (output == "smg.mp5 (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GMP5";
	}
	if (output == "multiplegrenadelauncher (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GGRENADE LAUNCHER";
	}
	if (output == "pistol.nailgun (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GNAILGUN";
	}
	if (output == "shotgun.pump (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GPUMP SHOTGUN";
	}
	if (output == "pistol.python (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GPYTHON";
	}
	if (output == "pistol.revolver (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GREVOLVER";
	}
	if (output == "rocket.launcher (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GROCKET LAUNCHER";
	}
	if (output == "shotgun.double (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GDOUBLE BARREL";
	}
	if (output == "smg.2 (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GCUSTOM SMG";
	}
	if (output == "smg.thompson (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GTOMMY";
	}
	if (output == "crossbow (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GCROSSBOW";
	}
	if (output == "rifle.bolt (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GBOLTY";
	}
	if (output == "shotgun.spas12 (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GSPAS-12";
	}
	if (output == "bow.hunting (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GBOW";
	}
	if (output == "bow.compound (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GCOMPOUND BOW";
	}
	if (output == "shotgun.waterpipe (world)" && Vars::Visuals::WORLD::Weapons) {
		return "GWATERPIPE";
	}

	return "ZOther";

}
bool IsValidPrefab(std::string output) {
	//assets/prefabs/weapon mods/lasersight/lasersight.entity.prefab
	//assets/bundled/prefabs/autospawn/resource/ores/stone-ore.prefab
	//assets/bundled/prefabs/autospawn/resource/ores/sulfur-ore.prefab
	//assets/bundled/prefabs/autospawn/resource/ores/metal-ore.prefab
	//assets/bundled/prefabs/autospawn/collectable/stone/stone-collectable.prefab
	//assets/bundled/prefabs/autospawn/collectable/stone/sulfur-collectable.prefab
	//assets/bundled/prefabs/autospawn/collectable/stone/metal-collectable.prefab
	//assets/prefabs/deployable/chinooklockedcrate/codelockedhackablecrate_oilrig.prefab
	//assets/prefabs/weapons/m39 emr/m39.entity.prefab
	//assets/prefabs/weapons/m92/m92.entity.prefab
	//assets/rust.ai/agents/bear/bear.prefab
	/*
	assets/prefabs/weapons/lr300/lr300.entity.prefab
	assets/prefabs/weapons/m249/m249.entity.prefab
	assets/prefabs/weapons/semi auto rifle/semi_auto_rifle.entity.prefab
	*/
	/*if (output == "assets/prefabs/deployable/small stash/small_stash_deployed.prefab") {
		return true;
	}
	if (output == "assets/bundled/prefabs/autospawn/resource/ores/sulfur-ore.prefab") {
		return true;
	}
	if (output == "assets/bundled/prefabs/autospawn/resource/ores/stone-ore.prefab") {
		return true;
	}
	if (output == "assets/bundled/prefabs/autospawn/resource/ores/metal-ore.prefab") {
		return true;
	}
	if (output == "assets/bundled/prefabs/autospawn/collectable/hemp/hemp-collectable.prefab") {
		return true;
	}
	if (output == "assets/content/vehicles/boats/rhib/rhib.prefab") {
		return true;
	}*/
	std::string PrefabName = GetPrefabName(output);
	if (PrefabName != "ZOther") {
		return true;
	}

	return false;

}


//bool PrefabEsp(std::string output, BasePlayer* ThisPlayer2) {
//
//	//assets/bundled/prefabs/autospawn/collectable/hemp/hemp-collectable.prefab //HEMP
//	//assets/bundled/prefabs/autospawn/resource/ores/sulfur-ore.prefab //SULFUR
//	//assets/bundled/prefabs/autospawn/resource/ores/metal-ore.prefab //METAL
//	//assets/bundled/prefabs/autospawn/resource/ores/stone-ore.prefab //STONE
//	//assets/bundled/prefabs/radtown/crate_tools.prefab //TOOL CRATE
//	//assets/bundled/prefabs/radtown/crate_normal_2.prefab //NORMAL CRATE 2
//	//assets/bundled/prefabs/radtown/loot_barrel_1.prefab //LOOT BARREL 1
//	//assets/bundled/prefabs/radtown/loot_barrel_2.prefab //LOOT BARREL 2
//	//assets/content/vehicles/boats/rhib/rhib.prefab //RHIB
//	//assets/prefabs/weapons/ak47u/ak47u.entity.prefab //AK PREFAB
//
//	//assets/content/vehicles/boats/rowboat/rowboat.prefab //ROW BOAT
//
//	//assets/prefabs/deployable/small stash/small_stash_deployed.prefab //STASH
//	//assets/prefabs/weapons/bow/bow_hunting.entity.prefab //HUNTING BOW
//
//	if (output == "assets/prefabs/deployable/small stash/small_stash_deployed.prefab") {
//		Vector3 PrefabPosition = ThisPlayer2->GetPrefabPos();
//		
//		if (GlobalOther::IsInRange(ULocalPlayerHead, PrefabPosition)) {
//			TempPrefabs[PrefabIterations].WorldPos = PrefabPosition;
//			TempPrefabs[PrefabIterations].Name = "STASH";
//			PrefabIterations++;
//			return true;
//
//		}
//	}
//	else if (output == "assets/bundled/prefabs/autospawn/resource/ores/sulfur-ore.prefab") {
//		Vector3 PrefabPosition = ThisPlayer2->GetPrefabPos();
//		
//		if (GlobalOther::IsInRange(ULocalPlayerHead, PrefabPosition)) {
//			TempPrefabs[PrefabIterations].WorldPos = PrefabPosition;
//			TempPrefabs[PrefabIterations].Name = "SULFUR";
//			PrefabIterations++;
//			return true;
//
//		}
//	}
//	else if (output == "assets/bundled/prefabs/autospawn/resource/ores/stone-ore.prefab") {
//	//else if (output.substr(47, 5) == "stone") {
//		Vector3 PrefabPosition = ThisPlayer2->GetPrefabPos();
//		if (GlobalOther::IsInRange(ULocalPlayerHead, PrefabPosition)) {
//			TempPrefabs[PrefabIterations].WorldPos = PrefabPosition;
//			TempPrefabs[PrefabIterations].Name = "STONE";
//			PrefabIterations++;
//			return true;
//		}
//		
//	}
//	else if (output == "assets/bundled/prefabs/autospawn/resource/ores/metal-ore.prefab") {
//		Vector3 PrefabPosition = ThisPlayer2->GetPrefabPos();
//		
//		if (GlobalOther::IsInRange(ULocalPlayerHead, PrefabPosition)) {
//			TempPrefabs[PrefabIterations].WorldPos = PrefabPosition;
//			TempPrefabs[PrefabIterations].Name = "METAL";
//			PrefabIterations++;
//			return true;
//		}
//	}
//	else if (output == "assets/bundled/prefabs/autospawn/collectable/hemp/hemp-collectable.prefab" && Vars::Visuals::WORLD::Hemp) {
//	//else if (output.substr(50, 4) == "hemp" && Vars::Visuals::WORLD::Hemp) {
//		Vector3 PrefabPosition = ThisPlayer2->GetPrefabPos();
//		
//		if (GlobalOther::IsInRange(ULocalPlayerHead, PrefabPosition)) {
//			TempPrefabs[PrefabIterations].WorldPos = PrefabPosition;
//			TempPrefabs[PrefabIterations].Name = "HEMP";
//			PrefabIterations++;
//			return true;
//
//		}
//	}
//	
//	else
//	{
//		return false;
//	}
//
//	
//	
//
//}
//

namespace GlobalOther {
	bool IsInRange(Vector3 LocalPos, Vector3 EnemyPos) {
		float DistanceX = LocalPos.x - EnemyPos.x;
		float DistanceY = LocalPos.z - EnemyPos.z;
		float Distance = sqrt((DistanceX * DistanceX) + (DistanceY * DistanceY));
		if (Vars::Visuals::PREFABRANGE < Distance) {
			return false;
		}
		else
		{
			return true;
		}

	}
}

class WeaponData
{
public:
	int GetItemID()
	{
		UINT64 Info = driver::read<UINT64>((const uintptr_t)this + oItemDefinition);
		return driver::read<int>((const uintptr_t)Info + oItemid);
	}
	int GetUID()
	{
		return driver::read<int>((const uintptr_t)this + 0x28);
	}
	void InstaBow()
	{
		if (Vars::Misc::InstaBow)
		{
			DWORD64 Held = driver::read<DWORD64>((const uintptr_t)this + oHeld);
			if (driver::read<int>(Held + 0x360) != 1) {
				driver::write<bool>(Held + 0x360, true);
			}
			if (driver::read<BYTE>(Held + 0x364) != 1) {
				driver::write<BYTE>(Held + 0x364, 1);
			}
		}
	}

	void SuperEoka()
	{
		if (Vars::Misc::InstaEoka) {
			DWORD64 Held = driver::read<DWORD>((const uintptr_t)this + oHeld);
			
			driver::write<float>(Held + oSuccessFraction, 0.0f);
			
		}
	}
	void Compund() {
		if (Vars::Misc::compound)
		{
			UINT64 Held = driver::read<UINT64>((const uintptr_t)this + oHeld);

			if (driver::read<float>(Held + 0x378) > 0.1f && GetAsyncKeyState(VK_RBUTTON)) {
				driver::write<float>(Held + 0x378, 0.0f);
			}


		}
	}
	void CripHold(bool Zoom, bool ADSSpeed/*, bool Sway*/, bool NoLower, bool NoBob) {
		if (Vars::Misc::bCripHold) {
			UINT64 Held = driver::read<UINT64>((const uintptr_t)this + oHeld);
			UINT64 ViewModel = driver::read<UINT64>(Held + 0x188);
			UINT64 ViewModelInstance = driver::read<UINT64>(ViewModel + 0x28);

		}
	}
	void AntiSpread()
	{
		if (Vars::Misc::anti_spread)
		{

			UINT64 Held = driver::read<UINT64>((const uintptr_t)this + oHeld);
			//std::cout << Held << std::endl;
			if (driver::read<float>(Held + oStancePenalty) != 0.0f) {
				driver::write<float>(Held + oStancePenalty, 0.0f);
				std::this_thread::sleep_for(chrono::milliseconds(1));
			}
			if (driver::read<float>(Held + oAimconePenalty) != 0.0f) {
				driver::write<float>(Held + oAimconePenalty, 0.0f);
				std::this_thread::sleep_for(chrono::milliseconds(1));
			}
			if (driver::read<float>(Held + oAimCone) != 0.0f) {
				driver::write<float>(Held + oAimCone, 0.0f);
				std::this_thread::sleep_for(chrono::milliseconds(1));
			}
			if (driver::read<float>(Held + oHipAimCone) != 0.0f) {
				driver::write<float>(Held + oHipAimCone, 0.0f);
				std::this_thread::sleep_for(chrono::milliseconds(1));
			}
			if (driver::read<float>(Held + oAimconePenaltyPerShot) != 0.0f) {
				driver::write<float>(Held + oAimconePenaltyPerShot, 0.0f);
				std::this_thread::sleep_for(chrono::milliseconds(1));
			}


		}
	}

	bool set_automatic()
	{
		if (Vars::Misc::force_auto)
		{
			bool fauto = true;
			DWORD64 Held = driver::read<DWORD64>((const uintptr_t)this + oHeld);
			if (!Held)
				return false;
			if (driver::read<bool>(Held + 0x288) == false) {
				driver::write<bool>(Held + 0x288, fauto);
			}
			//driver::write<bool>(Held + 0x288, fauto);
		}
	}
	void FatBullet()
	{
		if (Vars::Misc::FatBullet)
		{
			UINT64 Held = driver::read<UINT64>((const uintptr_t)this + oHeld);
			UINT64 List = driver::read<UINT64>(Held + 0x358);

			int size = driver::read<UINT64>(List + 0x18);
			List = driver::read<UINT64>(List + 0x10);
			{
				for (int i = 0; i < size; ++i)
				{
					UINT64 Item = driver::read<UINT64>(List + 0x20 + (i * 0x8));
					if (driver::read<float>(Item + 0x4C) != Vars::Misc::fFatBullet) {
						driver::write<float>(Item + 0x4C, Vars::Misc::fFatBullet);
						std::this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
			}
		}
	}
	void FastBullet() {
		if (Vars::Misc::FastBullet)
		{
			DWORD64 Held = driver::read<DWORD>((const uintptr_t)this + oHeld);
			driver::write<float>(Held + oprojectileVelocityScale, 1.5f);
		}
	}

	void setnojumpblock() {
		/*if (Vars::Misc::aimblock)
		 {
			INT64 Movement = driver::read<UINT64>((const uintptr_t)this + oPlayerMovement);
			driver::write<Vector3>(Movement + 0xB8, Vector3(0, 1000000, 0));
			driver::write<Vector3>(Movement + 0xB4, Vector3(9999999, 9999999, 9999999));
		}*/

	}

	void NoRecoil()
	{
		if (Vars::Misc::no_recoil)
		{

			DWORD64 Held = driver::read<DWORD64>((const uintptr_t)this + oHeld);
			DWORD64 recoil = driver::read<DWORD64>(Held + oRecoilProperties);

			if (driver::read<float>(recoil + oRecoilMinYaw) != 0) {
				driver::write<float>(recoil + oRecoilMinYaw, Vars::Misc::recoil1);
				std::this_thread::sleep_for(chrono::milliseconds(1));
			}
			if (driver::read<float>(recoil + oRecoilMaxYaw) != 0) {
				driver::write<float>(recoil + oRecoilMaxYaw, Vars::Misc::recoil2);
				std::this_thread::sleep_for(chrono::milliseconds(1));
			}
			if (driver::read<float>(recoil + oRecoilMinPitch) != 0) {
				driver::write<float>(recoil + oRecoilMinPitch, Vars::Misc::recoil3);
				std::this_thread::sleep_for(chrono::milliseconds(1));
			}
			if (driver::read<float>(recoil + oRecoilMaxPitch) != 0) {
				driver::write<float>(recoil + oRecoilMaxPitch, Vars::Misc::recoil4);
				std::this_thread::sleep_for(chrono::milliseconds(1));
			}
		}
	}
};







enum BoneList : int
{
	l_hip = 1,
	l_knee,
	l_foot,
	l_toe,
	l_ankle_scale,
	pelvis,
	penis,
	GenitalCensor,
	GenitalCensor_LOD0,
	Inner_LOD0,
	GenitalCensor_LOD1,
	GenitalCensor_LOD2,
	r_hip,
	r_knee,
	r_foot,
	r_toe,
	r_ankle_scale,
	spine1,
	spine1_scale,
	spine2,
	spine3,
	spine4,
	l_clavicle,
	l_upperarm,
	l_forearm,
	l_hand,
	l_index1,
	l_index2,
	l_index3,
	l_little1,
	l_little2,
	l_little3,
	l_middle1,
	l_middle2,
	l_middle3,
	l_prop,
	l_ring1,
	l_ring2,
	l_ring3,
	l_thumb1,
	l_thumb2,
	l_thumb3,
	IKtarget_righthand_min,
	IKtarget_righthand_max,
	l_ulna,
	neck,
	head,
	jaw,
	eyeTranform,
	l_eye,
	l_Eyelid,
	r_eye,
	r_Eyelid,
	r_clavicle,
	r_upperarm,
	r_forearm,
	r_hand,
	r_index1,
	r_index2,
	r_index3,
	r_little1,
	r_little2,
	r_little3,
	r_middle1,
	r_middle2,
	r_middle3,
	r_prop,
	r_ring1,
	r_ring2,
	r_ring3,
	r_thumb1,
	r_thumb2,
	r_thumb3,
	IKtarget_lefthand_min,
	IKtarget_lefthand_max,
	r_ulna,
	l_breast,
	r_breast,
	BoobCensor,
	BreastCensor_LOD0,
	BreastCensor_LOD1,
	BreastCensor_LOD2,
	collision,
	displacement
};





struct TransformAccessReadOnly
{
	uint64_t pTransformData;
};

struct TransformData
{
	uint64_t pTransformArray;
	uint64_t pTransformIndices;
};

struct Matrix34
{
	Vector4 vec0;
	Vector4 vec1;
	Vector4 vec2;
};


Vector3 GetBone(ULONG_PTR pTransform)
{
	__m128 result;

	const __m128 mulVec0 = { -2.000, 2.000, -2.000, 0.000 };
	const __m128 mulVec1 = { 2.000, -2.000, -2.000, 0.000 };
	const __m128 mulVec2 = { -2.000, -2.000, 2.000, 0.000 };

	TransformAccessReadOnly pTransformAccessReadOnly = driver::read<TransformAccessReadOnly>(pTransform + 0x38);


	unsigned int index = driver::read<unsigned int>(pTransform + 0x40);
	//std::cout << "INDEX : " << index << std::endl;

	TransformData transformData = driver::read<TransformData>(pTransformAccessReadOnly.pTransformData + 0x18);
	//std::cout << "pTransformArray : " << transformData.pTransformArray << std::endl;
	//std::cout << "pTransformIndices : " << transformData.pTransformIndices << std::endl;

	if (transformData.pTransformArray && transformData.pTransformIndices)
	{
		result = driver::read<__m128>(transformData.pTransformArray + 0x30 * index);
		//std::cout << "result : " << resu << std::endl;
		int transformIndex = driver::read<int>(transformData.pTransformIndices + 0x4 * index);
		//std::cout << "transformIndex : " << transformIndex << std::endl;
		int pSafe = 0;
		while (transformIndex >= 0 && pSafe++ < 200)
		{
			//std::cout << "PSAFE ITERATION : " << pSafe << std::endl;
			Matrix34 matrix34 = driver::read<Matrix34>(transformData.pTransformArray + 0x30 * transformIndex);

			__m128 xxxx = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x00));	// xxxx
			__m128 yyyy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x55));	// yyyy
			__m128 zwxy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x8E));	// zwxy
			__m128 wzyw = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0xDB));	// wzyw
			__m128 zzzz = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0xAA));	// zzzz
			__m128 yxwy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x71));	// yxwy
			__m128 tmp7 = _mm_mul_ps(*(__m128*)(&matrix34.vec2), result);

			result = _mm_add_ps(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(xxxx, mulVec1), zwxy),
								_mm_mul_ps(_mm_mul_ps(yyyy, mulVec2), wzyw)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0xAA))),
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(zzzz, mulVec2), wzyw),
								_mm_mul_ps(_mm_mul_ps(xxxx, mulVec0), yxwy)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0x55)))),
					_mm_add_ps(
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(yyyy, mulVec0), yxwy),
								_mm_mul_ps(_mm_mul_ps(zzzz, mulVec1), zwxy)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0x00))),
						tmp7)), *(__m128*)(&matrix34.vec0));

			transformIndex = driver::read<int>(transformData.pTransformIndices + 0x4 * transformIndex);
			//std::cout << "transformIndex2 : " << transformIndex << std::endl;
		}
	}

	Vector3 ReturnValue;
	ReturnValue.x = result.m128_f32[0];
	ReturnValue.y = result.m128_f32[1];
	ReturnValue.z = result.m128_f32[2];

	return ReturnValue;
}

DWORD_PTR GetTransform(int bone, DWORD_PTR entity)
{
	DWORD_PTR PlayerModel = driver::read<DWORD_PTR>(entity + 0x128); //public Transform[] boneTransforms;
	DWORD_PTR boneTransforms = driver::read<DWORD_PTR>(PlayerModel + 0x48); //public Transform[] boneTransforms;

	DWORD_PTR BoneValue = driver::read<DWORD_PTR>(boneTransforms + (0x20 + (bone * 0x8)));

	return driver::read<DWORD_PTR>(BoneValue + 0x10);
};
DWORD_PTR GetTransformModel(int bone, DWORD_PTR PlayerModel)
{
	DWORD_PTR boneTransforms = driver::read<DWORD_PTR>(PlayerModel + 0x48); //public Transform[] boneTransforms;

	DWORD_PTR BoneValue = driver::read<DWORD_PTR>(boneTransforms + (0x20 + (bone * 0x8)));

	return driver::read<DWORD_PTR>(BoneValue + 0x10);
};


Vector3 GetBoneByID(BoneList BoneID, DWORD_PTR entity)
{
	return GetBone(GetTransform(BoneID, entity));
}

Vector3 GetBoneByIDModel(BoneList BoneID, DWORD_PTR entity)
{
	return GetBone(GetTransformModel(BoneID, entity));
}

Vector3 GetBoneByIDInt(int BoneID, DWORD_PTR entity)
{
	return GetBone(GetTransform(BoneID, entity));
}



class BasePlayer
{
public:
	//PREFAB
	Vector3 GetPrefabPos() {
		UINT64 Object = driver::read<UINT64>((uintptr_t)this + 0x10);
		UINT64 ObjectClass = driver::read<UINT64>(Object + 0x30);
		UINT64 GameObject = driver::read<UINT64>(ObjectClass + 0x30);
		UINT64 Transform = driver::read<UINT64>(GameObject + 0x8);
		UINT64 Vec = driver::read<UINT64>(Transform + 0x38);

		return driver::read<Vector3>(Vec + 0x90);
	}


	Vector3 GetBoneID(BoneList id) {
		return GetBoneByID(id, (uintptr_t)this);
	}

	Vector3 GetBoneInt(int id) {
		return GetBoneByIDInt(id, (uintptr_t)this);
	}

	Vector3 HeadBone() {

		return GetBoneByID(BoneList::head, (uintptr_t)this);

	}
	Vector3 BasePos() {
		DWORD_PTR PlayerModel = driver::read<DWORD_PTR>((uintptr_t)this + 0x4C0);
		return driver::read<Vector3>(PlayerModel + 0x1F8);
	}

	Vector3 HeadBoneModel(UINT64 Model) {

		return GetBoneByIDModel(BoneList::head, Model);
	}

	Vector3 BasePos(UINT64 PlayaModel) {
		return driver::read<Vector3>(PlayaModel + 0x1F8);
	}
	/*PlayerInfo Info*/



	bool IsInFov(Vector3 ScreenPlayerHead) {

		if (960 - ScreenPlayerHead.x < Vars::Aim::Fov && 960 - ScreenPlayerHead.x > -Vars::Aim::Fov) {
			if (540 - ScreenPlayerHead.y < Vars::Aim::Fov && 540 - ScreenPlayerHead.y > -Vars::Aim::Fov) {
				return true;
			}
		}
		else
		{
			return false;
		}
	}

	UINT64 GetSteamID()
	{
		return driver::read<UINT64>((const uintptr_t)(const uintptr_t)this + oSteamID);
	}

	std::string GetDisplayName() {
		UINT64 DisplayNamePtr = driver::read<UINT64>((const uintptr_t)this + oDisplayName);
		wstring Name = driver::ReadUnicode(DisplayNamePtr + oDisplayNameString);
		std::string output(Name.begin(), Name.end());

		return output;
	}

	float GetHealth()
	{
		return driver::read<float>((const uintptr_t)(const uintptr_t)this + oPlayerHealth);
	}

	bool HasFlags(int Flg)
	{
		return driver::read<int>((const uintptr_t)(const uintptr_t)this + oPlayerFlags) & Flg;
	}

	UINT64 GetName() {
		return driver::read<UINT64>((const uintptr_t)(const uintptr_t)this + 0x6B0);
	}

	std::string GetPName()
	{
		std::string pname = driver::read<std::string>((const uintptr_t)(const uintptr_t)this + oPlayerName);
		return pname;
	}

	bool IsDead()
	{
		if (!(const uintptr_t)this) return true;
		return driver::read<bool>((const uintptr_t)(const uintptr_t)this + oLifestate);
	}

	bool IsSleeping() {

		if ((((Vars::Visuals::IgnoreSleeping) ? !HasFlags(16) : true))) {

			return false;
		}
		else
		{
			//std::cout << "FALSE" << std::endl;
			return true;
		}
	}

	bool IsLocalPlayer() {
		UINT64 PlayerModel = driver::read<UINT64>((const uintptr_t)this + 0x4C0);
		int Response = driver::read<UINT64>(PlayerModel + 0x1F8);
		if (Response == 1) {
			return true;
		}
		return false;
	}

	bool IsPlayer() {
		UINT64 steam = GetSteamID();
		int nums = 0;
		do {
			nums++;
			steam /= 10;
		} while (steam > 0);
		if (nums != 17 /*player*/) return false;
		return true;
	}


	bool IsInRange(Vector3 LocalPos, Vector3 EnemyPos, int Range) {
		float DistanceX = LocalPos.x - EnemyPos.x;
		float DistanceY = LocalPos.z - EnemyPos.z;

		float Distance = sqrt((DistanceX * DistanceX) + (DistanceY * DistanceY));
		//std::cout << Distance << std::endl;
		if (Range < Distance) {
			return false;
		}
		else
		{
			return true;
		}

	}
	bool IsInRange(Vector3 LocalPos, Vector3 EnemyPos) {
		float DistanceX = LocalPos.x - EnemyPos.x;
		float DistanceY = LocalPos.z - EnemyPos.z;

		float Distance = sqrt((DistanceX * DistanceX) + (DistanceY * DistanceY));
		//std::cout << Distance << std::endl;
		if (Vars::Visuals::ESPRANGE < Distance) {
			return false;
		}
		else
		{
			return true;
		}

	}


	bool IsValid(bool LPlayer = false)
	{
		//return true;
		if (!this) return false;
		//float health = GetHealth();
	//UINT64 steam = GetSteamID();

	//if (IsDead()) {
	//	return false;
	//}
	////std::cout << health << " " << steam;
	//if (health > 500.f || health < 0.1f) return false;

	//if ((Vars::Visuals::ShowSleeping)) {
	//	if (HasFlags(16)) {
	//		return false;
	//	}
	//}


		if ((((Vars::Visuals::IgnoreSleeping) ? !HasFlags(16) : true) && !IsDead())) {

			return true;
		}
		else
		{
			//std::cout << "FALSE" << std::endl;
			return false;
		}

		////std::cout << "ISvalid " << HasFlags(16) << "  " << IsDead() << " " << GetHealth() << std::endl;
		//int nums = 0;
		//do {
		//	nums++;
		//	steam /= 10;
		//} while (steam > 0);
		////std::cout << " " << nums << std::endl;
		//if (nums != 7 /*bot*/ && nums != 17 /*player*/) return false;


		//return (((LPlayer || Vars::Visuals::IgnoreSliping) ? !HasFlags(16) : true) && !IsDead());
		return true;
	}

	/*Vector*/
	Vector2 GetRecoilAngles() {
		UINT64 Input = driver::read<UINT64>((const uintptr_t)this + oPlayerInput);
		return driver::read<Vector2>(Input + oRecoilAngles);
	}


	Vector3 GetVelocity()
	{
		UINT64 PlayerModel = driver::read<UINT64>((const uintptr_t)(const uintptr_t)this + oPlayerModel);
		//return driver::read<Vector3>(PlayerModel + 0x214); // 	private Vector3 newVelocity;
		return driver::read<Vector3>(PlayerModel + 0x21C); // 	private Vector3 newVelocity;
	}


	bool IsVisible() {
		if (Vars::Aim::VisibleCheck) {
			UINT64 PlayerModel = driver::read<UINT64>((const uintptr_t)(const uintptr_t)this + oPlayerModel);
			return driver::read<bool>(PlayerModel + 0x268); // internal bool visible; WORK
		}
		else return true;
	}

	/*Fucktion*/
	Vector2 GetVA() {
		UINT64 Input = driver::read<UINT64>((const uintptr_t)this + oPlayerInput);
		return driver::read<Vector2>(Input + oBodyAngles);
	}
	void SetVA(const Vector2& VA)
	{
		UINT64 Input = driver::read<UINT64>((const uintptr_t)this + oPlayerInput);
		driver::write<Vector2>(Input + oBodyAngles, VA);
	}

	void FakeAdmin()
	{
		int Flags = driver::read<int>((const uintptr_t)this + oPlayerFlags);
		std::cout << "\n" << Flags;
		driver::write<int>((const uintptr_t)this + oPlayerFlags, (Flags |= 4));
	}

	int GetTeamSize()
	{
		UINT64 ClientTeam = driver::read<UINT64>((const uintptr_t)(const uintptr_t)this + oClientTeam); // valid
		UINT64 members = driver::read<UINT64>(ClientTeam + 0x30);
		return driver::read<UINT64>(members + 0x18);
	}

	UINT64 IsTeamMate(int Id)
	{
		UINT64 ClientTeam = driver::read<UINT64>((const uintptr_t)(const uintptr_t)this + oClientTeam);
		UINT64 members = driver::read<UINT64>(ClientTeam + 0x30);
		UINT64 List = driver::read<UINT64>(members + 0x10);
		UINT64 player = driver::read<UINT64>(List + 0x20 + (Id * 0x8));
		return driver::read<UINT64>(player + 0x20);
	}

	void SpiderMan()
	{
		UINT64 Movement = driver::read<UINT64>((const uintptr_t)this + oPlayerMovement);
		driver::write<float>(Movement + oGroundAngleNew, 0.f);
	}



	void SetGravity() {

		if (Vars::Misc::gravity)
		{
			UINT64 Movement = driver::read<UINT64>((const uintptr_t)this + oPlayerMovement);
			driver::write<float>(Movement + 0x7C, Vars::Misc::ggravity);
		}
		// write back to normal 
		/*if (!Vars::Misc::gravity)
		{
			driver::write<float>(Movement + 0x74, 3);
		}*/

	}

	void AlwaysDay()
	{
	






		driver::write<float>(TodCycle + 0x10, 12.f);

		
		
	}

	void DoWaterHax()
	{
		driver::write<float>((uintptr_t)this + 0x718, 0.10f);
	}
	/*Weapon Info*/
	WeaponData* GetWeaponInfo(int Id)
	{
		UINT64 Inventory = driver::read<UINT64>((const uintptr_t)this + oPlayerInventory);
		UINT64 Belt = driver::read <UINT64>(Inventory + 0x28);
		UINT64 ItemList = driver::read<UINT64>(Belt + 0x38);
		UINT64 Items = driver::read<UINT64>(ItemList + 0x10);
		return (WeaponData*)driver::read<UINT64>(Items + 0x20 + (Id * 0x8));
	}

	UINT64 GetItemsList() {
		UINT64 Inventory = driver::read<UINT64>((const uintptr_t)this + oPlayerInventory);
		UINT64 Belt = driver::read <UINT64>(Inventory + 0x28);
		UINT64 ItemList = driver::read<UINT64>(Belt + 0x38);
		return driver::read<UINT64>(ItemList + 0x10);
	}

	std::string GetBeltItems(UINT64 ItemsList, int Slot) {
		UINT64 SlotItem;
		if (Slot == 1) {
			SlotItem = driver::read<UINT64>(ItemsList + 0x20);
			if (!SlotItem) {
				return "None";
			}
		}
		else if (Slot == 2) {
			SlotItem = driver::read<UINT64>(ItemsList + 0x28);
			if (!SlotItem) {
				return "None";
			}
		}
		else if (Slot == 3) {
			SlotItem = driver::read<UINT64>(ItemsList + 0x30);
			if (!SlotItem) {
				return "None";
			}
		}
		else if (Slot == 4) {
			SlotItem = driver::read<UINT64>(ItemsList + 0x38);
			if (!SlotItem) {
				return "None";
			}
		}
		else if (Slot == 5) {
			SlotItem = driver::read<UINT64>(ItemsList + 0x40);
			if (!SlotItem) {
				return "None";
			}
		}
		else if (Slot == 6) {
			SlotItem = driver::read<UINT64>(ItemsList + 0x48);
			if (!SlotItem) {
				return "None";
			}
		}

		UINT64 Item1Info = driver::read<UINT64>(SlotItem + 0x20);
		if (!Item1Info) {
			return "None";
		}

		UINT64 ItemDisplayName = driver::read<UINT64>(Item1Info + 0x28);
		if (!ItemDisplayName) {
			return "None";
		}

		UINT64 ItemDisplayEnglish = driver::read<UINT64>(ItemDisplayName + 0x18);
		if (!ItemDisplayEnglish) {
			return "None";
		}

		UINT64 NameTest = driver::read<UINT64>(ItemDisplayEnglish + 0x14);

		if (!NameTest) {
			return "None";
		}

		wstring Name = driver::ReadUnicode(ItemDisplayEnglish + 0x14);

		std::string output(Name.begin(), Name.end());

		if (output == "dxeso") {
			return "None";
		}
		return output;

	}

	UINT64 GetClothingItemsList() {
		UINT64 Inventory = driver::read<UINT64>((const uintptr_t)this + oPlayerInventory);
		UINT64 Belt = driver::read <UINT64>(Inventory + 0x30);
		UINT64 ItemList = driver::read<UINT64>(Belt + 0x38);
		return driver::read<UINT64>(ItemList + 0x10);
	}
	int GetCurrentTeam() {
		return driver::read<int>((uintptr_t)this + 0x610);
	}
	std::string GetClothingItems(UINT64 ItemsList, int Slot) {
		UINT64 SlotItem;
		if (Slot == 1) {
			SlotItem = driver::read<UINT64>(ItemsList + 0x20);
			if (!SlotItem) {
				return "None";
			}
		}
		else if (Slot == 2) {
			SlotItem = driver::read<UINT64>(ItemsList + 0x28);
			if (!SlotItem) {
				return "None";
			}
		}
		else if (Slot == 3) {
			SlotItem = driver::read<UINT64>(ItemsList + 0x30);
			if (!SlotItem) {
				return "None";
			}
		}
		else if (Slot == 4) {
			SlotItem = driver::read<UINT64>(ItemsList + 0x38);
			if (!SlotItem) {
				return "None";
			}
		}
		else if (Slot == 5) {
			SlotItem = driver::read<UINT64>(ItemsList + 0x40);
			if (!SlotItem) {
				return "None";
			}
		}
		else if (Slot == 6) {
			SlotItem = driver::read<UINT64>(ItemsList + 0x48);
			if (!SlotItem) {
				return "None";
			}
		}
		else if (Slot == 7) {
			SlotItem = driver::read<UINT64>(ItemsList + 0x50);
			if (!SlotItem) {
				return "None";
			}
		}

		UINT64 Item1Info = driver::read<UINT64>(SlotItem + 0x20);
		if (!Item1Info) {
			return "None";
		}

		UINT64 ItemDisplayName = driver::read<UINT64>(Item1Info + 0x28);
		if (!ItemDisplayName) {
			return "None";
		}

		UINT64 ItemDisplayEnglish = driver::read<UINT64>(ItemDisplayName + 0x18);
		if (!ItemDisplayEnglish) {
			return "None";
		}

		wstring Name = driver::ReadUnicode(ItemDisplayEnglish + 0x14);

		std::string output(Name.begin(), Name.end());
		if (output == "dxeso") {
			return "None";
		}

		return output;

	}

	WeaponData* GetActiveWeapon()
	{
		int ActUID = driver::read<int>((const uintptr_t)this + oActiveUID);
		if (!ActUID) return nullptr;
		WeaponData* ActiveWeapon;
		for (int i = 0; i < 6; i++)
			if (ActUID == (ActiveWeapon = GetWeaponInfo(i))->GetUID()) {
				return ActiveWeapon;
			}
		return nullptr;
	}
	string GetActiveWeaponText() {
		uint16_t ItemID = this->GetActiveWeapon()->GetItemID();
		if (ItemID == 0xB98E) { //AK
			return "AK-47";
		}
		else if (ItemID == 0x31E1) { //SMG
			return "CUSTOM SMG";
		}
		else if (ItemID == 0x9A57) { //lR
			return "LR-300";
		}
		else if (ItemID == 0x9C37) { //MP5
			return "MP5";
		}
		else if (ItemID == 0xA375) { //Tommy???
			return "TOMMY";
		}
		else if (ItemID == 0xBB78) { //m249
			return "M249";
		}
		else if (ItemID == 0x0EC1) { //l96
			return "L96";
		}
		else if (ItemID == 0x82C3) { //Bolty???
			return "BOLTY";
		}
		else if (ItemID == 0x5371) { //M39
			return "M39";
		}
		else if (ItemID == 0x3261) { //Uknown
			return "UKNOWN 2";
		}
		else if (ItemID == 0x2660) { //Uknown
			return "UKNOWN 1";
		}
		else if (ItemID == 0xE126) { //REVO
			return "REVO";
		}
		else if (ItemID == 0x2593) { //PYTHON
			return "PYTHON";
		}
		else if (ItemID == 0xEBB5) { //m92 pistol
			return "M92";
		}
		else if (ItemID == 0x142C) { //SEMI PISTOL
			return "SEMI PISTOL";
		}
		else if (ItemID == 0xE257) { //SAR
			return "S.A.R.";
		}
		else
		{
			return " ";
		}
	}

	/*Local-PlayerInfo*/




	bool IsMenu()
	{
		if (!(const uintptr_t)this) return true;
		UINT64 Input = driver::read<UINT64>((const uintptr_t)(const uintptr_t)this + oPlayerInput);
		return !(driver::read<bool>(Input + 0x94));
	}

private:



};


DWORD64 Vmatrix;
class BaseLocalPlayer {
public:
	BasePlayer* BasePlayer;
	int CurrentTeam;



	static Vector3 WorldToScreen(const Vector3 pos) {
		view_matrix_t matrix = driver::read<view_matrix_t>(Vmatrix + 0x2E4);
		float _x = matrix[0][0] * pos.x + matrix[1][0] * pos.y + matrix[2][0] * pos.z + matrix[3][0];
		float _y = matrix[0][1] * pos.x + matrix[1][1] * pos.y + matrix[2][1] * pos.z + matrix[3][1];

		float w = matrix[0][3] * pos.x + matrix[1][3] * pos.y + matrix[2][3] * pos.z + matrix[3][3];

		float inv_w = 1.f / w;
		_x *= inv_w;
		_y *= inv_w;

		float x = screenX * .5f;
		float y = screenY * .5f;

		x += 0.5f * _x * screenX + 0.5f;
		y -= 0.5f * _y * screenY + 0.5f;

		return { x,y,w };
	}


	static Vector3 FastWorldToScreen(const Vector3 pos, view_matrix_t matrix) {
		//view_matrix_t matrix = driver::read<view_matrix_t>(Vmatrix + 0x2E4);
		float _x = matrix[0][0] * pos.x + matrix[1][0] * pos.y + matrix[2][0] * pos.z + matrix[3][0];
		float _y = matrix[0][1] * pos.x + matrix[1][1] * pos.y + matrix[2][1] * pos.z + matrix[3][1];

		float w = matrix[0][3] * pos.x + matrix[1][3] * pos.y + matrix[2][3] * pos.z + matrix[3][3];

		float inv_w = 1.f / w;
		_x *= inv_w;
		_y *= inv_w;

		float x = screenX * .5f;
		float y = screenY * .5f;

		x += 0.5f * _x * screenX + 0.5f;
		y -= 0.5f * _y * screenY + 0.5f;

		return { x,y,w };
	}

};

uint64_t GetCamera()
{
	/* Read into the first entry in the list */
	uint64_t gom_addr = driver::read<uint64_t>(driver::get_module_base_address("UnityPlayer.dll") + oGameObjectManager);
	uint64_t address = driver::read<uint64_t>(gom_addr + 0x8);

	/* Loop until we hit tag 5, which is camera */
	while (true)
	{
		/* Read into the GameObject */
		uint64_t game_object = driver::read<uint64_t>(address + 0x10);

		/* Read this object's tag */
		int16_t tag = driver::read<int16_t>(game_object + 0x54);

		if (tag == 5)
		{
			return driver::ReadChain<uint64_t>(game_object, { 0x30, 0x18 });;
		}

		/* Read into the next entry */
		address = driver::read<uint64_t>(address + 0x8);
	}

	return address;
}

BaseLocalPlayer LocalPlayer;
UINT64 MainCamera;

void UpdateLocalPlayer() {

	UINT64 LocalPlayerPtr1 = driver::read<UINT64>(Gbase + oBaseNetworkable);

	UINT64 LocalPlayerPtr2 = driver::read<UINT64>(LocalPlayerPtr1 + 0xB8);
	UINT64 LocalPlayerPtr3 = driver::read<UINT64>(LocalPlayerPtr2 + 0x0);
	UINT64 LocalPlayerPtr4 = driver::read<UINT64>(LocalPlayerPtr3 + 0x10);
	UINT64 LocalPlayerPtr5 = driver::read<UINT64>(LocalPlayerPtr4 + 0x28);
	UINT64 LocalPlayerPtr6 = driver::read<UINT64>(LocalPlayerPtr5 + 0x18);
	UINT64 LocalPlayerPtr7 = driver::read<UINT64>(LocalPlayerPtr6 + 0x20);
	LocalPlayer.BasePlayer = (BasePlayer*)(LocalPlayerPtr7);
	std::cout << LocalPlayer.BasePlayer << std::hex << std::endl;

	UINT64 ViewMatrixPtr1 = driver::read<UINT64>(Ubase + oGameObjectManager);
	UINT64 ViewMatrixPtr2 = driver::read<UINT64>(ViewMatrixPtr1 + 0x8);
	UINT64 ViewMatrixPtr3 = driver::read<UINT64>(ViewMatrixPtr2 + 0x10);
	UINT64 ViewMatrixPtr4 = driver::read<UINT64>(ViewMatrixPtr3 + 0x30);
	Vmatrix = driver::read<UINT64>(ViewMatrixPtr4 + 0x18);

	//2A18 instead of 2E4
	MainCamera = GetCamera();
}

void SetFullBright() {

	
	driver::write<float>(GetCamera() + 0x94, 3.8f);

	UINT64 TodShit = driver::read<UINT64>(GetCamera() + 0x88);
	UINT64 Sky = driver::read<UINT64>(TodShit + 0x18);
	UINT64 Night = driver::read<UINT64>(Sky + 0x58);

	//SUN SHIT
	UINT64 Sun = driver::read<UINT64>(Sky + 0x60);
	driver::write<float>(Sun + 0x14, 1.0f); //MESH BRIGHTNESS
	driver::write<float>(Sun + 0x10, 4.0f); //MESH SIZE
	driver::write<float>(Sun + 0x18, 4.0f); //MESH CONTRAST

	//Sleep(1);

	//MOON SHIT
	UINT64 Moon = driver::read<UINT64>(Sky + 0x68);
	driver::write<float>(Moon + 0x14, 6.0f); //MESH BRIGHTNESS
	driver::write<float>(Moon + 0x10, 5.0f); //MESH SIZE
	driver::write<float>(Moon + 0x18, 1.0f); //MESH CONTRAST
	driver::write<float>(Moon + 0x24, 5.0f); //POSITION

	//Sleep(1);

	//STARS SHIT
	UINT64 Stars = driver::read<UINT64>(Sky + 0x70);
	driver::write<float>(Stars + 0x10, 1.5f); //MESH SIZE	
	driver::write<float>(Stars + 0x14, 20.0f); //MESH BRIGHTNESS

	//Sleep(1);

	//AMBIENT SHIT
	UINT64 Ambient = driver::read<UINT64>(Sky + 0x90);
	driver::write<int>(Ambient + 0x10, 3); //MODE	
	driver::write<float>(Ambient + 0x14, 1.2f); //SATURATION


	//Sleep(1);
	//MOON COLOR SHIT
	UINT64 MoonColorPtr = driver::read<UINT64>(Night + 0x10);
	UINT64 MoonColor = driver::read<UINT64>(MoonColorPtr + 0x10);
	driver::write<float>(MoonColor, 1.0f);
	driver::write<float>(MoonColor + 0x4, 1.0f);
	driver::write<float>(MoonColor + 0x8, 0.6f);

	//Sleep(1);
	driver::write<float>(MoonColor + 0xC, 0.6f);
	driver::write<float>(MoonColor + 0x10, 0.6f);

	//Sleep(1);
	driver::write<float>(MoonColor + 0x14, 0.0f);
	driver::write<float>(MoonColor + 0x18, 1.0f);
	driver::write<float>(MoonColor + 0x1C, 1.0f);


	//Sleep(1);
	//SETTING DAY TO NIGHT
	driver::write<UINT64>(Sky + 0x50, Night);

	//NIGHT SHIT
}

//BULLET SPEEDS
float GetBulletSpeed()
{
	uint16_t ItemID = LocalPlayer.BasePlayer->GetActiveWeapon()->GetItemID();
	std::cout << ItemID << std::endl;
	if (ItemID == 0xB98E) { //AK
		return 344.0f;
	}
	else if (ItemID == 0x31E1) { //SMG
		return 240.0f;
	}
	else if (ItemID == 0x9A57) { //lR
		return 344.0f;
	}
	else if (ItemID == 0x9C37) { //MP5
		return 200.0f;
	}
	else if (ItemID == 0x5C8B) { //Tommy???
		return 277.0f;
	}
	else if (ItemID == 0xBB78) { //m249
		return 488.0f;
	}
	else if (ItemID == 0x0EC1) { //l96
		return 1125.0f;
	}
	else if (ItemID == 0x82C3) { //Bolty???
		return 656.0f;
	}
	else if (ItemID == 0x5371) { //M39
		return 462.0f;
	}
	else if (ItemID == 0x3261) { //Uknown
		return 177.0f;
	}
	else if (ItemID == 0x2660) { //Uknown
		return 166.0f;
	}
	else if (ItemID == 0xE126) { //REVO
		return 270.0f;
	}
	else if (ItemID == 0x2593) { //PYTHON
		return 259.0f;
	}
	else if (ItemID == 0xEBB5) { //m92 pistol
		return 300.0f;
	}
	else if (ItemID == 0x142C) { //SEMI PISTOL
		return 270.0f;
	}
	else if (ItemID == 0xE257) { //SAR
		return 350.0f;
	}
	else if (ItemID == 0x474F) { //bow
		return 56.8f;
	}
	else if (ItemID == 0x3D71) { //COMPOUND
		return 115.6f;
	}
	else if (ItemID == 0x110A) { //crossbow
		return 90.0f;
	}
	else if (ItemID == 0x3261) { //nailgun
		return 50.0f;
	}


	else
	{
		return 300.0f;
	}
	//spas 0xAb32
	//compound = 0x3D71
	//water pipe = 0xEEEB
	//pump shotty = 0x6650
	//eoka = 0x2d2b
	//dub barrel = 0x397F
}

//MAKE SURE ITS REAL WEAPON
void WeaponFix(WeaponData* weapon)
{
	int ItemID = 0;
	if (weapon)
		ItemID = weapon->GetItemID();
	if (!ItemID) return;

	for (DWORD64 val : semiautomatic) {
		if (ItemID == val) {
			//	std::cout << "SEMI AUTO" << std::endl;
			weapon->CripHold(Vars::Misc::bCripHold, Vars::Misc::InstaADS, Vars::Misc::NowGunLower, Vars::Misc::NoBob);
			weapon->NoRecoil();
			weapon->AntiSpread();
			weapon->set_automatic();

			//weapon->SetAutomatic();
			//weapon->FastBullet();
			weapon->FatBullet();
			return;
		}
	}

	for (DWORD64 val : sniper) {
		if (ItemID == val) {
			//	std::cout << "SNIPA" << std::endl;
			weapon->CripHold(Vars::Misc::bCripHold, Vars::Misc::InstaADS, Vars::Misc::NowGunLower, Vars::Misc::NoBob);
			weapon->NoRecoil();
			weapon->AntiSpread();
			weapon->FatBullet();
			//weapon->FastBullet();
			return;
		}
	}
	for (DWORD64 val : automatic) {
		if (ItemID == val) {
			//	std::cout << "AUTO" << std::endl;
			weapon->CripHold(Vars::Misc::bCripHold, Vars::Misc::InstaADS, Vars::Misc::NowGunLower, Vars::Misc::NoBob);
			weapon->NoRecoil();
			weapon->AntiSpread();
			weapon->FatBullet();
			//weapon->FastBullet();
			return;
		}
	}
	uint16_t ItemID2 = LocalPlayer.BasePlayer->GetActiveWeapon()->GetItemID();
	if (ItemID2 == 0x474F) {//BOW
		//std::cout << "BOW" << std::endl;
		weapon->InstaBow();
		weapon->AntiSpread();
		weapon->FatBullet();
		weapon->CripHold(Vars::Misc::bCripHold, Vars::Misc::InstaADS, Vars::Misc::NowGunLower, Vars::Misc::NoBob);
		//weapon->FastBullet();
		return;
	}

	if (ItemID2 == 0x110A) {//compound
		//std::cout << "BOW" << std::endl;

		weapon->AntiSpread();
		weapon->FatBullet();

		return;
	}
	if (ItemID2 == 0x3261) {//nail gun
		//std::cout << "BOW" << std::endl;

		weapon->AntiSpread();
		weapon->FatBullet();

		return;
	}
	else if (ItemID2 == 0x2D2B) { //EOKA
		weapon->SuperEoka();
		weapon->AntiSpread();
		weapon->FatBullet();
	}

	else if (ItemID2 == 0x3D71) { //compound
		weapon->Compund();
		weapon->AntiSpread();
		weapon->FatBullet();
		weapon->InstaBow();
	}
	else if (ItemID2 == 0x397F) { //DUB BARREL
		weapon->AntiSpread();
		weapon->FatBullet();
	}
	else if (ItemID2 == 0xAB32) { //SPAS
		weapon->AntiSpread();
		weapon->FatBullet();
	}
	else if (ItemID2 == 0xEEEB) { //WATER PIPE
		weapon->AntiSpread();
		weapon->FatBullet();
	}
	else if (ItemID2 == 0x6650) { //PUMP SHOTTY
		weapon->AntiSpread();
		weapon->FatBullet();
	}
	else if (ItemID2 == 0x5C8B) { //PUMP SHOTTY
		weapon->AntiSpread();
		weapon->FatBullet();
	}
	else if (ItemID2 == 0x2593) { //PUMP SHOTTY
		weapon->AntiSpread();
		weapon->FatBullet();
	}

	//spas 0xAb32
	//compound = 0x3D71
	//water pipe = 0xEEEB
	//pump shotty = 0x6650
	//eoka = 0x2d2b
	//dub barrel = 0x397F
}
Vector3 Prediction(const Vector3& LP_Pos, BasePlayer* Player, BoneList Bone, Vector3 BonePos)
{
	//Vector3 BonePos = PlayerInfo->HeadBone();
	float Dist = Calc3D_Dist(LP_Pos, BonePos);

	if (Dist > 0.001f) {
		float BulletTime = Dist / GetBulletSpeed();
		//	std::cout << GetBulletSpeed() << endl;
		Vector3 vel = Player->GetVelocity();
		Vector3 PredictVel;
		PredictVel.x = vel.x * BulletTime * 0.75f;
		PredictVel.y = vel.y * BulletTime * 0.75f;
		PredictVel.z = vel.z * BulletTime * 0.75f;

		BonePos.x += PredictVel.x;
		BonePos.y += PredictVel.y;
		BonePos.z += PredictVel.z;
		BonePos.y += (4.905f * BulletTime * BulletTime);
		//BonePos += PredictVel; BonePos.y += (4.905f * BulletTime * BulletTime);
	} return BonePos;
}