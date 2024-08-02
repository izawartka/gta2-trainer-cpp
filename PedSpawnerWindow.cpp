#include "pch.h"
#include "gta2dll.h"
#include "PedSpawnerWindow.h"

PedSpawnerWindow* psWnd = nullptr;

IMPLEMENT_DYNAMIC(PedSpawnerWindow, CDialogEx)

PedSpawnerWindow::PedSpawnerWindow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PS, pParent)
{
	psWnd = this;
}

PedSpawnerWindow::~PedSpawnerWindow()
{

}

BEGIN_MESSAGE_MAP(PedSpawnerWindow, CDialogEx)
	ON_BN_CLICKED(IDC_PS_SPAWN, &PedSpawnerWindow::OnSpawnClick)
	ON_BN_CLICKED(IDC_PS_GETPPOS, &PedSpawnerWindow::GetPlayerPos)
	ON_CBN_SELCHANGE(IDC_PS_PRESET, &PedSpawnerWindow::OnPresetSelChange)
	ON_CBN_SELCHANGE(IDC_PS_REMAP, &PedSpawnerWindow::OnCustomPresetTrigger)
	ON_CBN_SELCHANGE(IDC_PS_SHAPE, &PedSpawnerWindow::OnCustomPresetTrigger)
	ON_CBN_SELCHANGE(IDC_PS_WEAP, &PedSpawnerWindow::OnCustomPresetTrigger)
	ON_CBN_SELCHANGE(IDC_PS_OCCUP, &PedSpawnerWindow::OnCustomPresetTrigger)
	ON_CBN_SELCHANGE(IDC_PS_THR_S, &PedSpawnerWindow::OnCustomPresetTrigger)
	ON_CBN_SELCHANGE(IDC_PS_THR_R, &PedSpawnerWindow::OnCustomPresetTrigger)
	ON_EN_CHANGE(IDC_PS_HEALTH, &PedSpawnerWindow::OnCustomPresetTrigger)
	ON_EN_CHANGE(IDC_PS_AI0, &PedSpawnerWindow::OnCustomPresetTrigger)
	ON_EN_CHANGE(IDC_PS_AI1, &PedSpawnerWindow::OnCustomPresetTrigger)
	ON_EN_CHANGE(IDC_PS_AI2, &PedSpawnerWindow::OnCustomPresetTrigger)
	ON_EN_CHANGE(IDC_PS_AI3, &PedSpawnerWindow::OnCustomPresetTrigger)
	ON_EN_CHANGE(IDC_PS_AI4, &PedSpawnerWindow::OnCustomPresetTrigger)
	ON_EN_CHANGE(IDC_PS_AI5, &PedSpawnerWindow::OnCustomPresetTrigger)
	//ON_EN_CHANGE(IDC_PS_AI6, &PedSpawnerWindow::OnCustomPresetTrigger)
	//ON_EN_CHANGE(IDC_PS_AI7, &PedSpawnerWindow::OnCustomPresetTrigger)
	//ON_EN_CHANGE(IDC_PS_AI8, &PedSpawnerWindow::OnCustomPresetTrigger)
	//ON_EN_CHANGE(IDC_PS_AI9, &PedSpawnerWindow::OnCustomPresetTrigger)
	ON_EN_CHANGE(IDC_PS_LEADER, &PedSpawnerWindow::OnCustomPresetTrigger)
END_MESSAGE_MAP()


void PedSpawnerWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PS_X, m_xPos);
	DDX_Text(pDX, IDC_PS_Y, m_yPos);
	DDX_Text(pDX, IDC_PS_Z, m_zPos);
	DDX_Control(pDX, IDC_PS_PRESET, m_preset);
	DDX_Text(pDX, IDC_PS_HEALTH, m_health);
	DDX_Control(pDX, IDC_PS_REMAP, m_remap);
	DDX_Control(pDX, IDC_PS_SHAPE, m_shape);
	DDX_Control(pDX, IDC_PS_WEAP, m_weapon);
	DDX_Control(pDX, IDC_PS_OCCUP, m_occupation);
	DDX_Control(pDX, IDC_PS_THR_S, m_threatSearch);
	DDX_Control(pDX, IDC_PS_THR_R, m_threatReaction);
	DDX_Text(pDX, IDC_PS_AI0, m_aiValues[0]);
	DDX_Text(pDX, IDC_PS_AI1, m_aiValues[1]);
	DDX_Text(pDX, IDC_PS_AI2, m_aiValues[2]);
	DDX_Text(pDX, IDC_PS_AI3, m_aiValues[3]);
	DDX_Text(pDX, IDC_PS_AI4, m_aiValues[4]);
	DDX_Text(pDX, IDC_PS_AI5, m_aiValues[5]);
	//DDX_Text(pDX, IDC_PS_AI6, m_aiValues[6]);
	//DDX_Text(pDX, IDC_PS_AI7, m_aiValues[7]);
	//DDX_Text(pDX, IDC_PS_AI8, m_aiValues[8]);
	//DDX_Text(pDX, IDC_PS_AI9, m_aiValues[9]);
	DDX_Text(pDX, IDC_PS_LEADER, m_leaderID);
}

int PedSpawnerWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
}

void PedSpawnerWindow::ClearValues()
{
	m_xPos = 0;
	m_yPos = 0;
	m_zPos = 0;
	m_health = 100;

	UpdateData(FALSE);

	m_preset.ResetContent();
	int presetsCount = sizeof(pedPresets) / sizeof(pedPresets[0]);
	for (int i = 0; i < presetsCount; i++)
		m_preset.AddString(pedPresets[i].name);
	m_preset.AddString(L"Custom");
	m_customPresetIndex = presetsCount;

	m_shape.ResetContent();
	int shapesCount = sizeof(pedBodyShapes) / sizeof(pedBodyShapes[0]);
	for (int i = 0; i < shapesCount; i++)
		m_shape.AddString(pedBodyShapes[i].name);

	m_remap.ResetContent();
	int remapsCount = sizeof(pedRemaps) / sizeof(pedRemaps[0]);
	for (int i = 0; i < remapsCount; i++)
	m_remap.AddString(pedRemaps[i].name);

	m_weapon.ResetContent();
	int weaponsCount = sizeof(weapons) / sizeof(weapons[0]);
	m_weapon.AddString(L"None");
	for (int i = 0; i < weaponsCount; i++)
		m_weapon.AddString(weapons[i].name);

	m_occupation.ResetContent();
	int occupationsCount = sizeof(occupations) / sizeof(occupations[0]);
	for (int i = 0; i < occupationsCount; i++)
		m_occupation.AddString(occupations[i].name);

	m_threatSearch.ResetContent();
	int threatSearchCount = sizeof(pedThreatSearch) / sizeof(pedThreatSearch[0]);
	for (int i = 0; i < threatSearchCount; i++)
		m_threatSearch.AddString(pedThreatSearch[i].name);

	m_threatReaction.ResetContent();
	int threatReactionsCount = sizeof(pedThreatReactions) / sizeof(pedThreatReactions[0]);
	for (int i = 0; i < threatReactionsCount; i++)
		m_threatReaction.AddString(pedThreatReactions[i].name);

	GetPlayerPos();
	LoadPreset(0);
}

void PedSpawnerWindow::LoadPreset(int index)
{
	if (index < 0 || index >= m_customPresetIndex)
		return;

	m_preset.SetCurSel(index);

	UpdateData(TRUE);

	PedPreset preset = pedPresets[index];

	for (int i = 0; i < sizeof(pedBodyShapes) / sizeof(pedBodyShapes[0]); i++) {
		if (pedBodyShapes[i].id != preset.shape) 
			continue;

		m_shape.SetCurSel(i);
	}

	for (int i = 0; i < sizeof(pedRemaps) / sizeof(pedRemaps[0]); i++) {
		if (pedRemaps[i].id != preset.remap)
			continue;

		m_remap.SetCurSel(i);
	}

	m_weapon.SetCurSel(0);
	for (int i = 0; i < sizeof(weapons) / sizeof(weapons[0]); i++) {
		if (weapons[i].id != preset.weapon)
			continue;

		m_weapon.SetCurSel(i + 1);
	}

	for (int i = 0; i < sizeof(occupations) / sizeof(occupations[0]); i++) {
		if (occupations[i].id != preset.occupation)
			continue;

		m_occupation.SetCurSel(i);
	}

	for (int i = 0; i < sizeof(pedThreatSearch) / sizeof(pedThreatSearch[0]); i++) {
		if (pedThreatSearch[i].id != preset.threatSearch)
			continue;

		m_threatSearch.SetCurSel(i);
	}

	for (int i = 0; i < sizeof(pedThreatReactions) / sizeof(pedThreatReactions[0]); i++) {
		if (pedThreatReactions[i].id != preset.threatReaction)
			continue;

		m_threatReaction.SetCurSel(i);
	}

	m_health = preset.health;
	for(int i = 0; i < aiValuesCount; i++)
		m_aiValues[i] = preset.aiValues[i];

	m_leaderID = preset.playerLeader ? 1 : 0;

	UpdateData(FALSE);
}

void PedSpawnerWindow::OnPresetSelChange()
{
	int index = m_preset.GetCurSel();

	LoadPreset(index);
}

void PedSpawnerWindow::OnCustomPresetTrigger()
{
	m_preset.SetCurSel(m_customPresetIndex);
}

void PedSpawnerWindow::GetPlayerPos()
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

void PedSpawnerWindow::OnSpawnClick()
{
	// Return if not in the game
	if (*(DWORD*)ptrToPedManager == 0)
		return;

	UpdateData(TRUE);

	SCR_f x = m_xPos * 16384.0;
	SCR_f y = m_yPos * 16384.0;
	SCR_f z = m_zPos * 16384.0;

	// coordinates check
	if (!IsPointSafe(x, y, z)) {
		MessageBox(L"Target position is out of the map");
		return;
	}

	int remap = pedRemaps[m_remap.GetCurSel()].id;

	Ped* ped = fnSpawnPedAtPosition(
		x,
		y,
		z,
		(PED_REMAP)remap,
		0
	);

	if(!ped) return;

	ped->health = m_health;

	int shape = pedBodyShapes[m_shape.GetCurSel()].id;
	ped->remap2 = (PED_REMAP2)shape;

	int weaponSel = m_weapon.GetCurSel();
	if (weaponSel != 0) {
		int weapon = weapons[weaponSel - 1].id;
		fnSetNPCWeapon(ped, 0, (WEAPON_INDEX)weapon);
	}

	int occupation = occupations[m_occupation.GetCurSel()].id;
	ped->occupation = (PED_OCUPATION)occupation;

	int threatSearch = pedThreatSearch[m_threatSearch.GetCurSel()].id;
	ped->threatSearch = (PED_THREAT_SEARCH)threatSearch;

	int threatReaction = pedThreatReactions[m_threatReaction.GetCurSel()].id;
	ped->threatReaction = (PED_THREAT_REACTION)threatReaction;

	SetPedAiValues(ped, m_aiValues);

	if(m_leaderID != 0) {
		Ped* leaderPed = fnGetPedByID(m_leaderID);

		if(!leaderPed) {
			MessageBox(L"Leader ped not found");
			return;
		}

		if (leaderPed->group) {
			fnPedGroupAddPed(leaderPed->group, 0, ped);
		}
		else {
			fnPedGroupCreate(ped, 0, 0);
			fnPedGroupChangeLeader(leaderPed, 0, ped);
		}
	}
}

void PedSpawnerWindow::SetPedAiValues(Ped* ped, int* values)
{
	if(values[0] != -1) ped->state = (PED_STATE)values[0];
	if(values[1] != -1) ped->state2 = (PED_STATE2)values[1];
	if(values[2] != -1) ped->objective = (PED_OBJECTIVE)values[2];
	if(values[3] != -1) ped->bitState = (PED_BIT_STATE)values[3];
	if(values[4] != -1) ped->bitState2 = (PED_BIT_STATE2)values[4];
	if(values[5] != -1) ped->objectiveTimer = values[5];

}
