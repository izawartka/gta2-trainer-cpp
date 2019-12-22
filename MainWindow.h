#pragma once

// MainWindow dialog
#include "gta2.segments.fixed.exe.h"

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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	bool firstPaint;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDebugMakeInt3Crash();
	CEdit m_log;
	HWND m_gtaWindow;
	void log(const WCHAR* fmt, ...);
	afx_msg void OnCommandsHello();
	afx_msg void OnCommandsCaptureMouse();
	bool captureMouse = 0;
	void CaptureMouse();
	afx_msg void OnSpawncarTank();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnSpawncarGt();
	afx_msg void OnSpawnCarClick(UINT nID);
	afx_msg void OnGetWeaponClick(UINT nID);
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
	void DetonateLastCar();
	void GiveUnlimitedAmmo();
	void FixCar();
	void VisFixCar();
	void ShowPedIDs();
	void PedInfo();
};
