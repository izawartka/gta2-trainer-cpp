#pragma once

// Ped spawner dialog
#include "gta2-helper.h"
#include <vector>

extern class MainWindow;

class CameraWindow : public CDialogEx
{
	DECLARE_DYNAMIC(CameraWindow)

public:
	CameraWindow(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CameraWindow();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPositionInput();
	afx_msg void OnCheckboxChange();
	afx_msg void OnGoToTargetClick();
	afx_msg void OnTeleport();

	void OnGTAGameTick();

	MainWindow* m_mainWindow = nullptr;
	bool m_active = false;

	Player* m_player = nullptr;

	double m_xPos = 0;
	double m_yPos = 0;
	double m_zPos = 0;
	int m_zoom = 0;
	int m_followPlayer = 1;
	int m_lockZ = 0;
	int m_lockZoom = 0;
	int m_lockToTarget = 0;
};