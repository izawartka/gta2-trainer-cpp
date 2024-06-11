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

// MainWindow dialog
BOOL HookFunction(const DWORD originalFn, DWORD hookFn, size_t copyBytes = 5);

MainWindow* mainWnd = nullptr;

BOOL HookFunction(const DWORD originalFn, DWORD hookFn, size_t copyBytes) {
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

	// OutputDebugStringA("gameTick\n");
	mainWnd->OnGTAGameTick((Game*)*(DWORD*)ptrToGame);

	__asm {
		MOV EAX, pGameTick
		add eax, 5
		JMP EAX
	}

}

static __declspec(naked) void drawChat(void) {
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

	// OutputDebugStringA("draw\n");
	mainWnd->OnGTADraw();

	__asm {
		mov eax, pDrawChat
		add eax, 5
		jmp eax
	}

}

IMPLEMENT_DYNAMIC(MainWindow, CDialogEx)

MainWindow::MainWindow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	mainWnd = this;

	Game* pGame = (Game*)*(DWORD*)ptrToGame;

	m_acsWindow = new ACSWindow();
	m_acsWindow->Create(IDD_ACS, this);
	m_acsWindow->m_mainWindow = this;

	m_pedSpawnerWindow = new PedSpawnerWindow();
	m_pedSpawnerWindow->Create(IDD_PS, this);
	m_pedSpawnerWindow->m_mainWindow = this;

	m_liveTableWindow = new LiveTableWindow();
	m_liveTableWindow->Create(IDD_LT, this);
	m_liveTableWindow->m_mainWindow = this;

	HookFunction(pGameTick, (DWORD)gameTick);
	//HookFunction(pDrawChat, (DWORD)drawChat, 7);
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
	DDX_Check(pDX, IDC_PASSENGER, m_enterAsPassenger);
}


BEGIN_MESSAGE_MAP(MainWindow, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &MainWindow::OnBnClickedExit)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_COMMAND(ID_COMMANDS_HELLO, &MainWindow::OnCommandsHello)
	ON_COMMAND(ID_COMMANDS_HIJACKATRAIN, &MainWindow::HijackTrain)
	ON_COMMAND(IDC_MOUSECTRL, &MainWindow::MouseControl)
	ON_COMMAND(ID_COMMANDS_TANK, &MainWindow::OnSpawnCarTank)
	ON_COMMAND(ID_COMMANDS_LIVETABLE, &MainWindow::OnShowLiveTable)
	ON_WM_HOTKEY()
	ON_COMMAND_RANGE(ID_SPAWNCAR, ID_SPAWNOBJ - 1, &OnSpawnCarMenuClick)
	ON_COMMAND_RANGE(ID_SPAWNOBJ, ID_SPAWNPED - 1, &OnSpawnObjectMenuClick)
	ON_COMMAND_RANGE(ID_SPAWNPED, ID_GETWEAP - 1, &OnSpawnPedMenuClick)
	ON_COMMAND_RANGE(ID_GETWEAP, ID_GETCARWEAP - 1, &OnGetWeaponMenuClick)
	ON_COMMAND_RANGE(ID_GETCARWEAP, ID_VOCALS - 1, &OnGetCarWeaponMenuClick)
	ON_COMMAND_RANGE(ID_VOCALS, ID_NATIVE - 1, &OnPlayVocalMenuClick)
	ON_COMMAND_RANGE(ID_NATIVE, ID_NATIVE + 256, &OnNativeCheatMenuClick)
	ON_COMMAND(ID_COMMANDS_GUNJEEP, &MainWindow::OnSpawnCarGunjeep)
	ON_BN_CLICKED(IDC_CARENGINEOFF, &MainWindow::CarEngineOff)
	ON_BN_CLICKED(IDC_UNLMAMMO, &MainWindow::GiveUnlimitedAmmo)
	ON_COMMAND_RANGE(IDC_STAR0, IDC_STAR6, &SetStars)
	ON_BN_CLICKED(IDC_CARFIX, &MainWindow::FixCar)
	ON_BN_CLICKED(IDC_CARVISFIX, &MainWindow::VisFixCar)
	ON_BN_CLICKED(IDC_CARVISBRK, &MainWindow::VisBreakCar)
	ON_BN_CLICKED(IDC_LOCKCOPLEVEL, &MainWindow::LockStars)
	ON_BN_CLICKED(IDC_LOCKCARDAMAGE, &MainWindow::LockCarDamage)
	ON_BN_CLICKED(IDC_PEDS0TIME, &MainWindow::NoReloads)
	ON_BN_CLICKED(IDC_CARLASTTP, &MainWindow::TpToLastCar)
	ON_BN_CLICKED(IDC_CARINFO, &MainWindow::PrintCarInfo)
	ON_BN_CLICKED(IDC_PEDIMMORT, &MainWindow::PlayerImmortal)
	ON_BN_CLICKED(ID_COMMANDS_TPALLPEDS, &MainWindow::TeleportAllPeds)
	ON_COMMAND_RANGE(3040, 3048, &GangRespect)
	ON_COMMAND_RANGE(3075, 3078, &ToggleDoor)
	ON_BN_CLICKED(IDC_FREESHOP, &MainWindow::FreeShopping)
	ON_BN_CLICKED(IDC_BEAHUMAN, &MainWindow::WatchPeds)
	ON_BN_CLICKED(IDC_TPPLAYER, &MainWindow::TeleportPlayer)
	ON_BN_CLICKED(IDC_EMBP, &MainWindow::CarEmblemPlus)
	ON_BN_CLICKED(IDC_EMBM, &MainWindow::CarEmblemMinus)
	ON_BN_CLICKED(IDC_CARCOLP, &MainWindow::CarColorPlus)
	ON_BN_CLICKED(IDC_CAREXPLODE, &MainWindow::CarExplode)
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
	ON_BN_CLICKED(ID_COMMANDS_EXPLODECARS, &MainWindow::ExplodeCars)
	ON_BN_CLICKED(IDC_PASSENGER, &MainWindow::OnEnterAsPassengerToggle)
END_MESSAGE_MAP()

// Close GTA2 on Trainer exit
void MainWindow::OnBnClickedExit()
{
	if (m_gtaWindow) {
		::DestroyWindow(m_gtaWindow);
		::exit(0);
	}
}

void MainWindow::AddCategorizedMenuItems(
	CMenu* menu, 
	const LPCTSTR* categories, 
	uint categoriesCount, 
	const CatMenuItem* items, 
	uint itemsCount,
	UINT_PTR baseID
)
{
	CMenu** cMenus = new CMenu * [categoriesCount];
	for (int i = 0; i < categoriesCount; i++) {
		cMenus[i] = new CMenu();
		cMenus[i]->CreatePopupMenu();
		menu->AppendMenuW(MF_POPUP, (UINT_PTR)cMenus[i]->m_hMenu, (LPCTSTR)categories[i]);
	}

	for (int i = 0; i < itemsCount; i++) {
		CatMenuItem info = items[i];
		cMenus[info.category]->AppendMenuW(MF_STRING, (UINT_PTR)(info.id + baseID), info.name);
	}
}

void MainWindow::AddMenuItems(
	CMenu* menu,
	const MenuItem* items,
	uint itemsCount,
	UINT_PTR baseID
)
{
	for (int i = 0; i < itemsCount; i++) {
		MenuItem info = items[i];
		menu->AppendMenuW(MF_STRING, (UINT_PTR)(info.id + baseID), info.name);
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

	RegisterHotKey(
		GetSafeHwnd(),
		1,
		MOD_ALT | MOD_NOREPEAT,
		0x45); //ALT+E

	RegisterHotKey(
		GetSafeHwnd(),
		1,
		MOD_ALT | MOD_NOREPEAT,
		0x42); //ALT+B

	RegisterHotKey(
		GetSafeHwnd(),
		1,
		MOD_ALT | MOD_NOREPEAT,
		0x57); //ALT+W

	CMenu *menu = GetMenu();
	std::map<std::wstring, DWORD>::iterator itr;

	// Create the "Spawn car" menu

	CMenu* carMenu = menu->GetSubMenu(1)->GetSubMenu(0);
	AddCategorizedMenuItems(
		carMenu, 
		carsCategories, 
		sizeof(carsCategories)/sizeof(carsCategories[0]), 
		cars, 
		sizeof(cars) / sizeof(cars[0]), 
		ID_SPAWNCAR_START
	);
	this->carHMenu = carMenu->m_hMenu;

	// Create the "Spawn object" menu

	CMenu* objMenu = menu->GetSubMenu(1)->GetSubMenu(1);
	AddCategorizedMenuItems(
		objMenu, 
		objectsCategories, 
		sizeof(objectsCategories) / sizeof(objectsCategories[0]), 
		objects, 
		sizeof(objects) / sizeof(objects[0]), 
		ID_SPAWNOBJ_START
	);
	this->objHMenu = objMenu->m_hMenu;

	// Create the "Get weapon" menu

	CMenu* weapMenu = menu->GetSubMenu(2);
	AddMenuItems(weapMenu, weapons, sizeof(weapons) / sizeof(weapons[0]), ID_GETWEAP_START);

	// Create the "Get car weapon" menu

	CMenu* carWeapMenu = new CMenu();
	carWeapMenu->CreatePopupMenu();
	AddMenuItems(carWeapMenu, carWeapons, sizeof(carWeapons) / sizeof(carWeapons[0]), ID_GETCARWEAP_START);
	AppendMenu(menu->m_hMenu, MF_POPUP, (UINT_PTR)carWeapMenu->m_hMenu, L"Get car weapon");

	// Create the "Play vocal" menu
	
	CMenu* vocalsMenu = new CMenu();
	vocalsMenu->CreatePopupMenu();
	AddMenuItems(vocalsMenu, vocals, sizeof(vocals) / sizeof(vocals[0]), ID_VOCALS_START);
	AppendMenu(menu->m_hMenu, MF_POPUP, (UINT_PTR)vocalsMenu->m_hMenu, L"Play vocal");
	
	// Create the "Native cheats" menu

	CMenu* nativeCheatsMenu = new CMenu();
	nativeCheatsMenu->CreatePopupMenu();
	AddMenuItems(nativeCheatsMenu, nativeCheats, sizeof(nativeCheats) / sizeof(nativeCheats[0]), ID_NATIVE_START);
	AppendMenu(menu->m_hMenu, MF_POPUP, (UINT_PTR)nativeCheatsMenu->m_hMenu, L"Native cheats");
	this->ncHMenu = nativeCheatsMenu->m_hMenu;

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

	// we want to set target door only once per entering
	// so if they're blocked, ped will choose another one
	if (m_enterAsPassenger && playerPed->enterCarAsPassenger == 0) {
		playerPed->enterCarAsPassenger = 1;
		playerPed->targetCarDoor = 1;
	}

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
		for (int i = 0; i < sizeof(emblems)/sizeof(emblems[0]); i++)
		{
			currLastCarEmblem = getCarRoofWithSpriteIfExists(currLastCar->roof, emblems[i].id);
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

	if (object)
	{
		log(L"Object 0x%X spawned!", object);
	}

	wtSpawnObject = -1;

}

// Object spawning menu
void MainWindow::OnSpawnObjectMenuClick(UINT nID) {

	if(nID == ID_SPAWNOBJ_LAST)
	{
		if (lastSpawnedObjectType == -1)
			return;

		wtSpawnObject = lastSpawnedObjectType;
		return;
	}
	
	wtSpawnObject = nID - ID_SPAWNOBJ_START;
	lastSpawnedObjectType = wtSpawnObject;
	EnableMenuItem(objHMenu, ID_SPAWNOBJ_LAST, MF_ENABLED);
}

// Called evey game tick and only then
void MainWindow::SafeSpawnCars(WantToSpawn wtsArray[128], int* wtsArraySize)
{
	while (*wtsArraySize > 0)
	{
		(*wtsArraySize)--;
		WantToSpawn currentWTS = wtsArray[*wtsArraySize];

		// coordinates check
		if (!IsPointSafe(currentWTS.x, currentWTS.y, currentWTS.z)) {
			log(L"Target position is out of the map");
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
			
			short color = currentWTS.color;
			if (color != -1) {
				car->sprite->lockPalleteMaybe = 3;
				car->sprite->carColor = (color == -2) ? rand() % 36 : color;
			}
		}
	}
}

// Car spawning (in front of the player)
void MainWindow::OnSpawnCarMenuClick(UINT nID) {

	// Spawn last spawned car model
	if (nID == ID_SPAWNCAR_LAST)
	{
		if (lastSpawnedCarModel == -1)
			return;

		nID = lastSpawnedCarModel + ID_SPAWNCAR_START;
	}

	// Open advanced car spawner
	if (nID == ID_SPAWNCAR_ARRAY)
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
	WantToSpawn wts = { 
		targetXY[0], 
		targetXY[1], 
		playerPed->gameObject->sprite->z, 
		4 * 180, 
		nID - ID_SPAWNCAR_START, 
		-1 
	};

	wtsCar[wtsCarSize] = wts;
	wtsCarSize++;
	lastSpawnedCarModel = nID - ID_SPAWNCAR_START;
	EnableMenuItem(carHMenu, ID_SPAWNCAR_LAST, MF_ENABLED);
}

void MainWindow::OnSpawnCarTank()
{
	OnSpawnCarMenuClick(ID_SPAWNCAR_START + (int)TANK);
}

void MainWindow::OnSpawnCarGunjeep()
{
	OnSpawnCarMenuClick(ID_SPAWNCAR_START + (int)GUNJEEP);
}

void MainWindow::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	//log(L"OnHotKey(%X, %X, %X)", nHotKeyId, nKey1, nKey2);
	switch (nKey2)
	{
	case 0x54:
		OnSpawnCarTank();
		break;
	case 0x4a:
		OnSpawnCarGunjeep();
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
		OnSpawnObjectMenuClick(ID_SPAWNOBJ_LAST);
		break;
	case 0x43:
		OnSpawnCarMenuClick(ID_SPAWNCAR_LAST);
		break;
	case 0x45:
		ExplodeCars();
		break;
	case 0x42:
		ShowBigText();
		break;
	case 0x57:
		OnGetWeaponMenuClick(ID_GETWEAP_ALL);
		break;
	default:
		break;
	}

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

void MainWindow::OnSpawnPedMenuClick(UINT nID) {
	if (nID == ID_SPAWNPED_TOOL) {
		m_pedSpawnerWindow->ShowWindow(SW_SHOW);
		m_pedSpawnerWindow->SetFocus();
		m_pedSpawnerWindow->ClearValues();
		return;
	}
}

void MainWindow::OnGetWeaponMenuClick(UINT nID) {

	if(nID == ID_GETWEAP_ALL)
	{
		GetAllWeapons();
		return;
	}

	WEAPON_INDEX weapon = (WEAPON_INDEX)(nID - ID_GETWEAP_START);
	GetWeapon(weapon);
}

void MainWindow::GetWeapon(WEAPON_INDEX weapon, bool silent) {
	Ped* playerPed = fnGetPedByID(1);

	// Return if player ped doesn't exist
	if (!playerPed)
		return;

	playerPed->playerWeapons->weapons[weapon]->ammo = 990;
	
	if (!silent)
		log(L"Weapon #%d got", weapon);
}

void MainWindow::GetAllWeapons() {
	size_t weaponsCount = sizeof(weapons) / sizeof(weapons[0]);

	for (size_t i = 0; i < weaponsCount; i++)
	{
		WEAPON_INDEX weapon = (WEAPON_INDEX)(i);
		GetWeapon(weapon, true);
	}

	log(L"All weapons got");
}

void MainWindow::OnGetCarWeaponMenuClick(UINT nID) {
	
	Ped* playerPed = fnGetPedByID(1);

	// Return if player's car's sprite doesn't exist
	if (!playerPed || !playerPed->currentCar || !playerPed->currentCar->sprite)
		return;

	byte ID = nID - ID_GETCARWEAP_START;
	CAR_WEAPON weapon = (CAR_WEAPON)(15 + ID);

	fnCarAddWeapon(weapon, 99, currLastCar);
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

void MainWindow::OnPlayVocalMenuClick(UINT nID) {
	UINT ID = nID - ID_VOCALS_START;
	fnPlayVocal((DWORD*)0x005d85a0, 0, (VOCAL)(ID));
	log(L"Vocal #%d played", ID);
}

void MainWindow::OnNativeCheatMenuClick(UINT nID) {
	UINT ID = nID - ID_NATIVE_START;
	DWORD address = 0x5EAD00 + ID;
	bool* cheat = (bool*)(address);
	*cheat = !*cheat;
	log(L"%s cheat at 0x%X", *cheat ? L"Enabled" : L"Disabled", address);
	CheckMenuItem(ncHMenu, nID, *cheat ? MF_CHECKED : MF_UNCHECKED);
}

void MainWindow::OnShowLiveTable()
{
	m_liveTableWindow->ShowWindow(SW_SHOW);
	m_liveTableWindow->SetFocus();
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

void MainWindow::CarExplode()
{
	if (!currLastCar) return;
	fnExplodeCar(currLastCar, 0, EXPLOSION_SIZE_MEDIUM);
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

	UINT stars = nID - IDC_STAR0;
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
		swprintf(buf, 256, L"%s", emblems[currLastCarEmblemID].name);
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

	PedManager_S25* manager = ByPtr(PedManager_S25, ptrToPedManager);
	Ped* lastPed = manager->lastPedInArray;

	for (int i = 1; i <= lastPed->id; i++)
	{
		Ped* currentPed = fnGetPedByID(i);

		if(!currentPed) continue;
		if(!currentPed->gameObject) continue;

		currentPed->gameObject->sprite->x = playerPed->gameObject->sprite->x;
		currentPed->gameObject->sprite->y = playerPed->gameObject->sprite->y;
		currentPed->gameObject->sprite->z = playerPed->gameObject->sprite->z;
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
	int dataInt = (int)nID - 3040;
	int gangNo = dataInt / 3;

	int* gangresp;
	gangresp = (int*)*gangsArr + 0x47 + gangNo * 0x51;

	switch(dataInt % 3) {
	case 0:
		*gangresp -= 20;
		if (*gangresp < -100) *gangresp = -100;
		break;
	case 1:
		*gangresp = 0;
		break;
	case 2:
		*gangresp += 20;
		if (*gangresp > 100) *gangresp = 100;
		break;
	}
	
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
	if(!currLastCar) return;
	if(!currLastCar->sprite) return;
	if(!currLastCar->trailerController) return;
	if(!currLastCar->trailerController->trailer) return;
	if(!currLastCar->trailerController->trailer->sprite) return;

	currLastCar->trailerController->trailer->sprite->lockPalleteMaybe = currLastCar->sprite->lockPalleteMaybe;
	currLastCar->trailerController->trailer->sprite->carColor = currLastCar->sprite->carColor;
	log(L"Trailer color changed");
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
		currLastCarEmblem->sprite->sprite = emblems[currLastCarEmblemID].id;
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
			currLastCarEmblem->sprite->sprite = emblems[1].id;
			currLastCarEmblem->rotation = 0;
			currLastCarEmblem->sprite->layer++;
			m_carEmblemPos.SetPos(currLastCarEmblem->yOffset);
			log(L"Car emblem created");
		}
	}
	else if (currLastCarEmblemID < sizeof(emblems)/sizeof(emblems[0]) - 1)
	{
		// Next emblem //
		currLastCarEmblemID++;
		currLastCarEmblem->sprite->sprite = emblems[currLastCarEmblemID].id;
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
	Game* pGame = (Game*)*(DWORD*)ptrToGame;
	if (!pGame) return;
	Player* player = pGame->CurrentPlayer;
	if (!player) return;

	fesetround(FE_TONEAREST);
	CString buffer;

	m_pedX.GetWindowTextW(buffer);
	float newx = _wtof(buffer);
	m_pedY.GetWindowTextW(buffer);
	float newy = _wtof(buffer);

	fnDoTeleport(player, newx, newy);

	log(L"Player teleported to %f, %f", newx, newy);
}

void MainWindow::ExplodeCars() {
	Ped* playerPed = fnGetPedByID(1);
	CarsPrefab* carsManager = ByPtr(CarsPrefab, ptrToCarsPrefabs);
	if (!carsManager) return;

	for (int i = 0; i < 306; i++) {
		Car* car = &carsManager->arr306Cars[i];

		if(playerPed && playerPed->currentCar == car) continue;
		if(!car->sprite) continue;

		fnExplodeCar(car, 0, EXPLOSION_SIZE_MEDIUM);
	}

	log(L"Boom!");
}

void MainWindow::PreventFPSComprensation(Game* game) {
	HWND foregroundWindow = ::GetForegroundWindow();
	bool isFocused = this->GetSafeHwnd() == foregroundWindow;

	//log(isFocused ? L"focused" : L"unfocused");
	//log(L"time: %d", game->compensationFPSTime);

	/// TODO
}

void MainWindow::OnEnterAsPassengerToggle()
{
	UpdateData(TRUE);
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
	PreventFPSComprensation(game);
	if (wtSpawnObject != -1) SpawnObject((OBJECT_TYPE)wtSpawnObject);
}

void MainWindow::OnGTADraw()
{
	/*
	CString string = L"hello world";
	S4_ENUM1 s4enum1 = S4_ENUM1_2;
	fnDrawGTATextRaw(
		string.GetBuffer(),
		0x400000,
		0x400000,
		1,
		0x8000,
		&s4enum1,
		0, // 0 or 6
		SPRITE_INVISIBILITY_VISIBLE,
		0
	);
	*/
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
