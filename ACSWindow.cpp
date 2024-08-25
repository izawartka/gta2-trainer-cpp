#include "pch.h"
#include "gta2dll.h"
#include "ACSWindow.h"

ACSWindow* acsWnd = nullptr;

IMPLEMENT_DYNAMIC(ACSWindow, CDialogEx)

ACSWindow::ACSWindow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ACS, pParent)
{
	acsWnd = this;
}

ACSWindow::~ACSWindow()
{

}

BEGIN_MESSAGE_MAP(ACSWindow, CDialogEx)
	ON_BN_CLICKED(IDC_ACS_SPAWN, &ACSWindow::OnSpawnClick)
	ON_BN_CLICKED(IDC_ACS_GETPPOS, &ACSWindow::GetPlayerPos)
END_MESSAGE_MAP()


void ACSWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ACS_X, m_xPos);
	DDX_Text(pDX, IDC_ACS_Y, m_yPos);
	DDX_Text(pDX, IDC_ACS_Z, m_zPos);
	DDX_Text(pDX, IDC_ACS_ROT, m_rot);
	DDX_Text(pDX, IDC_ACS_XSIZE, m_xSize);
	DDX_Text(pDX, IDC_ACS_YSIZE, m_ySize);
	DDX_Text(pDX, IDC_ACS_XOFF, m_xOffset);
	DDX_Text(pDX, IDC_ACS_YOFF, m_yOffset);
	DDX_Check(pDX, IDC_ACS_VCOLORS, m_variateColors);
	DDX_Check(pDX, IDC_ACS_MINICAR, m_miniCar);
	DDX_Control(pDX, IDC_ACS_MODEL, m_model);
}

int ACSWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
}

void ACSWindow::OnSpawnClick()
{
	if (m_model.GetCurSel() < 0) return;
	unsigned int model = cars[m_model.GetCurSel()].id;

	UpdateData(TRUE);

	short color = m_variateColors == true ? -2 : -1;
	short rot = m_rot * 4;
	bool miniCar = m_miniCar == 1 ? true : false;

	SCR_f xPos = m_xPos * 16384.0;
	SCR_f yPos = m_yPos * 16384.0;
	SCR_f zPos = m_zPos * 16384.0;
	SCR_f xOffset = m_xOffset * 16384.0;
	SCR_f yOffset = m_yOffset * 16384.0;
	SCR_f xPosMax = xPos + m_xSize * xOffset;
	SCR_f yPosMax = yPos + m_ySize * yOffset;

	// coordinates check
	if (!IsPointSafe(xPos, yPos, zPos) || !IsPointSafe(xPosMax, yPosMax, zPos)) {
		MessageBox(L"Target position is out of the map");
		return;
	}

	for (int x = 0; x < m_xSize; x++)
	{
		for (int y = 0; y < m_ySize; y++)
		{
			if (m_mainWindow->wtsCarSize > 126) return;

			int targetX = xPos + x * xOffset;
			int targetY = yPos + y * yOffset;

			m_mainWindow->wtsCar[m_mainWindow->wtsCarSize] = WantToSpawn{ targetX, targetY, zPos, rot, model, color, miniCar };
			m_mainWindow->wtsCarSize++;
		}
	}
}

void ACSWindow::ClearValues()
{
	m_xPos = 0.0;
	m_yPos = 0.0;
	m_zPos = 0.0;
	m_rot = 0;
	m_xSize = 1;
	m_ySize = 1;
	m_xOffset = 1.0;
	m_yOffset = 1.0;
	m_variateColors = false;
	m_miniCar = false;

	UpdateData(FALSE);

	m_model.ResetContent();
	int carsCount = sizeof(cars) / sizeof(cars[0]);
	for (int i = 0; i < carsCount; i++)
		m_model.AddString(cars[i].name);
	m_model.SetCurSel(0);

	GetPlayerPos();
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

	UpdateData(TRUE);

	m_xPos = playerPed->gameObject->sprite->x / 16384.;
	m_yPos = playerPed->gameObject->sprite->y / 16384.;
	m_zPos = playerPed->gameObject->sprite->z / 16384.;

	UpdateData(FALSE);
}