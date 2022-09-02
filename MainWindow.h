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

public:
	MainWindow(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MainWindow();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedExit();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	ACSWindow* m_acsWindow;


	LPCTSTR carnames[80] = { L"ALFA", L"ALLARD", L"AMDB4", L"APC", L"BANKVAN", L"BMW", L"BOXCAR", L"BOXTRUCK",
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

	int carids[80] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14, 84, 16, 17, 18, 19, 21, 22, 23,
		24, 25, 26, 85, 27, 28, 29, 30, 31, 86, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 44, 45, 46, 47, 48,
		49, 50, 51, 52, 53, 54, 55, 56, 57, 58, /*59, 60, 61,*/ 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73,
		74, 75, 76, 77, 78, 79, 80, 81, 82, 83 };

	HMENU ncHMenu;
	HMENU oHMenu;
	HMENU nHMenu;
	bool firstPaint;
	HWND m_gtaWindow;
	void OnPaint();
	void log(const WCHAR* fmt, ...);
	CEdit m_log;
	afx_msg void OnCommandsHello();
	afx_msg void MouseControl();
	bool captureMouse = 0;
	void CaptureMouse();
	afx_msg void OnSpawncarTank();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void SpawnCarHere(UINT nID);
	afx_msg void OnSpawnObjectClick(UINT nID);
	afx_msg void OnSpawnLastObjectClick();
	afx_msg void OnGetWeaponClick(UINT nID);
	afx_msg void OnGetCarWeaponClick(UINT nID);
	afx_msg void OnPlayVocalClick(UINT nID);
	afx_msg void OnNativeCheatClick(UINT nID);
	afx_msg void OnSpawncarGunjeep();
	uint frames;
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
	void CarEngineOff();
	bool starsLocked = 0;
	short startCopValue = 0;
	void LockStars();
	bool noReloads = 0;
	void NoReloads();
	void KeepLockedValues();
	void SetStars(UINT nID);
	void TpToLastCar();
	bool playerImmortal = 0;
	void PlayerImmortal();
	void GiveUnlimitedAmmo();
	void FixCar();
	void VisFixCar();
	void VisBreakCar();
	short startCarDamage = 0;
	bool carDamageLocked = 0;
	void LockCarDamage();
	void PedInfo();
	Car* currLastCar = 0;
	Car* currLastCarOld = 0;
	int pedXOld = 0, pedYOld = 0, pedZOld = 0, pedRotOld = 0;
	int pedHOld = 1, pedAOld = 1, pedMOld = 1; // 1 not 0 because it has to be different than the actual value in the first tick
	int globalPedSpeedsOld[3] = { 1,1,1 }; // same here
	WantToSpawn wtsCar[128];
	int wtsCarSize = 0;
	int lastSpawnedCarModel = -1;
	int wtSpawnObject = -1;
	int lastSpawnedObjectType = -1;
	void TeleportAllPeds();
	Roof* currLastCarEmblem = 0;
	short currLastCarEmblemID = 0;
	short currLastCarEmblemLPos = 0;
	const int emblemValues[9] = { 0, 294, 295, 296, 297, 298, 299, 300, 8};
	const wchar_t* emblemNames[9] = { L"None", L"Loonies", L"Yakuza", L"Zaibatsu", L"Rednecks", L"Scientists", L"Krishna", L"Russians", L"Bomb"};
	Ped* selectedPed = 0;
	bool watchPeds = false;
	void WatchPeds();
	void WatchNextPed();
	int pedXPreHuman = 0, pedYPreHuman = 0, pedZPreHuman = 0;
	void GangRespect(UINT nID);
	void ToggleDoor(UINT nID);
	bool doorOpen[4] = { 0,0,0,0 }; // 1 - force open
	int currLastCarXOld = 0, currLastCarYOld = 0, currLastCarXYShift;
	void FreeShopping();
	void PrintCarInfo();
	void SyncTrailerColor();
	void CarEmblemPlus();
	void CarEmblemMinus();
	void CarColorPlus();
	void CarColorMinus();
	void CarColorReset();
	void PedClothesPlus();
	void FixCheckboxes();
	void PedClothesMinus();
	void PedShapePlus();
	void PedShapeMinus();
	void PedShapeClothesReset();
	void ShowBigText();
	void HijackTrain();
	void GoSlow();
	int* walkingSpeed = nullptr;
	void TeleportPlayer();
	void SetHealthArmorMoney();
	void SetGlobalPedSpeeds();
	void SafeSpawnCars(WantToSpawn wtsArray[128], int* wtsArraySize);
	void SpawnObject(OBJECT_TYPE type);

	void OnGTAGameTick(Game* game);
	void NewFunction();
};
