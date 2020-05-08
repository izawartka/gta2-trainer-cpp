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
static DWORD ptrToMapRelatedStruct = 0x00662c08;
static DWORD ptrToS10 = 0x00672f40;
static DWORD ptrToS2LocalesSettings = 0x00671550;
static DWORD ptrToCarsPrefabs = 0x005e4ca0;

#define ByPtr(type, x) (type*)*(DWORD*)x
#define FloatEncode(x) (int)(x * 16384)
#define FloatDecode(x) (double)x / 16384.0
// Usage: auto game = fnGetGame();
#define fnGetGame() ByPtr(Game, ptrToGame)

typedef Ped* (__stdcall GetPedById)(int);
static GetPedById* fnGetPedByID = (GetPedById*)0x0043ae10;

//Player* __thiscall Game::GetPlayerSlotByIndex(Game* this, byte index);
typedef Player* (__fastcall GetPlayerSlotByIndex)(Game* game, DWORD edx, byte index);
static GetPlayerSlotByIndex* fnGetPlayerSlotByIndexRaw = (GetPlayerSlotByIndex*)0x004219e0;
#define fnGetPlayerSlotByIndex(index) fnGetPlayerSlotByIndexRaw(ByPtr(Game, ptrToGame), 0, index)

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

// void __fastcall FindMaxZForLocation(void *param_1,undefined4 edx,int *outZ,SCR_f x,SCR_f y)
typedef void (__fastcall FindMaxZForLocation)(void* ptrToMapRelatedStruct, DWORD edx, SCR_f* outZ, SCR_f x, SCR_f y);
static FindMaxZForLocation* fnFindMaxZForLocationRaw = (FindMaxZForLocation*)0x0046a420;
#define fnFindMaxZForLocation(x, y, z) fnFindMaxZForLocationRaw(ByPtr(ptrToMapRelatedStruct), 0, z, x, y);

// int __thiscall FUN_00466990(void *ptrToMapRelatedStruct,int x,int y,int *outZ)
typedef void (__fastcall FindMaxZForTile)(void* ptrToMapRelatedStruct, DWORD edx, int x, int y, int* outZ);
static FindMaxZForTile* fnFindMaxZForTileRaw = (FindMaxZForTile*)0x00466990;
#define fnFindMaxZForTile(x, y, z) fnFindMaxZForTileRaw(ByPtr(ptrToMapRelatedStruct), 0, x, y, z);

// void __fastcall DoTeleport(Player *param_1)
typedef void (__fastcall DoTeleport)(Player*, DWORD edx);
static DoTeleport* fnDoTeleportRaw = (DoTeleport*)0x004a5ad0;
/*
Usage: 
fnDoTeleport(fnGetPlayerSlotByIndex(0), 133.9, 106.5);
*/
#define fnDoTeleport(p, x, y) \
	p->ph2.encodedCameraOrTeleportX  = FloatEncode(x); \
	p->ph2.encodedCameraOrTeleportY = FloatEncode(y); \
	fnDoTeleportRaw(p, 0);


// bool __fastcall PedTick(Ped *ped)
typedef void(__fastcall PedTick)(Ped*, DWORD edx);
static PedTick* fnPedTickRaw = (PedTick*)0x004454e0;


// void __fastcall showMessageToPlayer(DWORD* param_1, undefined edx, int timeInSeconds, char* messageCode)
typedef void(__fastcall ShowMessageToPlayer)(S10_TxtMessage*, DWORD edx, int timeInSeconds, char* messageCode);
static ShowMessageToPlayer* fnShowMessageToPlayerRaw = (ShowMessageToPlayer*)0x004c6750;
// example: fnShowMessageToPlayer(3, "nespray");
#define fnShowMessageToPlayer(seconds, messageCode) fnShowMessageToPlayerRaw(&(ByPtr(S10, ptrToS10))->txtMessage, 0, seconds, messageCode)

void fnShowCustomTextMessage(WCHAR* message);
Car* fnGetCarById(int id);

#endif // !GTA_H