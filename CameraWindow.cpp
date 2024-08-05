#include "pch.h"
#include "gta2dll.h"
#include "CameraWindow.h"
#include "gta2-helper.h"

CameraWindow* camWnd = nullptr;

IMPLEMENT_DYNAMIC(CameraWindow, CDialogEx)

CameraWindow::CameraWindow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PS, pParent)
{
	camWnd = this;
}

CameraWindow::~CameraWindow()
{

}

BEGIN_MESSAGE_MAP(CameraWindow, CDialogEx)
	ON_EN_CHANGE(IDC_CAM_X, &CameraWindow::OnPositionInput)
	ON_EN_CHANGE(IDC_CAM_Y, &CameraWindow::OnPositionInput)
	ON_EN_CHANGE(IDC_CAM_Z, &CameraWindow::OnPositionInput)
	ON_EN_CHANGE(IDC_CAM_ZOOM, &CameraWindow::OnPositionInput)
	ON_BN_CLICKED(IDC_CAM_SYNC, &CameraWindow::OnGoToTargetClick)
	ON_BN_CLICKED(IDC_CAM_FPL, &CameraWindow::OnCheckboxChange)
	ON_BN_CLICKED(IDC_CAM_ZL, &CameraWindow::OnCheckboxChange)
	ON_BN_CLICKED(IDC_CAM_ZOOML, &CameraWindow::OnCheckboxChange)
	ON_BN_CLICKED(IDC_CAM_TARL, &CameraWindow::OnCheckboxChange)
	ON_BN_CLICKED(IDC_CAM_TP, &CameraWindow::OnTeleport)
END_MESSAGE_MAP()


void CameraWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CAM_X, m_xPos);
	DDX_Text(pDX, IDC_CAM_Y, m_yPos);
	DDX_Text(pDX, IDC_CAM_Z, m_zPos);
	DDX_Text(pDX, IDC_CAM_ZOOM, m_zoom);
	DDX_Check(pDX, IDC_CAM_FPL, m_followPlayer);
	DDX_Check(pDX, IDC_CAM_ZL, m_lockZ);
	DDX_Check(pDX, IDC_CAM_ZOOML, m_lockZoom);
	DDX_Check(pDX, IDC_CAM_TARL, m_lockToTarget);
}

int CameraWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
}

void CameraWindow::OnPositionInput()
{
	if (!m_player) return;

	UpdateData(TRUE);

	m_player->ph1.cameraPos.x = FloatEncode(m_xPos);
	m_player->ph1.cameraPos.y = FloatEncode(m_yPos);
	m_player->ph1.cameraPos.z = FloatEncode(m_zPos);
	m_player->ph1.cameraPos.zoom = m_zoom;

	m_followPlayer = 0;
	m_player->ph1.followedPedID = 0;

	UpdateData(FALSE);
}

void CameraWindow::OnCheckboxChange()
{
	if (!m_player) return;

	UpdateData(TRUE);
	m_player->ph1.followedPedID = m_followPlayer == 1 ? 1 : 0;
}

void CameraWindow::OnGTAGameTick()
{
	if (!this->IsWindowVisible()) return;
	
	// Return if not in the game
	if (*(DWORD*)ptrToPedManager == 0)
	{
		m_player = nullptr;
		return;
	}

	Game* pGame = (Game*)*(DWORD*)ptrToGame;
	if (!pGame) return;

	m_player = pGame->CurrentPlayer;
	if (!m_player) return;

	if (m_lockToTarget) {
		m_player->ph1.cameraPos = m_player->ph1.cameraPosTarget;
	}

	m_xPos = FloatDecode(m_player->ph1.cameraPos.x);
	m_yPos = FloatDecode(m_player->ph1.cameraPos.y);

	if (m_lockZ) {
		m_player->ph1.cameraPos.z = FloatEncode(m_zPos);
	}
	else {
		m_zPos = FloatDecode(m_player->ph1.cameraPos.z);
	}

	if (m_lockZoom) {
		m_player->ph1.cameraPos.zoom = m_zoom;
	}
	else {
		m_zoom = m_player->ph1.cameraPos.zoom;
	}

	m_followPlayer = m_player->ph1.followedPedID == 1 ? 1 : 0;

	UpdateData(FALSE);
}


void CameraWindow::OnGoToTargetClick()
{
	if (!m_player) return;

	m_player->ph1.cameraPos = m_player->ph1.cameraPosTarget;
}


void CameraWindow::OnTeleport()
{
	if (!m_player) return;

	fnDoTeleport(m_player, m_xPos, m_yPos);
}
