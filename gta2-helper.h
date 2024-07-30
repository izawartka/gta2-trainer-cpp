#pragma once
#ifndef GTA_H
#define GTA_H

#include "gta2.h"
#include "MainWindowData.h"

static_assert(sizeof(u4) == 4, "Wrong size of u4 struct");
static_assert(sizeof(u2) == 2, "Wrong size of u2 struct");
static_assert(sizeof(u1) == 1, "Wrong size of u1 struct");
static_assert(sizeof(byte) == 1, "Wrong size of byte struct");
static_assert(sizeof(bool) == 1, "Wrong size of bool struct");

static_assert(sizeof(Car) == 0xbc, "Wrong size of Car struct");
static_assert(sizeof(Ped) == 0x294, "Wrong size of Ped struct");
static_assert(sizeof(HORN) == 0x1, "Wrong size of HORN enum");
static_assert(sizeof(CAR_SIREN_STATE) == 0x1, "Wrong size of CAR_SIREN_STATE enum");
static_assert(sizeof(CAR_MODEL4) == 0x4, "Wrong size of CAR_MODEL4 enum");
static_assert(sizeof(CAR_MODEL) == 0x1, "Wrong size of CAR_MODEL enum");
static_assert(sizeof(PED_REMAP) == 0x1, "Wrong size of PED_REMAP enum");
static_assert(sizeof(SPRITE_BIT1) == 0x1, "Wrong size of SPRITE_BIT1 enum");
static_assert(sizeof(TRAFFIC_PHASE) == 0x1, "Wrong size of TRAFFIC_PHASE enum");

const DWORD pGameTick = (DWORD)0x0045c1f0;
const DWORD pDraw = (DWORD)0x00461960;
const DWORD pFreeSurface = (DWORD)0x004caf50;
const DWORD pDrawUI = (DWORD)0x004ca440;
const DWORD pDrawChat = (DWORD)0x004c8910;
const DWORD pOpenChat = (DWORD)0x004a721b;
static const TrafficLigthStruct* ptrToTrafficLights = (TrafficLigthStruct*)0x006721cc;

static DWORD ptrToPedManager = 0x005e5bbc;
static DWORD ptrToGame = 0x005eb4fc;
static DWORD ptrToS3 = 0x00670684;
static DWORD ptrToCarEngines = 0x005e5488;
static DWORD ptrToMapRelatedStruct = 0x00662c08;
static DWORD ptrToS10 = 0x00672f40;
static DWORD ptrToS2LocalesSettings = 0x00671550;
static DWORD ptrToCarsPrefabs = 0x005e4ca0;
static DWORD ptrToTrafficManager = 0x005e4ca4;
static DWORD ptrToPlayerPhysics = 0x005e3cc4;
static DWORD ptrToFrontEnd = 0x005eb160;
static DWORD ptrToS6 = 0x005dcbc8;

#define ByPtr(type, x) (type*)*(DWORD*)x
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

//Car* __fastcall SpawnCarAdvanced(TrafficManager* trafficMngr, int edx, int x, int y, int z, int rot, CAR_MODEL4 model, int param_8)
typedef Car* (__fastcall SpawnCarAdvanced)(TrafficManager* trafficMngr, DWORD edx, int x, int y, int z, int rot, CAR_MODEL4 model, int param_8);
static SpawnCarAdvanced* fnSpawnCarAdvanced = (SpawnCarAdvanced*)0x00426ac0;

// void __fastcall PlayVocal(void *param_1,undefined4 unused,VOCAL vocal)
typedef void* (__fastcall PlayVocal)(void*, DWORD edx, VOCAL vocal);
static PlayVocal* fnPlayVocal = (PlayVocal*)0x004105b0;

// void __fastcall StartMapPlaySound(void *param_1)
typedef void* (__fastcall StartMapPlaySound)(void*, DWORD edx);
static StartMapPlaySound* fnStartMapPlaySound = (StartMapPlaySound*)0x004784d0;

// Ped * SpawnPedAtPosition(int x,int y,int z,PED_REMAP remap,short param_5)
typedef Ped* (SpawnPedAtPosition)(int x, int y, int z, PED_REMAP remap, short param_5);
static SpawnPedAtPosition* fnSpawnPedAtPosition = (SpawnPedAtPosition*)0x0043db40;

// bool __thiscall SetPedPosition(Ped *this,int x,int y,int z)
typedef bool* (__fastcall SetPedPosition)(Ped* ped, DWORD edx, int x, int y, int z);
static SetPedPosition* fnSetPedPosition = (SetPedPosition*)0x004360c0;

// void __thiscall ExplodeCarMaybe(Car *this,uint param_1_00 = 0x13)
typedef void(__fastcall ExplodeCar)(Car* car, DWORD edx, EXPLOSION_SIZE explosionSize);
static ExplodeCar* fnExplodeCar = (ExplodeCar*)0x00426fa0;

typedef uint (CarAddWeapon)(CAR_WEAPON type, uint ammo, Car* car);
static CarAddWeapon* fnCarAddWeapon = (CarAddWeapon*)0x004cd820;

typedef void(__fastcall CarAddRoofGun)(Car* car);
static CarAddRoofGun* fnCarAddRoofGun = (CarAddRoofGun*)0x0041fdf0;

typedef void(__fastcall CarAddRoofTankTurret)(Car* car);
static CarAddRoofTankTurret* fnCarAddRoofTankTurret = (CarAddRoofTankTurret*)0x0041fda0;

typedef void(__fastcall CarAddRoofWaterGun)(Car* car);
static CarAddRoofWaterGun* fnCarAddRoofWaterGun = (CarAddRoofWaterGun*)0x0041fd50;

typedef void(__fastcall CarAddRoofAntenna)(Car* car);
static CarAddRoofAntenna* fnCarAddRoofAntenna = (CarAddRoofAntenna*)0x00425fd0;

typedef GameObject* (__fastcall SpawnObject)(S33* s33, undefined edx, OBJECT_TYPE type, int x, int y, int z, short rot);
static SpawnObject* fnSpawnObject = (SpawnObject*)0x004852e0;

typedef void(__fastcall SetNPCWeapon)(Ped* ped, DWORD unk, WEAPON_INDEX weapon);
static SetNPCWeapon* fnSetNPCWeapon = (SetNPCWeapon*)0x0043d830;

// void __fastcall FindMaxZForLocation(void *param_1,undefined4 edx,int *outZ,SCR_f x,SCR_f y)
typedef void (__fastcall FindMaxZForLocation)(void* ptrToMapRelatedStruct, DWORD edx, SCR_f* outZ, SCR_f x, SCR_f y);
static FindMaxZForLocation* fnFindMaxZForLocationRaw = (FindMaxZForLocation*)0x0046a420;
#define fnFindMaxZForLocation(x, y, z) fnFindMaxZForLocationRaw(ByPtr(ptrToMapRelatedStruct), 0, z, x, y);

// int __thiscall FUN_00466990(void *ptrToMapRelatedStruct,int x,int y,int *outZ)
typedef void (__fastcall FindMaxZForTile)(void* ptrToMapRelatedStruct, DWORD edx, int x, int y, int* outZ);
static FindMaxZForTile* fnFindMaxZForTileRaw = (FindMaxZForTile*)0x00466990;
#define fnFindMaxZForTile(x, y, z) fnFindMaxZForTileRaw(ByPtr(ptrToMapRelatedStruct), 0, x, y, z);

// SCR_f * __fastcall WorldCoordinateToScreenCoord(SCR_f* axisValue, undefined edx, SCR_f* outVal, int eq_0x6666)
typedef void(__fastcall WorldCoordinateToScreenCoord)(SCR_f* axisValue, undefined edx, SCR_f* outVal, int *eq_0x6666);
static WorldCoordinateToScreenCoord* fnWorldCoordinateToScreenCoordRaw = (WorldCoordinateToScreenCoord*)0x00401b60;

// void __fastcall SetPedTeleportTarget(Ped *this,SCR_f x,SCR_f y)
typedef void(__fastcall SetPedTeleportTarget)(Ped* ped, DWORD edx, SCR_f x, SCR_f y);
static SetPedTeleportTarget* fnSetPedTeleportTarget = (SetPedTeleportTarget*)0x00435c80;

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

// 004cc100
// void DrawGTAText(WCHAR *str,SCR_f x,SCR_f y,int param_4,SCR_f scale,S4_ENUM1 *param_6,int param_7, SPRITE_INVISIBILITY spriteInvisibility, SCR_f param_9)
typedef void(DrawGTATextRaw)(WCHAR* str, SCR_f x, SCR_f y, int param_4, SCR_f scale, S4_ENUM1* param_6, int param_7, SPRITE_INVISIBILITY spriteInvisibility, SCR_f param_9);
static DrawGTATextRaw* fnDrawGTATextRaw = (DrawGTATextRaw*)0x004cc100;

// doesnt seem to make any effect
// int SetGamma(int param_1)
typedef int(SetGamma)(int param_1);
static SetGamma* fnSetGamma = (SetGamma*)0x004cb930;

void fnShowCustomTextMessage(WCHAR* message);
Roof* getCarRoofWithSpriteIfExists(Roof* startroof, short spritetype);
Roof* getCarLastRoof(Roof* startroof);
Car* fnGetCarByID(int id);
Ped* FindTheNearestPed(Ped* basePed);
Car* FindTheNearestCar(Ped* basePed);
SCR_f FloatEncode(double x);
double FloatDecode(SCR_f x);
SCR_f* GetPointInADistance(SCR_f baseX, SCR_f baseY, short rotation, SCR_f distance);
POINT ConvertGameWorldCoordinateToScreen(SCR_f gameX, SCR_f gameY);
bool IsPointSafe(SCR_f x, SCR_f y, SCR_f z);

#endif // !GTA_H