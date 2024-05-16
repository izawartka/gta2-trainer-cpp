#include "pch.h"
#include "gta2dll.h"
#include "LiveTableWindow.h"

LiveTableWindow* psWnd = nullptr;

IMPLEMENT_DYNAMIC(LiveTableWindow, CDialogEx)

LiveTableWindow::LiveTableWindow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LT, pParent)
{
	psWnd = this;
}

LiveTableWindow::~LiveTableWindow()
{

}

BEGIN_MESSAGE_MAP(LiveTableWindow, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LT_LIST, &LiveTableWindow::OnListEntryDoubleClick)
END_MESSAGE_MAP()


void LiveTableWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LT_LIST, m_list);
}

int LiveTableWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
}

BOOL LiveTableWindow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetTableMode(m_tableMode);

	return TRUE;
}

void LiveTableWindow::OnListEntryDoubleClick(NMHDR* pNMHDR, LRESULT* pResult)
{

}

void LiveTableWindow::SetTableMode(LT_MODE mode) {
	m_tableMode = mode;

	m_list.DeleteAllItems();
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_list.InsertColumn(0, L"Address", LVCFMT_LEFT, 100);
	m_list.InsertColumn(1, L"ID", LVCFMT_LEFT, 30);
}

void LiveTableWindow::Update()
{

}