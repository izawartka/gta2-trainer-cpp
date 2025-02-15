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
const DWORD pAfterDebugFlags = (DWORD)0x00451f28;
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
static DWORD ptrToMenu = 0x005ec070;
static DWORD ptrToS15 = 0x006644bc;

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

//Car* __fastcall SpawnCarAdvanced(TrafficManager* trafficMngr, int edx, int x, int y, int z, int rot, CAR_MODEL4 model, int scale)
typedef Car* (__fastcall SpawnCarAdvanced)(TrafficManager* trafficMngr, DWORD edx, int x, int y, int z, int rot, CAR_MODEL4 model, int scale);
static SpawnCarAdvanced* fnSpawnCarAdvanced = (SpawnCarAdvanced*)0x00426ac0;

// void __thiscall PutPedInCarRelated(Ped *this,Car *car,int param_3)
typedef void(__fastcall PutPedInCarRelated)(Ped* ped, DWORD edx, Car* car);
static PutPedInCarRelated* fnPutPedInCarRelated = (PutPedInCarRelated*)0x00436070;

// Ped * CreatePed(void)
typedef Ped* (CreatePed)(void);
static CreatePed* fnCreatePed = (CreatePed*)0x0043df60;

// void __thiscall CreatePed2(void *this,Ped *param_1_00)
// ptr = *0x006644b8
typedef void(__fastcall CreatePed2)(void* ptr, DWORD edx, Ped* ped);
static CreatePed2* fnCreatePed2 = (CreatePed2*)0x00476d20;

// void __thiscall CarMakeDriveable1(Car *this,int param_1_00,undefined4 param_3)
typedef void(__fastcall CarMakeDriveable1)(Car* car, DWORD edx, int param_2);
static CarMakeDriveable1* fnCarMakeDriveable1 = (CarMakeDriveable1*)0x00421560;

// void __fastcall CarMakeDriveable2(Car *car)
typedef void(__fastcall CarMakeDriveable2)(Car* car, DWORD edx);
static CarMakeDriveable2* fnCarMakeDriveable2 = (CarMakeDriveable2*)0x00421510;

// void __thiscall CarMakeDriveable3(CarManager4_S1 *this,Car *car)
typedef void(__fastcall CarMakeDriveable3)(CarManager4_S1* carManager, DWORD edx, Car* car);
static CarMakeDriveable3* fnCarMakeDriveable3 = (CarMakeDriveable3*)0x0042a9d0;

// void __fastcall CarMakeDriveable4(Car *car)
typedef void(__fastcall CarMakeDriveable4)(Car* car, DWORD edx);
static CarMakeDriveable4* fnCarMakeDriveable4 = (CarMakeDriveable4*)0x00425dd0;

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

// void __fastcall FixCarDamage(Car *car)
typedef void(__fastcall FixCarDamage)(Car* car, DWORD edx);
static FixCarDamage* fnFixCarDamage = (FixCarDamage*)0x00425f20;

// void __fastcall ExtinguishCar(Car *car)
// also set car->fireState to 0 for full extinguish
typedef void(__fastcall ExtinguishCar)(Car* car, DWORD edx);
static ExtinguishCar* fnExtinguishCar = (ExtinguishCar*)0x004bf070;

// void __fastcall FixCarBrokenEngine(Car *car)
// allows to run the engine even after the car exploded
typedef void(__fastcall FixCarBrokenEngine)(Car* car, DWORD edx);
static FixCarBrokenEngine* fnFixCarBrokenEngine = (FixCarBrokenEngine*)0x00421570;

// void __fastcall CarPutDummyDriverIn(Car *car)
typedef void(__fastcall CarPutDummyDriverIn)(Car* car, DWORD edx);
static CarPutDummyDriverIn* fnCarPutDummyDriverIn = (CarPutDummyDriverIn*)0x00423510;

// void __fastcall CarMakeDummy(Car *car)
typedef void(__fastcall CarMakeDummy)(Car* car, DWORD edx);
static CarMakeDummy* fnCarMakeDummy = (CarMakeDummy*)0x004279e0;

// void __thiscall PedGroupCreate(Ped *this,byte membersCount)
typedef void(__fastcall PedGroupCreate)(Ped* ped, DWORD edx, byte membersCount);
static PedGroupCreate* fnPedGroupCreate = (PedGroupCreate*)0x00440350;

// void __fastcall PedGroupChangeLeader(Ped *ped1,uint eq0,Ped *ped2)
typedef void(__fastcall PedGroupChangeLeader)(Ped* newLeader, DWORD edx, Ped* oldLeader);
static PedGroupChangeLeader* fnPedGroupChangeLeader = (PedGroupChangeLeader*)0x00435490;

// void __fastcall PedGroupAddPed(PedGroup *group,uint param_2,Ped *ped)
typedef void(__fastcall PedGroupAddPed)(PedGroup* group, DWORD edx, Ped* ped);
static PedGroupAddPed* fnPedGroupAddPed = (PedGroupAddPed*)0x00404c90;

// void __fastcall PedSetObjective(Ped *this,int edx,PED_OBJECTIVE objective,ushort timer,undefined param_5)
typedef void(__fastcall PedSetObjective)(Ped* ped, DWORD edx, PED_OBJECTIVE objective, ushort timer);
static PedSetObjective* fnPedSetObjective = (PedSetObjective*)0x0043bbc0;

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
#define fnDoTeleport(p, xPos, yPos) \
	p->ph2.cameraPos.x = FloatEncode(xPos); \
	p->ph2.cameraPos.y = FloatEncode(yPos); \
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

// 0046bc70
// void MatrixTransform3Advanced(SCR_f *x,SCR_f *y,SCR_f *z,float *outFloatArr)
typedef void(MatrixTransform3Advanced)(SCR_f* x, SCR_f* y, SCR_f* z, float* outFloatArr);
static MatrixTransform3Advanced* fnMatrixTransform3Advanced = (MatrixTransform3Advanced*)0x0046bc70;

// doesnt seem to make any effect
// int SetGamma(int param_1)
typedef int(SetGamma)(int param_1);
static SetGamma* fnSetGamma = (SetGamma*)0x004cb930;

// 004a5780
// uint __thiscall GivePowerUp(Player *this,POWERUP_TYPE type)
typedef uint(__fastcall GivePowerUp)(Player* player, DWORD edx, POWERUP_TYPE type);
static GivePowerUp* fnGivePowerUp = (GivePowerUp*)0x004a5780;

// 0047ef40
// void __thiscall SaveGame(S15_script *this,char *saveFileName)
typedef void(__fastcall SaveGame)(S15_script* s15, DWORD edx, char* saveFileName);
static SaveGame* fnSaveGame = (SaveGame*)0x0047ef40;

void fnShowCustomTextMessage(WCHAR* message);
Roof* getCarRoofWithSpriteIfExists(Roof* startroof, short spritetype);
Roof* getCarLastRoof(Roof* startroof);
Car* fnGetCarByID(int id);
Ped* FindTheNearestPed(Ped* basePed);
Car* FindTheNearestCar(SCR_f x, SCR_f y, SCR_f z);
Car* FindTheNearestCar(Ped* basePed);
SCR_f FloatEncode(double x);
double FloatDecode(SCR_f x);
SCR_f* GetPointInADistance(SCR_f baseX, SCR_f baseY, short rotation, SCR_f distance);
POINT ConvertGameWorldCoordinateToScreen(SCR_f gameX, SCR_f gameY);
bool IsPointSafe(SCR_f x, SCR_f y, SCR_f z);
void ClampPointToSafe(SCR_f &x, SCR_f &y);
void ClampPointToSafe(SCR_f &x, SCR_f &y, SCR_f &z);
void ReplaceCode(DWORD* address, BYTE* newCode, int length);

#endif // !GTA_H