#pragma once

// Ped spawner dialog
#include "gta2-helper.h"
#include <vector>

extern class MainWindow;

struct PedSpawnRequest {
	SCR_f xPos;
	SCR_f yPos;
	SCR_f zPos;
	PED_REMAP remap;
	PED_REMAP2 shape;
	WEAPON_INDEX weapon;
	short health;
	PED_OCUPATION occupation;
	PED_THREAT_SEARCH threatSearch;
	PED_THREAT_REACTION threatReaction;
	PED_OBJECTIVE objective;
	short objTimer;
	PED_OBJ_TARGET_TYPE objTargetType;
	Ped* objTargetPed;
	Ped* objTargetObject;
	Car* objTargetCar;
	SCR_f objTargetX;
	SCR_f objTargetY;
	SCR_f objTargetZ;
	int aiValues[aiValuesCount];
	Ped* leader = nullptr;
	Car* car = nullptr;

	Ped* ped = nullptr;
	bool requestedSpawn = false;
};

class PedSpawnerWindow : public CDialogEx
{
	DECLARE_DYNAMIC(PedSpawnerWindow)

public:
	PedSpawnerWindow(CWnd* pParent = nullptr);   // standard constructor
	virtual ~PedSpawnerWindow();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	void ClearValues();
	void LoadPreset(int index);
	afx_msg void OnPresetSelChange();
	afx_msg void OnCustomPresetTrigger();
	void UpdateObjectiveControls();
	void GetPlayerPos();

	afx_msg void OnSpawnClick();
	bool SetObjectiveRequest(PedSpawnRequest& request);

	bool SafeSpawnPed(PedSpawnRequest& request);
	void SetPedLeader(Ped* ped, Ped* leader);
	void SetPedObjective(PedSpawnRequest& request);

	void OnGTAGameTick();

	MainWindow* m_mainWindow = nullptr;
	PedSpawnRequest m_request;

	double m_xPos = 0;
	double m_yPos = 0;
	double m_zPos = 0;
	CComboBox m_preset;
	CComboBox m_remap;
	CComboBox m_shape;
	CComboBox m_occupation;
	CComboBox m_threatSearch;
	CComboBox m_threatReaction;
	CComboBox m_objective;
	PED_OBJ_TARGET_TYPE m_objTargetType = (PED_OBJ_TARGET_TYPE)-1;
	int m_objTimer = 9999;
	int m_health = 100;
	CEdit m_objXEdit;
	CEdit m_objYEdit;
	CEdit m_objZEdit;
	double m_objX = 0;
	double m_objY = 0;
	double m_objZ = 0;
	CStatic m_objXLabel;
	CStatic m_objYLabel;
	CStatic m_objZLabel;
	CComboBox m_weapon;
	int m_aiValues[aiValuesCount] = { 0 };
	int m_leaderID = 0;
	int m_inCar = 0;

	UINT m_customPresetIndex = 0;
	UINT m_noneWeaponIndex = 0;
};