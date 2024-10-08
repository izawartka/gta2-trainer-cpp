#pragma once

// MainWindow dialog
#include "gta2-helper.h"
#include "ACSWindow.h"
#include "PedSpawnerWindow.h"
#include "LiveTable/LiveTableWindow.h"
#include "CameraWindow.h"

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
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	// technical //
	MainWindow(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MainWindow();
	bool firstPaint;
	uint frames;
	HWND m_gtaWindow;
	ACSWindow* m_acsWindow;
	PedSpawnerWindow* m_pedSpawnerWindow;
	LiveTableWindow* m_liveTableWindow;
	CameraWindow* m_cameraWindow;

	void OnPaint();
	afx_msg void OnBnClickedExit();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void log(const WCHAR* fmt, ...);
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnCommandsHello();

	// UI //
	HMENU ncHMenu;
	HMENU objHMenu;
	HMENU carHMenu;
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
	CComboBox m_pedRemap;
	CComboBox m_pedShape;
	CEdit m_BigText;
	CEdit m_pedals[3];
	CEdit m_gangRespect[3];
	CEdit m_globalPedSpeeds[3];

	void AddCategorizedMenuItems(
		CMenu* menu,
		const LPCTSTR* categories,
		uint categoriesCount,
		const CatMenuItem* items,
		uint itemsCount,
		UINT_PTR baseID
	);

	void AddMenuItems(
		CMenu* menu,
		const MenuItem* items,
		uint itemsCount,
		UINT_PTR baseID
	);

	// features //

	// spawn car
	void SafeSpawnCars(WantToSpawn wtsArray[128], int* wtsArraySize);
	WantToSpawn wtsCar[128];
	int wtsCarSize = 0;
	int lastSpawnedCarModel = -1;
	afx_msg void OnSpawnCarMenuClick(UINT nID);
	afx_msg void OnSpawnCarTank();
	afx_msg void OnSpawnCarGunjeep();
	afx_msg void OnSpawnCarGT24640();

	// spawn object
	void SpawnObject(OBJECT_TYPE type);
	afx_msg void OnSpawnObjectMenuClick(UINT nID);
	int wtSpawnObject = -1;
	int lastSpawnedObjectType = -1;

	// spawn ped
	afx_msg void OnSpawnPedMenuClick(UINT nID);

	// get weapon
	afx_msg void OnGetWeaponMenuClick(UINT nID);
	void GetWeapon(WEAPON_INDEX weapon, bool silent = false);
	void GetAllWeapons();

	// other menus
	afx_msg void OnGetCarWeaponMenuClick(UINT nID);
	afx_msg void OnPlayVocalMenuClick(UINT nID);
	afx_msg void OnNativeCheatMenuClick(UINT nID);
	afx_msg void OnShowLiveTable();
	afx_msg void OnShowCamera();

	// currLastCar related
	Car* currLastCar = 0;
	Car* currLastCarOld = 0;
	void CarEngineOff();
	void TpToLastCar();
	void PrintCarInfo();
	void HijackTrain();
	void CarMakeDummy();

	// currLastCar's color
	afx_msg void CarColorReset();
	afx_msg void CarColorPlus();
	afx_msg void CarColorMinus();
	void CarColorSet(short index);
	void SyncTrailerColor();

	// currLastCar's damage
	void FixCar();
	void CarExplode();

	// currLastCar's physics bitmap
	void CarPhysBitmaskSet(UINT nID);
	void SetCarPhysBitmask(uint pos, bool value);
	void CarPhysBitmaskUpdate();
	int m_carInvAll = 0;
	int m_carInvBullets = 0;
	int m_carInvCollisions = 0;
	int m_carInvRockets = 0;
	int m_carInvFlames = 0;
	int m_carNoCollisions = 0;

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

	// watch peds
	void WatchPeds();
	void WatchNextPed();
	Ped* selectedPed = nullptr;
	bool watchPeds = false;
	int pedXPreWatch = 0, pedYPreWatch = 0, pedZPreWatch = 0;

	// mouse control
	afx_msg void MouseControl();
	bool captureMouse = 0;
	void CaptureMouse();

	// player ped remap and shape
	void PedRemapShapeSet();
	void PedRemapShapeDefault();
	void PedRemapShapeUpdate();

	// player immortal
	void PlayerImmortal();
	bool playerImmortal = 0;

	// other
	void SetHealthArmorMoney();
	void TeleportAllPeds();
	void GangRespect(UINT nID);
	void FreeShopping();
	void ShowBigText();
	void ExplodeCars();
	void PreventFPSComprensation(Game* game);
	afx_msg void OnEnterAsPassengerToggle();
	int m_enterAsPassenger = 0;

	// big functions
	void FixCheckboxes();
	void KeepLockedValues();
	void PedInfo();
	int currLastCarXOld = 0, currLastCarYOld = 0, currLastCarXYShift;
	int pedHOld = -1, pedAOld = -1, pedMOld = -1;

	// important
	void OnGTAGameTick(Game* game);
	void OnGTADraw();
	void NewFunction();
};
