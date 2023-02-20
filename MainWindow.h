#pragma once

// MainWindow dialog
#include "gta2-helper.h"
#include "ACSWindow.h"
#include "WantToSpawn.h"

enum TIMER {
	TIMER_CAPTURE_MOUSE,
	TIMER_PED_INFO
};

class MainWindow : public CDialogEx
{
	DECLARE_DYNAMIC(MainWindow)

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	// consts //
	const LPCTSTR carnames[79] = { L"ALFA", L"ALLARD", L"AMDB4", L"APC", L"BANKVAN", L"BMW", /*L"BOXCAR",*/ L"BOXTRUCK",
			L"BUG", L"BUICK", L"BUS", L"COPCAR", L"DART", L"EDSEL", L"EDSELFBI", L"FIAT", L"FIRETRUK",
			L"GRAHAM", L"GT24640", L"GTRUCK", L"GUNJEEP", L"HOTDOG", L"HOTDOG_D1",
			L"HOTDOG_D2", L"HOTDOG_D3", L"HOTDOG_D4", L"ICECREAM", L"ISETLIMO", L"ISETTA", L"JEEP", L"JEFFREY", L"KRSNABUS",
			L"LIMO", L"LIMO2", L"MEDICAR", L"MERC", L"MESSER", L"MIURA", L"MONSTER", L"MORGAN", L"MORRIS",
			L"PICKUP", L"RTYPE", L"SPIDER", L"SPRITE", L"STINGRAY", L"STRATOS",
			L"STRATOSB", L"STRIPETB", L"STYPE", L"STYPECAB", L"SWATVAN", L"T2000GT", L"TANK",
			L"TANKER", L"TAXI", L"TBIRD", L"TOWTRUCK", /*L"TRAIN", L"TRAINCAB", L"TRAINFB",*/ L"TRANCEAM",
			L"TRUKCAB1", L"TRUKCAB2", L"TRUKCONT", L"TRUKTRNS", L"TVVAN", L"VAN", L"VESPA", L"VTYPE",
			L"WBTWIN", L"WRECK0", L"WRECK1", L"WRECK2", L"WRECK3", L"WRECK4", L"WRECK5",
			L"WRECK6", L"WRECK7", L"WRECK8", L"WRECK9", L"XK120", L"ZCX5" };

	const int carids[79] = { 0, 1, 2, 3, 4, 5, /*6,*/ 7, 8, 10, 11, 12, 13, 14, 84, 16, 17, 18, 19, 21, 22, 23,
		24, 25, 26, 85, 27, 28, 29, 30, 31, 86, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 44, 45, 46, 47, 48,
		49, 50, 51, 52, 53, 54, 55, 56, 57, 58, /*59, 60, 61,*/ 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73,
		74, 75, 76, 77, 78, 79, 80, 81, 82, 83 };

	const int emblemValues[9] = { 0, 294, 295, 296, 297, 298, 299, 300, 8 };

	const wchar_t* emblemNames[9] = { L"None", L"Loonies", L"Yakuza", L"Zaibatsu", L"Rednecks", L"Scientists", L"Krishna", L"Russians", L"Bomb" };

	// technical //
	MainWindow(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MainWindow();
	bool firstPaint;
	uint frames;
	HWND m_gtaWindow;
	ACSWindow* m_acsWindow;

	void OnPaint();
	afx_msg void OnBnClickedExit();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void log(const WCHAR* fmt, ...);
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnCommandsHello();

	// UI //
	HMENU ncHMenu;
	HMENU oHMenu;
	HMENU nHMenu;
	CEdit m_log;
	CEdit m_pedX;
	CEdit m_pedY;
	CEdit m_pedZ;
	CEdit m_pedRot;
	CEdit m_pedSAmmo;
	CEdit m_pedSType;
	CEdit m_pedSTime;
	CEdit m_pedCopLevel;
	CEdit m_carDamage;
	CEdit m_carID;
	CEdit m_carVelocity;
	CEdit m_carVisualData;
	CEdit m_carEmblem;
	CSliderCtrl m_carEmblemPos;
	CEdit m_carColor;
	CEdit m_pedHealth;
	CEdit m_pedArmor;
	CEdit m_pedMoney;
	CEdit m_pedClothes;
	CEdit m_pedShape;
	CEdit m_BigText;
	CEdit m_pedals[3];
	CEdit m_gangRespect[3];
	CEdit m_globalPedSpeeds[3];

	// features //

	// car spawning
	void SafeSpawnCars(WantToSpawn wtsArray[128], int* wtsArraySize);
	WantToSpawn wtsCar[128];
	int wtsCarSize = 0;
	int lastSpawnedCarModel = -1;
	afx_msg void SpawnCarHere(UINT nID);
	afx_msg void OnSpawncarTank();
	afx_msg void OnSpawncarGunjeep();

	// object spawning
	void SpawnObject(OBJECT_TYPE type);
	afx_msg void OnSpawnObjectClick(UINT nID);
	int wtSpawnObject = -1;
	afx_msg void OnSpawnLastObjectClick();
	int lastSpawnedObjectType = -1;

	// other tabs
	afx_msg void OnGetWeaponClick(UINT nID);
	afx_msg void OnGetCarWeaponClick(UINT nID);
	afx_msg void OnPlayVocalClick(UINT nID);
	afx_msg void OnNativeCheatClick(UINT nID);

	// currLastCar related
	Car* currLastCar = 0;
	Car* currLastCarOld = 0;
	void CarEngineOff();
	void TpToLastCar();
	void PrintCarInfo();
	void HijackTrain();

	// currLastCar's color
	afx_msg void CarColorReset();
	afx_msg void CarColorPlus();
	afx_msg void CarColorMinus();
	void SyncTrailerColor();

	// currLastCar's damage
	void FixCar();
	void LockCarDamage();
	short startCarDamage = 0;
	bool carDamageLocked = 0;

	// currLastCar's visual damage
	void VisFixCar();
	void VisBreakCar();

	// currLastCar's emblem
	void CarEmblemPlus();
	void CarEmblemMinus();
	Roof* currLastCarEmblem = 0;
	short currLastCarEmblemID = 0;
	short currLastCarEmblemLPos = 0;

	// currLastCar's doors lock
	void ToggleDoor(UINT nID);
	bool doorOpen[4] = { 0,0,0,0 }; // 1 - force open

	// cop level
	void SetStars(UINT nID);
	void LockStars();
	bool starsLocked = 0;
	short startCopValue = 0;

	// current weapon related
	void GiveUnlimitedAmmo();
	void NoReloads();
	bool noReloads = 0;

	// walking speed
	void GoSlow();
	int* walkingSpeed = nullptr;
	void SetGlobalPedSpeeds();
	int globalPedSpeedsOld[3] = { 1,1,1 }; // same here

	// watch peds
	void WatchPeds();
	void WatchNextPed();
	Ped* selectedPed = 0;
	bool watchPeds = false;
	int pedXPreWatch = 0, pedYPreWatch = 0, pedZPreWatch = 0;

	// mouse control
	afx_msg void MouseControl();
	bool captureMouse = 0;
	void CaptureMouse();

	// ped clothes
	void PedClothesPlus();
	void PedClothesMinus();
	void PedShapePlus();
	void PedShapeMinus();
	void PedShapeClothesReset();

	// player immortal
	void PlayerImmortal();
	bool playerImmortal = 0;

	// other
	void TeleportPlayer();
	void SetHealthArmorMoney();
	void TeleportAllPeds();
	void GangRespect(UINT nID);
	void FreeShopping();
	void ShowBigText();

	// big functions
	void FixCheckboxes();
	void KeepLockedValues();
	void PedInfo();
	int currLastCarXOld = 0, currLastCarYOld = 0, currLastCarXYShift;
	int pedXOld = 0, pedYOld = 0, pedZOld = 0, pedRotOld = 0;
	int pedHOld = 1, pedAOld = 1, pedMOld = 1; // 1 not 0 because it has to be different than the actual value in the first tick

	// important
	void OnGTAGameTick(Game* game);
	void NewFunction();
};
