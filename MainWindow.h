#pragma once

// MainWindow dialog
#include "gta2-helper.h"

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
	//std::map<std::wstring, DWORD> cars;
	HMENU ncHMenu;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	bool firstPaint;
	CEdit m_log;
	HWND m_gtaWindow;
	void log(const WCHAR* fmt, ...);
	afx_msg void OnCommandsHello();
	afx_msg void MouseControl();
	bool captureMouse = 0;
	void CaptureMouse();
	afx_msg void OnSpawncarTank();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnSpawnCarClick(UINT nID);
	afx_msg void OnGetWeaponClick(UINT nID);
	afx_msg void OnPlayVocalClick(UINT nID);
	afx_msg void OnNativeCheatClick(UINT nID);
	uint frames;
	afx_msg void OnSpawncarGunjeep();
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
	void CopLockETC();
	void SetStars0();
	void SetStars1();
	void SetStars2();
	void SetStars3();
	void SetStars4();
	void SetStars5();
	void SetStars6();
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
	int wtSpawnCar = -1;
	void TeleportAllPeds();
	Ped* selectedPed = 0;
	bool beAHuman = false;
	void BeAHuman();
	void NextHuman();
	int pedXPreHuman = 0, pedYPreHuman = 0, pedZPreHuman = 0;
	void GangRespect(UINT nID);
	int currLastCarXOld = 0, currLastCarYOld = 0, currLastCarXYShift;
	void FreeShopping();
	void PrintCarInfo();
	void SyncTrailerColor();
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
	void WantToSpawnCar();

	void OnGTAGameTick(Game* game);
	void NewFunction();
};
