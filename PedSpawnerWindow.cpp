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
	ON_CBN_SELCHANGE(IDC_PS_OBJ, &PedSpawnerWindow::OnCustomPresetTrigger)
	ON_EN_CHANGE(IDC_PS_OBJTIMER, &PedSpawnerWindow::OnCustomPresetTrigger)
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
	ON_BN_CLICKED(IDC_PS_INCAR, &PedSpawnerWindow::OnCustomPresetTrigger)
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
	DDX_Control(pDX, IDC_PS_OBJ, m_objective);
	DDX_Text(pDX, IDC_PS_OBJTIMER, m_objTimer);
	DDX_Text(pDX, IDC_PS_OBJT_X, m_objX);
	DDX_Text(pDX, IDC_PS_OBJT_Y, m_objY);
	DDX_Text(pDX, IDC_PS_OBJT_Z, m_objZ);
	DDX_Control(pDX, IDC_PS_OBJT_X, m_objXEdit);
	DDX_Control(pDX, IDC_PS_OBJT_Y, m_objYEdit);
	DDX_Control(pDX, IDC_PS_OBJT_Z, m_objZEdit);
	DDX_Control(pDX, IDC_PS_OBJT_XL, m_objXLabel);
	DDX_Control(pDX, IDC_PS_OBJT_YL, m_objYLabel);
	DDX_Control(pDX, IDC_PS_OBJT_ZL, m_objZLabel);
	DDX_Text(pDX, IDC_PS_AI0, m_aiValues[0]);
	DDX_Text(pDX, IDC_PS_AI1, m_aiValues[1]);
	DDX_Text(pDX, IDC_PS_AI2, m_aiValues[2]);
	DDX_Text(pDX, IDC_PS_AI3, m_aiValues[3]);
	//DDX_Text(pDX, IDC_PS_AI4, m_aiValues[4]);
	//DDX_Text(pDX, IDC_PS_AI5, m_aiValues[5]);
	//DDX_Text(pDX, IDC_PS_AI6, m_aiValues[6]);
	//DDX_Text(pDX, IDC_PS_AI7, m_aiValues[7]);
	//DDX_Text(pDX, IDC_PS_AI8, m_aiValues[8]);
	//DDX_Text(pDX, IDC_PS_AI9, m_aiValues[9]);
	DDX_Text(pDX, IDC_PS_LEADER, m_leaderID);
	DDX_Check(pDX, IDC_PS_INCAR, m_inCar);
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
	m_health = 50;
	m_objTimer = 9999;

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

	m_objective.ResetContent();
	int objectivesCount = sizeof(pedObjectives) / sizeof(pedObjectives[0]);
	for (int i = 0; i < objectivesCount; i++)
		m_objective.AddString(pedObjectives[i].name);

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

	for (int i = 0; i < sizeof(pedObjectives) / sizeof(pedObjectives[0]); i++) {
		if (pedObjectives[i].id != preset.objective)
			continue;

		m_objective.SetCurSel(i);
	}

	m_health = preset.health;
	m_objTimer = preset.objTimer;
	for(int i = 0; i < aiValuesCount; i++)
		m_aiValues[i] = preset.aiValues[i];

	m_leaderID = preset.playerLeader ? 1 : 0;
	m_inCar = preset.inCar;

	UpdateData(FALSE);
	UpdateObjectiveControls();
}

void PedSpawnerWindow::OnPresetSelChange()
{
	int index = m_preset.GetCurSel();

	LoadPreset(index);
}

void PedSpawnerWindow::OnCustomPresetTrigger()
{
	UpdateData(TRUE);
	m_preset.SetCurSel(m_customPresetIndex);
	UpdateObjectiveControls();
}

void PedSpawnerWindow::UpdateObjectiveControls()
{
	const PedObjectiveProperty* objProperty = &pedObjectives[m_objective.GetCurSel()];
	PED_OBJ_TARGET_TYPE targetType = objProperty->targetType;

	if (targetType == m_objTargetType) return;
	m_objTargetType = targetType;

	switch (targetType) {
	case PED_OBJ_TARGET_TYPE_NONE:
		m_objXEdit.ShowWindow(SW_HIDE);
		m_objYEdit.ShowWindow(SW_HIDE);
		m_objZEdit.ShowWindow(SW_HIDE);
		m_objXLabel.ShowWindow(SW_HIDE);
		m_objYLabel.ShowWindow(SW_HIDE);
		m_objZLabel.ShowWindow(SW_HIDE);
		break;
	case PED_OBJ_TARGET_TYPE_OBJ:
	case PED_OBJ_TARGET_TYPE_PED:
	case PED_OBJ_TARGET_TYPE_CAR:
		m_objXEdit.ShowWindow(SW_SHOW);
		m_objYEdit.ShowWindow(SW_HIDE);
		m_objZEdit.ShowWindow(SW_HIDE);
		m_objXLabel.ShowWindow(SW_SHOW);
		m_objYLabel.ShowWindow(SW_HIDE);
		m_objZLabel.ShowWindow(SW_HIDE);

		m_objXLabel.SetWindowTextW(L"Target ID:");
		m_objX = 0;
		break;
	case PED_OBJ_TARGET_TYPE_COORDS:
		m_objXEdit.ShowWindow(SW_SHOW);
		m_objYEdit.ShowWindow(SW_SHOW);
		m_objZEdit.ShowWindow(SW_SHOW);
		m_objXLabel.ShowWindow(SW_SHOW);
		m_objYLabel.ShowWindow(SW_SHOW);
		m_objZLabel.ShowWindow(SW_SHOW);

		m_objXLabel.SetWindowTextW(L"Target X:");
		m_objX = m_xPos;
		m_objY = m_yPos;
		m_objZ = m_zPos;
		break;
	}

	UpdateData(FALSE);
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

	m_xPos = FloatDecode(playerPed->gameObject->sprite->x);
	m_yPos = FloatDecode(playerPed->gameObject->sprite->y);
	m_zPos = FloatDecode(playerPed->gameObject->sprite->z);

	UpdateData(FALSE);
}

void PedSpawnerWindow::OnSpawnClick()
{
	// Return if not in the game
	if (*(DWORD*)ptrToPedManager == 0)
		return;

	UpdateData(TRUE);

	PedSpawnRequest request;

	request.xPos = FloatEncode(m_xPos);
	request.yPos = FloatEncode(m_yPos);
	request.zPos = FloatEncode(m_zPos);

	// coordinates check
	if (!IsPointSafe(request.xPos, request.yPos, request.zPos)) {
		MessageBox(L"Ped position is out of the map");
		return;
	}

	// objective info
	if (!SetObjectiveRequest(request)) return;

	// car
	if (m_inCar == 1) {
		Car* car = FindTheNearestCar(request.xPos, request.yPos, request.zPos);

		if (!car) {
			MessageBox(L"Car not found");
			return;
		}

		if (car->driver) {
			MessageBox(L"Car is already occupied");
			return;
		}

		request.car = car;
	}

	// leader ped
	if (m_leaderID != 0) {
		Ped* leaderPed = fnGetPedByID(m_leaderID);

		if (!leaderPed) {
			MessageBox(L"Leader ped not found");
			return;
		}

		request.leader = leaderPed;
	}

	request.remap = (PED_REMAP)pedRemaps[m_remap.GetCurSel()].id;
	request.shape = (PED_REMAP2)pedBodyShapes[m_shape.GetCurSel()].id;
	request.weapon = (WEAPON_INDEX)(m_weapon.GetCurSel() == m_noneWeaponIndex ? -1 : weapons[m_weapon.GetCurSel() - 1].id);
	request.health = m_health;
	request.occupation = (PED_OCUPATION)occupations[m_occupation.GetCurSel()].id;
	request.threatSearch = (PED_THREAT_SEARCH)pedThreatSearch[m_threatSearch.GetCurSel()].id;
	request.threatReaction = (PED_THREAT_REACTION)pedThreatReactions[m_threatReaction.GetCurSel()].id;

	for (int i = 0; i < aiValuesCount; i++)
		request.aiValues[i] = m_aiValues[i];

	request.requestedSpawn = true;
	m_request = request;
}

bool PedSpawnerWindow::SetObjectiveRequest(PedSpawnRequest& request)
{
	const PedObjectiveProperty* objProperty = &pedObjectives[m_objective.GetCurSel()];
	request.objective = (PED_OBJECTIVE)objProperty->id;
	request.objTimer = m_objTimer;
	request.objTargetType = objProperty->targetType;

	int targetID = (int)m_objX;

	switch (request.objTargetType) {
	case PED_OBJ_TARGET_TYPE_NONE:
		break;
	case PED_OBJ_TARGET_TYPE_CAR:
		request.objTargetCar = fnGetCarByID(targetID);
		if (!request.objTargetCar) {
			MessageBox(L"Objective's target car not found");
			return false;
		}
		break;
	case PED_OBJ_TARGET_TYPE_PED:
		request.objTargetPed = fnGetPedByID(targetID);
		if (!request.objTargetPed) {
			MessageBox(L"Objective's target ped not found");
			return false;
		}
		break;
	case PED_OBJ_TARGET_TYPE_OBJ:
		request.objTargetPed = fnGetPedByID(targetID);
		if (!request.objTargetPed) {
			MessageBox(L"Objective's target object not found");
			return false;
		}
		break;
	case PED_OBJ_TARGET_TYPE_COORDS:
		request.objTargetX = FloatEncode(m_objX);
		request.objTargetY = FloatEncode(m_objY);
		request.objTargetZ = FloatEncode(m_objZ);

		if (!IsPointSafe(request.objTargetX, request.objTargetY, request.objTargetZ)) {
			MessageBox(L"Objective's target position is out of the map");
			return false;
		}
		break;
	}

	return true;
}

void PedSpawnerWindow::SetPedObjective(PedSpawnRequest& request)
{
	fnPedSetObjective(request.ped, 0, request.objective, request.objTimer);
	request.ped->bitState = (PED_BIT_STATE)(request.ped->bitState & ~PED_BIT_STATE_UNK_400);

	switch (request.objTargetType) {
		case PED_OBJ_TARGET_TYPE_NONE:
			break;
		case PED_OBJ_TARGET_TYPE_CAR:
			request.ped->objectiveTargetCar = request.objTargetCar;
			break;
		case PED_OBJ_TARGET_TYPE_PED:
			request.ped->objectiveTargetPed = request.objTargetPed;
			break;
		case PED_OBJ_TARGET_TYPE_OBJ:
			request.ped->objectiveTargetObject = request.objTargetObject;
			break;
		case PED_OBJ_TARGET_TYPE_COORDS:
			request.ped->objectiveTargetX = request.objTargetX;
			request.ped->objectiveTargetY = request.objTargetY;
			request.ped->objectiveTargetZ = request.objTargetZ;
			break;
	}
}

bool PedSpawnerWindow::SafeSpawnPed(PedSpawnRequest& request)
{
	if (!request.requestedSpawn) return false;
	request.requestedSpawn = false;

	if (request.car) {
		Ped* ped = fnCreatePed();

		if (!ped) {
			MessageBox(L"Failed to create ped");
			return false;
		}

		ped->remap = request.remap;
		fnPutPedInCarRelated(ped, 0, request.car);
		fnCreatePed2(*(void**)0x006644b8, 0, ped);
		fnCarMakeDriveable1(request.car, 0, 5);
		fnCarMakeDriveable2(request.car, 0);
		fnCarMakeDriveable3(request.car->notEngineStruct, 0, request.car);
		fnCarMakeDriveable4(request.car, 0);

		request.ped = ped;
	}
	else {
		Ped* ped = fnSpawnPedAtPosition(
			request.xPos,
			request.yPos,
			request.zPos,
			request.remap,
			0
		);

		if (!ped) {
			MessageBox(L"Failed to spawn ped");
			return false;
		}

		request.ped = ped;
	}

	request.ped->remap2 = request.shape;
	if(request.weapon != (WEAPON_INDEX)-1)
		fnSetNPCWeapon(request.ped, 0, request.weapon);
	request.ped->health = request.health;
	request.ped->occupation = request.occupation;
	request.ped->threatSearch = request.threatSearch;
	request.ped->threatReaction = request.threatReaction;

	if(request.leader) SetPedLeader(request.ped, request.leader);
	SetPedObjective(m_request);

	if (request.aiValues[0] != -1) request.ped->state = (PED_STATE)request.aiValues[0];
	if (request.aiValues[1] != -1) request.ped->state2 = (PED_STATE2)request.aiValues[1];
	if (request.aiValues[2] != -1) request.ped->bitState = (PED_BIT_STATE)request.aiValues[2];
	if (request.aiValues[3] != -1) request.ped->bitState2 = (PED_BIT_STATE2)request.aiValues[3];

	return true;
}

void PedSpawnerWindow::SetPedLeader(Ped* ped, Ped* leader)
{
	if (leader->group) {
		fnPedGroupAddPed(leader->group, 0, ped);
	}
	else {
		fnPedGroupCreate(ped, 0, 0);
		fnPedGroupChangeLeader(leader, 0, ped);
	}
}

void PedSpawnerWindow::OnGTAGameTick()
{
	SafeSpawnPed(m_request);
}
