#include "pch.h"
#include "gta2dll.h"
#include "ACSWindow.h"

ACSWindow* acsWnd = nullptr;

IMPLEMENT_DYNAMIC(ACSWindow, CDialogEx)

ACSWindow::ACSWindow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{
	acsWnd = this;
}

ACSWindow::~ACSWindow()
{

}

BEGIN_MESSAGE_MAP(ACSWindow, CDialogEx)
	ON_BN_CLICKED(IDC_ACS_SPAWN, &ACSWindow::ExecuteACS)
	ON_BN_CLICKED(IDC_ACS_GETPPOS, &ACSWindow::GetPlayerPos)
END_MESSAGE_MAP()


void ACSWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ACS_X, m_xPos);
	DDX_Control(pDX, IDC_ACS_Y, m_yPos);
	DDX_Control(pDX, IDC_ACS_Z, m_zPos);
	DDX_Control(pDX, IDC_ACS_ROT, m_rot);
	DDX_Control(pDX, IDC_ACS_ROT, m_rot);
	DDX_Control(pDX, IDC_ACS_XSIZE, m_xSize);
	DDX_Control(pDX, IDC_ACS_YSIZE, m_ySize);
	DDX_Control(pDX, IDC_ACS_XOFF, m_xOffset);
	DDX_Control(pDX, IDC_ACS_YOFF, m_yOffset);
	DDX_Control(pDX, IDC_ACS_MODEL, m_model);
}

int ACSWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
}

float ACSWindow::GetFloatFromCEditVal(CEdit* element)
{
	CString buffer;
	element->GetWindowTextW(buffer);
	return _wtof(buffer);
}

void ACSWindow::ExecuteACS()
{
	int model = m_mainWindow->carids[m_model.GetCurSel()];
	int xPos = GetFloatFromCEditVal(&m_xPos) * 16384.0f;
	int yPos = GetFloatFromCEditVal(&m_yPos) * 16384.0f;
	int zPos = GetFloatFromCEditVal(&m_zPos) * 16384.0f;
	int rot = GetFloatFromCEditVal(&m_rot) * 4;
	int xSize = GetFloatFromCEditVal(&m_xSize);
	int ySize = GetFloatFromCEditVal(&m_ySize);
	int xOffset = GetFloatFromCEditVal(&m_xOffset) * 16384.0f;
	int yOffset = GetFloatFromCEditVal(&m_yOffset) * 16384.0f;

	for (int x = 0; x < xSize; x++)
	{
		for (int y = 0; y < ySize; y++)
		{
			if (m_mainWindow->wtsCarSize > 126) return;

			int targetX = xPos + x * xOffset;
			int targetY = yPos + y * yOffset;

			m_mainWindow->wtsCar[m_mainWindow->wtsCarSize] = WantToSpawn(targetX, targetY, zPos, rot, model);
			m_mainWindow->wtsCarSize++;
		}
	}

	::DestroyWindow(acsWnd->m_hWnd);
}

void ACSWindow::ClearValues()
{
	m_xPos.SetWindowTextW(L"0");
	m_yPos.SetWindowTextW(L"0");
	m_zPos.SetWindowTextW(L"2");
	m_rot.SetWindowTextW(L"0");
	m_xSize.SetWindowTextW(L"1");
	m_ySize.SetWindowTextW(L"1");
	m_xOffset.SetWindowTextW(L"1");
	m_yOffset.SetWindowTextW(L"1");
	m_model.ResetContent();
	for (int i = 0; i < 80; i++)
		m_model.AddString(m_mainWindow->carnames[i]);
}

void ACSWindow::GetPlayerPos()
{
	// Return if not in the game
	if (*(DWORD*)ptrToPedManager == 0)
		return;

	Ped* playerPed = fnGetPedByID(1);
	
	// Return if player ped not found
	if (!playerPed || !playerPed->gameObject || !playerPed->gameObject->sprite)
		return;

	WCHAR buf[256];

	swprintf(buf, 256, L"%f", playerPed->gameObject->sprite->x / 16384.0f);
	m_xPos.SetWindowTextW(buf);

	swprintf(buf, 256, L"%f", playerPed->gameObject->sprite->y / 16384.0f);
	m_yPos.SetWindowTextW(buf);

	swprintf(buf, 256, L"%f", playerPed->gameObject->sprite->z / 16384.0f);
	m_zPos.SetWindowTextW(buf);

	swprintf(buf, 256, L"%i", playerPed->gameObject->sprite->rotation/4);
	m_rot.SetWindowTextW(buf);
}