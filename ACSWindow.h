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

	void ExecuteACS();
	void ClearValues();
	void GetPlayerPos();
	float GetFloatFromCEditVal(CEdit* element);

	MainWindow* m_mainWindow = nullptr;

	CEdit m_xPos;
	CEdit m_yPos;
	CEdit m_zPos;
	CEdit m_rot;
	CEdit m_xSize;
	CEdit m_ySize;
	CEdit m_xOffset;
	CEdit m_yOffset;
	CComboBox m_model;
	CButton m_variateColors;
	bool variateColors;
};