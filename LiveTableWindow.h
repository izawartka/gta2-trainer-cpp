#pragma once

// Live table dialog
#include "gta2-helper.h"
#include <vector>

extern class MainWindow;

typedef enum LT_MODE {
	LT_MODE_PEDS = 1
} LT_MODE;

class LiveTableWindow : public CDialogEx
{
	DECLARE_DYNAMIC(LiveTableWindow)

public:
	LiveTableWindow(CWnd* pParent = nullptr);   // standard constructor
	virtual ~LiveTableWindow();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnInitDialog();
	afx_msg void OnListEntryDoubleClick(NMHDR* pNMHDR, LRESULT* pResult);

	void SetTableMode(LT_MODE mode);
	void Update();

	MainWindow* m_mainWindow = nullptr;
	LT_MODE m_tableMode = LT_MODE_PEDS;
	
	CComboBox m_type;
	CListCtrl m_list;

};