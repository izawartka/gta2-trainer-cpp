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

	m_cameraWindow = new CameraWindow();
	m_cameraWindow->Create(IDD_CAM, this);
	m_cameraWindow->m_mainWindow = this;

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
	DDX_Text(pDX, IDC_PEDX, m_pedX);
	DDX_Text(pDX, IDC_PEDY, m_pedY);
	DDX_Text(pDX, IDC_PEDZ, m_pedZ);
	DDX_Text(pDX, IDC_PEDROT, m_pedRot);
	DDX_Text(pDX, IDC_PEDSAMMO, m_pedWeapAmmo);
	DDX_Text(pDX, IDC_PEDSTYPE, m_pedWeapName);
	DDX_Control(pDX, IDC_STARCOUNTER, m_pedCopLevel);
	DDX_Text(pDX, IDC_CARDAMAGE, m_carDamage);
	DDX_Text(pDX, IDC_CARID, m_carID);
	DDX_Text(pDX, IDC_GANG1V, m_gangRespect[0]);
	DDX_Text(pDX, IDC_GANG2V, m_gangRespect[1]);
	DDX_Text(pDX, IDC_GANG3V, m_gangRespect[2]);
	DDX_Text(pDX, IDC_CARVEL, m_carVelocity);
	DDX_Text(pDX, IDC_EMBCUR, m_carEmblemName);
	DDX_Control(pDX, IDC_EMBPOS, m_carEmblemPos);
	DDX_Text(pDX, IDC_CARCOLV, m_carColor);
	DDX_Text(pDX, IDC_CARVIS, m_carVisualData);
	DDX_Control(pDX, IDC_PEDHEALTH, m_pedHealth);
	DDX_Control(pDX, IDC_PEDARMOR, m_pedArmor);
	DDX_Control(pDX, IDC_PEDMONEY, m_pedMoney);
	DDX_Control(pDX, IDC_PREMAP_R, m_pedRemap);
	DDX_Control(pDX, IDC_PREMAP_S, m_pedShape);
	DDX_Control(pDX, IDC_BIGTEXTTEXT, m_BigText);
	DDX_Check(pDX, IDC_PASSENGER, m_enterAsPassenger);
	DDX_Check(pDX, IDC_CARINVALL, m_carInvAll);
	DDX_Check(pDX, IDC_CARINVBUL, m_carInvBullets);
	DDX_Check(pDX, IDC_CARINVFLM, m_carInvFlames);
	DDX_Check(pDX, IDC_CARINVRKT, m_carInvRockets);
	DDX_Check(pDX, IDC_CARINVCOL, m_carInvCollisions);
	DDX_Check(pDX, IDC_CARNOCOL, m_carNoCollisions);
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
	ON_COMMAND(ID_COMMANDS_CAMERA, &MainWindow::OnShowCamera)
	ON_WM_HOTKEY()
	ON_COMMAND_RANGE(ID_SPAWNCAR, ID_SPAWNOBJ - 1, &OnSpawnCarMenuClick)
	ON_COMMAND_RANGE(ID_SPAWNOBJ, ID_SPAWNPED - 1, &OnSpawnObjectMenuClick)
	ON_COMMAND_RANGE(ID_SPAWNPED, ID_GETWEAP - 1, &OnSpawnPedMenuClick)
	ON_COMMAND_RANGE(ID_GETWEAP, ID_GETCARWEAP - 1, &OnGetWeaponMenuClick)
	ON_COMMAND_RANGE(ID_GETCARWEAP, ID_VOCALS - 1, &OnGetCarWeaponMenuClick)
	ON_COMMAND_RANGE(ID_VOCALS, ID_NATIVE - 1, &OnPlayVocalMenuClick)
	ON_COMMAND_RANGE(ID_NATIVE, ID_POWERUP - 1, &OnNativeCheatMenuClick)
	ON_COMMAND_RANGE(ID_POWERUP, ID_POWERUP + 256, &OnPowerUpMenuClick)
	ON_COMMAND(ID_COMMANDS_GUNJEEP, &MainWindow::OnSpawnCarGunjeep)
	ON_COMMAND(ID_COMMANDS_GT24640, &MainWindow::OnSpawnCarGT24640)
	ON_BN_CLICKED(IDC_CARENGINEOFF, &MainWindow::CarEngineOff)
	ON_BN_CLICKED(IDC_UNLMAMMO, &MainWindow::GiveUnlimitedAmmo)
	ON_COMMAND_RANGE(IDC_STAR0, IDC_STAR6, &SetStars)
	ON_BN_CLICKED(IDC_CARFIX, &MainWindow::FixCar)
	ON_BN_CLICKED(IDC_CARVISFIX, &MainWindow::VisFixCar)
	ON_BN_CLICKED(IDC_CARVISBRK, &MainWindow::VisBreakCar)
	ON_BN_CLICKED(IDC_LOCKCOPLEVEL, &MainWindow::LockStars)
	ON_BN_CLICKED(IDC_PEDS0TIME, &MainWindow::NoReloads)
	ON_BN_CLICKED(IDC_CARLASTTP, &MainWindow::TpToLastCar)
	ON_BN_CLICKED(IDC_CARINFO, &MainWindow::PrintCarInfo)
	ON_BN_CLICKED(ID_COMMANDS_TPALLPEDS, &MainWindow::TeleportAllPeds)
	ON_COMMAND_RANGE(IDC_GANG1M, IDC_GANG3P, &GangRespect)
	ON_COMMAND_RANGE(IDC_DOOR1, IDC_DOOR4, &ToggleDoor)
	ON_COMMAND_RANGE(IDC_CARINVALL, IDC_CARNOCOL, &CarPhysBitmaskSet)
	ON_BN_CLICKED(IDC_FREESHOP, &MainWindow::FreeShopping)
	ON_BN_CLICKED(IDC_BEAHUMAN, &MainWindow::WatchPeds)
	ON_BN_CLICKED(IDC_EMBP, &MainWindow::CarEmblemPlus)
	ON_BN_CLICKED(IDC_EMBM, &MainWindow::CarEmblemMinus)
	ON_BN_CLICKED(IDC_CARCOLP, &MainWindow::CarColorPlus)
	ON_BN_CLICKED(IDC_CAREXPLODE, &MainWindow::CarExplode)
	ON_BN_CLICKED(IDC_CARCOLM, &MainWindow::CarColorMinus)
	ON_BN_CLICKED(IDC_CARCOLR, &MainWindow::CarColorReset)
	ON_BN_CLICKED(IDC_CARTRCOLR, &MainWindow::SyncTrailerColor)
	ON_BN_CLICKED(IDC_GOSLOW, &MainWindow::GoSlow)
	ON_BN_CLICKED(IDC_PEDHAMSET, &MainWindow::SetHealthArmorMoney)
	ON_BN_CLICKED(IDC_BIGTEXTSHOW, &MainWindow::ShowBigText)
	ON_BN_CLICKED(ID_COMMANDS_EXPLODECARS, &MainWindow::ExplodeCars)
	ON_BN_CLICKED(IDC_PASSENGER, &MainWindow::OnEnterAsPassengerToggle)
	ON_CBN_SELCHANGE(IDC_PREMAP_R, &MainWindow::PedRemapShapeSet)
	ON_CBN_SELCHANGE(IDC_PREMAP_S, &MainWindow::PedRemapShapeSet)
	ON_BN_CLICKED(IDC_PREMAP_DEF, &MainWindow::PedRemapShapeDefault)
	ON_BN_CLICKED(IDC_CARDUMMY, &MainWindow::CarMakeDummy)
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
		const MenuItem& info = items[i];
		menu->AppendMenuW(MF_STRING, (UINT_PTR)(info.id + baseID), info.name);
	}
}

void MainWindow::LoadNativeCheatsState()
{
	CMenu* menu = CMenu::FromHandle(ncHMenu);

	uint itemsCount = sizeof(nativeCheats) / sizeof(nativeCheats[0]);

	for (int i = 0; i < itemsCount; i++) {
		const MenuItem& info = nativeCheats[i];

		CString idString = std::to_wstring(info.id).c_str();
		int value = GetProfileInt(L"NativeCheats", idString, -1);
		if(value == 0 || value == 1) *(bool*)(0x5EAD00 + info.id) = value;
		else value = *(bool*)(0x5EAD00 + info.id);
		CheckMenuItem(menu->m_hMenu, info.id + ID_NATIVE_START, value ? MF_CHECKED : MF_UNCHECKED);
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
		0x4a); //ALT+J

	RegisterHotKey(
		GetSafeHwnd(),
		1,
		MOD_ALT | MOD_NOREPEAT,
		0x47); //ALT+G

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

	// Create the "Power-ups" menu
	CMenu* powerUpsMenu = new CMenu();
	powerUpsMenu->CreatePopupMenu();
	AddMenuItems(powerUpsMenu, powerUps, sizeof(powerUps) / sizeof(powerUps[0]), ID_POWERUP_START);
	AppendMenu(menu->m_hMenu, MF_POPUP, (UINT_PTR)powerUpsMenu->m_hMenu, L"Power-ups");

	return 0;
}

BOOL MainWindow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Create "Player body shape / remap" comboboxes
	m_pedShape.ResetContent();
	int shapesCount = sizeof(pedBodyShapes) / sizeof(pedBodyShapes[0]);
	for (int i = 0; i < shapesCount; i++)
		m_pedShape.AddString(pedBodyShapes[i].name);

	m_pedRemap.ResetContent();
	int remapsCount = sizeof(pedRemaps) / sizeof(pedRemaps[0]);
	for (int i = 0; i < remapsCount; i++)
		m_pedRemap.AddString(pedRemaps[i].name);

	return TRUE;
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
		return;
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

		uint scale = currentWTS.miniCar ? (*(uint*)0x005e4f38) : (*(uint*)0x005e4d4c);

		// Spawn a car
		Car* car = fnSpawnCarAdvanced(
			(TrafficManager*)(*(TrafficManager**)ptrToTrafficManager),
			0,
			currentWTS.x,
			currentWTS.y,
			currentWTS.z,
			currentWTS.rot,
			(CAR_MODEL4)currentWTS.model,
			scale
		);

		if (car)
		{
			log(L"Car 0x%X spawned!", car);
			
			short color = currentWTS.color;
			if (color != -1) {
				car->sprite->lockPalleteMaybe |= 1;
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
		nID - ID_SPAWNCAR_START
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

void MainWindow::OnSpawnCarGT24640()
{
	OnSpawnCarMenuClick(ID_SPAWNCAR_START + (int)GT24640);
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
	case 0x47:
		OnSpawnCarGT24640();
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

	fnCarAddWeapon(weapon, 99, m_lastCar);
	log(L"Car weapon #%d got", ID);

	switch (weapon)
	{
		case CAR_WEAP_TANKTURRET:
			if (!getCarRoofWithSpriteIfExists(m_lastCar->roof, 546))
			{
				fnCarAddRoofTankTurret(m_lastCar);
				log(L"Tank turret spawned", ID);
			}
			break;
		case CAR_WEAP_WATERGUN:
		case CAR_WEAP_FLAMETHROWER:
			if (!getCarRoofWithSpriteIfExists(m_lastCar->roof, 278))
			{
				fnCarAddRoofWaterGun(m_lastCar);
				log(L"Firetruck turret spawned", ID);
			}
			break;
		case CAR_WEAP_JEEPGUN:
			if (!getCarRoofWithSpriteIfExists(m_lastCar->roof, 285))
			{
				fnCarAddRoofGun(m_lastCar);
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

	CString stringValue = *cheat ? L"1" : L"0";
	WriteProfileString(L"NativeCheats", std::to_wstring(ID).c_str(), stringValue);
}

void MainWindow::OnPowerUpMenuClick(UINT nID)
{
	Game* game = (Game*)*(DWORD*)ptrToGame;
	if(!game) return;

	Player* player = game->CurrentPlayer;
	if(!player) return;

	POWERUP_TYPE type = (POWERUP_TYPE)(nID - ID_POWERUP_START);
	fnGivePowerUp(player, 0, type);
	log(L"%s powerup given", powerUps[type].name);
}

void MainWindow::OnShowLiveTable()
{
	m_liveTableWindow->ShowWindow(SW_SHOW);
	m_liveTableWindow->SetFocus();
}

void MainWindow::OnShowCamera()
{
	m_cameraWindow->m_active = true;
	m_cameraWindow->ShowWindow(SW_SHOW);
	m_cameraWindow->SetFocus();
}

void MainWindow::CarEngineOff()
{
	// Return if lastCar doesn't exist
	if (!m_lastCar)
		return;

	if (m_lastCar->engineState != CAR_ENGINE_STATE(ENGINE_ON))
	{
		log(L"Engine is already off or broken");
		return;
	}

	m_lastCar->engineState = CAR_ENGINE_STATE(TURNING_OFF);
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
	if (!m_lastCar) return;
	fnExplodeCar(m_lastCar, 0, EXPLOSION_SIZE_MEDIUM);
}

void MainWindow::CarPhysBitmaskSet(UINT nID)
{
	if(m_lastCar == nullptr) return;

	UpdateData(true);

	if (nID == IDC_CARINVALL) {
		m_carInvCollisions = m_carInvAll;
		m_carInvBullets = m_carInvAll;
		m_carInvRockets = m_carInvAll;
		m_carInvFlames = m_carInvAll;
	}

	SetCarPhysBitmask(0x8, m_carInvCollisions);
	SetCarPhysBitmask(0x10, m_carNoCollisions);
	SetCarPhysBitmask(0x100, m_carInvBullets);
	SetCarPhysBitmask(0x200, m_carInvRockets);
	SetCarPhysBitmask(0x400, m_carInvFlames);

	UpdateData(false);

	log(L"Car physics updated");
}

void MainWindow::SetCarPhysBitmask(uint bit, bool value)
{
	if (!m_lastCar) return;

	if (value) 
	{
		m_lastCar->physicsBitmask |= bit;
	}
	else 
	{
		m_lastCar->physicsBitmask &= ~bit;
	}
}

void MainWindow::UpdateCarPhysBitmask()
{
	if (m_lastCar == nullptr) {
		m_carInvCollisions = 0;
		m_carNoCollisions = 0;
		m_carInvBullets = 0;
		m_carInvRockets = 0;
		m_carInvFlames = 0;
		m_carInvAll = 0;
		return;
	}

	m_carInvCollisions = m_lastCar->physicsBitmask & 0x8 ? 1 : 0;
	m_carNoCollisions = m_lastCar->physicsBitmask & 0x10 ? 1 : 0;
	m_carInvBullets = m_lastCar->physicsBitmask & 0x100 ? 1 : 0;
	m_carInvRockets = m_lastCar->physicsBitmask & 0x200 ? 1 : 0;
	m_carInvFlames = m_lastCar->physicsBitmask & 0x400 ? 1 : 0;

	m_carInvAll = 
		m_carInvCollisions == 1 && 
		m_carInvBullets == 1 && 
		m_carInvRockets == 1 && 
		m_carInvFlames == 1 ? 1 : 0;
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
	Game* pGame = (Game*)*(DWORD*)ptrToGame;
	if (!pGame) return;

	Player* player = pGame->CurrentPlayer;
	if (!player) return;

	if (!m_lastCar || !m_lastCar->sprite) return;

	player->ph2.cameraPos.x = m_lastCar->sprite->x;
	player->ph2.cameraPos.y = m_lastCar->sprite->y;
	fnDoTeleportRaw(player, 0);

	log(L"Teleported to the car!");
}

void MainWindow::PrintCarInfo()
{
	// Return if lastCar doesn't exist
	if (!m_lastCar)
		return;

	// Print all info
	log(L"--- Car #%d info ---", m_lastCar->id);
	log(L"Address: 0x%X", m_lastCar);
	log(L"model: %d", m_lastCar->carModel);
	if (m_lastCar->roof)
	{
		log(L"Turret: 0x%X rot: %d x:%d y:%d", m_lastCar->roof, m_lastCar->roof->rotation, m_lastCar->roof->xOffset, m_lastCar->roof->yOffset);
		log(L"Turret Sprite: 0x%X spr: %d pal: %d lckpal: %d", m_lastCar->roof->sprite, m_lastCar->roof->sprite->sprite, m_lastCar->roof->sprite->carColor, m_lastCar->roof->sprite->lockPalleteMaybe);
		log(L"Turret GmObj: 0x%X id: %d", m_lastCar->roof->sprite->gameObject, m_lastCar->roof->sprite->gameObject->id);
	}
	else
		log(L"No turret");
	if (m_lastCar->physics)
		log(L"Physics: 0x%X", m_lastCar->physics);
	else
		log(L"No physics");
	if (m_lastCar->sprite)
	{
		log(L"Sprite: 0x%X", m_lastCar->sprite);
		log(L"x: %d y: %d z: %d r: %d", m_lastCar->sprite->x, m_lastCar->sprite->y, m_lastCar->sprite->z, m_lastCar->sprite->rotation);
	}
	else
		log(L"No sprite");
	if (m_lastCar->driver)
		log(L"Driver: 0x%X occ: %d", m_lastCar->driver, m_lastCar->driver->occupation);
	else
		log(L"No driver");
	log(L"damage: %d visdmg: %d", m_lastCar->carDamage, m_lastCar->carLights);
	if (m_lastCar->trailerController)
		log(L"Trailer: 0x%X model: %d", m_lastCar->trailerController->trailer, m_lastCar->trailerController->trailer->carModel);
	else
		log(L"No trailer");

	log(L"Prev: -1:0x%X, -2:0x%X, -3:0x%X", fnGetCarByID(m_lastCar->id - 1), fnGetCarByID(m_lastCar->id - 2), fnGetCarByID(m_lastCar->id - 3));
	log(L"Next: +1:0x%X, +2:0x%X, +3:0x%X", fnGetCarByID(m_lastCar->id + 1), fnGetCarByID(m_lastCar->id + 2), fnGetCarByID(m_lastCar->id + 3));
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
	// Return if lastCar doesn't exist
	if (!m_lastCar)
		return;

	m_lastCar->carDamage = 0;
	m_lastCar->fireState = 0;
	fnExtinguishCar(m_lastCar, 0);
	fnFixCarBrokenEngine(m_lastCar, 0);
	log(L"Fixed the engine");
}

void MainWindow::VisFixCar()
{
	// Return if lastCar doesn't exist
	if (!m_lastCar)
		return;

	m_lastCar->carLights = CAR_LIGHTS_AND_DOORS_BITSTATE((m_lastCar->carLights | 0x800040) & 0xFFFFFFE0); // turn on lights and filter out damage
	log(L"Fixed the car visually");
}

void MainWindow::VisBreakCar()
{
	// Return if lastCar doesn't exist
	if (!m_lastCar)
		return;

	m_lastCar->carLights = CAR_LIGHTS_AND_DOORS_BITSTATE((m_lastCar->carLights | 0x1F) & 0xFF387F9F); // make damage and filter out lights
	log(L"Broke the car visually");
}

void MainWindow::UpdateCar()
{
	bool carChanged = false;

	// Remove current car if not in the game
	if (*(DWORD*)ptrToPedManager == 0) {
		m_lastCarOld = m_lastCar;
		m_lastCar = nullptr;
		m_lastCarIDtest = 0;
	}
	else {
		Ped* playerPed = fnGetPedByID(1);

		// Change current car if playerPed's car changed
		if (playerPed->currentCar && playerPed->currentCar != m_lastCar) {
			carChanged = true;
			m_lastCarOld = m_lastCar;
			m_lastCar = playerPed->currentCar;
			m_lastCarIDtest = m_lastCar->id;
		}
	}

	// Prevents bugs on level restart
	if (m_lastCar && m_lastCar->id != m_lastCarIDtest) {
		m_lastCarOld = m_lastCar;
		m_lastCar = nullptr;
		m_lastCarIDtest = 0;
	}

	UpdateCarPhysBitmask();

	// Reset properties and return if lastCar doesn't exist
	if (!m_lastCar || !m_lastCar->sprite) {
		m_lastCar = nullptr;
		m_carVisualData = L"";
		m_carID = 0;
		m_carColor = 0;
		m_carDamage = 0;
		m_carEmblem = nullptr;
		m_carEmblemID = 0;
		m_carEmblemName = L"";
		m_carEmblemPos.SetPos(0);

		for (int i = 0; i < 4; i++) {
			CButton* pButton = (CButton*)GetDlgItem(IDC_DOOR1 + i);
			pButton->EnableWindow(false);
		}

		UpdateData(false);
		return;
	}

	// Update emblem info after car change
	if (carChanged) {
		m_carEmblemPos.SetRange(-8192, 8192, TRUE);

		bool found = false;

		for (int i = 0; i < sizeof(carEmblems) / sizeof(carEmblems[0]); i++)
		{
			m_carEmblem = getCarRoofWithSpriteIfExists(m_lastCar->roof, carEmblems[i].id);
			if (!m_carEmblem || m_carEmblem->sprite->spriteType != 4) continue;

			m_carEmblemID = i;
			m_carEmblemName = carEmblems[m_carEmblemID].name;
			m_carEmblemPos.SetPos(m_carEmblem->yOffset);
			found = true;
			break;
		}

		if (!found) {
			m_carEmblem = nullptr;
			m_carEmblemID = 0;
			m_carEmblemName = L"";
			m_carEmblemPos.SetPos(0);
		}
	}

	// Update car info
	m_carID = m_lastCar->id;
	m_carDamage = m_lastCar->carDamage;

	if (m_lastCar->physics) {
		int xVelocity = m_lastCar->physics->xVelocity;
		int yVelocity = m_lastCar->physics->yVelocity;
		m_carVelocity = (unsigned int)sqrt(xVelocity * xVelocity + yVelocity * yVelocity);
	}
	else {
		m_carVelocity = 0;
	}
	
	m_carColor = m_lastCar->sprite->carColor;
	if (~m_lastCar->sprite->lockPalleteMaybe & 1) m_carColor = -1;
	if (m_carEmblem) m_carEmblem->yOffset = m_carEmblemPos.GetPos();

	WCHAR buf[256];
	swprintf(buf, 256, L"%X", m_lastCar->carLights);
	m_carVisualData = buf;

	UpdateData(false);

	// Car doors
	for (int i = 0; i < 4; i++)
	{
		if(carChanged) doorOpen[i] = false;

		CButton* pButton = (CButton*)GetDlgItem(IDC_DOOR1 + i);
		pButton->EnableWindow(m_lastCar->carDoor[i].doorState != 0);

		if (!doorOpen[i]) continue; 
		m_lastCar->carDoor[i].doorState = 2;
	}
}

void MainWindow::PedInfo()
{
	// Return if not in the game
	if (*(DWORD*)ptrToPedManager == 0)
		return;

	WCHAR buf[256];
	Ped* playerPed = fnGetPedByID(1);

	if (playerPed == nullptr) return;

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
		char* gangRespect = (char*)*gangsArr + 0x11C + i * 0x144;
		m_gangRespect[i].Format(L"%d", (char)*gangRespect);
	}	

	// Display current weapon's ammo and reload time
	if (playerPed->selectedWeapon)
	{
		bool isCarWeapon = playerPed->selectedWeapon->id >= 15;
		m_pedWeapName = isCarWeapon ? carWeapons[playerPed->selectedWeapon->id - 15].name : weapons[playerPed->selectedWeapon->id].name;
		m_pedWeapAmmo.Format(L"%f", playerPed->selectedWeapon->ammo / 10.0f);
	}
	else
	{
		m_pedWeapName = L"";
		m_pedWeapAmmo = L"";
	}

	// If player in the car, display it's coords
	if (playerPed->currentCar)
	{	
		m_pedX.Format(L"%.2f", playerPed->currentCar->sprite->x / 16384.0);
		m_pedY.Format(L"%.2f", playerPed->currentCar->sprite->y / 16384.0);
		m_pedZ.Format(L"%.2f", playerPed->currentCar->sprite->z / 16384.0);
		m_pedRot.Format(L"%d\x00B0", playerPed->currentCar->sprite->rotation/4);
	}
	// If player is not in the car, display ped's coords
	else
	{
		// If player ped's sprite doesn't exist, clear textboxes
		if (!playerPed->gameObject || !playerPed->gameObject->sprite) {
			m_pedX = L"";
			m_pedY = L"";
			m_pedZ = L"";
			m_pedRot = L"";
		}
		else
		{
			// Display that ultra cool message
			if (playerPed->gameObject->cigaretteIdleTimer == 1)
				log(L"Smokin' time ;3");

			m_pedX.Format(L"%.2f", playerPed->gameObject->sprite->x / 16384.0);
			m_pedY.Format(L"%.2f", playerPed->gameObject->sprite->y / 16384.0);
			m_pedZ.Format(L"%.2f", playerPed->gameObject->sprite->z / 16384.0);
			m_pedRot.Format(L"%d\x00B0", playerPed->gameObject->sprite->rotation/4);
		}
	}

	UpdateData(false);
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
	int dataInt = (int)nID - IDC_GANG1M;
	int gangNo = dataInt / 3;

	char* gangresp;
	gangresp = (char*)*gangsArr + 0x11C + gangNo * 0x144;

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
	// Return if lastCar doesn't exist
	if (!m_lastCar)
		return;

	int doorID = uID - IDC_DOOR1;
	if (m_lastCar->carDoor[doorID].doorState == 6 || doorOpen[doorID] == true)
	{
		doorOpen[doorID] = !doorOpen[doorID];
		log(L"Door %s", (doorOpen[doorID] ? L"opened" : L"closed"));
	}
}

void MainWindow::SyncTrailerColor()
{
	if(!m_lastCar) return;
	if(!m_lastCar->sprite) return;
	if(!m_lastCar->trailerController) return;
	if(!m_lastCar->trailerController->trailer) return;
	if(!m_lastCar->trailerController->trailer->sprite) return;

	m_lastCar->trailerController->trailer->sprite->lockPalleteMaybe = m_lastCar->sprite->lockPalleteMaybe;
	m_lastCar->trailerController->trailer->sprite->carColor = m_lastCar->sprite->carColor;
	log(L"Trailer color changed");
}

void MainWindow::CarEmblemMinus()
{
	// Return if lastCar's sprite doesn't exist
	if (!m_lastCar || !m_lastCar->sprite)
		return;

	if (m_carEmblemID == 1)
	{
		// "Remove" emblem //
		m_carEmblemID = 0;
		m_carEmblem->sprite->spriteType = SPRITE_TYPE_INVISIBLE;
		m_carEmblem->sprite->layer--;
		m_carEmblem = 0;
		m_carEmblemName = L"";
	}
	else if (m_carEmblemID > 1)
	{
		// Prev emblem //
		m_carEmblemID--;
		m_carEmblem->sprite->sprite = carEmblems[m_carEmblemID].id;
		m_carEmblemName = carEmblems[m_carEmblemID].name;
		log(L"Car emblem changed");
	}
}


void MainWindow::CarEmblemPlus()
{
	// Return if lastCar's sprite doesn't exist
	if (!m_lastCar || !m_lastCar->sprite)
		return;

	if (m_carEmblemID == 0)
	{
		if (m_lastCar->carModel == CAR_MODEL4_TVVAN)
		{
			log(L"TV Van is the only car you cannot put emblem on :(");
			return;
		}

		// Create emblem //
		fnCarAddRoofAntenna(m_lastCar);
		m_carEmblem = getCarRoofWithSpriteIfExists(m_lastCar->roof, 0);
		if (!m_carEmblem) return;

		m_carEmblemID = 1;
		m_carEmblem->sprite->sprite = carEmblems[1].id;
		m_carEmblem->rotation = 0;
		m_carEmblem->sprite->layer++;
		m_carEmblemName = carEmblems[m_carEmblemID].name;
		log(L"Car emblem created");
	}
	else if (m_carEmblemID < sizeof(carEmblems)/sizeof(carEmblems[0]) - 1)
	{
		// Next emblem //
		m_carEmblemID++;
		m_carEmblem->sprite->sprite = carEmblems[m_carEmblemID].id;
		m_carEmblemName = carEmblems[m_carEmblemID].name;
		log(L"Car emblem changed");
	}
}

void MainWindow::CarColorPlus()
{
	// Return if lastCar's sprite doesn't exist
	if (!m_lastCar || !m_lastCar->sprite)
		return;

	short color = m_lastCar->sprite->carColor;
	if (~m_lastCar->sprite->lockPalleteMaybe & 1) color = -1;
	color++;

	CarColorSet(color);
}

void MainWindow::CarColorMinus()
{
	// Return if lastCar's sprite doesn't exist
	if (!m_lastCar || !m_lastCar->sprite)
		return;

	short color = m_lastCar->sprite->carColor;
	if (~m_lastCar->sprite->lockPalleteMaybe & 1) color = -1;
	color--;

	CarColorSet(color);
}

void MainWindow::CarColorReset()
{
	// Return if lastCar's sprite doesn't exist
	if (!m_lastCar || !m_lastCar->sprite)
		return;

	CarColorSet(-1);
}

void MainWindow::CarColorSet(short color)
{
	if (color < -1) color = 35;
	if (color > 35) color = -1;

	if (color == -1)
	{
		m_lastCar->sprite->lockPalleteMaybe &= ~1;
		m_lastCar->sprite->carColor = 0;
	}
	else
	{
		m_lastCar->sprite->lockPalleteMaybe |= 1;
		m_lastCar->sprite->carColor = color;
	}

	log(L"Car color changed");
}

void MainWindow::PedRemapShapeSet()
{
	bool inGame = *(DWORD*)ptrToPedManager != 0;
	if (!inGame) return;

	Ped* playerPed = fnGetPedByID(1);

	if (playerPed->remap != m_pedRemap.GetCurSel())
	{
		playerPed->remap = (PED_REMAP)m_pedRemap.GetCurSel();
		log(L"Remap set to %d", playerPed->remap);
	}

	if (playerPed->remap2 != m_pedShape.GetCurSel())
	{
		playerPed->remap2 = (PED_REMAP2)m_pedShape.GetCurSel();
		log(L"Shape set to %d", playerPed->remap2);
	}
}

void MainWindow::PedRemapShapeDefault()
{
	bool inGame = *(DWORD*)ptrToPedManager != 0;
	if (!inGame) return;

	Ped* playerPed = fnGetPedByID(1);

	playerPed->remap = PED_REMAP_PLAYER;
	playerPed->remap2 = PED_REMAP2_1;

	log(L"Remap and shape set to default");
}

void MainWindow::PedRemapShapeUpdate()
{
	Ped* playerPed = fnGetPedByID(1);

	if (playerPed->remap != m_pedRemap.GetCurSel() && !m_pedRemap.GetDroppedState())
	{
		m_pedRemap.SetCurSel(playerPed->remap);
	}

	if(playerPed->remap2 != m_pedShape.GetCurSel() && !m_pedShape.GetDroppedState())
	{
		m_pedShape.SetCurSel(playerPed->remap2);
	}
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
		log(L"Player is not in a train");
	}
}

void MainWindow::CarMakeDummy()
{
	if(!m_lastCar) return;

	if (m_lastCar->driver) {
		log(L"Car already has a driver");
		return;
	}

	fnCarPutDummyDriverIn(m_lastCar, 0);
	fnCarMakeDummy(m_lastCar, 0);
	m_lastCar->field_0x76 = 0;
	m_lastCar->field_0x7c = 5;

	log(L"Dummy driver created");
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
	Game* pGame = (Game*)*(DWORD*)ptrToGame;
	if (!pGame) return;
	Player* player = pGame->CurrentPlayer;
	if (!player) return;

	CString buffer;

	m_pedHealth.GetWindowTextW(buffer);
	fnGetPedByID(1)->health = (int)_ttof(buffer);

	m_pedArmor.GetWindowTextW(buffer);
	player->armor = (int)_ttof(buffer);

	m_pedMoney.GetWindowTextW(buffer);
	player->animatedMoney.value = (int)_ttof(buffer);

	log(L"Player's stats changed!");
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

void MainWindow::OnFirstGTAGameTick(Game* game)
{
	if (!m_isFirstTick) return;
	m_isFirstTick = false;

	LoadNativeCheatsState();
}

void MainWindow::OnGTAGameTick(Game* game)
{
	//OnTimer moved here, it's more stable now
	OnFirstGTAGameTick(game);
	KeepLockedValues();
	PedRemapShapeUpdate();
	UpdateCar();
	PedInfo();
	if (captureMouse) CaptureMouse();
	FixCheckboxes();
	SafeSpawnCars(wtsCar, &wtsCarSize);
	PreventFPSComprensation(game);
	if (wtSpawnObject != -1) SpawnObject((OBJECT_TYPE)wtSpawnObject);
	m_cameraWindow->OnGTAGameTick();
	m_pedSpawnerWindow->OnGTAGameTick();
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
