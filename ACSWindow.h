#pragma once

// Advanced car spawner dialog
#include "gta2-helper.h"

extern class MainWindow;

class ACSWindow : public CDialogEx
{
	DECLARE_DYNAMIC(ACSWindow)

public:
	ACSWindow(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ACSWindow();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	void OnSpawnClick();
	void ClearValues();
	void GetPlayerPos();

	MainWindow* m_mainWindow = nullptr;

	double m_xPos;
	double m_yPos;
	double m_zPos;
	double m_rot;
	unsigned int m_xSize;
	unsigned int m_ySize;
	double m_xOffset;
	double m_yOffset;
	CComboBox m_model;
	int m_variateColors;
};