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

	m_acsWindow = new ACSWindow();
	m_acsWindow->Create(IDD_DIALOG2, CWnd::GetDesktopWindow());
	m_acsWindow->m_mainWindow = this;

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
	ON_COMMAND_RANGE(35000, 35000 + 512, &SpawnCarHere)
	ON_COMMAND_RANGE(36000, 36000 + 512, &OnSpawnObjectClick)
	ON_COMMAND_RANGE(37000, 37000 + 15, &OnGetWeaponClick)
	ON_COMMAND_RANGE(37100, 37100 + 15, &OnGetCarWeaponClick)
	ON_COMMAND_RANGE(37200, 37200 + 62, &OnPlayVocalClick)
	ON_COMMAND_RANGE(38000, 38000 + 256, &OnNativeCheatClick)
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

	RegisterHotKey(
		GetSafeHwnd(),
		1,
		MOD_ALT | MOD_NOREPEAT,
		0x4F); //ALT+O

	RegisterHotKey(
		GetSafeHwnd(),
		1,
		MOD_ALT | MOD_NOREPEAT,
		0x43); //ALT+C

	CMenu *menu = GetMenu();
	std::map<std::wstring, DWORD>::iterator itr;
	
	// Prepare cars menu

	CMenu* nMenu = new CMenu();
	nMenu->CreatePopupMenu();	

	CMenu* naMenu = new CMenu();
	naMenu->CreatePopupMenu();

	CMenu* njMenu = new CMenu();
	njMenu->CreatePopupMenu();

	CMenu* ntMenu = new CMenu();
	ntMenu->CreatePopupMenu();

	for (int i = 0; i < 79; ++i) {
		if(i < 28)
			naMenu->AppendMenuW(MF_STRING, (UINT_PTR)(carids[i] + 35000), carnames[i]);
		else if(i < 51)
			njMenu->AppendMenuW(MF_STRING, (UINT_PTR)(carids[i] + 35000), carnames[i]);
		else
			ntMenu->AppendMenuW(MF_STRING, (UINT_PTR)(carids[i] + 35000), carnames[i]);
	}

	nMenu->AppendMenuW(MF_STRING, (UINT_PTR)(35200), L"Last spawned car -> ALT+C");
	nMenu->AppendMenuW(MF_STRING, (UINT_PTR)(35201), L"Array of cars...");
	nMenu->AppendMenuW(MF_POPUP, (UINT_PTR)naMenu->m_hMenu, L"A-I");
	nMenu->AppendMenuW(MF_POPUP, (UINT_PTR)njMenu->m_hMenu, L"J-S");
	nMenu->AppendMenuW(MF_POPUP, (UINT_PTR)ntMenu->m_hMenu, L"T-Z");
	menu->AppendMenuW(MF_POPUP, (UINT_PTR)nMenu->m_hMenu, L"Spawn car");

	nHMenu = nMenu->m_hMenu;
	EnableMenuItem(nHMenu, 35200, MF_DISABLED);

	// Prepare objects menu

	CMenu* oMenu = new CMenu();
	oMenu->CreatePopupMenu();

	CMenu* obMenu = new CMenu();
	obMenu->CreatePopupMenu();

	CMenu* owMenu = new CMenu();
	owMenu->CreatePopupMenu();

	CMenu* ocMenu = new CMenu();
	ocMenu->CreatePopupMenu();

	CMenu* opMenu = new CMenu();
	opMenu->CreatePopupMenu();

	CMenu* osMenu = new CMenu();
	osMenu->CreatePopupMenu();

	CMenu* orMenu = new CMenu();
	orMenu->CreatePopupMenu();

	CMenu* otMenu = new CMenu();
	otMenu->CreatePopupMenu();

	CMenu* ooMenu = new CMenu();
	ooMenu->CreatePopupMenu();

	CMenu* ooiMenu = new CMenu();
	ooiMenu->CreatePopupMenu();

	std::map<std::wstring, DWORD> objects;
	std::map<std::wstring, DWORD> objects_b; //basic
	std::map<std::wstring, DWORD> objects_w; //weapons
	std::map<std::wstring, DWORD> objects_c; //car weapons
	std::map<std::wstring, DWORD> objects_p; //power-ups
	std::map<std::wstring, DWORD> objects_s; //skids
	std::map<std::wstring, DWORD> objects_r; //projectiles
	std::map<std::wstring, DWORD> objects_t; //phones
	std::map<std::wstring, DWORD> objects_o; //others
	std::map<std::wstring, DWORD> objects_oi; //others invisible

	objects_b.insert(std::pair<std::wstring, DWORD>(L"BIN_LID", 1));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"BOLLARD", 2));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"CONE", 3));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"BOXES", 4));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"BLASTER", 5));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"RUBBISH", 6));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"BIN", 7));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"ANIMATING_OIL", 8));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"OIL", 9));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"MINE", 10));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"BUSH", 11));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"CRATE", 12));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"FOOTY", 13));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"HARDBOX", 14));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"NEWSDIS", 15));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"OILDRUM", 16));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"TYRE", 17));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"HYDRANT_LID", 18));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"HYDRANT", 19));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"HYDRANT_UNLID", 20));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"ROADBLOCK", 21));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"BENCH", 22));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"PACKAGE", 23));
	objects_oi.insert(std::pair<std::wstring, DWORD>(L"TOWER", 25));
	//objects_b.insert(std::pair<std::wstring, DWORD>(L"EXPLODE_MEDIUM", 42));
	objects_w.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_00 (Pistol)", 64));
	objects_w.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_01 (S-Uzi)", 65));
	objects_w.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_02 (Rocket Launcher)", 66));
	objects_w.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_03 (ElectroGun)", 67));
	objects_w.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_04 (Molotov Coctail)", 68));
	objects_w.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_05 (Grenade)", 69));
	objects_w.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_06 (Shotgun)", 70));
	objects_w.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_07 (ElectroBaton !)", 71));
	objects_w.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_08 (Flamethrower)", 72));
	objects_w.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_09 (Silenced S-Uzi)", 73));
	objects_w.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_10 (Dual Pistol)", 74));
	objects_w.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_11 (Letter L)", 75));
	objects_w.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_12 (Letter M)", 76));
	objects_w.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_13 (Letter N)", 77));
	objects_w.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_14 (Letter O)", 78));
	objects_c.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_15 (Vehicle bomb)", 79));
	objects_c.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_16 (Vehicle Oil Slick)", 80));
	objects_c.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_17 (Vehicle Mine)", 81));
	objects_c.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_18 (Vehicle Machine Gun)", 82));
	objects_c.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_19 (Tank Cannon)", 83));
	objects_c.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_20 (Water Cannon)", 84));
	objects_c.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_21 (Vehicle Flamethrower)", 85));
	objects_c.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_22 (Jeep Turret)", 86));
	objects_c.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_23 (Instant Vehicle Bomb)", 87));
	objects_c.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_24 (Letter J)", 88));
	objects_c.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_25 (Letter K)", 89));
	objects_c.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_26 (Letter L)", 90));
	objects_c.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_27 (Letter M)", 91));
	objects_p.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_28 (Multiplier +1)", 92));
	objects_p.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_29 (Life +1)", 93));
	objects_p.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_30 (Health)", 94));
	objects_p.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_31 (Armor)", 95));
	objects_p.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_32 (Get Outta Jail Free Card)", 96));
	objects_p.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_33 (Cop Bribe)", 97));
	objects_p.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_34 (Invulnerability*)", 98));
	objects_p.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_35 (Double Damage)", 99));
	objects_p.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_36 (Fast Reload)", 100));
	objects_p.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_37 (ElectroFingers)", 101));
	objects_p.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_38 (Respect!)", 102));
	objects_p.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_39 (Invisibility)", 103));
	objects_p.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_40 (Instant Gang)", 104));
	objects_p.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_41 (Letter N)", 105));
	objects_p.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_42 (Letter O)", 106));
	objects_p.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_43 (Letter P)", 107));
	objects_p.insert(std::pair<std::wstring, DWORD>(L"MOVING_COLLECT_44 (Letter Q)", 108));
	objects_o.insert(std::pair<std::wstring, DWORD>(L"SMALL_ARROW", 109));
	objects_o.insert(std::pair<std::wstring, DWORD>(L"BLOOD_SPARK", 111));
	objects_oi.insert(std::pair<std::wstring, DWORD>(L"PARTICLE_SYSTEM", 113));
	objects_o.insert(std::pair<std::wstring, DWORD>(L"FIREJET", 114));
	objects_s.insert(std::pair<std::wstring, DWORD>(L"SMALL_BROWN_SKID", 116));
	objects_s.insert(std::pair<std::wstring, DWORD>(L"SMALL_GREY_SKID", 117));
	objects_s.insert(std::pair<std::wstring, DWORD>(L"SMALL_RED_SKID", 118));
	objects_s.insert(std::pair<std::wstring, DWORD>(L"MEDIUM_BROWN_SKID", 119));
	objects_s.insert(std::pair<std::wstring, DWORD>(L"MEDIUM_GREY_SKID", 120));
	objects_s.insert(std::pair<std::wstring, DWORD>(L"MEDIUM_RED_SKID", 121));
	objects_oi.insert(std::pair<std::wstring, DWORD>(L"CAR_CROSSING", 122));
	objects_s.insert(std::pair<std::wstring, DWORD>(L"BIG_WHITE_SKID", 124));
	objects_s.insert(std::pair<std::wstring, DWORD>(L"MEDIUM_WHITE_SKID", 125));
	objects_s.insert(std::pair<std::wstring, DWORD>(L"SMALL_WHITE_SKID", 126));
	objects_r.insert(std::pair<std::wstring, DWORD>(L"ROCKET", 128));
	objects_oi.insert(std::pair<std::wstring, DWORD>(L"BUS_STOP_MARKER", 129));
	objects_oi.insert(std::pair<std::wstring, DWORD>(L"CAR_SHOP", 130));
	objects_oi.insert(std::pair<std::wstring, DWORD>(L"BUSY_CAR_SHOP", 131));
	objects_oi.insert(std::pair<std::wstring, DWORD>(L"CAR_BOMB", 132));
	objects_r.insert(std::pair<std::wstring, DWORD>(L"MOLOTOV_MOVING", 138));
	objects_s.insert(std::pair<std::wstring, DWORD>(L"HUGE_RED_SKID", 144));
	objects_s.insert(std::pair<std::wstring, DWORD>(L"HUGE_WHITE_SKID", 145));
	objects_s.insert(std::pair<std::wstring, DWORD>(L"HUGE_BROWN_SKID", 146));
	objects_s.insert(std::pair<std::wstring, DWORD>(L"HUGE_GREY_SKID", 147));
	objects_o.insert(std::pair<std::wstring, DWORD>(L"TANKTOP", 148));
	objects_o.insert(std::pair<std::wstring, DWORD>(L"ANTENNA", 149));
	objects_t.insert(std::pair<std::wstring, DWORD>(L"PHONE", 163));
	objects_t.insert(std::pair<std::wstring, DWORD>(L"PHONE_RINGING", 164));
	objects_t.insert(std::pair<std::wstring, DWORD>(L"PHONE_DEAD", 174));
	objects_o.insert(std::pair<std::wstring, DWORD>(L"BRIEFCASE", 175));
	objects_t.insert(std::pair<std::wstring, DWORD>(L"RED_PHONE", 176));
	objects_t.insert(std::pair<std::wstring, DWORD>(L"RED_PHONE_RINGING", 177));
	objects_t.insert(std::pair<std::wstring, DWORD>(L"YELLOW_PHONE", 178));
	objects_t.insert(std::pair<std::wstring, DWORD>(L"YELLOW_PHONE_RINGING", 179));
	objects_t.insert(std::pair<std::wstring, DWORD>(L"GREEN_PHONE", 180));
	objects_t.insert(std::pair<std::wstring, DWORD>(L"GREEN_PHONE_RINGING", 181));
	objects_r.insert(std::pair<std::wstring, DWORD>(L"GRENADE", 182));
	objects_r.insert(std::pair<std::wstring, DWORD>(L"SHOT", 192));
	objects_r.insert(std::pair<std::wstring, DWORD>(L"FLAMING_BULLET", 194));
	objects_o.insert(std::pair<std::wstring, DWORD>(L"FIRE", 197));
	objects_r.insert(std::pair<std::wstring, DWORD>(L"WATER_BULLET", 198));
	objects_o.insert(std::pair<std::wstring, DWORD>(L"BOMB", 247));
	objects_s.insert(std::pair<std::wstring, DWORD>(L"BIG_BROWN_SKID", 249));
	objects_s.insert(std::pair<std::wstring, DWORD>(L"BIG_GREY_SKID", 250));
	objects_s.insert(std::pair<std::wstring, DWORD>(L"BIG_RED_SKID", 253));
	objects_r.insert(std::pair<std::wstring, DWORD>(L"BULLET", 254));
	objects_o.insert(std::pair<std::wstring, DWORD>(L"TRAFFIC_LIGHT", 255));
	objects_o.insert(std::pair<std::wstring, DWORD>(L"RED_FOOTPRINTS", 256));
	objects_o.insert(std::pair<std::wstring, DWORD>(L"BLOOD", 257));
	objects_oi.insert(std::pair<std::wstring, DWORD>(L"CROSSING", 258));
	objects_o.insert(std::pair<std::wstring, DWORD>(L"SPARK", 259));
	objects_r.insert(std::pair<std::wstring, DWORD>(L"PISTOL_BULLET", 265));
	objects_p.insert(std::pair<std::wstring, DWORD>(L"BONUS_TOKEN", 266));
	objects_r.insert(std::pair<std::wstring, DWORD>(L"TASSER_BULLET", 277));
	objects_oi.insert(std::pair<std::wstring, DWORD>(L"SOUND_INSTANT", 279));
	objects_oi.insert(std::pair<std::wstring, DWORD>(L"INVISIBLE_TARGET", 280));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"POWERGEN", 281));
	objects_b.insert(std::pair<std::wstring, DWORD>(L"POWERGEN_DEAD", 282));
	objects_oi.insert(std::pair<std::wstring, DWORD>(L"INVISIBLE_DESTRUCTIBLE", 283));
	objects_o.insert(std::pair<std::wstring, DWORD>(L"GENLITE", 284));
	objects_oi.insert(std::pair<std::wstring, DWORD>(L"INVISIBLE_DEAD", 285));
	objects_p.insert(std::pair<std::wstring, DWORD>(L"KILL_FRENZY", 286));
	objects_oi.insert(std::pair<std::wstring, DWORD>(L"TUNNEL_BLOCKER", 294));
	objects_p.insert(std::pair<std::wstring, DWORD>(L"REMOTE", 295));

	objects.insert(std::pair<std::wstring, DWORD>(L"Last spawned object -> ALT+O", 400));

	for (itr = objects_b.begin(); itr != objects_b.end(); ++itr) {
		obMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 36000), itr->first.c_str());
	}

	for (itr = objects_w.begin(); itr != objects_w.end(); ++itr) {
		owMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 36000), itr->first.c_str());
	}

	for (itr = objects_c.begin(); itr != objects_c.end(); ++itr) {
		ocMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 36000), itr->first.c_str());
	}

	for (itr = objects_p.begin(); itr != objects_p.end(); ++itr) {
		opMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 36000), itr->first.c_str());
	}

	for (itr = objects_s.begin(); itr != objects_s.end(); ++itr) {
		osMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 36000), itr->first.c_str());
	}

	for (itr = objects_r.begin(); itr != objects_r.end(); ++itr) {
		orMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 36000), itr->first.c_str());
	}

	for (itr = objects_t.begin(); itr != objects_t.end(); ++itr) {
		otMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 36000), itr->first.c_str());
	}

	for (itr = objects_o.begin(); itr != objects_o.end(); ++itr) {
		ooMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 36000), itr->first.c_str());
	}

	for (itr = objects_oi.begin(); itr != objects_oi.end(); ++itr) {
		ooiMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 36000), itr->first.c_str());
	}

	for (itr = objects.begin(); itr != objects.end(); ++itr) {
		oMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 36000), itr->first.c_str());
	}

	oMenu->AppendMenuW(MF_POPUP, (UINT_PTR)obMenu->m_hMenu, L"Basic objects");
	oMenu->AppendMenuW(MF_POPUP, (UINT_PTR)owMenu->m_hMenu, L"Weapon collectibles");
	oMenu->AppendMenuW(MF_POPUP, (UINT_PTR)ocMenu->m_hMenu, L"Car Weapon collectibles");
	oMenu->AppendMenuW(MF_POPUP, (UINT_PTR)opMenu->m_hMenu, L"Power-Ups");
	oMenu->AppendMenuW(MF_POPUP, (UINT_PTR)osMenu->m_hMenu, L"Skids");
	oMenu->AppendMenuW(MF_POPUP, (UINT_PTR)orMenu->m_hMenu, L"Projectiles");
	oMenu->AppendMenuW(MF_POPUP, (UINT_PTR)otMenu->m_hMenu, L"Phones");
	oMenu->AppendMenuW(MF_POPUP, (UINT_PTR)ooMenu->m_hMenu, L"Others");
	ooMenu->AppendMenuW(MF_POPUP, (UINT_PTR)ooiMenu->m_hMenu, L"Invisible");
	menu->AppendMenuW(MF_POPUP, (UINT_PTR)oMenu->m_hMenu, L"Spawn object");

	oHMenu = oMenu->m_hMenu;
	EnableMenuItem(oHMenu, 36400, MF_DISABLED);

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
	weapons.insert(std::pair<std::wstring, DWORD>(L"ElectroBaton (!)", 7));
	weapons.insert(std::pair<std::wstring, DWORD>(L"Flamethrower", 8));
	weapons.insert(std::pair<std::wstring, DWORD>(L"Silenced S-Uzi", 9));
	weapons.insert(std::pair<std::wstring, DWORD>(L"Dual Pistol", 10));
	weapons.insert(std::pair<std::wstring, DWORD>(L"Letter L", 11));
	weapons.insert(std::pair<std::wstring, DWORD>(L"Letter M", 12));
	weapons.insert(std::pair<std::wstring, DWORD>(L"Letter N", 13));
	weapons.insert(std::pair<std::wstring, DWORD>(L"Letter O", 14));

	for (itr = weapons.begin(); itr != weapons.end(); ++itr) {
		wMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 37000), itr->first.c_str());
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
		cwMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 37100), itr->first.c_str());
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
		vMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 37200), itr->first.c_str());
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
	native.insert(std::pair<std::wstring, DWORD>(L"Skip right tiles", 0x59));
	native.insert(std::pair<std::wstring, DWORD>(L"No traffic", 0x5B));
	native.insert(std::pair<std::wstring, DWORD>(L"Unlock all levels", 0x5C));
	native.insert(std::pair<std::wstring, DWORD>(L"No police", 0x5E));
	native.insert(std::pair<std::wstring, DWORD>(L"Skip bottom tiles", 0x5F));
	native.insert(std::pair<std::wstring, DWORD>(L"Infinite lives", 0x61));
	native.insert(std::pair<std::wstring, DWORD>(L"No HUD", 0x64));
	native.insert(std::pair<std::wstring, DWORD>(L"Skip left tiles", 0x67));
	native.insert(std::pair<std::wstring, DWORD>(L"Show Imaginary Things", 0x6F));
	native.insert(std::pair<std::wstring, DWORD>(L"No peds spawn", 0x69));
	native.insert(std::pair<std::wstring, DWORD>(L"Mini cars", 0x6D));
	native.insert(std::pair<std::wstring, DWORD>(L"No audio", 0x72));
	//native.insert(std::pair<std::wstring, DWORD>(L"Get all weapons (req. restart)", 0x74));
	native.insert(std::pair<std::wstring, DWORD>(L"No slopes tiles", 0x78));
	native.insert(std::pair<std::wstring, DWORD>(L"Show FPS", 0x79));
	native.insert(std::pair<std::wstring, DWORD>(L"Show car horn", 0x7F));
	native.insert(std::pair<std::wstring, DWORD>(L"Show drawing info", 0x81));
	native.insert(std::pair<std::wstring, DWORD>(L"Show camera info", 0x82));
	native.insert(std::pair<std::wstring, DWORD>(L"Show vehicle info", 0x85));
	native.insert(std::pair<std::wstring, DWORD>(L"Debug keys", 0x87));
	native.insert(std::pair<std::wstring, DWORD>(L"Insane speed", 0x88));
	native.insert(std::pair<std::wstring, DWORD>(L"Show junctions IDs", 0x89));
	native.insert(std::pair<std::wstring, DWORD>(L"No top tiles", 0x8C));
	native.insert(std::pair<std::wstring, DWORD>(L"Show ped info", 0x8D));
	native.insert(std::pair<std::wstring, DWORD>(L"Skip tiles", 0x90));
	native.insert(std::pair<std::wstring, DWORD>(L"Show traffic info", 0x95));
	native.insert(std::pair<std::wstring, DWORD>(L"Keep weapons after death", 0x9E));
	native.insert(std::pair<std::wstring, DWORD>(L"Nekkid peds", 0xA0));
	native.insert(std::pair<std::wstring, DWORD>(L"Show peds IDs", 0xA1));
	native.insert(std::pair<std::wstring, DWORD>(L"Skip missions", 0xAE));
	native.insert(std::pair<std::wstring, DWORD>(L"Skip skidmarks", 0xAF));
	native.insert(std::pair<std::wstring, DWORD>(L"Show all arrows", 0xB2));

	for (itr = native.begin(); itr != native.end(); ++itr) {
		ncMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 38000), itr->first.c_str());
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
	log(L"Mouse control %sabled!", captureMouse ? L"en" : L"dis");
}

void MainWindow::CaptureMouse()
{
	// Return if not in the game
	if (*(DWORD*)ptrToPedManager == 0) {
		return;
	}

	Ped* playerPed = fnGetPedByID(1);

	// Return if playerPed doesn't exist
	if (!playerPed) {
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

	SetCursor(LoadCursor(0, IDC_CROSS));

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
		gtaAngle = (short)((angle + 360) * 4.0);
	}

	nAngle = 270 + angle;

	BYTE keyboard[256];
	GetKeyboardState(keyboard);

	auto player = fnGetPlayerSlotByIndex(0);

	auto keyUp = player->keyUp;
	auto keyDown = player->keyDown;
	auto keyRight = player->keyRight;
	auto keyLeft = player->keyLeft;
	auto keyAttack = player->keyAttack;

	if (playerPed->currentCar && playerPed->currentCar->physics)
	{
		// car steering
		if ((relX * 4.0f) / centerX > 1)
		{
			keyRight = 1;
			keyLeft = 0;
		}
		else if((relX * 4.0f) / centerX < -1)
		{
			keyRight = 0;
			keyLeft = 1;
		}
	}
	else if (playerPed->gameObject)
	{
		// ped steering
		playerPed->gameObject->spriteRotation = gtaAngle;
	}

	player->keyUp = (keyboard['W'] & 0x80) ? 1 : keyUp;
	player->keyDown = (keyboard['S'] & 0x80) ? 1 : keyDown;
	player->keyRight = (keyboard['D'] & 0x80) ? 1 : keyRight;
	player->keyLeft = (keyboard['A'] & 0x80) ? 1 : keyLeft;
	player->keyAttack = (keyboard[VK_LBUTTON] & 0x80) ? 1 : keyAttack;
}

void MainWindow::KeepLockedValues()
{
	// If not in game
	if (*(DWORD*)ptrToPedManager == 0) {
		currLastCar = 0;
		currLastCarEmblem = 0;
		currLastCarEmblemID = 0;
		currLastCarEmblemLPos = 0;
		currLastCarXOld = 0;
		currLastCarYOld = 0;
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

// Object spawning
void MainWindow::SpawnObject(OBJECT_TYPE type)
{
	S10* s10 = (S10*)*(DWORD*)0x00672f40;
	S33* s33 = (S33*)*(DWORD*)0x00665788;
	Ped* playerPed = fnGetPedByID(1);

	// Return if not in the game
	if (*(DWORD*)ptrToPedManager == 0)
		return;

	// Return if player ped doesn't exist
	if (!playerPed || !playerPed->gameObject || !playerPed->gameObject->sprite)
		return;

	// Return if player is in the car
	if (playerPed->currentCar)
		return;

	// Get target pos
	SCR_f* targetXY;
	targetXY = GetPointInADistance(
		playerPed->gameObject->sprite->x,
		playerPed->gameObject->sprite->y,
		playerPed->gameObject->sprite->rotation,
		16384
	);

	// Spawn object
	GameObject* object = fnSpawnObject(
		s33, 
		0, 
		type, 
		targetXY[0], 
		targetXY[1], 
		playerPed->gameObject->sprite->z, 
		0
	);

	// If everything successed, show label :D
	if (object)
	{
		log(L"Object 0x%X spawned!", object);
		fnShowBigOnScreenLabel(&s10->ptrToSomeStructRelToBIG_LABEL, 0, (WCHAR*)L"Object spawned!", 10);
	}

	wtSpawnObject = -1;

}

// Object spawning menu
void MainWindow::OnSpawnObjectClick(UINT nID) {
	switch (nID)
	{
	case 36400:
		OnSpawnLastObjectClick();
		break;
	default:
		wtSpawnObject = nID - 36000;
		lastSpawnedObjectType = wtSpawnObject;
		EnableMenuItem(oHMenu, 36400, MF_ENABLED);
		break;
	}
}

void MainWindow::OnSpawnLastObjectClick()
{
	if (lastSpawnedObjectType == -1)
		return;

	wtSpawnObject = lastSpawnedObjectType;
}

// Caleed evey game tick and only then
void MainWindow::SafeSpawnCars(WantToSpawn wtsList[128], int* wtsArraySize)
{
	while (*wtsArraySize > 0)
	{
		(*wtsArraySize)--;
		WantToSpawn currentWTS = wtsList[*wtsArraySize];

		// coordinates check
		if (
			currentWTS.x < 1 * 16384 ||
			currentWTS.x > 254 * 16384 ||
			currentWTS.y < 1 * 16384 ||
			currentWTS.y > 254 * 16384
			) {
			log(L"Car wasn't spawned, target position outside the world!");
			continue;
		}

		// Spawn a car
		Car* car = fnSpawnCar(
			currentWTS.x,
			currentWTS.y,
			currentWTS.z,
			currentWTS.rot,
			(CAR_MODEL)currentWTS.model
		);

		if (car)
		{
			log(L"Car 0x%X spawned!", car);

			short color = currentWTS.GetColor();
			if (color > -1) {
				car->sprite->lockPalleteMaybe = 3;
				car->sprite->carColor = color;
			}
		}
	}
}

// Car spawning (in front of the player)
void MainWindow::SpawnCarHere(UINT nID) {

	// Spawn last spawned car model
	if (nID == 35200)
	{
		if (lastSpawnedCarModel == -1)
			return;

		nID = lastSpawnedCarModel + 35000;
	}

	// Open advanced car spawner
	if (nID == 35201)
	{
		m_acsWindow->ShowWindow(SW_SHOW);
		m_acsWindow->SetFocus();
		m_acsWindow->ClearValues();
		return;
	}

	// Return if not in the game
	if (*(DWORD*)ptrToPedManager == 0)
		return;

	Ped* playerPed = fnGetPedByID(1);

	// Return if player ped doesn't exist
	if (!playerPed || !playerPed->gameObject || !playerPed->gameObject->sprite)
		return;

	// Return if player is in the car
	if (playerPed->currentCar)
		return;

	// Get target pos
	SCR_f* targetXY;
	targetXY = GetPointInADistance(
		playerPed->gameObject->sprite->x,
		playerPed->gameObject->sprite->y,
		playerPed->gameObject->sprite->rotation,
		16384
	);

	// Set wtsCar
	wtsCar[wtsCarSize] = WantToSpawn(targetXY[0], targetXY[1], playerPed->gameObject->sprite->z, 4 * 180, nID - 35000);
	wtsCarSize++;
	lastSpawnedCarModel = nID - 35000;
	EnableMenuItem(nHMenu, 35200, MF_ENABLED);
}

// Tank spawning
void MainWindow::OnSpawncarTank()
{
	SpawnCarHere(35000 + (int)TANK);
}

// Gunjeep spawning
void MainWindow::OnSpawncarGunjeep()
{
	SpawnCarHere(35000 + (int)GUNJEEP);
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
	case 0x4f:
		OnSpawnLastObjectClick();
		break;
	case 0x43:
		SpawnCarHere(35200);
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

	UINT ID = nID - 37000;
	playerPed->playerWeapons->weapons[ID]->ammo += 100;
	log(L"Weapon #%d got", nID - 37000);
}

void MainWindow::OnGetCarWeaponClick(UINT nID) {
	
	Ped* playerPed = fnGetPedByID(1);

	// Return if player's car's sprite doesn't exist
	if (!playerPed || !playerPed->currentCar || !playerPed->currentCar->sprite)
		return;

	byte ID = nID - 37100;
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
	fnPlayVocal((DWORD*)0x005d85a0, 0, (VOCAL)(nID - 37200));
	log(L"Vocal #%d played", nID - 37200);
}

void MainWindow::OnNativeCheatClick(UINT nID) {
	DWORD address = 0x5EAD00 + nID - 38000;
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
	log(L"No reloads %sabled", noReloads ? L"en" : L"dis");

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

		if (currLastCar->sprite)
		{
			// Calculate and display currLastCar's velocity
			currLastCarXYShift = (int)sqrt(pow(currLastCar->sprite->x - currLastCarXOld, 2) + pow(currLastCar->sprite->y - currLastCarYOld, 2));
			currLastCarXOld = currLastCar->sprite->x;
			currLastCarYOld = currLastCar->sprite->y;
			swprintf(buf, 256, L"%d", currLastCarXYShift);
			m_carVelocity.SetWindowTextW(buf);

			// Display currLastCar's color
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
				swprintf(buf, 256, L"%d", playerPed->currentCar->sprite->rotation/4);
				m_pedRot.SetWindowTextW(buf);
				pedRotOld = playerPed->currentCar->sprite->rotation;
			}
			
		}
		// If player is not in the car, display ped's coords
		else
		{
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
					swprintf(buf, 256, L"%d", playerPed->gameObject->sprite->rotation/4);
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

		playerPed->gameObject->sprite->x = pedXPreWatch;
		playerPed->gameObject->sprite->y = pedYPreWatch;
		playerPed->gameObject->sprite->z = pedZPreWatch;


	}
	else if (playerPed && playerPed->gameObject)
	{
		watchPeds = true;
		log(L"You are now watching peds");
		log(L"You can change selected ped by pressing ALT + N");

		pedXPreWatch = playerPed->gameObject->sprite->x;
		pedYPreWatch = playerPed->gameObject->sprite->y;
		pedZPreWatch = playerPed->gameObject->sprite->z;

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
	else if (playerPed->currentCar && playerPed->currentCar->physics)
	{
		m_pedX.GetWindowTextW(buffer);
		float newx = _wtof(buffer);
		playerPed->currentCar->physics->xPos = newx * 16384;

		m_pedY.GetWindowTextW(buffer);
		float newy = _wtof(buffer);
		playerPed->currentCar->physics->yPos = newy * 16384;

		m_pedZ.GetWindowTextW(buffer);
		float newz = _wtof(buffer);
		playerPed->currentCar->physics->zPos = (newz * 16384) + 10;

		log(L"Player's car teleported to %f, %f, %f!", newx, newy, newz);
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
	SafeSpawnCars(wtsCar, &wtsCarSize);
	if (wtSpawnObject != -1) SpawnObject((OBJECT_TYPE)wtSpawnObject);
}

void MainWindow::NewFunction()
{
	// You can add anything here to test it and then press ALT+D ingame to run the code :)
	Ped* playerPed = fnGetPedByID(1);
	if (!playerPed) return;
	Ped* nearestPed = FindTheNearestPed(playerPed);
	Car* nearestCar = FindTheNearestCar(playerPed);
	log(L"Nearest ped: %d (0x%X) Nearest car: %d (0x%X)", nearestPed->id, nearestPed, nearestCar->id, nearestCar);
}
