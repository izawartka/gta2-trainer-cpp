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
	ON_BN_CLICKED(IDC_CAM_AA, &CameraWindow::OnAntialiasingChange)
	ON_BN_CLICKED(IDC_CAM_SHADOWS, &CameraWindow::OnShadowsChange)
	ON_BN_CLICKED(IDC_CAM_NIGHT, &CameraWindow::OnNightChange)
	ON_BN_CLICKED(IDC_CAM_NOLIGHTS, &CameraWindow::OnNoLightsChange)
	ON_MESSAGE(WM_CAMERA_MOVE_BTN, &CameraWindow::OnMoveButton)
	ON_WM_HSCROLL()
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
	DDX_Control(pDX, IDC_CAM_SEN, m_sensitivitySlider);
	DDX_Check(pDX, IDC_CAM_AA, m_antialiasing);
	DDX_Check(pDX, IDC_CAM_SHADOWS, m_shadows);
	DDX_Check(pDX, IDC_CAM_NIGHT, m_night);
	DDX_Check(pDX, IDC_CAM_NOLIGHTS, m_noLights);
}

BOOL CameraWindow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_moveBtns[0].SubclassDlgItem(IDC_CAM_UP, this);
	m_moveBtns[1].SubclassDlgItem(IDC_CAM_DOWN, this);
	m_moveBtns[2].SubclassDlgItem(IDC_CAM_LEFT, this);
	m_moveBtns[3].SubclassDlgItem(IDC_CAM_RIGHT, this);
	m_moveBtns[4].SubclassDlgItem(IDC_CAM_ZUP, this);
	m_moveBtns[5].SubclassDlgItem(IDC_CAM_ZDOWN, this);

	m_sensitivitySlider.SetRange(1, 100);
	m_sensitivitySlider.SetPos(m_sensitivity);

	m_night = *(BYTE*)0x00595011 == 1 ? 1 : 0;

	ApplyShadowsDistanceFix();

	return TRUE;
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

	HandleButtonMove();
	UpdateShadowsDistance();
}

void CameraWindow::ApplyShadowsDistanceFix()
{
	DWORD* pUIScaleCode = (DWORD*)0x004be38e;
	DWORD* pDummyUIScale = (DWORD*)&m_shadowsDummyUIScale;

	BYTE bytes[6] = { 0xB9, 0x00, 0x00, 0x00, 0x00, 0x90 };
	memcpy(bytes + 1, &pDummyUIScale, 4);

	ReplaceCode(pUIScaleCode, bytes, 6);
}

void CameraWindow::UpdateShadowsDistance()
{
	float shadowsDistance = (1.0f / (m_zPos + 7.0f)) * 8.0f;
	int uiScale = m_player->ph1.uiScale;
	m_shadowsDummyUIScale = shadowsDistance * uiScale;
}

void CameraWindow::HandleButtonMove()
{
	if (!m_player) return;
	if (m_btnMoveDirection == 0) return;
	float moveSpeed = m_sensitivity / 100.0f;

	switch (m_btnMoveDirection)
	{
	case IDC_CAM_UP:
		m_yPos -= moveSpeed;
		break;
	case IDC_CAM_DOWN:
		m_yPos += moveSpeed;
		break;
	case IDC_CAM_LEFT:
		m_xPos -= moveSpeed;
		break;
	case IDC_CAM_RIGHT:
		m_xPos += moveSpeed;
		break;
	case IDC_CAM_ZUP:
		m_zPos += moveSpeed;
		break;
	case IDC_CAM_ZDOWN:
		m_zPos -= moveSpeed;
		break;
	}

	UpdateData(FALSE);
	OnPositionInput();
}

void CameraWindow::SetAntialiasing(bool enable)
{
	DWORD* pConvertColourBank = *(DWORD**)0x00595328;
	DWORD* pAATest = (DWORD*)((BYTE*)pConvertColourBank + 0x650);

	BYTE enabledBytes[6] = { 0xF7, 0xC7, 0x00, 0x00, 0x02, 0x00 };
	BYTE disabledBytes[6] = { 0x90, 0x90, 0x90, 0x90, 0x85, 0xFF };

	ReplaceCode(pAATest, enable ? enabledBytes : disabledBytes, 6);
}

void CameraWindow::SetShadows(bool enable)
{
	DWORD* pShadows = (DWORD*)0x004BAC10;

	BYTE enabledBytes[5] = { 0x8B, 0x41, 0x30, 0x48, 0x83 };
	BYTE disabledBytes[5] = { 0xB0, 0x00, 0xC2, 0x00, 0x00 };

	ReplaceCode(pShadows, enable ? enabledBytes : disabledBytes, 5);
}

void CameraWindow::SetNight(bool enable)
{
	DWORD* pNight1 = (DWORD*)0x004cb235;
	DWORD* pNight2 = (DWORD*)0x004cb248;

	BYTE enabledBytes[7] = { 0xc6, 0x05, 0x11, 0x50, 0x59, 0x00, 0x01 };
	BYTE disabledBytes[7] = { 0xc6, 0x05, 0x11, 0x50, 0x59, 0x00, 0x00 };

	ReplaceCode(pNight1, enable ? enabledBytes : disabledBytes, 7);
	ReplaceCode(pNight2, enable ? enabledBytes : disabledBytes, 7);

	*(int*)0x00595011 = enable ? 1 : 0;
}

void CameraWindow::SetNoLights(bool enable)
{
	DWORD* pConvertColourBank = *(DWORD**)0x00595328;
	DWORD* pLights = (DWORD*)((BYTE*)pConvertColourBank - 0x9C1);

	BYTE enabledBytes[1] = { 0x90 };
	BYTE disabledBytes[1] = { 0x42 };

	ReplaceCode(pLights, enable ? enabledBytes : disabledBytes, 1);
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

void CameraWindow::OnAntialiasingChange()
{
	UpdateData(TRUE);
	SetAntialiasing(m_antialiasing == 1);
}

void CameraWindow::OnShadowsChange()
{
	UpdateData(TRUE);
	SetShadows(m_shadows == 1);
}

void CameraWindow::OnNightChange()
{
	UpdateData(TRUE);
	SetNight(m_night == 1);
}

void CameraWindow::OnNoLightsChange()
{
	UpdateData(TRUE);
	SetNoLights(m_noLights == 1);
}

void CameraWindow::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar->GetDlgCtrlID() == IDC_CAM_SEN)
	{
		m_sensitivity = ((CSliderCtrl*)pScrollBar)->GetPos();
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

LRESULT CameraWindow::OnMoveButton(WPARAM wParam, LPARAM lParam)
{
	m_btnMoveDirection = lParam == TRUE ? (int)wParam : 0;

	return 0;
}