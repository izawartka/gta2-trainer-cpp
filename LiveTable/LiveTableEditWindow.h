#pragma once

// Live table column edit dialog
#include "LiveTableData.h"
#include "LiveTableHelper.h"
#include "LiveTableWindow.h"
#include <vector>

extern class LiveTableWindow;

typedef enum LTE_LIST
{
	LTE_LIST_AVAILABLE = 0,
	LTE_LIST_SELECTED = 1
};

class LiveTableEditWindow : public CDialogEx
{
	DECLARE_DYNAMIC(LiveTableEditWindow)

public:
	LiveTableEditWindow(CWnd* pParent = nullptr);   // standard constructor
	virtual ~LiveTableEditWindow();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LTE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnInitDialog();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnListAvailableItemChange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnListSelectedItemChange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnListAvailableDoubleClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnListSelectedDoubleClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDownClick();
	afx_msg void OnRemoveClick();
	afx_msg void OnAddClick();
	afx_msg void OnUpClick();
	afx_msg void OnOK();
	void Show(LiveTableWindow* liveTableWindow, LT_MODE mode);
	void CreateItemsVectors(LT_MODE mode);
	void CreateTableItems(LTE_LIST listIndex);
	void CreateTableItem(LTE_LIST listIndex, int index, LiveTableData data);
	void SetButtonsEnabled(bool down, bool remove, bool add, bool up);
	void UpdateButtonsEnabled(LTE_LIST listIndex);
	void MoveItem(LTE_LIST srcList, int srcIndex, LTE_LIST dstList, int dstIndex);

	LT_MODE m_mode = LT_MODE_PEDS;
	LiveTableWindow* m_liveTableWindow = nullptr;
	std::vector<LiveTableData> m_availableItems;
	std::vector<LiveTableData> m_selectedItems;
	int m_selectedIndex;

	CListCtrl m_listAvailable;
	CListCtrl m_listSelected;
	CButton m_buttonDown;
	CButton m_buttonRemove;
	CButton m_buttonAdd;
	CButton m_buttonUp;
};