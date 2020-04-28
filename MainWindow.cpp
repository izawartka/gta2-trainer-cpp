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

#include <detours.h>
#pragma comment(lib, "detours.lib")

// MainWindow dialog
BOOL DetourFunc(const DWORD originalFn, DWORD hookFn, size_t copyBytes = 5);

const DWORD pGameTick = (DWORD)0x0045c1f0;
const DWORD pDraw = (DWORD)0x00461960;
const TrafficLigthStruct *ptrToTrafficLights = (TrafficLigthStruct*)0x006721cc;
Game* game = 0;
MainWindow* mainWnd = nullptr;


// void __fastcall PlayVocal(void *param_1,undefined4 unused,VOCAL vocal)
typedef void* (__fastcall PlayVocal)(void*, DWORD edx, VOCAL vocal);
PlayVocal* fnPlayVocal = (PlayVocal*)0x004105b0;

// void __fastcall StartMapPlaySound(void *param_1)
typedef void* (__fastcall StartMapPlaySound)(void*, DWORD edx);
StartMapPlaySound* fnStartMapPlaySound = (StartMapPlaySound*)0x004784d0;

void __fastcall myPlayVocal(void* _this, DWORD edx, VOCAL v) {
	//replace VOCAL to something else
	OutputDebugStringA("myPlayVocal");
	fnPlayVocal(_this, edx, VOCAL_DAMNATION__NO_DONATION__NO_SALVATION);
}

void __fastcall myStartMapPlaySound(void* _this, DWORD edx) {
	DetourRestoreAfterWith();

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)fnPlayVocal, myPlayVocal);
	DetourTransactionCommit();

	fnStartMapPlaySound(_this, edx);
}

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

	*(BYTE*)((LPBYTE)originalFn) = 0xE9; //JMP FAR
	DWORD offset = (((DWORD)hookFn) - ((DWORD)originalFn + 5)); //Offset math.
	*(DWORD*)((LPBYTE)originalFn + 1) = offset;

	for (i = 5; i < copyBytes; i++) {
		*(BYTE*)((LPBYTE)originalFn + i) = 0x90; //JMP FAR
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

	__asm MOV game, ECX; // copy ptr to game

	OutputDebugStringA("gameTick\n");
	mainWnd->OnGTAGameTick(game);

	__asm {
		MOV EAX, pGameTick
		add eax, 5
		JMP EAX
	}

}

static __declspec(naked) void draw(void) {
	// this will be replaced by original bytes 6 bytes
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

	__asm pushad

	OutputDebugStringA("draw\n");
	mainWnd->OnGTADraw();

	__asm popad

	__asm {
		mov eax, pDraw
		add eax, 5
		jmp eax
	}

}

IMPLEMENT_DYNAMIC(MainWindow, CDialogEx)

MainWindow::MainWindow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	mainWnd = this;
	DetourFunc(pGameTick, (DWORD)gameTick);
	DetourFunc(pDraw, (DWORD)draw, 6);

	DetourRestoreAfterWith();

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)fnStartMapPlaySound, myStartMapPlaySound);
	DetourTransactionCommit();
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
	DDX_Control(pDX, IDC_CARCOLV, m_carColor);
	DDX_Control(pDX, IDC_CARVIS, m_carVisualData);
	DDX_Control(pDX, IDC_PEDHEALTH, m_pedHealth);
	DDX_Control(pDX, IDC_PEDARMOR, m_pedArmor);
	DDX_Control(pDX, IDC_PEDMONEY, m_pedMoney);
}


BEGIN_MESSAGE_MAP(MainWindow, CDialogEx)
	ON_BN_CLICKED(IDOK, &MainWindow::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &MainWindow::OnBnClickedCancel)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_COMMAND(ID_COMMANDS_HELLO, &MainWindow::OnCommandsHello)
	ON_COMMAND(ID_COMMANDS_CAPTUREMOUSE, &MainWindow::OnCommandsCaptureMouse)
	ON_COMMAND(ID_SPAWNCAR_TANK, &MainWindow::OnSpawncarTank)
	ON_WM_HOTKEY()
	ON_COMMAND(ID_SPAWNCAR_GT, &MainWindow::OnSpawncarGt)
	ON_COMMAND_RANGE(35000, 35000 + 83, &OnSpawnCarClick)
	ON_COMMAND_RANGE(45000, 45000 + 15, &OnGetWeaponClick)
	ON_COMMAND_RANGE(55000, 55000 + 62, &OnPlayVocalClick)
	ON_COMMAND(ID_SPAWNCAR_GUNJEEP, &MainWindow::OnSpawncarGunjeep)
	ON_BN_CLICKED(IDC_CARENGINEOFF, &MainWindow::CarEngineOff)
	ON_BN_CLICKED(IDC_UNLMAMMO, &MainWindow::GiveUnlimitedAmmo)
	ON_BN_CLICKED(IDC_STAR0, &MainWindow::SetStars0)
	ON_BN_CLICKED(IDC_STAR1, &MainWindow::SetStars1)
	ON_BN_CLICKED(IDC_STAR2, &MainWindow::SetStars2)
	ON_BN_CLICKED(IDC_STAR3, &MainWindow::SetStars3)
	ON_BN_CLICKED(IDC_STAR4, &MainWindow::SetStars4)
	ON_BN_CLICKED(IDC_STAR5, &MainWindow::SetStars5)
	ON_BN_CLICKED(IDC_STAR6, &MainWindow::SetStars6)
	//ON_BN_CLICKED(IDC_CARDETONATE, &MainWindow::DetonateLastCar)
	ON_BN_CLICKED(IDC_CARFIX, &MainWindow::FixCar)
	ON_BN_CLICKED(IDC_CARVISFIX, &MainWindow::VisFixCar)
	ON_BN_CLICKED(IDC_CARVISBRK, &MainWindow::VisBreakCar)
	ON_BN_CLICKED(IDC_LOCKCOPLEVEL, &MainWindow::LockStars)
	ON_BN_CLICKED(IDC_LOCKCARDAMAGE, &MainWindow::LockCarDamage)
	ON_BN_CLICKED(IDC_PEDS0TIME, &MainWindow::NoReloads)
	ON_BN_CLICKED(IDC_CARLASTTP, &MainWindow::TpToLastCar)
	ON_BN_CLICKED(IDC_PEDIMMORT, &MainWindow::PlayerImmortal)
	ON_BN_CLICKED(ID_TPALLPEDS, &MainWindow::TeleportAllPeds)
	ON_BN_CLICKED(IDC_BEAHUMAN, &MainWindow::BeAHuman)
	ON_COMMAND_RANGE(3040, 3048, &GangRespect)
	ON_BN_CLICKED(IDC_SHOWPEDIDS, &MainWindow::ShowIDs)
	ON_BN_CLICKED(IDC_FREESHOP, &MainWindow::FreeShopping)
	ON_BN_CLICKED(IDC_SHOWCOUNTERS, &MainWindow::ShowCounters)
	ON_BN_CLICKED(IDC_KEEPWEAPONS, &MainWindow::KeepWeapons)
	ON_BN_CLICKED(IDC_BEAHUMAN, &MainWindow::BeAHuman)
	ON_BN_CLICKED(IDC_TPPLAYER, &MainWindow::TeleportPlayer)
	ON_BN_CLICKED(IDC_CARCOLP, &MainWindow::CarColorPlus)
	ON_BN_CLICKED(IDC_CARCOLM, &MainWindow::CarColorMinus)
	ON_BN_CLICKED(IDC_CARCOLR, &MainWindow::CarColorReset)
	ON_BN_CLICKED(IDC_GOSLOW, &MainWindow::GoSlow)
	ON_BN_CLICKED(IDC_PEDHAMSET, &MainWindow::SetHealthArmorMoney)
END_MESSAGE_MAP()


void MainWindow::OnBnClickedOk()
{
	//CDialogEx::OnOK();
}


void MainWindow::OnBnClickedCancel()
{
	if (m_gtaWindow) {
		::DestroyWindow(m_gtaWindow);
		::exit(0);
	}
}


int MainWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_gtaWindow = NULL;
	firstPaint = true;
	frames = 0;

	SetTimer(TIMER_CAPTURE_MOUSE, 1000 / 60, NULL);
	SetTimer(TIMER_PED_INFO, 1000 / 60, NULL);

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
		0x44); //ALT+N

	RegisterHotKey(
		GetSafeHwnd(),
		1,
		MOD_ALT | MOD_NOREPEAT,
		0x4e); //ALT+N

	//AppendMenu();
	CMenu *menu = GetMenu();
	
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
	//cars.insert(std::pair<std::wstring, DWORD>(L"CAR15", 15));
	//cars.insert(std::pair<std::wstring, DWORD>(L"CAR20", 20));
	//cars.insert(std::pair<std::wstring, DWORD>(L"CAR43", 43));
	//cars.insert(std::pair<std::wstring, DWORD>(L"CAR9", 9));
	cars.insert(std::pair<std::wstring, DWORD>(L"COPCAR", 12));
	cars.insert(std::pair<std::wstring, DWORD>(L"DART", 13));
	cars.insert(std::pair<std::wstring, DWORD>(L"EDSEL", 14));
	cars.insert(std::pair<std::wstring, DWORD>(L"EDSELFBI", 84));
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
	cars.insert(std::pair<std::wstring, DWORD>(L"HOTDOG_D4", 85));
	cars.insert(std::pair<std::wstring, DWORD>(L"ICECREAM", 27));
	cars.insert(std::pair<std::wstring, DWORD>(L"ISETLIMO", 28));
	cars.insert(std::pair<std::wstring, DWORD>(L"ISETTA", 29));
	cars.insert(std::pair<std::wstring, DWORD>(L"JEEP", 30));
	cars.insert(std::pair<std::wstring, DWORD>(L"JEFFREY", 31));
	cars.insert(std::pair<std::wstring, DWORD>(L"KRSNABUS", 86));
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
	//cars.insert(std::pair<std::wstring, DWORD>(L"TRAIN", 59));
	//cars.insert(std::pair<std::wstring, DWORD>(L"TRAINCAB", 60));
	//cars.insert(std::pair<std::wstring, DWORD>(L"TRAINFB", 61));
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

	std::map<std::wstring, DWORD>::iterator itr;
	for (itr = cars.begin(); itr != cars.end(); ++itr) {
		nMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 35000), itr->first.c_str());
	}

	menu->AppendMenuW(MF_POPUP, (UINT_PTR)nMenu->m_hMenu, L"Spawn car");

	CMenu* wMenu = new CMenu();
	wMenu->CreatePopupMenu();

	std::map<std::wstring, DWORD> weapons;

	weapons.insert(std::pair<std::wstring, DWORD>(L"PISTOL", 0));
	weapons.insert(std::pair<std::wstring, DWORD>(L"UZI", 1));
	weapons.insert(std::pair<std::wstring, DWORD>(L"ROCKET LAUNCHER", 2));
	weapons.insert(std::pair<std::wstring, DWORD>(L"ELECTROSHOCKER", 3));
	weapons.insert(std::pair<std::wstring, DWORD>(L"MOLOTOV COCTAIL", 4));
	weapons.insert(std::pair<std::wstring, DWORD>(L"GRENADE", 5));
	weapons.insert(std::pair<std::wstring, DWORD>(L"SHOTGUN", 6));
	weapons.insert(std::pair<std::wstring, DWORD>(L"ELECTROBATON", 7));
	weapons.insert(std::pair<std::wstring, DWORD>(L"FLAMETHROWER", 8));
	weapons.insert(std::pair<std::wstring, DWORD>(L"SILENCED UZI", 9));
	weapons.insert(std::pair<std::wstring, DWORD>(L"DOUBLE PISTOL", 10));
	weapons.insert(std::pair<std::wstring, DWORD>(L"LETTER L", 11));
	weapons.insert(std::pair<std::wstring, DWORD>(L"LETTER M", 12));
	weapons.insert(std::pair<std::wstring, DWORD>(L"LETTER N", 13));
	weapons.insert(std::pair<std::wstring, DWORD>(L"LETTER O", 14));

	//weapons.insert(std::pair<std::wstring, DWORD>(L"CAR UZI", 29));
	//weapons.insert(std::pair<std::wstring, DWORD>(L"CAR MINES", 37));
	//weapons.insert(std::pair<std::wstring, DWORD>(L"OIL", 38));
	//weapons.insert(std::pair<std::wstring, DWORD>(L"CAR BOMB", 45));

	for (itr = weapons.begin(); itr != weapons.end(); ++itr) {
		wMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 45000), itr->first.c_str());
	}

	menu->AppendMenuW(MF_POPUP, (UINT_PTR)wMenu->m_hMenu, L"Get weapon");

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

	menu->AppendMenuW(MF_POPUP, (UINT_PTR)vMenu->m_hMenu, L"Play Vocal");

	return 0;
}


void MainWindow::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
	if (firstPaint && m_gtaWindow) {
		firstPaint = false;
		CRect rect, rect2;
		
		GetWindowRect(&rect);
		::GetWindowRect(m_gtaWindow, &rect2);

		int x = GetSystemMetrics(SM_CXSCREEN) - rect2.Width();
		
		::MoveWindow(m_gtaWindow, x, 0, rect2.Width(), rect2.Height(), true);
		MoveWindow(0, 0, rect.Width(), rect.Height(), true);

		m_log.ShowScrollBar(SB_VERT);
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


void MainWindow::OnCommandsCaptureMouse()
{
	CMenu *menu = GetMenu();
	MENUITEMINFO menuItem = { 0 };
	menuItem.cbSize = sizeof(MENUITEMINFO);
	menuItem.fMask = MIIM_STATE;

	menu->GetMenuItemInfoW(ID_COMMANDS_CAPTUREMOUSE, &menuItem);

	if (menuItem.fState == MFS_CHECKED) {
		// Checked, uncheck it
		menuItem.fState = MFS_UNCHECKED;
		log(L"Do not capture mouse");
		captureMouse = false;
	}
	else {
		// Unchecked, check it
		menuItem.fState = MFS_CHECKED;
		log(L"Capture mouse");
		captureMouse = true;
	}
	menu->SetMenuItemInfoW(ID_COMMANDS_CAPTUREMOUSE, &menuItem);
}

DWORD ptrToPedManager = 0x005e5bbc;
DWORD ptrToGame = 0x005eb4fc;

typedef Ped* (__stdcall GetPedById)(int);
GetPedById* fnGetPedByID = (GetPedById*)0x0043ae10;

//Player* __thiscall Game::GetPlayerSlotByIndex(Game* this, byte index);
typedef Player* (__fastcall GetPlayerSlotByIndex)(Game* game, DWORD edx, byte index);
GetPlayerSlotByIndex* fnGetSaveSlotByIndex = (GetPlayerSlotByIndex*)0x004219e0;

//void __thiscall ShowBigOnScreenLabel(void* this, WCHAR* txt, int timeToShowInSeconds);
typedef void(__fastcall ShowBigOnScreenLabel)(void* ptr, DWORD edx, WCHAR* txt, int time);
ShowBigOnScreenLabel* fnShowBigOnScreenLabel = (ShowBigOnScreenLabel*)0x004c6060;

//void SpawnCar(int x, int y, int z, short rot, CAR_MODEL model)
typedef Car* (SpawnCar)(int x, int y, int z, short rot, CAR_MODEL model);
SpawnCar* fnSpawnCar = (SpawnCar*)0x00426e10;

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
			//log(L"Cursor is outside of the game window");
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

	if (playerPed->pedSprite) {
		playerPed->pedSprite->spriteRotation = gtaAngle;
	}

}

void MainWindow::CopLockETC()
{
	///AFTERCAPTURE///
	if (*(DWORD*)ptrToPedManager == 0) {
		if (frames++ % 60 == 0) {
			//log(L"Not in a game");
		}
		return;
	}
	Ped* playerPed = fnGetPedByID(1);

	if (playerPed)
	{
		if (starsLocked)
		{
			playerPed->copValue = startCopValue;
				//log(L"locktick");
		}

		if (noReloads && playerPed->selectedWeapon) playerPed->selectedWeapon->timeToReload = 0;

		if (beAHuman)
		{
			//Ped* lastped = fnGetPedByID((int)*nextpedid - 1);

			if (selectedPed && selectedPed->pedSprite)
			{
				playerPed->pedSprite->actualPosition->x = selectedPed->pedSprite->actualPosition->x;
				playerPed->pedSprite->actualPosition->y = selectedPed->pedSprite->actualPosition->y;
				playerPed->pedSprite->actualPosition->z = selectedPed->pedSprite->actualPosition->z;
			}
			else
			{
				log(L"Something is wrong with current Ped; choosing the new one...");

				NextHuman();
				
			}
		}
		
	}

		if (playerPed->currentCar)
		{
			currLastCar = playerPed->currentCar;

			if (currLastCar != currLastCarOld)
			{
				const WCHAR* carlist[87] = {
					L"Player has entered ALFA #%i",
					L"Player has entered ALLARD #%i",
					L"Player has entered AMDB4 #%i",
					L"Player has entered APC #%i",
					L"Player has entered BANKVAN #%i",
					L"Player has entered BMW #%i",
					L"Player has entered BOXCAR #%i",
					L"Player has entered BOXTRUCK #%i",
					L"Player has entered BUG #%i",
					L"Player has entered CAR9 #%i",
					L"Player has entered BUICK #%i",
					L"Player has entered BUS #%i",
					L"Player has entered COPCAR #%i",
					L"Player has entered DART #%i",
					L"Player has entered EDSEL #%i",
					L"Player has entered CAR15 #%i",
					L"Player has entered FIAT #%i",
					L"Player has entered FIRETRUK #%i",
					L"Player has entered GRAHAM #%i",
					L"Player has entered GT24640 #%i",
					L"Player has entered CAR20 #%i",
					L"Player has entered GTRUCK #%i",
					L"Player has entered GUNJEEP #%i",
					L"Player has entered HOTDOG #%i",
					L"Player has entered HOTDOG_D1 #%i",
					L"Player has entered HOTDOG_D2 #%i",
					L"Player has entered HOTDOG_D3 #%i",
					L"Player has entered ICECREAM #%i",
					L"Player has entered ISETLIMO #%i",
					L"Player has entered ISETTA #%i",
					L"Player has entered JEEP #%i",
					L"Player has entered JEFFREY #%i",
					L"Player has entered LIMO #%i",
					L"Player has entered LIMO2 #%i",
					L"Player has entered MEDICAR #%i",
					L"Player has entered MERC #%i",
					L"Player has entered MESSER #%i",
					L"Player has entered MIURA #%i",
					L"Player has entered MONSTER #%i",
					L"Player has entered MORGAN #%i",
					L"Player has entered MORRIS #%i",
					L"Player has entered PICKUP #%i",
					L"Player has entered RTYPE #%i",
					L"Player has entered CAR43 #%i",
					L"Player has entered SPIDER #%i",
					L"Player has entered SPRITE #%i",
					L"Player has entered STINGRAY #%i",
					L"Player has entered STRATOS #%i",
					L"Player has entered STRATOSB #%i",
					L"Player has entered STRIPETB #%i",
					L"Player has entered STYPE #%i",
					L"Player has entered STYPECAB #%i",
					L"Player has entered SWATVAN #%i",
					L"Player has entered T2000GT #%i",
					L"Player has entered TANK #%i",
					L"Player has entered TANKER #%i",
					L"Player has entered TAXI #%i",
					L"Player has entered TBIRD #%i",
					L"Player has entered TOWTRUCK #%i",
					L"Player has entered TRAIN #%i",
					L"Player has entered TRAINCAB #%i",
					L"Player has entered TRAINFB #%i",
					L"Player has entered TRANCEAM #%i",
					L"Player has entered TRUKCAB1 #%i",
					L"Player has entered TRUKCAB2 #%i",
					L"Player has entered TRUKCONT #%i",
					L"Player has entered TRUKTRNS #%i",
					L"Player has entered TVVAN #%i",
					L"Player has entered VAN #%i",
					L"Player has entered VESPA #%i",
					L"Player has entered VTYPE #%i",
					L"Player has entered WBTWIN #%i",
					L"Player has entered WRECK0 #%i",
					L"Player has entered WRECK1 #%i",
					L"Player has entered WRECK2 #%i",
					L"Player has entered WRECK3 #%i",
					L"Player has entered WRECK4 #%i",
					L"Player has entered WRECK5 #%i",
					L"Player has entered WRECK6 #%i",
					L"Player has entered WRECK7 #%i",
					L"Player has entered WRECK8 #%i",
					L"Player has entered WRECK9 #%i",
					L"Player has entered XK120 #%i",
					L"Player has entered ZCX5 #%i",
					L"Player has entered EDSELFBI #%i",
					L"Player has entered HOTDOG_D4 #%i",
					L"Player has entered KRSNABUS #%i",
				};
				
				log(carlist[playerPed->currentCar->carModel], playerPed->currentCar->id);
				
			}
		}


	if (currLastCar && carDamageLocked)
	{
		if (currLastCar == currLastCarOld)
		{
			currLastCar->carDamage = startCarDamage;
		}
		else
		{
			((CButton*)GetDlgItem(IDC_LOCKCARDAMAGE))->SetCheck(false);
			carDamageLocked = false;
			startCarDamage = 0;
			log(L"Player has changed the car; Engine damage unlocked");
		}
	}

	currLastCarOld = currLastCar;

}

struct SPAWNCAR {
	CAR_MODEL model;
	MainWindow* win;
};

UINT SpawnCarThread(LPVOID data)
{
	S10* s10 = (S10*)*(DWORD*)0x00672f40;
	SPAWNCAR* info = (SPAWNCAR*)data;
	Ped* playerPed = fnGetPedByID(1);

	if (*(DWORD*)ptrToPedManager == 0) {
		//info->win->log(L"ptrToPedManager isn't set. Not in a game probably.");
		return 0;
	}

	if (!playerPed->currentCar)
	{
		//info->win->log(L"The car will be spawned in 3 secs on front of you");



		if (!playerPed || !playerPed->pedSprite || !playerPed->pedSprite->actualPosition) {
			//info->win->log(L"Cannot find ped location");
			return 0;
		}

		//info->win->log(L"Player ped -> %08X", playerPed);


		//info->win->log(L"Spawn %d", info->model);
		double nAngle = playerPed->pedSprite->actualPosition->rotation / 4.0 + 270.0;
		const double distance = 1;
		Car* car = fnSpawnCar(
			playerPed->pedSprite->actualPosition->x + (int)(cos(nAngle * (M_PI / 180.0)) * distance * 16384.0),
			playerPed->pedSprite->actualPosition->y - (int)(sin(nAngle * (M_PI / 180.0)) * distance * 16384.0),
			playerPed->pedSprite->actualPosition->z,
			180 * 4,
			info->model
		);
		if (car) {
			//info->win->log(L"The car spawned at 0x%08X", car);
			fnShowBigOnScreenLabel(&s10->ptrToSomeStructRelToBIG_LABEL, 0, (WCHAR*)L"Car is here!", 10);
		}
		delete info;
		return 0;
	}
	else
	{
	}
	return 0;
}


void MainWindow::OnSpawncarTank()
{
	SPAWNCAR *info = new SPAWNCAR;
	info->win = this;
	info->model = TANK;
	::CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SpawnCarThread, info, 0, 0);
}


void MainWindow::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	//log(L"OnHotKey(%X, %X, %X)", nHotKeyId, nKey1, nKey2);
	switch (nKey2)
	{
	case 0x54:
		OnSpawncarTank();
		break;
	case 0x47:
		OnSpawncarGt();
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
		NextHuman();
		break;
	default:
		break;
	}

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}


void MainWindow::OnSpawncarGt()
{
	SPAWNCAR* info = new SPAWNCAR;
	info->win = this;
	info->model = GT24640;
	::CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SpawnCarThread, info, 0, 0);
}


void MainWindow::OnSpawnCarClick(UINT nID) {
	log(L"Car 3%d spawned", nID);

	SPAWNCAR* info = new SPAWNCAR;
	info->win = this;
	info->model = (CAR_MODEL)(nID - 35000);
	::CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SpawnCarThread, info, 0, 0);
}

void MainWindow::OnGetWeaponClick(UINT nID) {
	log(L"Weapon #%d got", nID - 45000);

	Ped* playerPed = fnGetPedByID(1);

	if (playerPed)
	{
		UINT ID = nID - 45000;
		playerPed->playerWeapons->weapons[ID]->ammo += 100;
		
	}
	else
	{
		log(L"Player ped not found :c");
	}
}

void MainWindow::OnPlayVocalClick(UINT nID) {
	log(L"Vocal #%d played", nID - 55000);
	fnPlayVocal((DWORD*)0x005d85a0, 0, (VOCAL)(nID - 55000));
}

void MainWindow::OnSpawncarGunjeep()
{
	SPAWNCAR* info = new SPAWNCAR;
	info->win = this;
	info->model = GUNJEEP;
	::CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SpawnCarThread, info, 0, 0);
}

void MainWindow::CarEngineOff()
{
	if (currLastCar)
	{
		currLastCar->engineState = CAR_ENGINE_STATE(TURNING_OFF);
		log(L"Engine turned off");
	}
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
	if (noReloads) log(L"No reloads enabled");
	else           log(L"No reloads disabled");

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

void MainWindow::SetStars0()
{
	fnGetPedByID(1)->copValue = 0;
	startCopValue = 0;
	log(L"0 stars you looser!");
}

void MainWindow::SetStars1()
{
	fnGetPedByID(1)->copValue = 600;
	startCopValue = 600;
	log(L"1 star");
}

void MainWindow::SetStars2()
{
	fnGetPedByID(1)->copValue = 1600;
	startCopValue = 1600;
	log(L"2 stars");
}

void MainWindow::SetStars3()
{
	fnGetPedByID(1)->copValue = 3000;
	startCopValue = 3000;
	log(L"3 stars");
}

void MainWindow::SetStars4()
{
	fnGetPedByID(1)->copValue = 5000;
	startCopValue = 5000;
	log(L"4 stars");
}

void MainWindow::SetStars5()
{
	fnGetPedByID(1)->copValue = 8000;
	startCopValue = 8000;
	log(L"5 stars");
}

void MainWindow::SetStars6()
{
	fnGetPedByID(1)->copValue = 12000;
	startCopValue = 12000;
	log(L"6 stars");
}

void MainWindow::TpToLastCar()
{
	Ped* playerPed = fnGetPedByID(1);

	if (currLastCar && playerPed && playerPed->pedSprite)
	{
		playerPed->pedSprite->actualPosition->x = currLastCar->position->x;
		playerPed->pedSprite->actualPosition->y = currLastCar->position->y;
		playerPed->pedSprite->actualPosition->z = currLastCar->position->z + 10;
	}
}

void MainWindow::GiveUnlimitedAmmo()
{
	Ped* playerPed = fnGetPedByID(1);

	if (playerPed->selectedWeapon)
	{
		playerPed->selectedWeapon->ammo = -1;
		log(L"Unlimited ammo given");
	}
	else
	{
		log(L"Unlimited hands? Get a weapon first");
	}
}

void MainWindow::FixCar()
{
	if (currLastCar)
	{
		currLastCar->carDamage = 0;
		startCarDamage = 0;
	}
}

void MainWindow::VisFixCar()
{
	if (currLastCar)currLastCar->carLights = CAR_LIGHTS_AND_DOORS_BITSTATE(0x800040);
}

void MainWindow::VisBreakCar()
{
	if (currLastCar)currLastCar->carLights = CAR_LIGHTS_AND_DOORS_BITSTATE(4294967295);
}

void MainWindow::PlayerImmortal()
{
	playerImmortal = !playerImmortal;

	if (playerImmortal)
	{
		fnGetPedByID(1)->Invulnerability = 9999;
		log(L"Invulnerability enabled");
	}
	else
	{
		fnGetPedByID(1)->Invulnerability = 1;
		log(L"Invulnerability disabled");
	}
}

void MainWindow::PedInfo()
{
	WCHAR buf[256];
	if (*(DWORD*)ptrToPedManager == 0) {
		return;
	}

	Ped* playerPed = fnGetPedByID(1);

	if (playerPed)
	{
		if (pedHOld != playerPed->health)
		{
			m_pedHealth.SetWindowTextW(L"0");
			swprintf(buf, 256, L"%d", playerPed->health);
			m_pedHealth.SetWindowTextW(buf);
		}
		
		if (pedAOld != *(int*)(*(DWORD*)(*(DWORD*)0x005eb4fc + 0x4) + 0x6fa)) //TEMPONARY; when i learn how to use Ghirda, i'll fix that xD
		{
			m_pedArmor.SetWindowTextW(L"0");
			swprintf(buf, 256, L"%d", *(int*)(*(DWORD*)(*(DWORD*)0x005eb4fc + 0x4) + 0x6fa)); //TEMPONARY; when i learn how to use Ghirda, i'll fix that xD
			m_pedArmor.SetWindowTextW(buf);
		}

		if (pedMOld != *(int*)(*(DWORD*)(*(DWORD*)0x005eb4fc + 0x38) + 0x2d4)) //TEMPONARY; when i learn how to use Ghirda, i'll fix that xD
		{
			m_pedMoney.SetWindowTextW(L"0");
			swprintf(buf, 256, L"%d", *(int*)(*(DWORD*)(*(DWORD*)0x005eb4fc + 0x38) + 0x2d4)); //TEMPONARY; when i learn how to use Ghirda, i'll fix that xD
			m_pedMoney.SetWindowTextW(buf);
		}

		pedHOld = playerPed->health;
		pedAOld = *(int*)(*(DWORD*)(*(DWORD*)0x005eb4fc + 0x4) + 0x6fa);
		pedMOld = *(int*)(*(DWORD*)(*(DWORD*)0x005eb4fc + 0x38) + 0x2d4);

		int Pvalue = playerPed->copValue;

		if(Pvalue <600) swprintf(buf, 256, L"%d (0) Peace", Pvalue);
		else if (Pvalue < 1600)  swprintf(buf, 256, L"%d (1) Lite", Pvalue);
		else if (Pvalue < 3000) swprintf(buf, 256, L"%d (2) All units", Pvalue);
		else if (Pvalue < 5000)  swprintf(buf, 256, L"%d (3) Barricades", Pvalue);
		else if (Pvalue < 8000) swprintf(buf, 256, L"%d (4) SWAT", Pvalue);
		else if (Pvalue < 12000) swprintf(buf, 256, L"%d (5) FBI", Pvalue);
		else swprintf(buf, 256, L"%d (6) Army!", Pvalue);

		m_pedCopLevel.SetWindowTextW(buf);

		if (currLastCar && !currLastCar->position) currLastCar = 0; //without this the game crashes after some missions and after WCB

		if (currLastCar)
		{
			swprintf(buf, 256, L"%d", currLastCar->carDamage);
			m_carDamage.SetWindowTextW(buf);

			swprintf(buf, 256, L"%d", currLastCar->id);
			m_carID.SetWindowTextW(buf);

			currLastCarXYShift = (int)sqrt(pow(currLastCar->position->x - currLastCarXOld, 2) + pow(currLastCar->position->y - currLastCarYOld, 2));
			currLastCarXOld = currLastCar->position->x;
			currLastCarYOld = currLastCar->position->y;
			swprintf(buf, 256, L"%d", currLastCarXYShift);
			m_carVelocity.SetWindowTextW(buf);

			if (currLastCar->position)
			{
				swprintf(buf, 256, L"%d", currLastCar->position->carColor);
				m_carColor.SetWindowTextW(buf);
			}
			
		}

		int* gangresp;
		DWORD* gangsArr = (DWORD*)0x005eb898;

		for (int i = 0; i < 3; i++)
		{
			gangresp = (int*)*gangsArr + 0x47 + i * 0x51;
			
			swprintf(buf, 256, L"%d", *gangresp);
			m_gangRespect[i].SetWindowTextW(buf);
		}
		
		

		if (playerPed->currentCar)
		{
			swprintf(buf, 256, L"%.2f", playerPed->currentCar->position->x / 16384.0);
			m_pedX.SetWindowTextW(buf);

			swprintf(buf, 256, L"%.2f", playerPed->currentCar->position->y / 16384.0);
			m_pedY.SetWindowTextW(buf);

			swprintf(buf, 256, L"%.2f", playerPed->currentCar->position->z / 16384.0);
			m_pedZ.SetWindowTextW(buf);

			swprintf(buf, 256, L"%d", playerPed->currentCar->position->rotation);
			m_pedRot.SetWindowTextW(buf);

			swprintf(buf, 256, L"%X", playerPed->currentCar->carLights);
			m_carVisualData.SetWindowTextW(buf);
			

		}
		else
		{
			if (!playerPed->pedSprite || !playerPed->pedSprite->actualPosition) {

				m_pedX.SetWindowTextW(L"");
				m_pedY.SetWindowTextW(L"");
				m_pedZ.SetWindowTextW(L"");
				m_pedRot.SetWindowTextW(L"");
				

			}
			else
			{
				if (playerPed->pedSprite->actualPosition->x != pedXOld)
				{
					swprintf(buf, 256, L"%.2f", playerPed->pedSprite->actualPosition->x / 16384.0);
					m_pedX.SetWindowTextW(buf);
					
				}
				
				if (playerPed->pedSprite->actualPosition->y != pedYOld)
				{
					swprintf(buf, 256, L"%.2f", playerPed->pedSprite->actualPosition->y / 16384.0);
					m_pedY.SetWindowTextW(buf);
					
				}

				if (playerPed->pedSprite->actualPosition->z != pedZOld)
				{
					swprintf(buf, 256, L"%.2f", playerPed->pedSprite->actualPosition->z / 16384.0);
					m_pedZ.SetWindowTextW(buf);
					
				}

				if (playerPed->pedSprite->actualPosition->rotation != pedRotOld)
				{
					swprintf(buf, 256, L"%d", playerPed->pedSprite->actualPosition->rotation);
					m_pedRot.SetWindowTextW(buf);

				}

				pedXOld = playerPed->pedSprite->actualPosition->x;
				pedYOld = playerPed->pedSprite->actualPosition->y;
				pedZOld = playerPed->pedSprite->actualPosition->z;
				pedRotOld = playerPed->pedSprite->actualPosition->rotation;
			}
		}

	}
	
	/*int weaponID = (playerPed->selectedWeapon - &playerPed->playerWeapons->weapons[0]->ammo) / 48*/;
	///int* selectedWeapon = (int*)0x1F3CC4;
	int weapSTART = reinterpret_cast<int>(&playerPed->playerWeapons->weapons[0]->ammo);
	int weapCURR = reinterpret_cast<int>(&playerPed->selectedWeapon->ammo);
	int weapID = (weapCURR - weapSTART) / 48;
	swprintf(buf, 256, L"%d", weapID);

	if (weapID >= 0) m_pedSType.SetWindowTextW(buf);
	else m_pedSType.SetWindowTextW(L"");	

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
	
}

void MainWindow::TeleportAllPeds()
{
	int* nextpedid = (int*)0x591e84;
	Ped* currentPed;
	Ped* playerPed = fnGetPedByID(1);
	if (playerPed && playerPed->pedSprite)
	{
		for (int i = 1; i < *nextpedid; i++)
		{
			currentPed = fnGetPedByID(i);

			if (currentPed && currentPed->pedSprite)
			{
				currentPed->pedSprite->actualPosition->x = playerPed->pedSprite->actualPosition->x;
				currentPed->pedSprite->actualPosition->y = playerPed->pedSprite->actualPosition->y;
				currentPed->pedSprite->actualPosition->z = playerPed->pedSprite->actualPosition->z;
			}
		}
		log(L"Teleported");
	}
	else log(L"Player ped not found :c");
}

void MainWindow::BeAHuman()
{
	Ped* playerPed = fnGetPedByID(1);

	if (beAHuman)
	{
		beAHuman = false;
		log(L"You are no longer a human");

		playerPed->pedSprite->actualPosition->x = pedXPreHuman;
		playerPed->pedSprite->actualPosition->y = pedYPreHuman;
		playerPed->pedSprite->actualPosition->z = pedZPreHuman;


	}
	else if (playerPed && playerPed->pedSprite)
	{
		beAHuman = true;
		log(L"Congratulations! You are a human now");
		log(L"You can change your identity by pressing ALT + N");

		pedXPreHuman = playerPed->pedSprite->actualPosition->x;
		pedYPreHuman = playerPed->pedSprite->actualPosition->y;
		pedZPreHuman = playerPed->pedSprite->actualPosition->z;

		NextHuman();
	}
	else
	{
		log(L"Player ped not found");
		((CButton*)GetDlgItem(IDC_BEAHUMAN))->SetCheck(false);
	}
}

void MainWindow::NextHuman()
{
	if (beAHuman)
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

			if (currentPed && currentPed->pedSprite)
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

				if (currentPed && currentPed->pedSprite)
				{
					newSelectedPed = currentPed;
					break;
				}

			}
		}

		selectedPed = newSelectedPed;

		if (selectedPed != nullptr) {
			log(L"You're now the ped #%d", selectedPed->id);
		}
	}
	
}

void MainWindow::GangRespect(UINT nID)
{
	DWORD* gangsArr = (DWORD*)0x005eb898;
	int gangNo;
	int dataInt = (int)nID - 3040;

	if (dataInt >= 0 && dataInt <= 2) gangNo = 0;
	if (dataInt >= 3 && dataInt <= 5) gangNo = 1;
	if (dataInt >= 6 && dataInt <= 8) gangNo = 2;

	int* gangresp;
	gangresp = (int*)*gangsArr + 0x47 + gangNo * 0x51;

	if (dataInt == 0 || dataInt == 3 || dataInt == 6) *gangresp -= 20;
	if (dataInt == 1 || dataInt == 4 || dataInt == 7) *gangresp = 0;
	if (dataInt == 2 || dataInt == 5 || dataInt == 8) *gangresp += 20;
	
	log(L"Changed the respect to %d", *gangresp);
}

void MainWindow::CarColorPlus()
{
	if (currLastCar && currLastCar->position)
	{
		currLastCar->position->lockPalleteMaybe = 3;

		currLastCar->position->carColor++;
		if (currLastCar->position->carColor >35) currLastCar->position->carColor = 0;
	}
}

void MainWindow::CarColorMinus()
{
	if (currLastCar && currLastCar->position)
	{
		currLastCar->position->lockPalleteMaybe = 3;

		currLastCar->position->carColor--;
		if (currLastCar->position->carColor <0) currLastCar->position->carColor = 35;
	}
}

void MainWindow::CarColorReset()
{
	currLastCar->position->lockPalleteMaybe = 2;
	currLastCar->position->carColor = 0;
}

void MainWindow::ShowIDs()
{
	showIDs = (bool*)0x5EADA1;
	*showIDs = !*showIDs;

	if (*showIDs) log(L"IDs shown!");
	else log(L"IDs hidden!");
}

void MainWindow::ShowCounters()
{
	showCounters = (bool*)0x5EAD95;
	*showCounters = !*showCounters;

	if (*showCounters) log(L"Counters shown!");
	else log(L"Counters hidden!");
}

void MainWindow::KeepWeapons()
{
	keepWeapons = (bool*)0x5EAD9E;
	*keepWeapons = !*keepWeapons;

	if (*keepWeapons) log(L"Weapons will be kept!");
	else log(L"Weapons won't be kept!");
}

void MainWindow::FreeShopping()
{
	TrafficManager* trafficManager = (TrafficManager*)*(DWORD*)0x005e4ca4;
	trafficManager->do_free_shoping = !trafficManager->do_free_shoping;
	//log(L"%d, %d", carManagerPointer, carManager);

	if (trafficManager->do_free_shoping) log(L"Free shopping enabled!");
	else log(L"Free shopping disabled!");
}

void MainWindow::GoSlow()
{
	walkingSpeed = (int*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)0x05e3cc4 + 0x34) + 0x168) + 0x80) + 0x8) + 0x3c); //Temponary; when i learn how to use Ghirda, i'll fix that xD

	*walkingSpeed = 256 * (1024 / *walkingSpeed);
	if (*walkingSpeed == 256) log(L"Slow walking enabled");
	if (*walkingSpeed == 1024) log(L"Slow walking disabled");
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

}

void MainWindow::TeleportPlayer()
{
	Ped* playerPed = fnGetPedByID(1);
	CString buffer;

	if (playerPed->pedSprite && playerPed->pedSprite->actualPosition)
	{
		m_pedX.GetWindowTextW(buffer);
		fesetround(FE_TONEAREST);
		playerPed->pedSprite->actualPosition->x = (int)(_wtof(buffer) * 16384.0);

		m_pedY.GetWindowTextW(buffer);
		playerPed->pedSprite->actualPosition->y = (int)(_wtof(buffer) * 16384.0);

		m_pedZ.GetWindowTextW(buffer);
		playerPed->pedSprite->actualPosition->z = (int)(_wtof(buffer) * 16384.0) + 10;

		log(L"Player teleported to %f, %f, %f!", ((float)playerPed->pedSprite->actualPosition->x)/16384.0f, ((float)playerPed->pedSprite->actualPosition->y) / 16384.0f, ((float)playerPed->pedSprite->actualPosition->z) / 16384.0f);

	}
	else
	{
		log(L"Couldn't teleport; player is in the car or something :/");
	}
}

void MainWindow::OnGTADraw()
{

}

void MainWindow::OnGTAGameTick(Game* game)
{
	//OnTimer moved here, it's more stable now
	CopLockETC();
	PedInfo();
	if (captureMouse) CaptureMouse();
}

void MainWindow::NewFunction()
{
	// You can add anything here to test it and then press ALT+D ingame to run the code :)
	void* _this = (void*)0x005d85a0;
/*
	static BOOL once = false;
	if (!once) {
		once = true;
		return;
	}
*/
	fnPlayVocal(_this, 0, VOCAL_BACK_TO_FRONT_BONUS);
}