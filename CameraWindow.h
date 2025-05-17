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
	afx_msg void OnShadowsChange();
	afx_msg void OnNightChange();
	afx_msg void OnNoLightsChange();
	afx_msg void OnRotationModeChange(UINT nID);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg LRESULT OnMoveButton(WPARAM wParam, LPARAM lParam);

	void HandleButtonMove();
	void SetAntialiasing(bool enable);
	void SetShadows(bool enable);
	void SetNight(bool enable);
	void SetNoLights(bool enable);

public:
	void OnGTAGameTick();
	void ApplyShadowsDistanceFix();
	void UpdateShadowsDistance();

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
	CameraMoveBtn m_moveBtns[8];
	UINT m_btnMoveDirection = 0;
	CSliderCtrl m_sensitivitySlider;
	CSliderCtrl m_horAngleSlider;
	int m_sensitivity = 10;
	int m_antialiasing = 1;
	int m_shadows = 1;
	int m_noLights = 0;
	int m_night = 0;
	int m_followRotation = 0;
	int m_forceClearScreen = 0;

	int m_shadowsDummyUIScale = 32768;
};