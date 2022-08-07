// MainWindow.cpp : implementation file
//

#include "pch.h"
#include "gta2dll.h"
#include "MainWindow.h"
#include "afxdialogex.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <iterator>
#include <map>
#include <cfenv>
#include <ddraw.h>
#include <d3d9.h>

#include <detours.h>
#pragma comment(lib, "detours.lib")


// MainWindow dialog
BOOL DetourFunc(const DWORD originalFn, DWORD hookFn, size_t copyBytes = 5);

MainWindow* mainWnd = nullptr;

BOOL DetourFunc(const DWORD originalFn, DWORD hookFn, size_t copyBytes) {
	DWORD OldProtection = { 0 };
	BOOL success = VirtualProtectEx(GetCurrentProcess(), (LPVOID)hookFn, copyBytes, PAGE_EXECUTE_READWRITE, &OldProtection);
	if (!success) {
		DWORD error = GetLastError();
		return 0;
	}

	size_t i;

	// memcpy(hookFn, originalFn, copyBytes);
	for (i = 0; i < copyBytes; i++) {
		*(BYTE*)((LPBYTE)hookFn + i + 1) = *(BYTE*)((LPBYTE)originalFn + i);
	}

	success = VirtualProtectEx(GetCurrentProcess(), (LPVOID)originalFn, copyBytes, PAGE_EXECUTE_READWRITE, &OldProtection);
	if (!success) {
		DWORD error = GetLastError();
		return 0;
	}

	Game* pGame = (Game*)*(DWORD*)ptrToGame;

	//if (pGame && pGame->gameStatus)
	{
		*(BYTE*)((LPBYTE)originalFn) = 0xE9; //JMP FAR
		DWORD offset = (((DWORD)hookFn) - ((DWORD)originalFn + 5)); //Offset math.
		*(DWORD*)((LPBYTE)originalFn + 1) = offset;

		for (i = 5; i < copyBytes; i++) {
			*(BYTE*)((LPBYTE)originalFn + i) = 0x90; //JMP FAR
		}
	}

	return 1;
}

static __declspec(naked) void gameTick(void) {
	// this will be replaced by original 5 bytes
	__asm {
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
		NOP
	}

	OutputDebugStringA("gameTick\n");
	mainWnd->OnGTAGameTick((Game*)*(DWORD*)ptrToGame);

	__asm {
		MOV EAX, pGameTick
		add eax, 5
		JMP EAX
	}

}

IMPLEMENT_DYNAMIC(MainWindow, CDialogEx)

MainWindow::MainWindow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	mainWnd = this;

	Game* pGame = (Game*)*(DWORD*)ptrToGame;

	DetourFunc(pGameTick, (DWORD)gameTick);
}

MainWindow::~MainWindow()
{

}

void MainWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_log);
	DDX_Control(pDX, IDC_PEDX, m_pedX);
	DDX_Control(pDX, IDC_PEDY, m_pedY);
	DDX_Control(pDX, IDC_PEDZ, m_pedZ);
	DDX_Control(pDX, IDC_PEDROT, m_pedRot);
	DDX_Control(pDX, IDC_PEDSAMMO, m_pedSAmmo);
	DDX_Control(pDX, IDC_PEDSTYPE, m_pedSType);
	DDX_Control(pDX, IDC_PEDSTIME, m_pedSTime);
	DDX_Control(pDX, IDC_STARCOUNTER, m_pedCopLevel);
	DDX_Control(pDX, IDC_CARDAMAGE, m_carDamage);
	DDX_Control(pDX, IDC_CARID, m_carID);
	DDX_Control(pDX, IDC_GANG1V, m_gangRespect[0]);
	DDX_Control(pDX, IDC_GANG2V, m_gangRespect[1]);
	DDX_Control(pDX, IDC_GANG3V, m_gangRespect[2]);
	DDX_Control(pDX, IDC_CARVEL, m_carVelocity);
	DDX_Control(pDX, IDC_EMBCUR, m_carEmblem);
	DDX_Control(pDX, IDC_EMBPOS, m_carEmblemPos);
	DDX_Control(pDX, IDC_CARCOLV, m_carColor);
	DDX_Control(pDX, IDC_CARVIS, m_carVisualData);
	DDX_Control(pDX, IDC_PEDHEALTH, m_pedHealth);
	DDX_Control(pDX, IDC_PEDARMOR, m_pedArmor);
	DDX_Control(pDX, IDC_PEDMONEY, m_pedMoney);
	DDX_Control(pDX, IDC_PEDCLOTHV, m_pedClothes);
	DDX_Control(pDX, IDC_PEDSHAPEV, m_pedShape);
	DDX_Control(pDX, IDC_BIGTEXTTEXT, m_BigText);
	DDX_Control(pDX, IDC_SPRUN, m_globalPedSpeeds[0]);
	DDX_Control(pDX, IDC_SPWLK, m_globalPedSpeeds[1]);
	DDX_Control(pDX, IDC_SPSTD, m_globalPedSpeeds[2]);
}


BEGIN_MESSAGE_MAP(MainWindow, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &MainWindow::OnBnClickedExit)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_COMMAND(ID_COMMANDS_HELLO, &MainWindow::OnCommandsHello)
	ON_COMMAND(ID_COMMANDS_HIJACKATRAIN, &MainWindow::HijackTrain)
	ON_COMMAND(IDC_MOUSECTRL, &MainWindow::MouseControl)
	ON_COMMAND(ID_SPAWNCAR_TANK, &MainWindow::OnSpawncarTank)
	ON_WM_HOTKEY()
	ON_COMMAND_RANGE(35000, 35000 + 86, &OnSpawnCarClick)
	ON_COMMAND_RANGE(45000, 45000 + 15, &OnGetWeaponClick)
	ON_COMMAND_RANGE(75000, 75000 + 15, &OnGetCarWeaponClick)
	ON_COMMAND_RANGE(55000, 55000 + 62, &OnPlayVocalClick)
	ON_COMMAND_RANGE(65000, 65000 + 256, &OnNativeCheatClick)
	ON_COMMAND(ID_SPAWNCAR_GUNJEEP, &MainWindow::OnSpawncarGunjeep)
	ON_BN_CLICKED(IDC_CARENGINEOFF, &MainWindow::CarEngineOff)
	ON_BN_CLICKED(IDC_UNLMAMMO, &MainWindow::GiveUnlimitedAmmo)
	ON_COMMAND_RANGE(3011, 3017, &SetStars)
	ON_BN_CLICKED(IDC_CARFIX, &MainWindow::FixCar)
	ON_BN_CLICKED(IDC_CARVISFIX, &MainWindow::VisFixCar)
	ON_BN_CLICKED(IDC_CARVISBRK, &MainWindow::VisBreakCar)
	ON_BN_CLICKED(IDC_LOCKCOPLEVEL, &MainWindow::LockStars)
	ON_BN_CLICKED(IDC_LOCKCARDAMAGE, &MainWindow::LockCarDamage)
	ON_BN_CLICKED(IDC_PEDS0TIME, &MainWindow::NoReloads)
	ON_BN_CLICKED(IDC_CARLASTTP, &MainWindow::TpToLastCar)
	ON_BN_CLICKED(IDC_CARPINFO, &MainWindow::PrintCarInfo)
	ON_BN_CLICKED(IDC_PEDIMMORT, &MainWindow::PlayerImmortal)
	ON_BN_CLICKED(ID_TPALLPEDS, &MainWindow::TeleportAllPeds)
	ON_COMMAND_RANGE(3040, 3048, &GangRespect)
	ON_COMMAND_RANGE(3075, 3078, &ToggleDoor)
	ON_BN_CLICKED(IDC_FREESHOP, &MainWindow::FreeShopping)
	ON_BN_CLICKED(IDC_BEAHUMAN, &MainWindow::WatchPeds)
	ON_BN_CLICKED(IDC_TPPLAYER, &MainWindow::TeleportPlayer)
	ON_BN_CLICKED(IDC_EMBP, &MainWindow::CarEmblemPlus)
	ON_BN_CLICKED(IDC_EMBM, &MainWindow::CarEmblemMinus)
	ON_BN_CLICKED(IDC_CARCOLP, &MainWindow::CarColorPlus)
	ON_BN_CLICKED(IDC_CARCOLM, &MainWindow::CarColorMinus)
	ON_BN_CLICKED(IDC_CARCOLR, &MainWindow::CarColorReset)
	ON_BN_CLICKED(IDC_CARTRCOLR, &MainWindow::SyncTrailerColor)
	ON_BN_CLICKED(IDC_GOSLOW, &MainWindow::GoSlow)
	ON_BN_CLICKED(IDC_PEDHAMSET, &MainWindow::SetHealthArmorMoney)
	ON_BN_CLICKED(IDC_PEDCLOTHP, &MainWindow::PedClothesPlus)
	ON_BN_CLICKED(IDC_PEDCLOTHM, &MainWindow::PedClothesMinus)
	ON_BN_CLICKED(IDC_PEDSHAPEP, &MainWindow::PedShapePlus)
	ON_BN_CLICKED(IDC_PEDSHAPEM, &MainWindow::PedShapeMinus)
	ON_BN_CLICKED(IDC_PEDSHAPECLOTHR, &MainWindow::PedShapeClothesReset)
	ON_BN_CLICKED(IDC_BIGTEXTSHOW, &MainWindow::ShowBigText)
	ON_BN_CLICKED(IDC_SPSET, &MainWindow::SetGlobalPedSpeeds)
END_MESSAGE_MAP()

// Close GTA2 on Trainer exit
void MainWindow::OnBnClickedExit()
{
	if (m_gtaWindow) {
		::DestroyWindow(m_gtaWindow);
		::exit(0);
	}
}

// Prepare things
int MainWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_gtaWindow = NULL;
	firstPaint = true;
	frames = 0;

	SetTimer(TIMER_CAPTURE_MOUSE, 1000 / 60, NULL);
	SetTimer(TIMER_PED_INFO, 1000 / 60, NULL);

	// Register HotKeys

	RegisterHotKey(
		GetSafeHwnd(),
		1,
		MOD_ALT | MOD_NOREPEAT,
		0x54); //ALT+T

	RegisterHotKey(
		GetSafeHwnd(),
		1,
		MOD_ALT | MOD_NOREPEAT,
		0x47); //ALT+G

	RegisterHotKey(
		GetSafeHwnd(),
		1,
		MOD_ALT | MOD_NOREPEAT,
		0x4a); //ALT+J

	RegisterHotKey(
		GetSafeHwnd(),
		1,
		MOD_ALT | MOD_NOREPEAT,
		0x50); //ALT+P

	RegisterHotKey(
		GetSafeHwnd(),
		1,
		MOD_ALT | MOD_NOREPEAT,
		0x44); //ALT+D

	RegisterHotKey(
		GetSafeHwnd(),
		1,
		MOD_ALT | MOD_NOREPEAT,
		0x4e); //ALT+N
	RegisterHotKey(
		GetSafeHwnd(),
		1,
		MOD_ALT | MOD_NOREPEAT,
		0x48); //ALT+H

	CMenu *menu = GetMenu();
	
	// Prepare cars menu

	CMenu* nMenu = new CMenu();
	nMenu->CreatePopupMenu();	

	std::map<std::wstring, DWORD> cars;

	cars.insert(std::pair<std::wstring, DWORD>(L"ALFA", 0));
	cars.insert(std::pair<std::wstring, DWORD>(L"ALLARD", 1));
	cars.insert(std::pair<std::wstring, DWORD>(L"AMDB4", 2));
	cars.insert(std::pair<std::wstring, DWORD>(L"APC", 3));
	cars.insert(std::pair<std::wstring, DWORD>(L"BANKVAN", 4));
	cars.insert(std::pair<std::wstring, DWORD>(L"BMW", 5));
	cars.insert(std::pair<std::wstring, DWORD>(L"BOXCAR", 6));
	cars.insert(std::pair<std::wstring, DWORD>(L"BOXTRUCK", 7));
	cars.insert(std::pair<std::wstring, DWORD>(L"BUG", 8));
	cars.insert(std::pair<std::wstring, DWORD>(L"BUICK", 10));
	cars.insert(std::pair<std::wstring, DWORD>(L"BUS", 11));
	cars.insert(std::pair<std::wstring, DWORD>(L"COPCAR", 12));
	cars.insert(std::pair<std::wstring, DWORD>(L"DART", 13));
	cars.insert(std::pair<std::wstring, DWORD>(L"EDSEL", 14));
	cars.insert(std::pair<std::wstring, DWORD>(L"FIAT", 16));
	cars.insert(std::pair<std::wstring, DWORD>(L"FIRETRUK", 17));
	cars.insert(std::pair<std::wstring, DWORD>(L"GRAHAM", 18));
	cars.insert(std::pair<std::wstring, DWORD>(L"GT24640", 19));
	cars.insert(std::pair<std::wstring, DWORD>(L"GTRUCK", 21));
	cars.insert(std::pair<std::wstring, DWORD>(L"GUNJEEP", 22));
	cars.insert(std::pair<std::wstring, DWORD>(L"HOTDOG", 23));
	cars.insert(std::pair<std::wstring, DWORD>(L"HOTDOG_D1", 24));
	cars.insert(std::pair<std::wstring, DWORD>(L"HOTDOG_D2", 25));
	cars.insert(std::pair<std::wstring, DWORD>(L"HOTDOG_D3", 26));
	cars.insert(std::pair<std::wstring, DWORD>(L"ICECREAM", 27));
	cars.insert(std::pair<std::wstring, DWORD>(L"ISETLIMO", 28));
	cars.insert(std::pair<std::wstring, DWORD>(L"ISETTA", 29));
	cars.insert(std::pair<std::wstring, DWORD>(L"JEEP", 30));
	cars.insert(std::pair<std::wstring, DWORD>(L"JEFFREY", 31));
	cars.insert(std::pair<std::wstring, DWORD>(L"LIMO", 32));
	cars.insert(std::pair<std::wstring, DWORD>(L"LIMO2", 33));
	cars.insert(std::pair<std::wstring, DWORD>(L"MEDICAR", 34));
	cars.insert(std::pair<std::wstring, DWORD>(L"MERC", 35));
	cars.insert(std::pair<std::wstring, DWORD>(L"MESSER", 36));
	cars.insert(std::pair<std::wstring, DWORD>(L"MIURA", 37));
	cars.insert(std::pair<std::wstring, DWORD>(L"MONSTER", 38));
	cars.insert(std::pair<std::wstring, DWORD>(L"MORGAN", 39));
	cars.insert(std::pair<std::wstring, DWORD>(L"MORRIS", 40));
	cars.insert(std::pair<std::wstring, DWORD>(L"PICKUP", 41));
	cars.insert(std::pair<std::wstring, DWORD>(L"RTYPE", 42));
	cars.insert(std::pair<std::wstring, DWORD>(L"SPIDER", 44));
	cars.insert(std::pair<std::wstring, DWORD>(L"SPRITE", 45));
	cars.insert(std::pair<std::wstring, DWORD>(L"STINGRAY", 46));
	cars.insert(std::pair<std::wstring, DWORD>(L"STRATOS", 47));
	cars.insert(std::pair<std::wstring, DWORD>(L"STRATOSB", 48));
	cars.insert(std::pair<std::wstring, DWORD>(L"STRIPETB", 49));
	cars.insert(std::pair<std::wstring, DWORD>(L"STYPE", 50));
	cars.insert(std::pair<std::wstring, DWORD>(L"STYPECAB", 51));
	cars.insert(std::pair<std::wstring, DWORD>(L"SWATVAN", 52));
	cars.insert(std::pair<std::wstring, DWORD>(L"T2000GT", 53));
	cars.insert(std::pair<std::wstring, DWORD>(L"TANK", 54));
	cars.insert(std::pair<std::wstring, DWORD>(L"TANKER", 55));
	cars.insert(std::pair<std::wstring, DWORD>(L"TAXI", 56));
	cars.insert(std::pair<std::wstring, DWORD>(L"TBIRD", 57));
	cars.insert(std::pair<std::wstring, DWORD>(L"TOWTRUCK", 58));
	cars.insert(std::pair<std::wstring, DWORD>(L"TRANCEAM", 62));
	cars.insert(std::pair<std::wstring, DWORD>(L"TRUKCAB1", 63));
	cars.insert(std::pair<std::wstring, DWORD>(L"TRUKCAB2", 64));
	cars.insert(std::pair<std::wstring, DWORD>(L"TRUKCONT", 65));
	cars.insert(std::pair<std::wstring, DWORD>(L"TRUKTRNS", 66));
	cars.insert(std::pair<std::wstring, DWORD>(L"TVVAN", 67));
	cars.insert(std::pair<std::wstring, DWORD>(L"VAN", 68));
	cars.insert(std::pair<std::wstring, DWORD>(L"VESPA", 69));
	cars.insert(std::pair<std::wstring, DWORD>(L"VTYPE", 70));
	cars.insert(std::pair<std::wstring, DWORD>(L"WBTWIN", 71));
	cars.insert(std::pair<std::wstring, DWORD>(L"WRECK0", 72));
	cars.insert(std::pair<std::wstring, DWORD>(L"WRECK1", 73));
	cars.insert(std::pair<std::wstring, DWORD>(L"WRECK2", 74));
	cars.insert(std::pair<std::wstring, DWORD>(L"WRECK3", 75));
	cars.insert(std::pair<std::wstring, DWORD>(L"WRECK4", 76));
	cars.insert(std::pair<std::wstring, DWORD>(L"WRECK5", 77));
	cars.insert(std::pair<std::wstring, DWORD>(L"WRECK6", 78));
	cars.insert(std::pair<std::wstring, DWORD>(L"WRECK7", 79));
	cars.insert(std::pair<std::wstring, DWORD>(L"WRECK8", 80));
	cars.insert(std::pair<std::wstring, DWORD>(L"WRECK9", 81));
	cars.insert(std::pair<std::wstring, DWORD>(L"XK120", 82));
	cars.insert(std::pair<std::wstring, DWORD>(L"ZCX5", 83));
	cars.insert(std::pair<std::wstring, DWORD>(L"EDSELFBI", 84));
	cars.insert(std::pair<std::wstring, DWORD>(L"HOTDOG_D4", 85));
	cars.insert(std::pair<std::wstring, DWORD>(L"KRSNABUS", 86));

	std::map<std::wstring, DWORD>::iterator itr;
	for (itr = cars.begin(); itr != cars.end(); ++itr) {
		nMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 35000), itr->first.c_str());
	}

	menu->AppendMenuW(MF_POPUP, (UINT_PTR)nMenu->m_hMenu, L"Spawn car");

	// Prepare weapons menu

	CMenu* wMenu = new CMenu();
	wMenu->CreatePopupMenu();

	std::map<std::wstring, DWORD> weapons;

	weapons.insert(std::pair<std::wstring, DWORD>(L"Pistol", 0));
	weapons.insert(std::pair<std::wstring, DWORD>(L"S-Uzi", 1));
	weapons.insert(std::pair<std::wstring, DWORD>(L"Rocket Launcher", 2));
	weapons.insert(std::pair<std::wstring, DWORD>(L"ElectroGun", 3));
	weapons.insert(std::pair<std::wstring, DWORD>(L"Molotov Coctail", 4));
	weapons.insert(std::pair<std::wstring, DWORD>(L"Grenade", 5));
	weapons.insert(std::pair<std::wstring, DWORD>(L"Shotgun", 6));
	weapons.insert(std::pair<std::wstring, DWORD>(L"ElectroBaton", 7));
	weapons.insert(std::pair<std::wstring, DWORD>(L"Flamethrower", 8));
	weapons.insert(std::pair<std::wstring, DWORD>(L"Silenced S-Uzi", 9));
	weapons.insert(std::pair<std::wstring, DWORD>(L"Dual Pistol", 10));
	weapons.insert(std::pair<std::wstring, DWORD>(L"Letter L", 11));
	weapons.insert(std::pair<std::wstring, DWORD>(L"Letter M", 12));
	weapons.insert(std::pair<std::wstring, DWORD>(L"Letter N", 13));
	weapons.insert(std::pair<std::wstring, DWORD>(L"Letter O", 14));

	for (itr = weapons.begin(); itr != weapons.end(); ++itr) {
		wMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 45000), itr->first.c_str());
	}

	menu->AppendMenuW(MF_POPUP, (UINT_PTR)wMenu->m_hMenu, L"Get weapon");

	// Prepare car weapons menu

	CMenu* cwMenu = new CMenu();
	cwMenu->CreatePopupMenu();

	std::map<std::wstring, DWORD> carweapons;

	carweapons.insert(std::pair<std::wstring, DWORD>(L"Vehicle Bomb", 0));
	carweapons.insert(std::pair<std::wstring, DWORD>(L"Vehicle Oil Slick", 1));
	carweapons.insert(std::pair<std::wstring, DWORD>(L"Vehicle Mine", 2));
	carweapons.insert(std::pair<std::wstring, DWORD>(L"Vehicle Machine Gun", 3));
	carweapons.insert(std::pair<std::wstring, DWORD>(L"Tank Cannon", 4));
	carweapons.insert(std::pair<std::wstring, DWORD>(L"Water Cannon", 5));
	carweapons.insert(std::pair<std::wstring, DWORD>(L"Vehicle Flamethrower", 6));
	carweapons.insert(std::pair<std::wstring, DWORD>(L"Jeep Turret", 7));
	carweapons.insert(std::pair<std::wstring, DWORD>(L"Instant Vehicle Bomb", 8));
	carweapons.insert(std::pair<std::wstring, DWORD>(L"Letter J", 9));
	carweapons.insert(std::pair<std::wstring, DWORD>(L"Letter K", 10));
	carweapons.insert(std::pair<std::wstring, DWORD>(L"Letter L", 11));
	carweapons.insert(std::pair<std::wstring, DWORD>(L"Letter M", 12));

	for (itr = carweapons.begin(); itr != carweapons.end(); ++itr) {
		cwMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 75000), itr->first.c_str());
	}

	menu->AppendMenuW(MF_POPUP, (UINT_PTR)cwMenu->m_hMenu, L"Get car weapon");

	// Prepare vocals menu

	CMenu* vMenu = new CMenu();
	vMenu->CreatePopupMenu();

	std::map<std::wstring, DWORD> vocals;

	vocals.insert(std::pair<std::wstring, DWORD>(L"INSANE STUNT BONUS", 1));
	vocals.insert(std::pair<std::wstring, DWORD>(L"GRAND THEFT AUTO", 2));
	vocals.insert(std::pair<std::wstring, DWORD>(L"WIPEOUT", 3));
	vocals.insert(std::pair<std::wstring, DWORD>(L"EXPEDITIOUS EXECUTION", 4));
	vocals.insert(std::pair<std::wstring, DWORD>(L"GENOCIDE", 5));
	vocals.insert(std::pair<std::wstring, DWORD>(L"COP KILLA", 6));
	vocals.insert(std::pair<std::wstring, DWORD>(L"CAR JACKA", 7));
	vocals.insert(std::pair<std::wstring, DWORD>(L"ELVIS HAS LEFT THE BUILDING", 8));
	vocals.insert(std::pair<std::wstring, DWORD>(L"ACCURACY BONUS", 9));
	vocals.insert(std::pair<std::wstring, DWORD>(L"BACK TO FRONT BONUS", 10));
	vocals.insert(std::pair<std::wstring, DWORD>(L"MEDICAL EMERGENCY", 11));
	vocals.insert(std::pair<std::wstring, DWORD>(L"KILL FRENZY", 12));
	vocals.insert(std::pair<std::wstring, DWORD>(L"BUSTED", 17));
	vocals.insert(std::pair<std::wstring, DWORD>(L"FRENZY FAILED", 18));
	vocals.insert(std::pair<std::wstring, DWORD>(L"FRENZY PASSED", 19));
	vocals.insert(std::pair<std::wstring, DWORD>(L"FRYING TONIGHT", 20));
	vocals.insert(std::pair<std::wstring, DWORD>(L"GAME OVER", 21));
	vocals.insert(std::pair<std::wstring, DWORD>(L"JOB COMPLETE", 22));
	vocals.insert(std::pair<std::wstring, DWORD>(L"JOB FAILED", 23));
	vocals.insert(std::pair<std::wstring, DWORD>(L"AND REMEMBER, RESPECT IS EVERYTHING", 24));
	vocals.insert(std::pair<std::wstring, DWORD>(L"SHOCKING", 25));
	vocals.insert(std::pair<std::wstring, DWORD>(L"MMM... SOMETHIN'S COOKIN", 26));
	vocals.insert(std::pair<std::wstring, DWORD>(L"TIME'S UP, PAL", 27));
	vocals.insert(std::pair<std::wstring, DWORD>(L"TOASTED", 28));
	vocals.insert(std::pair<std::wstring, DWORD>(L"WASTED", 29));
	vocals.insert(std::pair<std::wstring, DWORD>(L"BOMB ARMED", 30));
	vocals.insert(std::pair<std::wstring, DWORD>(L"LAUGH6", 31));
	vocals.insert(std::pair<std::wstring, DWORD>(L"LAUGH (random)", 32));
	vocals.insert(std::pair<std::wstring, DWORD>(L"RACE OVER", 33));
	vocals.insert(std::pair<std::wstring, DWORD>(L"SECOND LAP", 34));
	vocals.insert(std::pair<std::wstring, DWORD>(L"FINAL LAP", 35));
	vocals.insert(std::pair<std::wstring, DWORD>(L"RACE ON", 36));
	vocals.insert(std::pair<std::wstring, DWORD>(L"MULTIPLIER X2", 37));
	vocals.insert(std::pair<std::wstring, DWORD>(L"MULTIPLIER X3", 38));
	vocals.insert(std::pair<std::wstring, DWORD>(L"MULTIPLIER X4", 39));
	vocals.insert(std::pair<std::wstring, DWORD>(L"MULTIPLIER X5", 40));
	vocals.insert(std::pair<std::wstring, DWORD>(L"MULTIPLIER X6", 41));
	vocals.insert(std::pair<std::wstring, DWORD>(L"TIME OUT", 42));
	vocals.insert(std::pair<std::wstring, DWORD>(L"YOUR TIME IS EXTENDED", 43));
	vocals.insert(std::pair<std::wstring, DWORD>(L"TIME'S UP, PAL (duplicate)", 44));
	vocals.insert(std::pair<std::wstring, DWORD>(L"OH SORRY ABOUT THAT... DID THAT HURT?", 45));
	vocals.insert(std::pair<std::wstring, DWORD>(L"NICE WORK", 46));
	vocals.insert(std::pair<std::wstring, DWORD>(L"CHOCTASTIC", 47));
	vocals.insert(std::pair<std::wstring, DWORD>(L"RASPBERRY RIPPLE", 48));
	vocals.insert(std::pair<std::wstring, DWORD>(L"YOU SHOT YOUR LOAD", 49));
	vocals.insert(std::pair<std::wstring, DWORD>(L"OH... DID THAT HURT?", 50));
	vocals.insert(std::pair<std::wstring, DWORD>(L"DEATH TO ICE CREAM VANS", 51));
	vocals.insert(std::pair<std::wstring, DWORD>(L"CRISPY CRITTER", 52));
	vocals.insert(std::pair<std::wstring, DWORD>(L"YOU'RE TOAST, BUDDY", 53));
	vocals.insert(std::pair<std::wstring, DWORD>(L"EAT LEADEN DEATH, PUNK", 54));
	vocals.insert(std::pair<std::wstring, DWORD>(L"THAT'S GONNA HURT", 55));
	vocals.insert(std::pair<std::wstring, DWORD>(L"SORRY ABOUT THAT", 56));
	vocals.insert(std::pair<std::wstring, DWORD>(L"XIN LOI, MY MAN", 57));
	vocals.insert(std::pair<std::wstring, DWORD>(L"DAMN SUNDAY DRIVERS", 58));
	vocals.insert(std::pair<std::wstring, DWORD>(L"SUCK IT AND SEE", 59));
	vocals.insert(std::pair<std::wstring, DWORD>(L"TASTE MY WRATH, ICE-CREAM BOY", 60));
	vocals.insert(std::pair<std::wstring, DWORD>(L"HALLELUJAH! ANOTHER SOUL SAVED", 61));
	vocals.insert(std::pair<std::wstring, DWORD>(L"DAMNATION! NO DONATION, NO SALVATION", 62));
	
	for (itr = vocals.begin(); itr != vocals.end(); ++itr) {
		vMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 55000), itr->first.c_str());
	}

	menu->AppendMenuW(MF_POPUP, (UINT_PTR)vMenu->m_hMenu, L"Play vocal");
	
	// Prepare native cheats menu

	CMenu* ncMenu = new CMenu();
	ncMenu->CreatePopupMenu();

	std::map<std::wstring, DWORD> native;

	native.insert(std::pair<std::wstring, DWORD>(L"Do blood", 0x51));
	native.insert(std::pair<std::wstring, DWORD>(L"Show objects IDs", 0x52));
	native.insert(std::pair<std::wstring, DWORD>(L"Skip traffic lights", 0x53));
	native.insert(std::pair<std::wstring, DWORD>(L"Skip buses", 0x54));
	native.insert(std::pair<std::wstring, DWORD>(L"Show counters", 0x55));
	native.insert(std::pair<std::wstring, DWORD>(L"Skip particles", 0x56));
	//native.insert(std::pair<std::wstring, DWORD>(L"Skip trains", 0x57)); crashes the game;v
	native.insert(std::pair<std::wstring, DWORD>(L"Show input", 0x58));
	native.insert(std::pair<std::wstring, DWORD>(L"Skip right textures", 0x59));
	native.insert(std::pair<std::wstring, DWORD>(L"No traffic", 0x5B));
	native.insert(std::pair<std::wstring, DWORD>(L"No police", 0x5E));
	native.insert(std::pair<std::wstring, DWORD>(L"Skip bottom textures", 0x5F));
	native.insert(std::pair<std::wstring, DWORD>(L"Infinite lives", 0x61));
	native.insert(std::pair<std::wstring, DWORD>(L"No HUD", 0x64));
	native.insert(std::pair<std::wstring, DWORD>(L"Skip left textures", 0x67));
	native.insert(std::pair<std::wstring, DWORD>(L"No peds spawn", 0x69));
	native.insert(std::pair<std::wstring, DWORD>(L"Mini cars", 0x6D));
	native.insert(std::pair<std::wstring, DWORD>(L"No audio", 0x72));
	native.insert(std::pair<std::wstring, DWORD>(L"No slopes textures", 0x78));
	native.insert(std::pair<std::wstring, DWORD>(L"Show FPS", 0x79));
	native.insert(std::pair<std::wstring, DWORD>(L"Show car horn", 0x7F));
	native.insert(std::pair<std::wstring, DWORD>(L"Show drawing info", 0x81));
	native.insert(std::pair<std::wstring, DWORD>(L"Show camera info", 0x82));
	native.insert(std::pair<std::wstring, DWORD>(L"Show vehicle info", 0x85));
	native.insert(std::pair<std::wstring, DWORD>(L"Debug keys", 0x87));
	native.insert(std::pair<std::wstring, DWORD>(L"Insane speed", 0x88));
	native.insert(std::pair<std::wstring, DWORD>(L"Show junctions IDs", 0x89));
	native.insert(std::pair<std::wstring, DWORD>(L"No top textures", 0x8C));
	native.insert(std::pair<std::wstring, DWORD>(L"Show ped info", 0x8D));
	native.insert(std::pair<std::wstring, DWORD>(L"Skip textures", 0x90));
	native.insert(std::pair<std::wstring, DWORD>(L"Show traffic info", 0x95));
	native.insert(std::pair<std::wstring, DWORD>(L"Keep weapons after death", 0x9E));
	native.insert(std::pair<std::wstring, DWORD>(L"Nekkid peds", 0xA0));
	native.insert(std::pair<std::wstring, DWORD>(L"Show peds IDs", 0xA1));
	native.insert(std::pair<std::wstring, DWORD>(L"Show all arrows", 0xB2));

	for (itr = native.begin(); itr != native.end(); ++itr) {
		ncMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 65000), itr->first.c_str());
	}

	ncHMenu = ncMenu->m_hMenu;
	menu->AppendMenuW(MF_POPUP, (UINT_PTR)ncHMenu, L"Native Cheats");

	return 0;
}

void MainWindow::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// If first game paint after launch
	if (firstPaint && m_gtaWindow) {
		firstPaint = false;
		CRect rect, rect2;

		GetWindowRect(&rect);
		::GetWindowRect(m_gtaWindow, &rect2);

		int x = GetSystemMetrics(SM_CXSCREEN) - rect2.Width();

		::MoveWindow(m_gtaWindow, x, 0, rect2.Width(), rect2.Height(), true);
		MoveWindow(0, 0, rect.Width(), rect.Height(), true);

		InvalidateRect(rect);
	}
	else if (!m_gtaWindow) {
		m_gtaWindow = FindWindowA("WinMain", "GTA2");
	}
}

void MainWindow::log(const WCHAR* fmt, ...)
{
	CString tmp;
	m_log.GetWindowTextW(tmp);
	std::wstring logStore(tmp.GetBuffer());
	logStore.append(L"\r\n");
	WCHAR buf[1024];
	va_list args;
	va_start(args, fmt);
	vswprintf(buf, 512, fmt, args);

	logStore.append(buf);
	std::wstring str;
	if (logStore.length() > 16384) {
		str = logStore.substr(logStore.length() - 4096, 4096).c_str();
	}
	else {
		str = logStore;
	}

	m_log.SetWindowTextW(str.c_str());
	DWORD len = str.length();
	m_log.SetSel(len-1, len, false);
}


void MainWindow::OnCommandsHello()
{
	MessageBox(L"Hello", L"GTA 2 DLL");
}


void MainWindow::MouseControl()
{
	captureMouse = !captureMouse;
	if (captureMouse) log(L"Mouse control enabled!");
	else log(L"Mouse control disabled!");
}

void MainWindow::CaptureMouse()
{
	if (*(DWORD*)ptrToPedManager == 0) {
		if (frames++ % 60 == 0) {
			//log(L"Not in a game");
		}
		return;
	}
	Ped* playerPed = fnGetPedByID(1);

	if (!playerPed || playerPed->currentCar) {
		if (frames++ % 60 == 0) {
			//log(L"No player ped is found");
		}
		return;
	}

	POINT p;
	RECT rect;
	GetCursorPos(&p);
	::GetWindowRect(m_gtaWindow, &rect);
	if (p.x < rect.left || p.x > rect.right || p.y < rect.top || p.y > rect.bottom) {
		if (frames++ % 60 == 0) {
			log(L"Cursor is outside of the game window");
		}
		return;
	}

	int nCaptionHeight = ::GetSystemMetrics(SM_CYCAPTION);

	int centerX = rect.left + (rect.right - rect.left) / 2;
	int centerY = rect.top + nCaptionHeight + (rect.bottom - rect.top - nCaptionHeight) / 2;

	int relX = p.x - centerX;
	int relY = p.y - centerY;
	double angle = atan2(relX, relY) * (180.0 / M_PI);
	double nAngle = 0;

	short gtaAngle = 0;
	if (angle >= 0) {
		gtaAngle = (short)(angle * 4.0);
		nAngle = angle + 90;
	}
	else {
		//on top -180, 0 on bottom
		gtaAngle = (short)((angle + 360) * 4.0);
	}

	nAngle = 270 + angle;

	if (frames++ % 60 == 0) {
		//log(L"cursor at %dx%d angle is %f", relX, relY, angle);
	}

	if (playerPed->gameObject) {
		playerPed->gameObject->spriteRotation = gtaAngle;
	}

	BYTE keyboard[256];
	GetKeyboardState(keyboard);

	auto player = fnGetPlayerSlotByIndex(0);

	auto keyUp = player->keyUp;
	auto keyDown = player->keyDown;
	auto keyAttack = player->keyAttack;


	if (keyboard['W'] & 0x80) {
		player->keyUp = 1;
	}
	else {
		player->keyUp = keyUp;
	}

	if (keyboard['S'] & 0x80) {
		player->keyDown = 1;
	}
	else {
		player->keyDown = keyDown;
	}

	if (keyboard[VK_LBUTTON] & 0x80) {
		player->keyAttack = 1;
	}
	else {
		player->keyAttack = keyAttack;
	}
}

void MainWindow::KeepLockedValues()
{
	// If not in game
	if (*(DWORD*)ptrToPedManager == 0) {
		return;
	}

	// Remove currLastCar if its sprite doesn't exist
	if (currLastCar && !currLastCar->sprite)
		currLastCar = 0; //without this the game crashes after some missions and after WCB

	if (currLastCar)
	{
		// Update emblem 
		int carEmblemPos = m_carEmblemPos.GetPos();
		if (currLastCarEmblemID && carEmblemPos != currLastCarEmblemLPos)
		{
			currLastCarEmblem->yOffset = carEmblemPos;
			currLastCarEmblemLPos = carEmblemPos;
		}

		// Lock engine damage
		if (carDamageLocked)
		{
			currLastCar->carDamage = startCarDamage;
		}

		// Lock doors
		for (int i = 0; i < 4; i++)
		{
			if (doorOpen[i])
			{
				currLastCar->carDoor[i].doorState = 2;
			}
		}
	}


	Ped* playerPed = fnGetPedByID(1);

	// Return if no player ped found
	if (!playerPed)
		return;

	// Lock police if enabled
	if (starsLocked)
	{
		playerPed->copValue = startCopValue;
	}

	// Lock reload time if enabled
	if (noReloads && playerPed->selectedWeapon) playerPed->selectedWeapon->timeToReload = 0;

	// Watch peds if enabled
	if (watchPeds)
	{
		//Ped* lastped = fnGetPedByID((int)*nextpedid - 1);

		if (selectedPed && selectedPed->gameObject)
		{
			playerPed->gameObject->sprite->x = selectedPed->gameObject->sprite->x;
			playerPed->gameObject->sprite->y = selectedPed->gameObject->sprite->y;
			playerPed->gameObject->sprite->z = selectedPed->gameObject->sprite->z;
		}
		else
		{
			log(L"Something is wrong with current Ped; choosing the new one...");

			WatchNextPed();
				
		}
	}

	// Return if player not in the car
	if (!playerPed->currentCar)
		return;

	currLastCar = playerPed->currentCar;

	if (currLastCar != currLastCarOld)
	{
		log(L"\"Current / Last car\" changed");

		// Unlock engine damage lock if car changed
		if (carDamageLocked)
		{
			((CButton*)GetDlgItem(IDC_LOCKCARDAMAGE))->SetCheck(false);
			carDamageLocked = false;
			startCarDamage = 0;
			log(L"Player has changed the car; Engine damage unlocked");
		}

		// Reset door open locks if car changed
		for (int i = 0; i < 4; i++)
		{
			doorOpen[i] = false;
		}

		// Detect and prepare emblems if car changed
		m_carEmblemPos.SetRange(-8192, 8192, TRUE);
		currLastCarEmblemID = 0;
		for (int i = 0; i < sizeof(emblemValues)/sizeof(emblemValues[0]); i++)
		{
			currLastCarEmblem = getCarRoofWithSpriteIfExists(currLastCar->roof, emblemValues[i]);
			if (currLastCarEmblem && currLastCarEmblem->sprite->spriteType == 4)
			{
				currLastCarEmblemID = i;
				m_carEmblemPos.SetPos(currLastCarEmblem->yOffset);
				break;
			}
		}
	}

	currLastCarOld = currLastCar;
}

struct SPAWNCAR {
	CAR_MODEL model;
	MainWindow* win;
};

// Car spawning
UINT SpawnCarThread(LPVOID data)
{
	S10* s10 = (S10*)*(DWORD*)0x00672f40;
	SPAWNCAR* info = (SPAWNCAR*)data;
	Ped* playerPed = fnGetPedByID(1);

	// Return if not in the game
	if (*(DWORD*)ptrToPedManager == 0)
		return 0;

	// Return if player ped doesn't exist
	if (!playerPed || !playerPed->gameObject || !playerPed->gameObject->sprite)
		return 0;

	// Return if player is in the car
	if (playerPed->currentCar)
		return 0;

	// Spawn car
	double nAngle = playerPed->gameObject->sprite->rotation / 4.0 + 270.0;
	const double distance = 1;
	Car* car = fnSpawnCar(
		playerPed->gameObject->sprite->x + (int)(cos(nAngle * (M_PI / 180.0)) * distance * 16384.0),
		playerPed->gameObject->sprite->y - (int)(sin(nAngle * (M_PI / 180.0)) * distance * 16384.0),
		playerPed->gameObject->sprite->z,
		180 * 4,
		info->model
	);

	// If everything successed, show label :D
	if (car)
		fnShowBigOnScreenLabel(&s10->ptrToSomeStructRelToBIG_LABEL, 0, (WCHAR*)L"Car is here!", 10);

	delete info;
	return 0;
}

// Create car spawn thread
void MainWindow::WantToSpawnCar()
{
	SPAWNCAR* info = new SPAWNCAR;
	info->win = this;
	info->model = (CAR_MODEL)(wtSpawnCar);
	::CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SpawnCarThread, info, 0, 0);

	wtSpawnCar = -1;
}

// Custom car spawning
void MainWindow::OnSpawnCarClick(UINT nID) {
	wtSpawnCar = (nID - 35000);
}

// Tank spawning
void MainWindow::OnSpawncarTank()
{
	wtSpawnCar = TANK;
}

// Gunjeep spawning
void MainWindow::OnSpawncarGunjeep()
{
	wtSpawnCar = GUNJEEP;
}

void MainWindow::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	//log(L"OnHotKey(%X, %X, %X)", nHotKeyId, nKey1, nKey2);
	switch (nKey2)
	{
	case 0x54:
		OnSpawncarTank();
		break;
	case 0x4a:
		OnSpawncarGunjeep();
		break;
	case 0x50:
		TeleportAllPeds();
		break;
	case 0x44:
		NewFunction();
		break;
	case 0x4e:
		WatchNextPed();
		break;
	case 0x48:
		HijackTrain();
		break;
	default:
		break;
	}

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

void MainWindow::OnGetWeaponClick(UINT nID) {

	Ped* playerPed = fnGetPedByID(1);

	// Return if player ped doesn't exist
	if (!playerPed)
		return;

	UINT ID = nID - 45000;
	playerPed->playerWeapons->weapons[ID]->ammo += 100;
	log(L"Weapon #%d got", nID - 45000);
}

void MainWindow::OnGetCarWeaponClick(UINT nID) {
	
	Ped* playerPed = fnGetPedByID(1);

	// Return if player's car's sprite doesn't exist
	if (!playerPed || !playerPed->currentCar || !playerPed->currentCar->sprite)
		return;

	byte ID = nID - 75000;
	CAR_WEAPON weapon = (CAR_WEAPON)(15 + ID);

	fnCarAddWeapon(weapon, 10, currLastCar);
	log(L"Car weapon #%d got", ID);

	switch (weapon)
	{
		case CAR_WEAP_TANKTURRET:
			if (!getCarRoofWithSpriteIfExists(currLastCar->roof, 546))
			{
				fnCarAddRoofTankTurret(currLastCar);
				log(L"Tank turret spawned", ID);
			}
			break;
		case CAR_WEAP_WATERGUN:
		case CAR_WEAP_FLAMETHROWER:
			if (!getCarRoofWithSpriteIfExists(currLastCar->roof, 278))
			{
				fnCarAddRoofWaterGun(currLastCar);
				log(L"Firetruck turret spawned", ID);
			}
			break;
		case CAR_WEAP_JEEPGUN:
			if (!getCarRoofWithSpriteIfExists(currLastCar->roof, 285))
			{
				fnCarAddRoofGun(currLastCar);
				log(L"Jeep turret spawned", ID);
			}
			break;
		default:
			break;
	}
}

void MainWindow::OnPlayVocalClick(UINT nID) {
	fnPlayVocal((DWORD*)0x005d85a0, 0, (VOCAL)(nID - 55000));
	log(L"Vocal #%d played", nID - 55000);
}

void MainWindow::OnNativeCheatClick(UINT nID) {
	DWORD address = 0x5EAD00 + nID - 65000;
	bool* cheat = (bool*)(address);
	*cheat = !*cheat;
	log(L"%s cheat at 0x%X", *cheat ? L"Enabled" : L"Disabled", address);
	CheckMenuItem(ncHMenu, nID, *cheat ? MF_CHECKED : MF_UNCHECKED);
}

void MainWindow::CarEngineOff()
{
	// Return if currLastCar doesn't exist
	if (!currLastCar)
		return;

	currLastCar->engineState = CAR_ENGINE_STATE(TURNING_OFF);
	log(L"Engine turned off");
}

void MainWindow::LockStars()
{
	starsLocked = !starsLocked;
	startCopValue = fnGetPedByID(1)->copValue;
	if(starsLocked) log(L"Cop level locked at %d", startCopValue);
	else            log(L"Cop level unlocked");
	 
}

void MainWindow::NoReloads()
{
	noReloads = !noReloads;
	log(L"No reloads %sabled", noReloads ? "en" : "dis");

}

void MainWindow::LockCarDamage()
{

	if (carDamageLocked)
	{
		log(L"Engine damage unlocked");
	}
	else if (currLastCar)
	{
		startCarDamage = currLastCar->carDamage;
		log(L"Engine damage locked at %d", startCarDamage);
	}

	carDamageLocked = !carDamageLocked;

}

void MainWindow::SetStars(UINT nID)
{
	Ped* playerPed = fnGetPedByID(1);

	// Return if player ped doesn't exist
	if (!playerPed)
		return;

	UINT stars = nID - 3011;
	short copValues[] = { 0,600,1600,3000,5000,8000,12000 };
	startCopValue = copValues[stars];
	playerPed->copValue = copValues[stars];
	log(L"%i star(s) set", stars);
}

void MainWindow::TpToLastCar()
{
	Ped* playerPed = fnGetPedByID(1);

	if (currLastCar && playerPed && playerPed->gameObject)
	{
		playerPed->gameObject->sprite->x = currLastCar->sprite->x + 10;
		playerPed->gameObject->sprite->y = currLastCar->sprite->y + 10;
		playerPed->gameObject->sprite->z = currLastCar->sprite->z + 10;

		log(L"Teleported to the car!");
	}
}

void MainWindow::PrintCarInfo()
{
	// Return if currLastCar doesn't exist
	if (!currLastCar)
		return;

	// Print all info
	log(L"--- Car #%d info ---", currLastCar->id);
	log(L"Address: 0x%X", currLastCar);
	log(L"model: %d", currLastCar->carModel);
	if (currLastCar->roof)
	{
		log(L"Turret: 0x%X rot: %d x:%d y:%d", currLastCar->roof, currLastCar->roof->rotation, currLastCar->roof->xOffset, currLastCar->roof->yOffset);
		log(L"Turret Sprite: 0x%X spr: %d pal: %d lckpal: %d", currLastCar->roof->sprite, currLastCar->roof->sprite->sprite, currLastCar->roof->sprite->carColor, currLastCar->roof->sprite->lockPalleteMaybe);
		log(L"Turret GmObj: 0x%X id: %d", currLastCar->roof->sprite->gameObject, currLastCar->roof->sprite->gameObject->id);
	}
	else
		log(L"No turret");
	if (currLastCar->physics)
		log(L"Physics: 0x%X", currLastCar->physics);
	else
		log(L"No physics");
	if (currLastCar->sprite)
	{
		log(L"Sprite: 0x%X", currLastCar->sprite);
		log(L"x: %d y: %d z: %d r: %d", currLastCar->sprite->x, currLastCar->sprite->y, currLastCar->sprite->z, currLastCar->sprite->rotation);
	}
	else
		log(L"No sprite");
	if (currLastCar->driver)
		log(L"Driver: 0x%X occ: %d", currLastCar->driver, currLastCar->driver->occupation);
	else
		log(L"No driver");
	log(L"damage: %d visdmg: %d", currLastCar->carDamage, currLastCar->carLights);
	if (currLastCar->trailerController)
		log(L"Trailer: 0x%X model: %d", currLastCar->trailerController->trailer, currLastCar->trailerController->trailer->carModel);
	else
		log(L"No trailer");

	log(L"Prev: -1:0x%X, -2:0x%X, -3:0x%X", fnGetCarByID(currLastCar->id - 1), fnGetCarByID(currLastCar->id - 2), fnGetCarByID(currLastCar->id - 3));
	log(L"Next: +1:0x%X, +2:0x%X, +3:0x%X", fnGetCarByID(currLastCar->id + 1), fnGetCarByID(currLastCar->id + 2), fnGetCarByID(currLastCar->id + 3));
}

void MainWindow::GiveUnlimitedAmmo()
{
	Ped* playerPed = fnGetPedByID(1);

	// Return if player ped doesn't exist
	if (!playerPed)
		return;

	// Return if player doesn't have weapon selected
	if (!playerPed->selectedWeapon)
	{
		log(L"Select a weapon first");
		return;
	}

	playerPed->selectedWeapon->ammo = -1;
	log(L"Unlimited ammo given");
}

void MainWindow::FixCar()
{
	// Return if currLastCar doesn't exist
	if (!currLastCar)
		return;

	currLastCar->carDamage = 0;
	startCarDamage = 0;
	log(L"Fixed the engine");
}

void MainWindow::VisFixCar()
{
	// Return if currLastCar doesn't exist
	if (!currLastCar)
		return;

	currLastCar->carLights = CAR_LIGHTS_AND_DOORS_BITSTATE((currLastCar->carLights | 0x800040) & 0xFFFFFFE0); // turn on lights and filter out damage
	log(L"Fixed the car visually");
}

void MainWindow::VisBreakCar()
{
	// Return if currLastCar doesn't exist
	if (!currLastCar)
		return;

	currLastCar->carLights = CAR_LIGHTS_AND_DOORS_BITSTATE((currLastCar->carLights | 0x1F) & 0xFF387F9F); // make damage and filter out lights
	log(L"Broke the car visually");
}

void MainWindow::PlayerImmortal()
{
	Ped* playerPed = fnGetPedByID(1);

	// Return if player ped doesn't exist
	if (!playerPed)
		return;

	playerPed->Invulnerability = 9999*(!playerPed->Invulnerability);
	log(L"Invulnerability %s", (playerPed->Invulnerability) ? L"enabled" : L"disabled");
}

void MainWindow::PedInfo()
{
	// Return if not in the game
	if (*(DWORD*)ptrToPedManager == 0)
		return;

	WCHAR buf[256];
	Ped* playerPed = fnGetPedByID(1);

	// Global running speed
	if ((int)*(DWORD*)0x66a504 != globalPedSpeedsOld[0])
	{
		m_globalPedSpeeds[0].SetWindowTextW(L"0");
		swprintf(buf, 256, L"%d", (int)*(DWORD*)0x66a504);
		m_globalPedSpeeds[0].SetWindowTextW(buf);
	}

	// Global walking speed
	if ((int)*(DWORD*)0x66a574 != globalPedSpeedsOld[1])
	{
		m_globalPedSpeeds[1].SetWindowTextW(L"0");
		swprintf(buf, 256, L"%d", (int)*(DWORD*)0x66a574);
		m_globalPedSpeeds[1].SetWindowTextW(buf);
	}

	// Global standing speed (XD)
	if ((int)*(DWORD*)0x66a634 != globalPedSpeedsOld[2])
	{
		m_globalPedSpeeds[2].SetWindowTextW(L"0");
		swprintf(buf, 256, L"%d", (int)*(DWORD*)0x66a634);
		m_globalPedSpeeds[2].SetWindowTextW(buf);
	}

	globalPedSpeedsOld[0] = (int)*(DWORD*)0x66a504;
	globalPedSpeedsOld[1] = (int)*(DWORD*)0x66a574;
	globalPedSpeedsOld[2] = (int)*(DWORD*)0x66a634;

	if (currLastCar)
	{
		// Display currLastCar's id
		swprintf(buf, 256, L"%d", currLastCar->id);
		m_carID.SetWindowTextW(buf);

		// Display engine damage
		swprintf(buf, 256, L"%d", currLastCar->carDamage);
		m_carDamage.SetWindowTextW(buf);

		// Calculate and display velocity
		currLastCarXYShift = (int)sqrt(pow(currLastCar->sprite->x - currLastCarXOld, 2) + pow(currLastCar->sprite->y - currLastCarYOld, 2));
		currLastCarXOld = currLastCar->sprite->x;
		currLastCarYOld = currLastCar->sprite->y;
		swprintf(buf, 256, L"%d", currLastCarXYShift);
		m_carVelocity.SetWindowTextW(buf);

		// Display currLastCar's color
		if (currLastCar->sprite)
		{
			swprintf(buf, 256, L"%d", currLastCar->sprite->carColor);
			m_carColor.SetWindowTextW(buf);
		}

		// Lock door's buttons if car doesn't have ones
		for (int i = 0; i < 4; i++)
		{
			CButton* pButton = (CButton*)GetDlgItem(3075 + i);
			pButton->EnableWindow(currLastCar->carDoor[i].doorState != 0);
		}

		// Display emblem name 
		swprintf(buf, 256, L"%s", emblemNames[currLastCarEmblemID]);
		m_carEmblem.SetWindowTextW(buf);

		// Display visual state
		swprintf(buf, 256, L"%X", currLastCar->carLights);
		m_carVisualData.SetWindowTextW(buf);

	}
	else
	{
		m_carID.SetWindowTextW(L"");
		m_carDamage.SetWindowTextW(L"");
		m_carVelocity.SetWindowTextW(L"");
		m_carColor.SetWindowTextW(L"");
		m_carEmblem.SetWindowTextW(L"");
		m_carVisualData.SetWindowTextW(L"");
	}

	if (playerPed)
	{
		// Display ped's clothes color
		swprintf(buf, 256, L"%d", playerPed->remap);
		m_pedClothes.SetWindowTextW(buf);

		// Display ped's body shape
		swprintf(buf, 256, L"%d", playerPed->remap2);
		m_pedShape.SetWindowTextW(buf);

		// If player's health changed
		if (pedHOld != playerPed->health)
		{
			m_pedHealth.SetWindowTextW(L"0");
			swprintf(buf, 256, L"%d", playerPed->health);
			m_pedHealth.SetWindowTextW(buf);
		}
		pedHOld = playerPed->health;
		
		// If player's armor changed
		int *pedA = (int*)(*(DWORD*)(*(DWORD*)0x005eb4fc + 0x4) + 0x6fa); // TEMPOARY
		if (pedAOld != *pedA)
		{
			m_pedArmor.SetWindowTextW(L"0");
			swprintf(buf, 256, L"%d", *pedA);
			m_pedArmor.SetWindowTextW(buf);
			pedAOld = *pedA;
		}

		// If player's money changed
		int *pedM = (int*)(*(DWORD*)(*(DWORD*)0x005eb4fc + 0x38) + 0x2d4); // TEMPORARY
		if (pedMOld != *pedM)
		{
			m_pedMoney.SetWindowTextW(L"0");
			swprintf(buf, 256, L"%d", *pedM);
			m_pedMoney.SetWindowTextW(buf);
			pedMOld = *pedM;
		}

		// Display police level
		int Pvalue = playerPed->copValue;
		if(Pvalue <600) swprintf(buf, 256, L"%d (0) Peace", Pvalue);
		else if (Pvalue < 1600)  swprintf(buf, 256, L"%d (1) Lite", Pvalue);
		else if (Pvalue < 3000) swprintf(buf, 256, L"%d (2) All units", Pvalue);
		else if (Pvalue < 5000)  swprintf(buf, 256, L"%d (3) Barricades", Pvalue);
		else if (Pvalue < 8000) swprintf(buf, 256, L"%d (4) SWAT", Pvalue);
		else if (Pvalue < 12000) swprintf(buf, 256, L"%d (5) FBI", Pvalue);
		else swprintf(buf, 256, L"%d (6) Army!", Pvalue);
		m_pedCopLevel.SetWindowTextW(buf);

		// Display gangs respect
		DWORD* gangsArr = (DWORD*)0x005eb898;
		for (int i = 0; i < 3; i++)
		{
			int* gangresp = (int*)*gangsArr + 0x47 + i * 0x51;
			swprintf(buf, 256, L"%d", (char)*gangresp);
			m_gangRespect[i].SetWindowTextW(buf);
		}	

		// Calculate and display selected weapon ID
		short* weapSTART = (short*)(&playerPed->playerWeapons->weapons[0]->ammo);
		short* weapCURR = (short*)(&playerPed->selectedWeapon->ammo);
		int weapID = (weapCURR - weapSTART) / 48;
		if (weapID >= 0)
		{
			swprintf(buf, 256, L"%d", weapID);
			m_pedSType.SetWindowTextW(buf);
		}
		else m_pedSType.SetWindowTextW(L"");

		// Display current weapon's ammo and reload time
		if (playerPed->selectedWeapon)
		{
			float ammowithcomma = playerPed->selectedWeapon->ammo / 10.0f;
			swprintf(buf, 256, L"%f", ammowithcomma);
			m_pedSAmmo.SetWindowTextW(buf);

			swprintf(buf, 256, L"%d", playerPed->selectedWeapon->timeToReload);
			m_pedSTime.SetWindowTextW(buf);
		}
		else
		{
			m_pedSAmmo.SetWindowTextW(L"");
			m_pedSTime.SetWindowTextW(L"");
		}

		// If player in the car, display it's coords
		if (playerPed->currentCar)
		{
			m_pedZ.SetReadOnly(true);
	
			if (playerPed->currentCar->sprite->x != pedXOld)
			{
				swprintf(buf, 256, L"%.2f", playerPed->currentCar->sprite->x / 16384.0);
				m_pedX.SetWindowTextW(buf);
				pedXOld = playerPed->currentCar->sprite->x;
			}

			if (playerPed->currentCar->sprite->y != pedYOld)
			{
				swprintf(buf, 256, L"%.2f", playerPed->currentCar->sprite->y / 16384.0);
				m_pedY.SetWindowTextW(buf);
				pedYOld = playerPed->currentCar->sprite->y;
			}

			if (playerPed->currentCar->sprite->z != pedZOld)
			{
				swprintf(buf, 256, L"%.2f", playerPed->currentCar->sprite->z / 16384.0);
				m_pedZ.SetWindowTextW(buf);
				pedZOld = playerPed->currentCar->sprite->z;
			}

			if (playerPed->currentCar->sprite->rotation != pedRotOld)
			{
				swprintf(buf, 256, L"%d", playerPed->currentCar->sprite->rotation);
				m_pedRot.SetWindowTextW(buf);
				pedRotOld = playerPed->currentCar->sprite->rotation;
			}
			
		}
		// If player is not in the car, display ped's coords
		else
		{
			m_pedZ.SetReadOnly(false);

			// If player ped's sprite doesn't exist, clear textboxes
			if (!playerPed->gameObject || !playerPed->gameObject->sprite) {

				m_pedX.SetWindowTextW(L"");
				m_pedY.SetWindowTextW(L"");
				m_pedZ.SetWindowTextW(L"");
				m_pedRot.SetWindowTextW(L"");
			}
			else
			{
				// Display that ultra-cool message
				if (playerPed->gameObject->cigaretteIdleTimer == 1)
					log(L"Smokin' time ;3");

				if (playerPed->gameObject->sprite->x != pedXOld)
				{
					swprintf(buf, 256, L"%.2f", playerPed->gameObject->sprite->x / 16384.0);
					m_pedX.SetWindowTextW(buf);
					pedXOld = playerPed->gameObject->sprite->x;
				}
				
				if (playerPed->gameObject->sprite->y != pedYOld)
				{
					swprintf(buf, 256, L"%.2f", playerPed->gameObject->sprite->y / 16384.0);
					m_pedY.SetWindowTextW(buf);
					pedYOld = playerPed->gameObject->sprite->y;	
				}

				if (playerPed->gameObject->sprite->z != pedZOld)
				{
					swprintf(buf, 256, L"%.2f", playerPed->gameObject->sprite->z / 16384.0);
					m_pedZ.SetWindowTextW(buf);
					pedZOld = playerPed->gameObject->sprite->z;	
				}

				if (playerPed->gameObject->sprite->rotation != pedRotOld)
				{
					swprintf(buf, 256, L"%d", playerPed->gameObject->sprite->rotation);
					m_pedRot.SetWindowTextW(buf);
					pedRotOld = playerPed->gameObject->sprite->rotation;
				}
			}
		}
	}	
}

void MainWindow::TeleportAllPeds()
{
	Ped* playerPed = fnGetPedByID(1);

	// Return if player ped doesn't exist
	if (!playerPed || !playerPed->gameObject)
		return;

	int* nextpedid = (int*)0x591e84;
	Ped* currentPed;
	for (int i = 1; i < *nextpedid; i++)
	{
		currentPed = fnGetPedByID(i);

		if (currentPed && currentPed->gameObject)
		{
			currentPed->gameObject->sprite->x = playerPed->gameObject->sprite->x;
			currentPed->gameObject->sprite->y = playerPed->gameObject->sprite->y;
			currentPed->gameObject->sprite->z = playerPed->gameObject->sprite->z;
		}
	}
	log(L"Teleported");
}

void MainWindow::WatchPeds()
{
	Ped* playerPed = fnGetPedByID(1);

	if (watchPeds)
	{
		watchPeds = false;
		log(L"You are no longer watching peds");

		playerPed->gameObject->sprite->x = pedXPreHuman;
		playerPed->gameObject->sprite->y = pedYPreHuman;
		playerPed->gameObject->sprite->z = pedZPreHuman;


	}
	else if (playerPed && playerPed->gameObject)
	{
		watchPeds = true;
		log(L"You are now watching peds");
		log(L"You can change selected ped by pressing ALT + N");

		pedXPreHuman = playerPed->gameObject->sprite->x;
		pedYPreHuman = playerPed->gameObject->sprite->y;
		pedZPreHuman = playerPed->gameObject->sprite->z;

		WatchNextPed();
	}
	else
	{
		log(L"Player ped not found");
		((CButton*)GetDlgItem(IDC_BEAHUMAN))->SetCheck(false);
	}
}

void MainWindow::WatchNextPed()
{
	if (watchPeds)
	{
		int* nextpedid = (int*)0x591e84;
		Ped* currentPed;
		Ped* newSelectedPed = nullptr;
		int selectedPedID;
		if (selectedPed && selectedPed->id)
		{
			selectedPedID = selectedPed->id;
		}
		else
		{
			selectedPedID = 1;
		}

		for (int i = selectedPedID + 1; i < *nextpedid; i++)
		{
			currentPed = fnGetPedByID(i);

			if (currentPed && currentPed->gameObject)
			{
				newSelectedPed = currentPed;
				break;
			}
		}

		if (newSelectedPed == nullptr)
		{
			log(L"Couldn't find any Ped with further ID than the last one; Starting from 0 again...");

			for (int i = 2; i < *nextpedid; i++)
			{
				currentPed = fnGetPedByID(i);

				if (currentPed && currentPed->gameObject)
				{
					newSelectedPed = currentPed;
					break;
				}

			}
		}

		selectedPed = newSelectedPed;

		if (selectedPed != nullptr) {
			log(L"You're now watching ped #%d", selectedPed->id);
		}
	}
	
}

void MainWindow::GangRespect(UINT nID)
{
	DWORD* gangsArr = (DWORD*)0x005eb898;
	int gangNo = 0;
	int dataInt = (int)nID - 3040;

	if (dataInt >= 0 && dataInt <= 2) gangNo = 0;
	else if (dataInt >= 3 && dataInt <= 5) gangNo = 1;
	else if (dataInt >= 6 && dataInt <= 8) gangNo = 2;

	int* gangresp;
	gangresp = (int*)*gangsArr + 0x47 + gangNo * 0x51;

	if (dataInt == 0 || dataInt == 3 || dataInt == 6) *gangresp -= 20;
	else if (dataInt == 1 || dataInt == 4 || dataInt == 7) *gangresp = 0;
	else if (dataInt == 2 || dataInt == 5 || dataInt == 8) *gangresp += 20;
	
	log(L"Changed the respect to %i", (char)*gangresp);
}

void MainWindow::ToggleDoor(UINT uID)
{
	// Return if currLastCar doesn't exist
	if (!currLastCar)
		return;

	int doorID = uID - 3075;
	if (currLastCar->carDoor[doorID].doorState == 6 || doorOpen[doorID] == true)
	{
		doorOpen[doorID] = !doorOpen[doorID];
		log(L"Door %s", (doorOpen[doorID] ? L"opened" : L"closed"));
	}
}

void MainWindow::SyncTrailerColor()
{
	if 
	(
		currLastCar &&
		currLastCar->sprite &&
		currLastCar->trailerController && 
		currLastCar->trailerController->trailer &&
		currLastCar->trailerController->trailer->sprite
	)
	{
		currLastCar->trailerController->trailer->sprite->lockPalleteMaybe = currLastCar->sprite->lockPalleteMaybe;
		currLastCar->trailerController->trailer->sprite->carColor = currLastCar->sprite->carColor;
		log(L"Trailer color changed");
	}
}



void MainWindow::CarEmblemMinus()
{
	// Return if currLastCar's sprite doesn't exist
	if (!currLastCar || !currLastCar->sprite)
		return;

	if (currLastCarEmblemID == 1)
	{
		// "Remove" emblem //
		currLastCarEmblemID = 0;
		currLastCarEmblem->sprite->spriteType = SPRITE_TYPE_INVISIBLE;
		currLastCarEmblem->sprite->layer--;
		currLastCarEmblem = 0;
	}
	else if (currLastCarEmblemID > 1)
	{
		// Prev emblem //
		currLastCarEmblemID--;
		currLastCarEmblem->sprite->sprite = emblemValues[currLastCarEmblemID];
		log(L"Car emblem changed");
	}
}


void MainWindow::CarEmblemPlus()
{
	// Return if currLastCar's sprite doesn't exist
	if (!currLastCar || !currLastCar->sprite)
		return;

	if (currLastCarEmblemID == 0)
	{
		if (currLastCar->carModel == CAR_MODEL4_TVVAN)
		{
			log(L"TV Van is the only car you cannot put emblem on :(");
			return;
		}

		// Create emblem //
		fnCarAddRoofAntenna(currLastCar);
		currLastCarEmblem = getCarRoofWithSpriteIfExists(currLastCar->roof, 0);
		if (currLastCarEmblem)
		{
			currLastCarEmblemID = 1;
			currLastCarEmblem->sprite->sprite = emblemValues[1];
			currLastCarEmblem->rotation = 0;
			currLastCarEmblem->sprite->layer++;
			m_carEmblemPos.SetPos(currLastCarEmblem->yOffset);
			log(L"Car emblem created");
		}
	}
	else if (currLastCarEmblemID < sizeof(emblemValues)/sizeof(emblemValues[0]) - 1)
	{
		// Next emblem //
		currLastCarEmblemID++;
		currLastCarEmblem->sprite->sprite = emblemValues[currLastCarEmblemID];
		log(L"Car emblem changed");
	}
}

void MainWindow::CarColorPlus()
{
	// Return if currLastCar's sprite doesn't exist
	if (!currLastCar || !currLastCar->sprite)
		return;

	currLastCar->sprite->lockPalleteMaybe = 3;
	currLastCar->sprite->carColor++;
	if (currLastCar->sprite->carColor >35) 
		currLastCar->sprite->carColor = 0;

	log(L"Car color changed");
}

void MainWindow::CarColorMinus()
{
	// Return if currLastCar's sprite doesn't exist
	if (!currLastCar || !currLastCar->sprite)
		return;

	currLastCar->sprite->lockPalleteMaybe = 3;
	currLastCar->sprite->carColor--;
	if (currLastCar->sprite->carColor <0) currLastCar->sprite->carColor = 35;
	log(L"Car color changed");
}

void MainWindow::CarColorReset()
{
	// Return if currLastCar's sprite doesn't exist
	if (!currLastCar || !currLastCar->sprite)
		return;

	currLastCar->sprite->lockPalleteMaybe = 2;
	currLastCar->sprite->carColor = 0;
	log(L"Car color changed");
}

void MainWindow::PedClothesMinus()
{
	Ped* playerPed = fnGetPedByID(1);

	// Return if player ped doesn't exist
	if (!playerPed)
		return;

	playerPed->remap = (PED_REMAP)((BYTE)playerPed->remap - 1);
	if (playerPed->remap == 255) playerPed->remap = (PED_REMAP)52;
	log(L"Player clothes changed");
}

void MainWindow::PedClothesPlus()
{
	Ped* playerPed = fnGetPedByID(1);

	// Return if player ped doesn't exist
	if (!playerPed)
		return;

	playerPed->remap = (PED_REMAP)((BYTE)playerPed->remap + 1);
	if (playerPed->remap > 52) playerPed->remap = (PED_REMAP)0;
	log(L"Player clothes changed");
}

void MainWindow::PedShapeMinus()
{
	Ped* playerPed = fnGetPedByID(1);

	// Return if player ped doesn't exist
	if (!playerPed)
		return;

	playerPed->remap2 = (PED_REMAP2)((BYTE)playerPed->remap2 - 1);
	if (playerPed->remap2 == -1) playerPed->remap2 = (PED_REMAP2)2;
	log(L"Player appearance changed");
}

void MainWindow::PedShapePlus()
{
	Ped* playerPed = fnGetPedByID(1);

	// Return if player ped doesn't exist
	if (!playerPed)
		return;

	playerPed->remap2 = (PED_REMAP2)((BYTE)playerPed->remap2 + 1);
	if (playerPed->remap2 > 2) playerPed->remap2 = (PED_REMAP2)0;
	log(L"Player appearance changed");
}

void MainWindow::PedShapeClothesReset()
{
	Ped* playerPed = fnGetPedByID(1);

	// Return if player ped doesn't exist
	if (!playerPed)
		return;

	playerPed->remap2 = PED_REMAP2_1;
	playerPed->remap = PED_REMAP_PLAYER;
	log(L"Player appearance reset");
}

void MainWindow::ShowBigText()
{
	S10* s10 = (S10*)*(DWORD*)0x00672f40;
	CString buffer;
	m_BigText.GetWindowTextW(buffer);
	fnShowBigOnScreenLabel(&s10->ptrToSomeStructRelToBIG_LABEL, 0, (WCHAR*)(LPCTSTR)buffer, 10);
	log(L"Text shown!");
}

void MainWindow::HijackTrain()
{
	Ped* playerPed = fnGetPedByID(1);

	// Return if player ped doesn't exist
	if (!playerPed)
		return;

	S10* s10 = (S10*)*(DWORD*)0x00672f40;

	if (playerPed->currentCar && playerPed->currentCar->carModel == 59)
	{
		Car* loco = nullptr;
		for (int i = 1; i < 10; i++)
		{
			Car* thisCar = fnGetCarByID(playerPed->currentCar->id + i);
			if (thisCar && thisCar->carModel == 60)
			{
				loco = thisCar;
				break;
			}
		}
		if (loco == nullptr)
		{
			log(L"Couldn't find the loco :(");
			return;
		}

		loco->driver = playerPed;
		playerPed->currentCar = loco;
		*(bool*)(*(DWORD*)&playerPed + 0x248) = 0;
		fnShowBigOnScreenLabel(&s10->ptrToSomeStructRelToBIG_LABEL, 0, (WCHAR*)L"The train is yours!", 10);
	}
	else if (playerPed->currentCar && playerPed->currentCar->carModel == 60)
	{
		playerPed->currentCar->carModel = CAR_MODEL4_STYPE;
		fnShowBigOnScreenLabel(&s10->ptrToSomeStructRelToBIG_LABEL, 0, (WCHAR*)L"WHAT.", 10);
	}
	else
	{
		log(L"Player is not in the train");
	}
}

void MainWindow::SetGlobalPedSpeeds()
{
	CString buffer;

	m_globalPedSpeeds[0].GetWindowTextW(buffer);
	*(int*)(DWORD*)0x66a504 = (int)_ttof(buffer);
	m_globalPedSpeeds[1].GetWindowTextW(buffer);
	*(int*)(DWORD*)0x66a574 = (int)_ttof(buffer);
	m_globalPedSpeeds[2].GetWindowTextW(buffer);
	*(int*)(DWORD*)0x66a634 = (int)_ttof(buffer);

	log(L"Peds speeds changed *experimental feature*");
}

void MainWindow::FreeShopping()
{
	TrafficManager* trafficManager = (TrafficManager*)*(DWORD*)0x005e4ca4;
	trafficManager->do_free_shoping = !trafficManager->do_free_shoping;
	log(L"Free shopping %s", trafficManager->do_free_shoping ? L"enabled" : L"disabled");
}

void MainWindow::GoSlow()
{
	walkingSpeed = (int*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)0x05e3cc4 + 0x34) + 0x168) + 0x80) + 0x8) + 0x3c); // TEMPORARY

	*walkingSpeed = 256 * (1024 / *walkingSpeed);
	log(L"Slow walking %s", (*walkingSpeed == 256) ? L"enabled" : L"disabled");
}

void MainWindow::SetHealthArmorMoney()
{
	CString buffer;

	m_pedHealth.GetWindowTextW(buffer);
	fnGetPedByID(1)->health = (int)_ttof(buffer);

	m_pedArmor.GetWindowTextW(buffer);
	*(int*)(*(DWORD*)(*(DWORD*)0x005eb4fc + 0x4) + 0x6fa) = (int)_ttof(buffer); //TEMPONARY; when i learn how to use Ghirda, i'll fix that xD

	m_pedMoney.GetWindowTextW(buffer);
	*(int*)(*(DWORD*)(*(DWORD*)0x005eb4fc + 0x38) + 0x2d4) = (int)_ttof(buffer); //TEMPONARY; when i learn how to use Ghirda, i'll fix that xD

	log(L"Player stats changed!");

}

void MainWindow::TeleportPlayer()
{
	Ped* playerPed = fnGetPedByID(1);

	// Return if player ped doesn't exist
	if (!playerPed)
		return;

	fesetround(FE_TONEAREST);
	CString buffer;

	// If player is not in the car
	if (playerPed->gameObject && playerPed->gameObject->sprite)
	{
		m_pedX.GetWindowTextW(buffer);
		float newx = _wtof(buffer);
		playerPed->gameObject->sprite->x = newx * 16384;

		m_pedY.GetWindowTextW(buffer);
		float newy = _wtof(buffer);
		playerPed->gameObject->sprite->y = newy * 16384;

		m_pedZ.GetWindowTextW(buffer);
		float newz = _wtof(buffer);
		playerPed->gameObject->sprite->z = (newz * 16384.0) + 10;

		log(L"Player teleported to %f, %f, %f!", newx, newy, newz);
	}
	// If player is in the car
	else if (playerPed->currentCar)
	{
		m_pedX.GetWindowTextW(buffer);
		float newx = _wtof(buffer);
		playerPed->currentCar->physics->X_CM = newx * 16384;

		m_pedY.GetWindowTextW(buffer);
		float newy = _wtof(buffer);
		playerPed->currentCar->physics->Y_CM = newy * 16384;

		log(L"Player's car teleported to %f, %f!", newx, newy);
	}
}

void MainWindow::FixCheckboxes()
{
	Ped* playerPed = fnGetPedByID(1);
	TrafficManager* trafficManager = (TrafficManager*)*(DWORD*)0x005e4ca4;

	if (playerPed)
	{
		((CButton*)GetDlgItem(IDC_PEDIMMORT))->SetCheck(playerPed->Invulnerability);
	}

	if (trafficManager)
	{
		((CButton*)GetDlgItem(IDC_FREESHOP))->SetCheck(trafficManager->do_free_shoping);
	}

	((CButton*)GetDlgItem(IDC_BEAHUMAN))->SetCheck(watchPeds);
	((CButton*)GetDlgItem(IDC_MOUSECTRL))->SetCheck(captureMouse);

}

void Strafe(bool right, bool movingBackward) {
	Ped* playerPed = fnGetPedByID(1);

	// Return if player ped doesn't exist
	if (!playerPed)
		return;

	playerPed->state = PED_STATE_0_WALK;
	playerPed->state2 = (PED_STATE2)0;
	bool* IsPlayerPedMoving = (bool*)0x0066a3c7;
	*IsPlayerPedMoving = true;
	playerPed->gameObject->speed = 1024;

	DWORD* pedDefaultSpeedForStaying = (DWORD*)0x0066a634;
	*pedDefaultSpeedForStaying = 1024;
	auto original = playerPed->gameObject->spriteRotation;
	if (right)
		playerPed->gameObject->spriteRotation -= 360;
	else
		playerPed->gameObject->spriteRotation += 360;
	fnPedTickRaw(playerPed, 0);
	*pedDefaultSpeedForStaying = 0;
	playerPed->gameObject->spriteRotation = original;
}

void MainWindow::OnGTAGameTick(Game* game)
{
	//OnTimer moved here, it's more stable now
	KeepLockedValues();
	PedInfo();
	if (captureMouse) CaptureMouse();
	FixCheckboxes();
	if(wtSpawnCar+1) WantToSpawnCar();
}

void MainWindow::NewFunction()
{
	// You can add anything here to test it and then press ALT+D ingame to run the code :)
	log(L"Nearest ped: %d Nearest car: %d", FindTheNearestPed(fnGetPedByID(1))->id, FindTheNearestCar(fnGetPedByID(1))->id);
}
