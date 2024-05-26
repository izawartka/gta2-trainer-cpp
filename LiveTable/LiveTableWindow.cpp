#include "../pch.h"
#include "../gta2dll.h"
#include "LiveTableWindow.h"
#include "LiveTableHelper.h"

LiveTableWindow* ltWnd = nullptr;

IMPLEMENT_DYNAMIC(LiveTableWindow, CDialogEx)

LiveTableWindow::LiveTableWindow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LT, pParent)
{
	ltWnd = this;

	m_editWindow = new LiveTableEditWindow(this);
	m_editWindow->Create(IDD_LTE, this);
	m_editWindow->ShowWindow(SW_HIDE);
}

LiveTableWindow::~LiveTableWindow()
{

}

BEGIN_MESSAGE_MAP(LiveTableWindow, CDialogEx)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_NOTIFY(NM_DBLCLK, IDC_LT_LIST, &LiveTableWindow::OnListEntryDoubleClick)
	ON_BN_CLICKED(IDC_LT_UPDATE, &LiveTableWindow::OnUpdateCheckboxChange)
	ON_BN_CLICKED(IDC_LT_SORT, &LiveTableWindow::OnSortCheckboxChange)
	ON_BN_CLICKED(IDC_LT_EDIT, &LiveTableWindow::OnEditColumnsClick)
	ON_MESSAGE(WM_LT_COLUMNS_UPDATE, &LiveTableWindow::OnColumnsUpdate)
	ON_CBN_SELCHANGE(IDC_LT_MODE, &LiveTableWindow::OnModeSelChange)
END_MESSAGE_MAP()


void LiveTableWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LT_LIST, m_list);
	DDX_Check(pDX, IDC_LT_UPDATE, m_doUpdate);
	DDX_Check(pDX, IDC_LT_SORT, m_doSort);
	DDX_Control(pDX, IDC_LT_MODE, m_modeCombo);
}

int LiveTableWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
}

BOOL LiveTableWindow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	UpdateData(FALSE);

	m_modeCombo.ResetContent();
	for(int i = 0; i < LT_MODE_COUNT; i++) {
		m_modeCombo.AddString(LT_MODE_STR[i]);
	}

	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	Rebuild();

	return TRUE;
}

void LiveTableWindow::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 640;
	lpMMI->ptMinTrackSize.y = 480;

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

void LiveTableWindow::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		UpdateTimerState();
	}
	else {
		KillTimer(1);
	}
}

void LiveTableWindow::OnListEntryDoubleClick(NMHDR* pNMHDR, LRESULT* pResult)
{

}

void LiveTableWindow::OnUpdateCheckboxChange()
{
	UpdateData(TRUE);
	UpdateTimerState();
}

void LiveTableWindow::OnSortCheckboxChange()
{
	UpdateData(TRUE);
}

void LiveTableWindow::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) {
		Update();
	}

	CDialogEx::OnTimer(nIDEvent);
}

void LiveTableWindow::OnEditColumnsClick()
{
	m_editWindow->Show(this, m_mode);
}

void LiveTableWindow::OnModeSelChange()
{
	int mode = m_modeCombo.GetCurSel();

	m_mode = (LT_MODE)mode;
	Rebuild();
}


LRESULT LiveTableWindow::OnColumnsUpdate(WPARAM wParam, LPARAM lParam)
{
	Rebuild();

	return 0;
}

void LiveTableWindow::UpdateTimerState()
{
	if (m_doUpdate) {
		SetTimer(1, LT_REFRESH_INTERVAL, NULL);
	} else {
		KillTimer(1);
	}
}

void LiveTableWindow::Rebuild() {
	CString caption;
	caption.Format(L"Live table - %s", LT_MODE_STR[m_mode]);
	this->SetWindowText(caption);

	m_modeCombo.SetCurSel(m_mode);

	m_listKeyToIndex.clear();
	m_list.DeleteAllItems();

	while (m_list.DeleteColumn(0));

	m_selectedData = LiveTableHelper::GetSelectedData(m_mode);

	for(int i = 0; i < m_selectedData->size(); i++) {
		LiveTableData data = m_selectedData->at(i);
		m_list.InsertColumn(i, data.name, LVCFMT_LEFT, data.width);
	}
}

void LiveTableWindow::Update()
{
	void* firstItem = nullptr;
	int itemsCount = -1;
	LiveTableHelper::GetItems(m_mode, firstItem, itemsCount);

	if (itemsCount == -1) {
		m_list.DeleteAllItems();
		m_listKeyToIndex.clear();
		return;
	}

	LiveTableData keyData = m_selectedData->at(0);

	// mark all list items as not in use
	// if they are still in use, they will be marked as in use later
	int listItemsCount = m_list.GetItemCount();
	for(int i = 0; i < listItemsCount; i++) {
		m_list.SetItemData(i, 0);
	}

	// mark back all items that are still in use
	// and store new items (recently spawned peds)
	bool failed = false; // dummy variable
	std::vector<void*> newItems;
	for (int i = 0; i < itemsCount; i++) {
		void* item = (void*)((int)firstItem + i * ltItemSize[m_mode]);

		int key = LiveTableHelper::GetData(item, keyData, &failed);
		if(key == 0) continue;

		auto foundIndex = m_listKeyToIndex.find(key);

		if (foundIndex == m_listKeyToIndex.end()) {
			newItems.push_back(item);
			continue;
		}

		int index = foundIndex->second;
		m_list.SetItemData(index, (int)item);
	}

	// remove items that are not in use anymore
	bool removedItems = false;
	for(int i = 0; i < m_list.GetItemCount(); i++) {
		if(m_list.GetItemData(i) != 0) continue;

		m_list.DeleteItem(i);
		i--;
		removedItems = true;
	}

	// add new items
	for(void* item : newItems) {
		int index = m_list.InsertItem(m_list.GetItemCount(), L"");
		m_list.SetItemData(index, (int)item);
	}

	// if any changes were made, sort the list again and rebuild the index map
	if (newItems.size() > 0 || removedItems) {
		SortList();

		// update indexes map
		m_listKeyToIndex.clear();
		int itemsCount = m_list.GetItemCount();
		for (int i = 0; i < itemsCount; i++) {
			void* item = (void*)m_list.GetItemData(i);
			int key = LiveTableHelper::GetData(item, keyData, &failed);
			m_listKeyToIndex[key] = i;
		}
	}

	// update list view
	for (int i = 0; i < m_list.GetItemCount(); i++) {
		void* item = (void*)m_list.GetItemData(i);

		for (int v = 0; v < m_selectedData->size(); v++) {
			CString valueStr = LiveTableHelper::GetDataString(item, m_selectedData->at(v));

			if (m_list.GetItemText(i, v) != valueStr)
				m_list.SetItemText(i, v, valueStr);
		}
	}
}

void LiveTableWindow::SortList()
{
	if(!m_doSort) return;

	m_list.SortItems([](LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) -> int {
		LiveTableData keyData = ltWnd->m_selectedData->at(0);

		bool failed = false; // dummy variable

		int key1 = LiveTableHelper::GetData((void*)lParam1, keyData, &failed);
		int key2 = LiveTableHelper::GetData((void*)lParam2, keyData, &failed);

		return key1 - key2;
	}, 0);
}