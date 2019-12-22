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

// MainWindow dialog

IMPLEMENT_DYNAMIC(MainWindow, CDialogEx)

MainWindow::MainWindow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	
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
}


BEGIN_MESSAGE_MAP(MainWindow, CDialogEx)
	ON_BN_CLICKED(IDOK, &MainWindow::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &MainWindow::OnBnClickedCancel)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_COMMAND(ID_DEBUG_MAKEINT3CRASHTOATTACHDEBUGGER, &MainWindow::OnDebugMakeInt3Crash)
	ON_COMMAND(ID_COMMANDS_HELLO, &MainWindow::OnCommandsHello)
	ON_COMMAND(ID_COMMANDS_CAPTUREMOUSE, &MainWindow::OnCommandsCaptureMouse)
	ON_COMMAND(ID_SPAWNCAR_TANK, &MainWindow::OnSpawncarTank)
	ON_WM_HOTKEY()
	ON_COMMAND(ID_SPAWNCAR_GT, &MainWindow::OnSpawncarGt)
	ON_COMMAND_RANGE(35000, 35000 + 83, &OnSpawnCarClick)
	ON_COMMAND_RANGE(45000, 45000 + 10, &OnGetWeaponClick)
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
	ON_BN_CLICKED(IDC_PEDIDS, &MainWindow::ShowPedIDs)
	ON_BN_CLICKED(IDC_LOCKCOPLEVEL, &MainWindow::LockStars)
	ON_BN_CLICKED(IDC_PEDS0TIME, &MainWindow::NoReloads)
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

	//weapons.insert(std::pair<std::wstring, DWORD>(L"CAR UZI", 29));
	//weapons.insert(std::pair<std::wstring, DWORD>(L"CAR MINES", 37));
	//weapons.insert(std::pair<std::wstring, DWORD>(L"OIL", 38));
	//weapons.insert(std::pair<std::wstring, DWORD>(L"CAR BOMB", 45));

	for (itr = weapons.begin(); itr != weapons.end(); ++itr) {
		wMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 45000), itr->first.c_str());
	}

	menu->AppendMenuW(MF_POPUP, (UINT_PTR)wMenu->m_hMenu, L"Get weapon");

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


void MainWindow::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent) {
	case TIMER_CAPTURE_MOUSE:
		if (captureMouse) {
			CaptureMouse();
		}
		CopLockETC();
		break;
	case TIMER_PED_INFO:
		PedInfo();
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void MainWindow::OnDebugMakeInt3Crash()
{
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

//Save* __thiscall Game::GetSaveSlotByIndex(Game* this, byte index);
typedef Save* (__fastcall GetSaveSlotByIndex)(Game* game, DWORD edx, byte index);
GetSaveSlotByIndex* fnGetSaveSlotByIndex = (GetSaveSlotByIndex*)0x004219e0;

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
	}
	
}

struct SPAWNCAR {
	CAR_MODEL model;
	MainWindow* win;
};

UINT SpawnCarThread(LPVOID data)
{
	SPAWNCAR* info = (SPAWNCAR*)data;
	if (*(DWORD*)ptrToPedManager == 0) {
		//info->win->log(L"ptrToPedManager isn't set. Not in a game probably.");
		return 0;
	}

	//info->win->log(L"The car will be spawned in 3 secs on front of you");

	S10* s10 = (S10*) * (DWORD*)0x00672f40;

	Ped* playerPed = fnGetPedByID(1);

	if (!playerPed || playerPed->currentCar || !playerPed->pedSprite || !playerPed->pedSprite->actualPosition) {
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


void MainWindow::OnSpawncarTank()
{
	SPAWNCAR *info = new SPAWNCAR;
	info->win = this;
	info->model = TANK;
	::CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SpawnCarThread, info, 0, 0);
}


void MainWindow::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	log(L"OnHotKey(%X, %X, %X)", nHotKeyId, nKey1, nKey2);
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
		
		//playerPed->selectedWeapon = (WEAPON_STRUCT*)&playerPed->playerWeapons->weapons[ID];
	}
	else
	{
		log(L"Where the fuck is the ped?!?");
	}
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
	Ped* playerPed = fnGetPedByID(1);

	if (playerPed->currentCar)
	{
		playerPed->currentCar->engineState = CAR_ENGINE_STATE(TURNING_OFF);
		log(L"Engine turned off");
	}
	else
	{
		log(L"Do you want to stop your heart or something? Find a car first");
	}
}

void MainWindow::LockStars()
{
	starsLocked = !starsLocked;
	startCopValue = fnGetPedByID(1)->copValue;
	if(starsLocked) log(L"Cop level locked");
	else            log(L"Cop level unlocked");
	 
}

void MainWindow::NoReloads()
{
	noReloads = !noReloads;
	if (noReloads) log(L"No reloads enabled");
	else           log(L"No reloads disabled");

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

void MainWindow::DetonateLastCar()
{
	
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
	if (fnGetPedByID(1)->currentCar) fnGetPedByID(1)->currentCar->carDamage = 0;
	else log(L"Does people have engines? Player not in the car");
}

void MainWindow::VisFixCar()
{
	if (fnGetPedByID(1)->currentCar) fnGetPedByID(1)->currentCar->carLights = CAR_LIGHTS_AND_DOORS_BITSTATE(0x800040);
	else log(L"Maybe you need a plastic surgery? Player not in the car");
}

void MainWindow::ShowPedIDs()
{
	
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
		int Pvalue = playerPed->copValue;

		if(Pvalue <600) swprintf(buf, 256, L"%d (0) Peace", Pvalue);
		else if (Pvalue < 1600)  swprintf(buf, 256, L"%d (1) Lite", Pvalue);
		else if (Pvalue < 3000) swprintf(buf, 256, L"%d (2) All units", Pvalue);
		else if (Pvalue < 5000)  swprintf(buf, 256, L"%d (3) Barricades", Pvalue);
		else if (Pvalue < 8000) swprintf(buf, 256, L"%d (4) SWAT", Pvalue);
		else if (Pvalue < 12000) swprintf(buf, 256, L"%d (5) FBI", Pvalue);
		else swprintf(buf, 256, L"%d (6) Army!", Pvalue);

		m_pedCopLevel.SetWindowTextW(buf);

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

			swprintf(buf, 256, L"%d", playerPed->currentCar->carDamage);
			m_carDamage.SetWindowTextW(buf);
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
				swprintf(buf, 256, L"%.2f", playerPed->pedSprite->actualPosition->x / 16384.0);
				m_pedX.SetWindowTextW(buf);

				swprintf(buf, 256, L"%.2f", playerPed->pedSprite->actualPosition->y / 16384.0);
				m_pedY.SetWindowTextW(buf);

				swprintf(buf, 256, L"%.2f", playerPed->pedSprite->actualPosition->z / 16384.0);
				m_pedZ.SetWindowTextW(buf);

				swprintf(buf, 256, L"%d", playerPed->pedSprite->actualPosition->rotation);
				m_pedRot.SetWindowTextW(buf);

				m_carDamage.SetWindowTextW(L"");
			}
		}

	}
	
	/*int weaponID = (playerPed->selectedWeapon - &playerPed->playerWeapons->weapons[0]->ammo) / 48*/;
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
