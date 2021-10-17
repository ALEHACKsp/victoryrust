#pragma once
#include "Drawing.h"
#include "Math.h"
#include "Memory.h"
#include "offsets.h"

#include <vector>
#include "BasePlayer.h"

using namespace std;

struct InfoPanelPlayer {

    float Health;

    int Distance;

    std::string Name;
    std::string HeldItem;
};
InfoPanelPlayer PanelPlayer;
struct PlayerBones {
    Vector3 Head;
    Vector3 Neck;

    Vector3 Stomach;

    Vector3 LArm1;
    Vector3 LArm2;
    Vector3 LArm3;

    Vector3 RArm1;
    Vector3 RArm2;
    Vector3 RArm3;

    Vector3 LLeg1;
    Vector3 LLeg2;
    Vector3 LLeg3;


    Vector3 RLeg1;
    Vector3 RLeg2;
    Vector3 RLeg3;
};
struct GoodPrefab {
    std::string PrefabName;
    Vector3 PrefabPos;
    int PrefabDistance;
};
struct GoodPlayers2 {
    UINT64 PlayerBase;

    Vector3 PlayerPos;
    Vector3 PlayerHeadPos;

    float PlayerHealth;
    int PlayerDistance;

    std::string PlayerName;

    bool IsTarget;

    PlayerBones Bones;

};

template <typename Type>
struct ThreadVec
{
    std::vector<Type> vec;
    std::mutex mutex;
};

ThreadVec<GoodPlayers2> GoodPlayers3 = {};
ThreadVec<GoodPrefab> GoodPrefabs = {};

ThreadVec<UINT64> GoodPlayers = {};
ThreadVec<UINT64> discovered = {};


Vector3 LocalPlayerBasePos;


UINT64 client_ents;
uint64_t list_base;
UINT64 RibandciScript;

void Update() {
    int EntityListSize = 0;
    while (EntityListSize == 0)
    {
        EntityListSize = driver::read<int32_t>(client_ents + 0x10);
        Sleep(500);
    }
    UpdateLocalPlayer();

}

void EntityDiscovery()
{
    list_base = driver::read<uint64_t>(client_ents + 0x18);

    while (true)
    {
        if (list_base == 0) {
            list_base = driver::read<uint64_t>(client_ents + 0x18);
        }
       


        std::vector<UINT64> local_players;
        std::vector<GoodPrefab> local_prefabs;

        int32_t list_size = driver::read<int32_t>(client_ents + 0x10);

        if (list_size == 0) {
            Update();       
        }

        uint64_t* entities = new uint64_t[list_size * sizeof(uint64_t)];
        driver::read(list_base + 0x20, entities, list_size * sizeof(uint64_t));
        std::vector<uint64_t> discovered_entities = std::vector<uint64_t>(entities, entities + list_size);

        std::cout << "DISCOVERING ENTITIES, LIST SIZE : " << list_size << std::endl;
        delete[] entities;


        long long i = 0;
        UINT64  ObjMgr = driver::read<UINT64>(Ubase + oGameObjectManager);
        UINT64  Obj = driver::read<UINT64>(ObjMgr + 0x8);

        std::cout << "ObjMgr " << ObjMgr << std::endl;
        std::cout << "Obj " << Obj << std::endl;

        bool LP_isValid = false;
        std::cout << "Loading..." << std::endl;
        for (UINT64 Obj = driver::read<UINT64>(ObjMgr + 0x8); (Obj && (Obj != driver::read<UINT64>(ObjMgr))); Obj = driver::read<UINT64>(Obj + 0x8))
        {
            //std::cout << "Ent" << endl;
            UINT64 GameObject = driver::read<UINT64>(Obj + 0x10);
            WORD Tag = driver::read<WORD>(GameObject + 0x54);

            if (Tag == 6 || Tag == 5 || Tag == 20011)
            {
                UINT64 ObjClass = driver::read<UINT64>(GameObject + 0x30);
                UINT64 Entity = driver::read<UINT64>(ObjClass + 0x18);

                if (Tag == 6)
                {
                    RibandciScript = driver::read<UINT64>(Entity + 0x28);
                    //if (!Player->IsValid())continue;
                    std::cout << "BASEPLAYER FOUND" << std::endl;

                    if (driver::read<UINT64>(driver::read<UINT64>(GameObject + 0x60)) == 0x616C506C61636F4C)
                    {

                        LP_isValid = true;
                        RibandciScript;
                        std::cout << "LocalPlayer " << RibandciScript << std::endl;

                    }
                }
                else if (Tag == 5)
                {
                    UINT64 ObjClass = driver::read<UINT64>(GameObject + 0x30);
                    UINT64	Entity = driver::read<UINT64>(ObjClass + 0x18);

                }
                else if (Tag == 20011)
                {
                    UINT64 ObjClass = driver::read<UINT64>(GameObject + 0x30);
                    UINT64	Entity = driver::read<UINT64>(ObjClass + 0x18);
                    UINT64 Dome = driver::read<UINT64>(Entity + 0x28);
                    TodCycle = driver::read<UINT64>(Dome + 0x38);
                }
            }

        NextEnt:
            continue;
        }
        if (!LP_isValid) {

            std::cin.get();
            exit(1);
        }

        for (auto ent : discovered_entities)
        {
            if (Vars::Visuals::PrefabEsp) {

                //UINT64 DisplayNamePtr = driver::read <UINT64>(ent + 0x60);
                //UINT64 DisplayNamePtr = driver::read <UINT64>(ent + 0x150);
                //UINT64 DisplayNamePtr2 = driver::read <UINT64>(DisplayNamePtr + 0x18);
                UINT64 DisplayNamePtr = driver::read <UINT64>(ent + 0x10);
                UINT64 DisplayNamePtr2 = driver::read <UINT64>(DisplayNamePtr + 0x30);
                UINT64 DisplayNamePtr3 = driver::read <UINT64>(DisplayNamePtr2 + 0x60);
                if (DisplayNamePtr3) {
               
                    std::string output = driver::ReadASCII(DisplayNamePtr3);

                    




                    if (IsValidPrefab(output) == true) {
                        GoodPrefab ThisPrefab;
                        Vector3 ThisPrefabPos = GetPrefabPos(ent);
                        int PrefabRange = Calc3D_Dist(LocalPlayerBasePos, ThisPrefabPos);
                        if (PrefabRange < 100) {
                            ThisPrefab.PrefabName = GetPrefabName(output);
                            ThisPrefab.PrefabPos = ThisPrefabPos;
                            ThisPrefab.PrefabDistance = PrefabRange;

                            local_prefabs.push_back(ThisPrefab);
                        }
                    }

                }

            }

            bool NetworkStatus = static_cast<bool>(driver::read<uint64_t>(ent + 0x50));

            if (!NetworkStatus)
                continue;

            if (ent == (UINT64)LocalPlayer.BasePlayer) {
                continue;
            }


            uint64_t GameObject = ReadChain(ent, { 0x10, 0x30 });
            int16_t Tag = driver::read<int16_t>(GameObject + 0x54);

            //here make sure its a player
            if (Tag != 6)
                continue;

            if (Vars::Visuals::IgnoreSleeping) {
                BasePlayer* DiscoverPlayer = (BasePlayer*)ent;
                if (DiscoverPlayer->IsSleeping()) {
                    continue;
                }
            }

            std::cout << "Entity Found" << std::endl;
            local_players.push_back(ent);
        }

        //save players here daddy
        discovered.mutex.lock();
        discovered.vec = local_players;
        discovered.mutex.unlock();
        if (Vars::Visuals::PrefabEsp) {
            GoodPrefabs.mutex.lock();
            GoodPrefabs.vec = local_prefabs;
            GoodPrefabs.mutex.unlock();
        }


        SleepEx(5000, false);
    }
}

view_matrix_t FastViewMatrix;


BasePlayer* TempTargetPlayer;
BasePlayer* TargetPlayer;

Vector3 LocalPlayerHead;

Vector3 TargetBonePos;


std::string BeltItems[7];
std::string ClothingItems[8];
std::string PanelName;


void EntityUpdate()
{


    while (true)
    {
        //TargetBonePos = { 0, 0, 0 };


        TempTargetPlayer = 0;
        if (GetAsyncKeyState(VK_SPACE) && Vars::Misc::spyderman)
        {
            LocalPlayer.BasePlayer->SpiderMan();
        }

        if (GetAsyncKeyState(VK_SPACE))
        {
            LocalPlayer.BasePlayer->SetGravity();
        }


        WeaponData* active = LocalPlayer.BasePlayer->GetActiveWeapon();
        WeaponFix(active);

        if (Vars::Misc::FakeAdmin) {
            if (!LocalPlayer.BasePlayer->HasFlags(4) && GetAsyncKeyState(VK_F2)) {
                LocalPlayer.BasePlayer->FakeAdmin();
            }
        }

        if (Vars::Misc::AlwaysDay)
        {
            LocalPlayer.BasePlayer->AlwaysDay();

        }

        SleepEx(16, false);


        float Finish;
        Vector3 Calc = { 0, 0, 0 };
        float Closest = FLT_MAX;
        int ClosestEntity = 1;

        std::vector<GoodPlayers2> updated_players;

        discovered.mutex.lock();
        std::vector<UINT64> players = discovered.vec;
        discovered.mutex.unlock();

        LocalPlayerHead = LocalPlayer.BasePlayer->HeadBone();

        LocalPlayerBasePos = LocalPlayer.BasePlayer->BasePos();


        for (auto entry : players)
        {

            BasePlayer* updated_player = (BasePlayer*)entry;
            if (updated_player == LocalPlayer.BasePlayer) {
                continue;
            }
            if (updated_player->IsLocalPlayer()) {
                continue;
            }
            float updated_player_health = updated_player->GetHealth();
            Vector3 updated_player_pos = updated_player->BasePos();

            int updated_player_distance = Calc3D_Dist(LocalPlayerBasePos, updated_player_pos);

            if (updated_player_distance > 300) {
                continue;
            }

            Vector3 updated_player_screen_pos = LocalPlayer.FastWorldToScreen(updated_player_pos, FastViewMatrix);

            if (updated_player_screen_pos.z < 0.1f || updated_player_screen_pos.x > 2200 || updated_player_screen_pos.y > 1400 || updated_player_screen_pos.x < -200 || updated_player_screen_pos.y < -200) {
                continue;
            }

            if (updated_player_health < 0.1) continue;
            if (updated_player_pos.x == 0.f || updated_player_pos.z == 0.f) continue;

            GoodPlayers2 ThisPlayer;
            ThisPlayer.PlayerHealth = updated_player_health;
            ThisPlayer.PlayerPos = updated_player_pos;
            ThisPlayer.PlayerDistance = updated_player_distance;
            std::string updated_player_name = updated_player->GetDisplayName();
            if (Vars::Visuals::DisplayName) {
                ThisPlayer.PlayerName = updated_player_name;
            }
            Vector3 updated_player_headpos = updated_player->HeadBone();

            ThisPlayer.PlayerHeadPos = updated_player_headpos;

            if (TargetPlayer == updated_player) {
                ThisPlayer.IsTarget = true;

                PanelPlayer.Distance = updated_player_distance;
                PanelPlayer.Name = updated_player_name;
                PanelPlayer.Health = updated_player_health;



            }
            else
            {
                ThisPlayer.IsTarget = false;
            }


            Vector3 HeadScreen = LocalPlayer.FastWorldToScreen(updated_player_headpos, FastViewMatrix);

            Finish = pythag(HeadScreen.x, HeadScreen.y, 960, 540);

            if (Finish < Closest && updated_player->IsInFov(HeadScreen)) {
                Closest = Finish;
                TempTargetPlayer = (BasePlayer*)entry;


            }

            //BONE SHITS
            if (Vars::Visuals::Bones && updated_player_distance < 35) {
                ThisPlayer.Bones.Head = updated_player_headpos;
                ThisPlayer.Bones.Neck = updated_player->GetBoneInt(46);
                ThisPlayer.Bones.Stomach = updated_player->GetBoneInt(19);

                ThisPlayer.Bones.LArm3 = updated_player->GetBoneInt(26);
                ThisPlayer.Bones.LArm2 = updated_player->GetBoneInt(25);
                ThisPlayer.Bones.LArm1 = updated_player->GetBoneInt(24);


                ThisPlayer.Bones.RArm3 = updated_player->GetBoneInt(57);
                ThisPlayer.Bones.RArm2 = updated_player->GetBoneInt(56);
                ThisPlayer.Bones.RArm1 = updated_player->GetBoneInt(55);

                ThisPlayer.Bones.LLeg3 = updated_player->GetBoneInt(15);
                ThisPlayer.Bones.LLeg2 = updated_player->GetBoneInt(14);
                ThisPlayer.Bones.LLeg1 = updated_player->GetBoneInt(13);

                ThisPlayer.Bones.RLeg3 = updated_player->GetBoneInt(3);
                ThisPlayer.Bones.RLeg2 = updated_player->GetBoneInt(2);
                ThisPlayer.Bones.RLeg1 = updated_player->GetBoneInt(1);
            }


            updated_players.push_back(ThisPlayer);


        }
        ////BONE SHITS
        TargetPlayer = TempTargetPlayer;

        GoodPlayers3.mutex.lock();
        GoodPlayers3.vec = updated_players;
        GoodPlayers3.mutex.unlock();




        if (Vars::Visuals::ShowPanel) {


            if (Vars::Visuals::ShowHotBar && TargetPlayer != 0) {

                UINT64 ItemsList = TargetPlayer->GetItemsList();

                BeltItems[1] = TargetPlayer->GetBeltItems(ItemsList, 1);
                BeltItems[2] = TargetPlayer->GetBeltItems(ItemsList, 2);
                BeltItems[3] = TargetPlayer->GetBeltItems(ItemsList, 3);
                BeltItems[4] = TargetPlayer->GetBeltItems(ItemsList, 4);
                BeltItems[5] = TargetPlayer->GetBeltItems(ItemsList, 5);
                BeltItems[6] = TargetPlayer->GetBeltItems(ItemsList, 6);

            }

            if (Vars::Visuals::ShowClothes && TargetPlayer != 0) {

                UINT64 ItemsList = TargetPlayer->GetClothingItemsList();

                ClothingItems[1] = TargetPlayer->GetClothingItems(ItemsList, 1);
                ClothingItems[2] = TargetPlayer->GetClothingItems(ItemsList, 2);
                ClothingItems[3] = TargetPlayer->GetClothingItems(ItemsList, 3);
                ClothingItems[4] = TargetPlayer->GetClothingItems(ItemsList, 4);
                ClothingItems[5] = TargetPlayer->GetClothingItems(ItemsList, 5);
                ClothingItems[6] = TargetPlayer->GetClothingItems(ItemsList, 6);
                ClothingItems[7] = TargetPlayer->GetClothingItems(ItemsList, 7);

            }

        }
    }
}


void SmoothAim(Vector2 Angle, float smooth) {
    Angle.x /= smooth;
    Angle.y /= smooth;
}

//bool TempHoldingAim;
#include "Silent.h"
void Aimbot() {
    while (true)
    {
        SleepEx(20, false);

        //if (GetAsyncKeyState(VK_LMENU) && Vars::Aim::AimBot && TargetPlayer != 0) {
        //    std::cout << "GETTING KEY" << std::endl;
        //    if (TargetPlayer->IsDead()) {
        //        continue;
        //    }


        //    TargetBonePos = TargetPlayer->HeadBone();
        //    if (TargetBonePos.x == 0 || TargetBonePos.y == 0) {
        //        continue;
        //    }


        //    if (TargetPlayer->IsDead()) {
        //        continue;
        //    }


        //    if (Vars::Aim::Prediction && Vars::Aim::AimBot) {
        //        TargetBonePos = Prediction(LocalPlayerHead, TargetPlayer, BoneList(Vars::Aim::BoneToAim), TargetBonePos);
        //    }

        //    if (true) {
        //        UINT64 HeadAngles = 0x1B6712362D8;
        //        UINT64 BodyAngles = 0x1B6712362BC;

        //        if (GetAsyncKeyState(VK_LMENU)) {
        //            TempHoldingAim = true;

        //            Vector2 CurrentAngles = driver::read<Vector2>(BodyAngles);
        //            Vector2 CurrentRotation = driver::read<Vector2>(HeadAngles);
        //            Vector3 WantedAngles = CalcAngle(LocalPlayerHead, TargetBonePos);
        //            Vector2 HeadRotation = { CurrentRotation.x + (CurrentAngles.x - WantedAngles.x) , CurrentRotation.y + (CurrentAngles.y - WantedAngles.y) };
        //            driver::write<float>(0x1B6712362F8, 0);
        //            driver::write<Vector2>(HeadAngles, HeadRotation);
        //            driver::write<Vector2>(BodyAngles, { WantedAngles.x, WantedAngles.y });
        //           
        //            //driver::write<float>(0x11FEE00F2F8, 0);
        //            driver::write<Vector2>(BodyAngles, { WantedAngles.x, WantedAngles.y });
        //        }
        //    }




        //    
        //}
        //else
        //{
        //    UINT64 HeadAngles = 0x1B6712362D8;
        //    UINT64 BodyAngles = 0x1B6712362BC;
        //    if (TempHoldingAim == true) {
        //         Vector2 CurrentAngles = driver::read<Vector2>(BodyAngles);
        //        Vector2 HeadRotation = driver::read<Vector2>(HeadAngles);
        //        Vector2 SetBackAngles = { HeadRotation.x + CurrentAngles.x, HeadRotation.y + CurrentAngles.y };
        //        driver::write<Vector2>(BodyAngles, SetBackAngles);
        //        driver::write<Vector2>(HeadAngles, { 0.0f, 0.0f });
        //    }
        //    TempHoldingAim = false;
        //}
        
        if (GetAsyncKeyState(0x58) && Vars::Aim::SilentAim && TargetPlayer != 0) {
           
            //body rot = 0x44
            if (TargetPlayer->IsDead()) {
                continue;
            }


            TargetBonePos = TargetPlayer->HeadBone();
            if (TargetBonePos.x == 0 || TargetBonePos.y == 0) {
                continue;
            }


            if (TargetPlayer->IsDead()) {
                continue;
            }


            if (Vars::Aim::Prediction && Vars::Aim::AimBot) {
                TargetBonePos = Prediction(LocalPlayerHead, TargetPlayer, BoneList(Vars::Aim::BoneToAim), TargetBonePos);
            }

            UINT64 PlayerEyes = driver::read<UINT64>((uintptr_t)LocalPlayer.BasePlayer + 0x658);

            Vector3 Angles = CalcAngle(LocalPlayerHead, TargetBonePos);
            

            if (!Normalize(Angles.y, Angles.x)) {
                std::cout << "NOT NORMAL : " << Angles.x << " , " << Angles.y << std::endl;
                continue;
            }
            if (isnan(Angles.x) || isnan(Angles.y)) {
                std::cout << "ISNAN" << std::endl;
                continue;
            }
            //std::cout << "SETTING VA" << std::endl;

            Vector4 QuatAngles = ToQuat({ Angles.x, Angles.y, 0.0f });
            //std::cout << "EULER ANGLES : " << Angles.x << " , " << Angles.y << " , " << Angles.z << std::endl;
            //std::cout << "QUAT ANGLES : " << QuatAngles.w << " , " << QuatAngles.x << " , " << QuatAngles.y << " , " << QuatAngles.z << std::endl;
            driver::write<Vector4>(PlayerEyes + 0x44, QuatAngles);

        }
        else if (GetAsyncKeyState(VK_XBUTTON1) && Vars::Aim::AimBot && TargetPlayer != 0) {
       
            std::cout << "GETTING KEY" << std::endl;
            if (TargetPlayer->IsDead()) {
                continue;
            }


            TargetBonePos = TargetPlayer->HeadBone();
            if (TargetBonePos.x == 0 || TargetBonePos.y == 0) {
                continue;
            }


            if (TargetPlayer->IsDead()) {
                continue;
            }


            if (Vars::Aim::Prediction && Vars::Aim::AimBot) {
                TargetBonePos = Prediction(LocalPlayerHead, TargetPlayer, BoneList(Vars::Aim::BoneToAim), TargetBonePos);
            }

           
            if (Vars::Aim::bSmoothing == false) {
                Vector3 TargetAngles = CalcAngle(LocalPlayerHead, TargetBonePos);
                Vector2 Angles; Angles.x = TargetAngles.x, Angles.y = TargetAngles.y;

                if (!Normalize(Angles.y, Angles.x)) {
                    std::cout << "NOT NORMAL : " << Angles.x << " , " << Angles.y << std::endl;
                    continue;
                }
                if (isnan(Angles.x) || isnan(Angles.y)) {
                    std::cout << "ISNAN" << std::endl;
                    continue;
                }
                std::cout << "SETTING VA" << std::endl;
                std::cout << "EULER ANGLES : " << Angles.x << " , " << Angles.y << std::endl;
                LocalPlayer.BasePlayer->SetVA(Angles);
            }
            else if (Vars::Aim::bSmoothing == true)
            {
                Vector3 TargetHeadPos = LocalPlayer.FastWorldToScreen(TargetBonePos, FastViewMatrix);
                Vector2 CursorPos = { 960, 540 };
                Vector2 Movement = { (TargetHeadPos.x - CursorPos.x) , (TargetHeadPos.y - CursorPos.y) };

                if (Movement.x > Vars::Aim::Fov) {
                    continue;
                }
                if (Movement.y > Vars::Aim::Fov) {
                    continue;
                }

#define SMOOTHING1 10
#define SMOOTHING2 2

                int XSmoothing = SMOOTHING1;
                int YSmoothing = SMOOTHING1;
                if (Movement.x < 0) {
                    if (Movement.x < 20) {
                        XSmoothing = SMOOTHING2;

                    }
                    else
                    {
                        XSmoothing = SMOOTHING1;
                    }
                }
                else
                {
                    if (Movement.x > -SMOOTHING1) {
                        XSmoothing = SMOOTHING2;

                    }
                    else
                    {
                        XSmoothing = SMOOTHING1;
                    }
                }
                if (Movement.y < 0) {
                    if (Movement.y < SMOOTHING1) {
                        YSmoothing = SMOOTHING2;
                    }
                    else
                    {
                        YSmoothing = SMOOTHING1;
                    }
                }
                else
                {
                    if (Movement.y > -SMOOTHING1) {
                        YSmoothing = SMOOTHING2;
                    }
                    else
                    {
                        YSmoothing = SMOOTHING1;
                    }
                }

                mouse_event(1, Movement.x / XSmoothing, Movement.y / YSmoothing, 0, 0);
            
            }
        }
        

    }
}

int Iterations;

void DrawPlayerPanel() {
    ImGuiWindowFlags ResizeFlags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar;
    string EntityDisplayName = PanelPlayer.Name;
    //string EntityWeapon = PanelPlayer.HeldItem;
    float Health = PanelPlayer.Health;
    int EntityDistance = PanelPlayer.Distance;


    std::string DisplayNameInfo = ("Name : " + EntityDisplayName);



    stringstream strshealth;
    strshealth << Health;
    std::string HealthInfo = ("Health : " + strshealth.str());


    stringstream strsdistance;
    strsdistance << EntityDistance;
    std::string DistanceInfo = ("Distance : " + strsdistance.str() + "m");

    ImGui::SetNextWindowSize(ImVec2(130, 240));
    ImGui::Begin("Player Info", NULL);
    ImVec2 WindowSize = ImGui::GetWindowSize();
    ImGui::BeginChild(1, ImVec2(WindowSize.x - 10, WindowSize.y - 23), true);
    ImGui::Text(DisplayNameInfo.c_str());
    ImGui::Text(HealthInfo.c_str());
    //ImGui::Text(DistanceInfo.c_str());
    
    ImGui::Text(" ");
    if (Vars::Visuals::ShowHotBar) {
       
    
        
        for (int i = 0; i < 7; i++)
        {
            if (BeltItems[i] != "None" && BeltItems[i] != "dxeso") {
                ImGui::Text(BeltItems[i].c_str());
            }
        }
        /* ImGui::Text(BeltItems[1].c_str());
         ImGui::Text(BeltItems[2].c_str());
         ImGui::Text(BeltItems[3].c_str());
         ImGui::Text(BeltItems[4].c_str());
         ImGui::Text(BeltItems[5].c_str());
         ImGui::Text(BeltItems[6].c_str());*/
       
    }
    if (Vars::Visuals::ShowClothes) {
        for (int i = 0; i < 8; i++)
        {
            if (ClothingItems[i] != "None" && ClothingItems[i] != "dxeso" && ClothingItems[i].substr(0, 1) != "x") {
                ImGui::Text(ClothingItems[i].c_str());
            }
        }
       /* ImGui::Text(" ");
        ImGui::Text("CLOTHING");
        ImGui::BeginChild(2, ImVec2(160, 135), true, ResizeFlags);
        for (int i = 0; i < 8; i++)
        {
            if (ClothingItems[i] != "None" && ClothingItems[i] != "dxeso" && ClothingItems[i].substr(0, 1) != "x") {
                ImGui::Text(ClothingItems[i].c_str());
            }
        }
       
        ImGui::EndChild();*/
    }
    ImGui::EndChild();

    ImGui::End();
}

void DrawPlayersLol()
{
    if (Vars::Visuals::ShowPanel) {
        DrawPlayerPanel();
    }
    
    //std::cout << TargetPlayer << std::endl;
    timer Time;
    Time.Start();
    FastViewMatrix = driver::read<view_matrix_t>(Vmatrix + 0x2E4);

    GoodPlayers3.mutex.lock();
    std::vector<GoodPlayers2> render_players = GoodPlayers3.vec;
    GoodPlayers3.mutex.unlock();
    Iterations = 0;

    if (Vars::Visuals::PrefabEsp) {
        GoodPrefabs.mutex.lock();
        std::vector<GoodPrefab> render_prefabs = GoodPrefabs.vec;
        GoodPrefabs.mutex.unlock();

        for (auto& entry : render_prefabs) {
            GoodPrefab DrawPrefab = entry;
            Vector3 PrefabPos = DrawPrefab.PrefabPos;
            if (PrefabPos.x == 0.f || PrefabPos.z == 0.f) continue;
            Vector3 PrefabScreenPos = LocalPlayer.FastWorldToScreen(PrefabPos, FastViewMatrix);
            if (PrefabScreenPos.z > 0.1f) {
                int PrefabRange = Calc3D_Dist(LocalPlayerBasePos, DrawPrefab.PrefabPos);
                std::string PrefabName = DrawPrefab.PrefabName;
                RGBA PrefabColor;
                if (PrefabName.substr(0, 1) == "G") //GUNS
                {
                    PrefabColor = { 127, 30, 255, 240 };
                }
                else if (PrefabName.substr(0, 1) == "N") { //NODES
                    PrefabColor = { 40, 255, 204, 255 };
                }
                else if (PrefabName.substr(0, 1) == "H") { //HEMP
                    PrefabColor = { 51, 255, 153, 255 };
                }
                else if (PrefabName.substr(0, 1) == "C") { //Corpses
                    PrefabColor = { 30, 30, 30, 255 };
                }
                else if (PrefabName.substr(0, 1) == "B") { //Bags
                    PrefabColor = { 0, 0, 0, 255 };
                }
                else if (PrefabName.substr(0, 1) == "S") { //Stashes
                    PrefabColor = { 255, 255, 0, 255 };
                }
                else if (PrefabName.substr(0, 1) == "O") { //OTHER
                    PrefabColor = { 255, 255, 255, 255 };
                }
                else
                {
                    PrefabColor = { 255, 255, 255, 255 };
                }
                std::string PrefabTitle = "[" + std::to_string(PrefabRange) + "] " + PrefabName.substr(1);

                DrawNewTextImGui(PrefabScreenPos.x, PrefabScreenPos.y, PrefabColor, PrefabTitle.c_str());
                //DrawLineImGui(PrefabScreenPos.x, PrefabScreenPos.y, 960, 1080, VanityColor, 1);
            }

        }
    }


    for (auto& entry : render_players)
    {
        RGBA VanityColor = { 0, 246, 197, 240 };
        RGBA ESPCOLOR = { 66, 150, 249, 240 };

        Iterations++;


        GoodPlayers2 DrawPlayer = entry;

        float DrawPlayerHealth = DrawPlayer.PlayerHealth;

        if (DrawPlayerHealth < 0.1) continue;

        Vector3 PlayerPos = DrawPlayer.PlayerPos;
        Vector3 PlayerHeadPos = DrawPlayer.PlayerHeadPos;
        PlayerHeadPos.y += .2;
        PlayerPos.y -= .1;
        Vector3 PlayerScreen = LocalPlayer.FastWorldToScreen(PlayerPos, FastViewMatrix);
        Vector3 PlayerHeadScreen = LocalPlayer.FastWorldToScreen(PlayerHeadPos, FastViewMatrix);

        std::string DisplayName = DrawPlayer.PlayerName;

        int DrawPlayerDistance = DrawPlayer.PlayerDistance;

        int Height = PlayerScreen.y - PlayerHeadScreen.y;
        int Width = Height / 2;

        if (DrawPlayer.IsTarget == true) {
            VanityColor = { 255, 20, 60, 240 };
        }
        else
        {
            VanityColor = { 66, 150, 249, 240 };
        }

        if (Vars::Visuals::FilledBox) {
            DrawFilledRectImGui(PlayerScreen.x - (Width / 2), PlayerHeadScreen.y, Width, Height, { 30, 30, 30, 150 });
        }
        if (Vars::Visuals::Box) {
            DrawRectImGui(PlayerScreen.x - (Width / 2), PlayerHeadScreen.y, Width, Height, VanityColor, 1);
        }
        if (Vars::Visuals::HP) {

            if (DrawPlayerHealth > 101) {
                DrawPlayerHealth = 100;
            }
            float HealthHeightCalc = ((float)DrawPlayerHealth / 100) * (float)Height;

            if (Height > 15) {
                DrawFilledRectImGui(PlayerScreen.x - ((Width / 2) + 5), PlayerScreen.y, 2, -Height, { 30, 30, 30, 220 });
                DrawFilledRectImGui(PlayerScreen.x - ((Width / 2) + 5), PlayerScreen.y, 2, -HealthHeightCalc, { 80, 220, 100, 225 });
            }

        }
        if (Vars::Visuals::Line) {
            DrawLineImGui(960, 1080, PlayerScreen.x, PlayerScreen.y, VanityColor, 1);
        }

        if (Vars::Visuals::DisplayName) {
            std::string DisplayNameShit = "[" + std::to_string(DrawPlayerDistance) + "]  " + DisplayName;
            //DrawNewTextImGui(PlayerHeadScreen.x - (Width / 2), PlayerHeadScreen.y - 13, { 230, 230, 230, 230 }, DisplayNameShit.c_str());
            DrawShadowTextImGui(PlayerHeadScreen.x - (Width / 2), PlayerHeadScreen.y - 13, { 230, 230, 230, 230 }, DisplayNameShit.c_str());
        }


        if (Vars::Visuals::Bones && DrawPlayerHealth > 0.1) {

            Vector3 BoneHead = LocalPlayer.FastWorldToScreen(DrawPlayer.Bones.Head, FastViewMatrix);
            Vector3 BoneNeck = LocalPlayer.FastWorldToScreen(DrawPlayer.Bones.Neck, FastViewMatrix);
            Vector3 BoneStomach = LocalPlayer.FastWorldToScreen(DrawPlayer.Bones.Stomach, FastViewMatrix);
            Vector3 BoneLArm1 = LocalPlayer.FastWorldToScreen(DrawPlayer.Bones.LArm1, FastViewMatrix);
            Vector3 BoneLArm2 = LocalPlayer.FastWorldToScreen(DrawPlayer.Bones.LArm2, FastViewMatrix);
            Vector3 BoneLArm3 = LocalPlayer.FastWorldToScreen(DrawPlayer.Bones.LArm3, FastViewMatrix);
            Vector3 BoneRArm1 = LocalPlayer.FastWorldToScreen(DrawPlayer.Bones.RArm1, FastViewMatrix);
            Vector3 BoneRArm2 = LocalPlayer.FastWorldToScreen(DrawPlayer.Bones.RArm2, FastViewMatrix);
            Vector3 BoneRArm3 = LocalPlayer.FastWorldToScreen(DrawPlayer.Bones.RArm3, FastViewMatrix);
            Vector3 BoneLLeg1 = LocalPlayer.FastWorldToScreen(DrawPlayer.Bones.LLeg1, FastViewMatrix);
            Vector3 BoneLLeg2 = LocalPlayer.FastWorldToScreen(DrawPlayer.Bones.LLeg2, FastViewMatrix);
            Vector3 BoneLLeg3 = LocalPlayer.FastWorldToScreen(DrawPlayer.Bones.LLeg3, FastViewMatrix);
            Vector3 BoneRLeg1 = LocalPlayer.FastWorldToScreen(DrawPlayer.Bones.RLeg1, FastViewMatrix);
            Vector3 BoneRLeg2 = LocalPlayer.FastWorldToScreen(DrawPlayer.Bones.RLeg2, FastViewMatrix);
            Vector3 BoneRLeg3 = LocalPlayer.FastWorldToScreen(DrawPlayer.Bones.RLeg3, FastViewMatrix);
            if (BoneHead.z > 0.1f && BoneRLeg3.z > 0.1f && BoneRLeg1.z > 0.1f) {
                DrawLineImGui(BoneHead.x, BoneHead.y, BoneNeck.x, BoneNeck.y, ESPCOLOR, 1);

                DrawLineImGui(BoneNeck.x, BoneNeck.y, BoneLArm1.x, BoneLArm1.y, ESPCOLOR, 1);
                DrawLineImGui(BoneLArm1.x, BoneLArm1.y, BoneLArm2.x, BoneLArm2.y, ESPCOLOR, 1);
                DrawLineImGui(BoneLArm2.x, BoneLArm2.y, BoneLArm3.x, BoneLArm3.y, ESPCOLOR, 1);

                DrawLineImGui(BoneNeck.x, BoneNeck.y, BoneRArm1.x, BoneRArm1.y, ESPCOLOR, 1);
                DrawLineImGui(BoneRArm1.x, BoneRArm1.y, BoneRArm2.x, BoneRArm2.y, ESPCOLOR, 1);
                DrawLineImGui(BoneRArm2.x, BoneRArm2.y, BoneRArm3.x, BoneRArm3.y, ESPCOLOR, 1);

                DrawLineImGui(BoneNeck.x, BoneNeck.y, BoneStomach.x, BoneStomach.y, ESPCOLOR, 1);


                DrawLineImGui(BoneStomach.x, BoneStomach.y, BoneLLeg1.x, BoneLLeg1.y, ESPCOLOR, 1);
                DrawLineImGui(BoneLLeg1.x, BoneLLeg1.y, BoneLLeg2.x, BoneLLeg2.y, ESPCOLOR, 1);
                DrawLineImGui(BoneLLeg2.x, BoneLLeg2.y, BoneLLeg3.x, BoneLLeg3.y, ESPCOLOR, 1);


                DrawLineImGui(BoneStomach.x, BoneStomach.y, BoneRLeg1.x, BoneRLeg1.y, ESPCOLOR, 1);
                DrawLineImGui(BoneRLeg1.x, BoneRLeg1.y, BoneRLeg2.x, BoneRLeg2.y, ESPCOLOR, 1);
                DrawLineImGui(BoneRLeg2.x, BoneRLeg2.y, BoneRLeg3.x, BoneRLeg3.y, ESPCOLOR, 1);
            }
        }

        // DrawCircleFilledImGui(PlayerHeadScreen.x, PlayerHeadScreen.y, Width / 6, { 24, 24, 24, 70 }, 20);



    }


    int time = Time.GetDuration();
    if (GetAsyncKeyState(VK_LMENU)) {
        std::cout << Iterations << " ITERATIONS WITH A TIME OF : " << time << std::endl;
    }

}


UINT64 oPlayerList;
bool Initialized = true;
void InitializeOffsets() {

    UpdateLocalPlayer();

    oPlayerList = 0;
    if (!oPlayerList) {
        UINT64 val = driver::read<UINT64>(Gbase + oBaseNetworkable);
        UINT64 st = driver::read<UINT64>(val + 0xB8);
        UINT64 listptr = driver::read<UINT64>(st + 0x0);
        UINT64 list = driver::read<UINT64>(listptr + 0x10);
        oPlayerList = driver::read<UINT64>(list + 0x28);
    }

    client_ents = oPlayerList;
    Initialized = true;
}
void InitializeCheat() {
    InitializeOffsets();
    std::thread(EntityUpdate).detach();
    std::thread(EntityDiscovery).detach();
    std::thread(Aimbot).detach();
}