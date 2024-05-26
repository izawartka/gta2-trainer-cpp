#pragma once

// Live table dialog
#include "../gta2-helper.h"
#include <vector>
#include <map>
#include "LiveTableData.h"
#include "LiveTableEditWindow.h"

extern class MainWindow;

#define WM_LT_COLUMNS_UPDATE (WM_USER + 1)

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
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnListEntryDoubleClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateCheckboxChange();
	afx_msg void OnSortCheckboxChange();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEditColumnsClick();
	afx_msg void OnModeSelChange();
	afx_msg LRESULT OnColumnsUpdate(WPARAM wParam, LPARAM lParam);

	void UpdateTimerState();
	void Rebuild();
	void Update();
	void SortList();

	MainWindow* m_mainWindow = nullptr;
	LiveTableEditWindow* m_editWindow = nullptr;
	LT_MODE m_mode = LT_MODE_PEDS;
	std::vector<LiveTableData>* m_selectedData;
	
	CComboBox m_modeCombo;
	CListCtrl m_list;
	int m_doUpdate = 1;
	int m_doSort = 1;

	std::map<int, int> m_listKeyToIndex = {};
};