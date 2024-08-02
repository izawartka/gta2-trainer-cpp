#pragma once

// Ped spawner dialog
#include "gta2-helper.h"
#include <vector>

extern class MainWindow;

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
	void GetPlayerPos();
	afx_msg void OnSpawnClick();
	static void SetPedAiValues(Ped* ped, int* values);

	MainWindow* m_mainWindow = nullptr;

	double m_xPos = 0;
	double m_yPos = 0;
	double m_zPos = 0;
	CComboBox m_preset;
	CComboBox m_remap;
	CComboBox m_shape;
	CComboBox m_occupation;
	CComboBox m_threatSearch;
	CComboBox m_threatReaction;
	short m_health = 100;
	CComboBox m_weapon;
	int m_aiValues[aiValuesCount] = { 0 };
	int m_leaderID = 0;

	UINT m_customPresetIndex = 0;
	UINT m_noneWeaponIndex = 0;

};