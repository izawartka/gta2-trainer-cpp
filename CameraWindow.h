#pragma once

// Ped spawner dialog
#include "gta2-helper.h"
#include "CameraMoveBtn.h"
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
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPositionInput();
	afx_msg void OnCheckboxChange();
	afx_msg void OnGoToTargetClick();
	afx_msg void OnTeleport();
	afx_msg void OnAntialiasingChange();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg LRESULT OnMoveButton(WPARAM wParam, LPARAM lParam);

	void HandleButtonMove();
	void SetAntialiasing(bool enable);

public:
	void OnGTAGameTick();

	bool m_active = false;
	MainWindow* m_mainWindow = nullptr;

protected:
	Player* m_player = nullptr;

	double m_xPos = 0;
	double m_yPos = 0;
	double m_zPos = 0;
	int m_zoom = 0;
	int m_followPlayer = 1;
	int m_lockZ = 0;
	int m_lockZoom = 0;
	int m_lockToTarget = 0;
	CameraMoveBtn m_moveBtns[6];
	UINT m_btnMoveDirection = 0;
	CSliderCtrl m_sensitivitySlider;
	int m_sensitivity = 10;
	int m_antialiasing = 1;
};