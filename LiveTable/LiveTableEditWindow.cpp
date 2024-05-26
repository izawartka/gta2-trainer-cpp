#include "../pch.h"
#include "../gta2dll.h"
#include "LiveTableEditWindow.h"

LiveTableEditWindow* lteWnd = nullptr;

IMPLEMENT_DYNAMIC(LiveTableEditWindow, CDialogEx)

LiveTableEditWindow::LiveTableEditWindow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LTE, pParent)
{
	lteWnd = this;
}

LiveTableEditWindow::~LiveTableEditWindow()
{

}

BEGIN_MESSAGE_MAP(LiveTableEditWindow, CDialogEx)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LTE_LIST_AVA, &LiveTableEditWindow::OnListAvailableItemChange)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LTE_LIST_SEL, &LiveTableEditWindow::OnListSelectedItemChange)
	ON_NOTIFY(NM_DBLCLK, IDC_LTE_LIST_AVA, &LiveTableEditWindow::OnListAvailableDoubleClick)
	ON_NOTIFY(NM_DBLCLK, IDC_LTE_LIST_SEL, &LiveTableEditWindow::OnListSelectedDoubleClick)
	ON_BN_CLICKED(IDC_LTE_DOWN, &LiveTableEditWindow::OnDownClick)
	ON_BN_CLICKED(IDC_LTE_REMOVE, &LiveTableEditWindow::OnRemoveClick)
	ON_BN_CLICKED(IDC_LTE_ADD, &LiveTableEditWindow::OnAddClick)
	ON_BN_CLICKED(IDC_LTE_UP, &LiveTableEditWindow::OnUpClick)
	ON_BN_CLICKED(IDOK, &LiveTableEditWindow::OnOK)
END_MESSAGE_MAP()


void LiveTableEditWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LTE_LIST_AVA, m_listAvailable);
	DDX_Control(pDX, IDC_LTE_LIST_SEL, m_listSelected);
	DDX_Control(pDX, IDC_LTE_DOWN, m_buttonDown);
	DDX_Control(pDX, IDC_LTE_REMOVE, m_buttonRemove);
	DDX_Control(pDX, IDC_LTE_ADD, m_buttonAdd);
	DDX_Control(pDX, IDC_LTE_UP, m_buttonUp);
}

int LiveTableEditWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
}

BOOL LiveTableEditWindow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	UpdateData(FALSE);

	m_listAvailable.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_listAvailable.InsertColumn(0, L"Name", LVCFMT_LEFT, 100);
	m_listAvailable.InsertColumn(1, L"Offset(s)", LVCFMT_LEFT, 100);
	m_listAvailable.InsertColumn(2, L"Type", LVCFMT_LEFT, 100);
	m_listAvailable.InsertColumn(3, L"Size", LVCFMT_LEFT, 100);

	m_listSelected.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_listSelected.InsertColumn(0, L"Name", LVCFMT_LEFT, 100);
	m_listSelected.InsertColumn(1, L"Offset(s)", LVCFMT_LEFT, 100);
	m_listSelected.InsertColumn(2, L"Type", LVCFMT_LEFT, 100);
	m_listSelected.InsertColumn(3, L"Size", LVCFMT_LEFT, 100);

	return TRUE;
}

void LiveTableEditWindow::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 640;
	lpMMI->ptMinTrackSize.y = 480;

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

void LiveTableEditWindow::OnListAvailableItemChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	POSITION pos = m_listAvailable.GetFirstSelectedItemPosition();
	m_selectedIndex = m_listSelected.GetNextSelectedItem(pos);

	UpdateButtonsEnabled(LTE_LIST_AVAILABLE);
}


void LiveTableEditWindow::OnListSelectedItemChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	POSITION pos = m_listSelected.GetFirstSelectedItemPosition();
	m_selectedIndex = m_listSelected.GetNextSelectedItem(pos);

	UpdateButtonsEnabled(LTE_LIST_SELECTED);
}

void LiveTableEditWindow::OnListAvailableDoubleClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	MoveItem(LTE_LIST_AVAILABLE, pNMItemActivate->iItem, LTE_LIST_SELECTED, m_selectedItems.size());
}

void LiveTableEditWindow::OnListSelectedDoubleClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;

	if(pNMItemActivate->iItem < 2)
		return;

	MoveItem(LTE_LIST_SELECTED, pNMItemActivate->iItem, LTE_LIST_AVAILABLE, m_availableItems.size());
}

void LiveTableEditWindow::OnDownClick()
{
	MoveItem(LTE_LIST_SELECTED, m_selectedIndex, LTE_LIST_SELECTED, m_selectedIndex + 1);
}


void LiveTableEditWindow::OnRemoveClick()
{
	MoveItem(LTE_LIST_SELECTED, m_selectedIndex, LTE_LIST_AVAILABLE, m_availableItems.size());
}


void LiveTableEditWindow::OnAddClick()
{
	MoveItem(LTE_LIST_AVAILABLE, m_selectedIndex, LTE_LIST_SELECTED, m_selectedItems.size());
}


void LiveTableEditWindow::OnUpClick()
{
	MoveItem(LTE_LIST_SELECTED, m_selectedIndex, LTE_LIST_SELECTED, m_selectedIndex - 1);
}

void LiveTableEditWindow::OnOK()
{
	std::vector<LiveTableData>* selectedItems = LiveTableHelper::GetSelectedData(m_mode);

	selectedItems->clear();
	selectedItems->insert(selectedItems->begin(), m_selectedItems.begin(), m_selectedItems.end());

	m_liveTableWindow->SendMessage(WM_LT_COLUMNS_UPDATE, m_mode, (LPARAM)&m_selectedItems);

	CDialogEx::OnOK();
}


void LiveTableEditWindow::Show(LiveTableWindow* liveTableWindow, LT_MODE mode)
{
	this->m_liveTableWindow = liveTableWindow;
	this->m_mode = mode;

	this->ShowWindow(SW_SHOW);
	this->SetFocus();

	CString caption;
	caption.Format(L"Edit columns - %s", LT_MODE_STR[m_mode]);
	this->SetWindowText(caption);

	CreateItemsVectors(mode);

	CreateTableItems(LTE_LIST_AVAILABLE);
	CreateTableItems(LTE_LIST_SELECTED);
}

void LiveTableEditWindow::CreateItemsVectors(LT_MODE mode)
{
	std::vector<LiveTableData>* selectedItems = LiveTableHelper::GetSelectedData(mode);

	m_selectedItems.clear();
	m_selectedItems.insert(m_selectedItems.begin(), selectedItems->begin(), selectedItems->end());
	m_availableItems.clear();

	for (int i = 0; i < ltDataCount[m_mode]; i++) {
		LiveTableData data = ltData[m_mode][i];

		bool found = false;

		for (int j = 0; j < m_selectedItems.size(); j++) {
			if (m_selectedItems.at(j).name == data.name) {
				found = true;
				break;
			}
		}

		if (!found)
			m_availableItems.push_back(data);
	}
}

void LiveTableEditWindow::CreateTableItems(LTE_LIST listIndex)
{
	CListCtrl* list = listIndex == LTE_LIST_AVAILABLE ? &m_listAvailable : &m_listSelected;
	std::vector<LiveTableData>* items = listIndex == LTE_LIST_AVAILABLE ? &m_availableItems : &m_selectedItems;

	list->DeleteAllItems();

	for (int i = 0; i < items->size(); i++)
	{
		LiveTableData data = items->at(i);

		CreateTableItem(listIndex, i, data);
	}

	list->SetColumnWidth(0, LVSCW_AUTOSIZE);
	list->SetColumnWidth(1, LVSCW_AUTOSIZE);
	list->SetColumnWidth(2, LVSCW_AUTOSIZE);
	list->SetColumnWidth(3, 40);
}

void LiveTableEditWindow::CreateTableItem(LTE_LIST listIndex, int index, LiveTableData data)
{
	CListCtrl* list = listIndex == LTE_LIST_AVAILABLE ? &m_listAvailable : &m_listSelected;

	int i = list->InsertItem(index, data.name);

	CString offsetsStr;
	for (int j = 0; j < data.offsetsCount; j++)
	{
		offsetsStr.AppendFormat(L"0x%X", data.offsets[j]);
		if (j < data.offsetsCount - 1)
			offsetsStr.Append(L", ");
	}

	list->SetItemText(i, 1, offsetsStr);

	CString typeStr = LT_DATA_TYPE_STR[data.type];
	list->SetItemText(i, 2, typeStr);

	CString sizeStr;
	sizeStr.Format(L"%d", data.size);
	list->SetItemText(i, 3, sizeStr);

	list->SetItemData(i, index);
}

void LiveTableEditWindow::SetButtonsEnabled(bool down, bool remove, bool add, bool up)
{
	m_buttonDown.EnableWindow(down);
	m_buttonRemove.EnableWindow(remove);
	m_buttonAdd.EnableWindow(add);
	m_buttonUp.EnableWindow(up);
}

void LiveTableEditWindow::UpdateButtonsEnabled(LTE_LIST listIndex)
{
	if (m_selectedIndex == -1) {
		SetButtonsEnabled(false, false, false, false);
		return;
	}

	if(listIndex == LTE_LIST_AVAILABLE)
	{
		SetButtonsEnabled(false, false, true, false);
		return;
	}

	if (m_selectedIndex < 2) {
		SetButtonsEnabled(false, false, false, false);
		return;
	}

	bool up = m_selectedIndex != 2;
	bool down = m_selectedIndex != m_selectedItems.size() - 1;

	SetButtonsEnabled(down, true, false, up);
}

void LiveTableEditWindow::MoveItem(LTE_LIST srcList, int srcIndex, LTE_LIST dstList, int dstIndex)
{
	std::vector<LiveTableData>* srcItems = srcList == LTE_LIST_AVAILABLE ? &m_availableItems : &m_selectedItems;
	std::vector<LiveTableData>* dstItems = dstList == LTE_LIST_AVAILABLE ? &m_availableItems : &m_selectedItems;

	LiveTableData data = srcItems->at(srcIndex);
	srcItems->erase(srcItems->begin() + srcIndex);
	dstItems->insert(dstItems->begin() + dstIndex, data);

	CListCtrl* srcListCtrl = srcList == LTE_LIST_AVAILABLE ? &m_listAvailable : &m_listSelected;
	CListCtrl* dstListCtrl = dstList == LTE_LIST_AVAILABLE ? &m_listAvailable : &m_listSelected;

	srcListCtrl->DeleteItem(srcIndex);
	CreateTableItem(dstList, dstIndex, data);

	dstListCtrl->SetItemState(dstIndex, LVIS_SELECTED, LVIS_SELECTED);
	dstListCtrl->SetFocus();

	m_selectedIndex = dstIndex;
	UpdateButtonsEnabled(dstList);
}