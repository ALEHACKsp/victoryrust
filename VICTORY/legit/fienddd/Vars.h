#pragma once

namespace Vars
{
	namespace Screen
	{
		static int Width = GetSystemMetrics(SM_CXSCREEN);
		static int Height = GetSystemMetrics(SM_CYSCREEN);
	}



	namespace Aim
	{
		static bool SilentAim = false;
		static bool AimBot = false;
		static bool bSmoothing = false;
		static int iSmoothing = 10;
		static bool Prediction = false;
		static bool VisibleCheck = false;
		static 	bool IgnoreTeam = false;
		static int BoneToAim = 47;
		static int Fov = 200;
		static int bone = 0;

		static bool Crosshair = true;
	}


	namespace Visuals
	{
		static bool TeamCheck = true;

		static bool ShowPredictionCircle = true;

		static int ESPRANGE = 300;
		static int PREFABRANGE = 200;
		static bool PrefabEsp = false;

		static bool OnlyShowPlayers = true;

		static bool ShowPanel = false;
		static bool ShowHotBar = true;
		static bool ShowClothes = false;

		static bool VisCheck = false;
		static bool HP = false;
		static bool Line = false;
		static bool IgnoreSleeping = true;
		static bool PlayerESP = false;
		static bool DisplayName = false;

		static bool FilledBox = true;
		static bool Weapon = false;
		static bool Box = false;
		static bool CornerBox = false;
		static bool HeadCircle = false;
		static bool Bones = false;
		static int FOV = 90;
		static bool ShowDistance = true;

		namespace WORLD {


			static bool Weapons = true;
			static bool Nodes = false;
			static bool Hemp = true;
			static bool NodesCollectable = false;
			static bool Corpse = false;
			static bool Bags = false;
			static bool Stash = true;
			static bool Other = false;




		}

	}

	namespace Misc
	{


		static bool bCripHold = false;
		static float ViewModelZoom = 1;
		static bool InstaADS = false;
		static bool NowGunLower = false;
		static bool NoBob = false;
		static float DayTime = 12.f;
		static bool force_auto = false;
		static bool spyderman = false;
		static bool AlwaysDay = false;
		static bool aimblock = false;
		static bool gravity = false;
		static float ggravity = 2.5;

		static bool compound = false;
		static bool InstaBow = false;
		static bool InstaEoka = false;
		static bool FakeAdmin = false;
		static bool ApplyFov = false;
		static bool FatBullet = false;
		static 	bool anti_spread = false;
		static int line = 0;


		static 	bool no_recoil = false;
		static bool FastBullet = false;
		static float fFatBullet = 0.7f;


		static float recoil1 = 0;
		static float recoil2 = 0;
		static float recoil3 = 0;
		static float recoil4 = 0;
	}
	namespace Menu {
		static bool ShowMovement = true;
		static bool ShowVisual = true;
		static bool ShowMisc = true;
		static bool ShowAim = true;
		static bool ShowWeapon = true;
		static bool ShowWorld = true;
	}
}

