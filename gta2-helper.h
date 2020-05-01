#ifndef GTA_H
#define GTA_H

#include "gta2.h"

const DWORD pGameTick = (DWORD)0x0045c1f0;
const DWORD pDraw = (DWORD)0x00461960;
static const TrafficLigthStruct* ptrToTrafficLights = (TrafficLigthStruct*)0x006721cc;

static DWORD ptrToPedManager = 0x005e5bbc;
static DWORD ptrToGame = 0x005eb4fc;
static DWORD ptrToS3 = 0x00670684;
static DWORD ptrToCarEngines = 0x005e5488;

typedef Ped* (__stdcall GetPedById)(int);
static GetPedById* fnGetPedByID = (GetPedById*)0x0043ae10;

//Player* __thiscall Game::GetPlayerSlotByIndex(Game* this, byte index);
typedef Player* (__fastcall GetPlayerSlotByIndex)(Game* game, DWORD edx, byte index);
static GetPlayerSlotByIndex* fnGetSaveSlotByIndex = (GetPlayerSlotByIndex*)0x004219e0;

//void __thiscall ShowBigOnScreenLabel(void* this, WCHAR* txt, int timeToShowInSeconds);
typedef void(__fastcall ShowBigOnScreenLabel)(void* ptr, DWORD edx, WCHAR* txt, int time);
static ShowBigOnScreenLabel* fnShowBigOnScreenLabel = (ShowBigOnScreenLabel*)0x004c6060;

//void SpawnCar(int x, int y, int z, short rot, CAR_MODEL model)
typedef Car* (SpawnCar)(int x, int y, int z, short rot, CAR_MODEL model);
static SpawnCar* fnSpawnCar = (SpawnCar*)0x00426e10;

// void __fastcall PlayVocal(void *param_1,undefined4 unused,VOCAL vocal)
typedef void* (__fastcall PlayVocal)(void*, DWORD edx, VOCAL vocal);
static PlayVocal* fnPlayVocal = (PlayVocal*)0x004105b0;

// void __fastcall StartMapPlaySound(void *param_1)
typedef void* (__fastcall StartMapPlaySound)(void*, DWORD edx);
static StartMapPlaySound* fnStartMapPlaySound = (StartMapPlaySound*)0x004784d0;

// void Vid_FlipBuffers(D3DContext *param_1)
typedef void* (Vid_FlipBuffers)(D3DContext* param_1);
static Vid_FlipBuffers* fnVid_FlipBuffers = 0;

// Ped * SpawnPedAtPosition(int x,int y,int z,PED_REMAP remap,short param_5)
typedef Ped* (SpawnPedAtPosition)(int x, int y, int z, PED_REMAP remap, short param_5);
static SpawnPedAtPosition* fnSpawnPedAtPosition = (SpawnPedAtPosition*)0x0043db40;

// bool __thiscall SetPedPosition(Ped *this,int x,int y,int z)
typedef bool* (__fastcall SetPedPosition)(Ped* ped, DWORD edx, int x, int y, int z);
static SetPedPosition* fnSetPedPosition = (SetPedPosition*)0x004360c0;

#endif // !GTA_H