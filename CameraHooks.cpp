#include "pch.h"
#include "CameraHooks.h"
#include "HookHelper.h"
#include "gta2.h"
#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>

CameraHookMode CameraHooks::m_mode = CameraHookMode::Disabled;
bool CameraHooks::m_followRotation = false;
bool CameraHooks::m_forceClearScreen = false;
float CameraHooks::m_gameCameraZ = 0;
float CameraHooks::m_gameCameraField60 = 0;
bool CameraHooks::m_enabled = false;
bool CameraHooks::m_wasFullScreen = false;
float CameraHooks::m_destAngle = 0.0f;
float CameraHooks::m_angle = 0.0f; // in radians
float CameraHooks::m_horAngle = 0.0f;
DWORD CameraHooks::m_drawTileOrig = 0;
DWORD CameraHooks::m_drawQuadOrig = 0;
DWORD CameraHooks::m_drawTriangleOrig = 0;
float CameraHooks::m_rotationCenterX = 0.0f;
float CameraHooks::m_rotationCenterY = 0.0f;
float CameraHooks::m_rotationCenterZ = 0.0f;
float CameraHooks::m_horRotationCenterZ = 0.0f;
struct GTAVertex CameraHooks::m_vertexBuf[8];

float CameraHooks::normalizeAngle(float angle) {
	while (angle < -M_PI) angle += M_PI * 2;
	while (angle >= M_PI) angle -= M_PI * 2;
	return angle;
}

float CameraHooks::moveAngleTowards(float currentAngle, float destAngle, float speedRad) {
	float delta = normalizeAngle(destAngle - currentAngle);

	if (std::abs(delta) <= speedRad) {
		return destAngle;
	}

	return normalizeAngle(currentAngle + (delta > 0 ? speedRad : -speedRad));
}

float CameraHooks::gtaAngleToFloat(short angle)
{
	return angle / 4.0f / 180.0f * M_PI;
}

void CameraHooks::rotateVertex(GTAVertex& vertex) {
	float x0 = vertex.x - m_rotationCenterX;
	float y0 = vertex.y - m_rotationCenterY;
	float z0 = vertex.z - m_rotationCenterZ;

	// Rotate around Z-axis (vertical in this context)
	float x1 = x0 * cos(m_angle) - y0 * sin(m_angle);
	float y1 = x0 * sin(m_angle) + y0 * cos(m_angle);
	float z1 = z0; // unchanged

	float x2 = x1;
	float y2 = y1;
	float z2 = z1;

	if (m_mode == CameraHookMode::Full3D) {
		// Convert from screen space to world space
		x1 = x1 / (m_gameCameraField60 * z1);
		y1 = y1 / (m_gameCameraField60 * z1);
		z1 = m_gameCameraZ + 8.0f - (1.0f / z1);

		z1 -= m_horRotationCenterZ;

		// Rotate the world
		x2 = x1; // unchanged
		y2 = y1 * cos(m_horAngle) - z1 * sin(m_horAngle);
		z2 = y1 * sin(m_horAngle) + z1 * cos(m_horAngle);

		z1 += m_horRotationCenterZ;

		// Convert back to screen space
		z2 = 1.0f / (m_gameCameraZ + 8.0f - z2);
		x2 = x2 * m_gameCameraField60 * z2;
		y2 = y2 * m_gameCameraField60 * z2;
	}

	vertex.x = x2 + m_rotationCenterX;
	vertex.y = y2 + m_rotationCenterY;
	vertex.z = z0 + m_rotationCenterZ;
}

void CameraHooks::rotateTile(GTAVertex* vertexArr) {
	if (m_mode == CameraHookMode::Disabled) return;

	for (int i = 0; i < 4; i++) {
		rotateVertex(vertexArr[i]);
	}
}

void CameraHooks::rotateQuad(uint32_t flags, GTAVertex** vertexArrPtr) {
	if (m_mode == CameraHookMode::Disabled) return;
	if ((flags & 0x20000) != 0) return; // do not affect UI

	// car lights bug fix
	memcpy(m_vertexBuf, *vertexArrPtr, sizeof(m_vertexBuf));
	*vertexArrPtr = &m_vertexBuf[0];

	for (int i = 0; i < 4; i++) {
		rotateVertex(m_vertexBuf[i]);
	}
}

void CameraHooks::rotateTriangle(GTAVertex* vertexArr) {
	if (m_mode == CameraHookMode::Disabled) return;

	for (int i = 0; i < 3; i++) {
		rotateVertex(vertexArr[i]);
	}
}

__declspec(naked) void CameraHooks::drawTile(void) {
	__asm {
		PUSH[ESP + 0xc]
		CALL rotateTile

		MOV EAX, ds:m_drawTileOrig
		JMP EAX
	}
}

__declspec(naked) void CameraHooks::drawQuad(void) {
	__asm {
		PUSH ESP
		ADD[ESP], 0xc
		PUSH[ESP + 0x8]
		CALL rotateQuad

		MOV EAX, ds:m_drawQuadOrig
		JMP EAX
	}
}

__declspec(naked) void CameraHooks::drawTriangle(void) {
	__asm {
		PUSH[ESP + 0xc]
		CALL rotateTriangle

		MOV EAX, ds:m_drawTriangleOrig
		JMP EAX
	}
}

static DWORD clearScreenContinueAddr = 0x00461980;
static DWORD clearScreenClearAddr = 0x004619a4;

__declspec(naked) void CameraHooks::clearScreen(void) {
	__asm {
		MOV AL, m_forceClearScreen
		TEST AL, AL
		JNZ clear_screen // clear screen if forced

		MOV AL, ds:[0x005ead9c] // part of the original fn
		TEST AL, AL
		JNZ clear_screen

		JMP clearScreenContinueAddr

	clear_screen:
		JMP clearScreenClearAddr
	}
}

void CameraHooks::updateRotationCenter(bool force)
{
	bool isFullScreen = *(bool*)0x00595014;
	if (isFullScreen == m_wasFullScreen && !force) return;
	m_wasFullScreen = isFullScreen;

	int fullScreenWidth = *(int*)0x006732e4;
	int fullScreenHeight = *(int*)0x006732e0;
	int windowWidth = *(int*)0x00673578;
	int windowHeight = *(int*)0x006732e8;
	m_rotationCenterX = (isFullScreen ? fullScreenWidth : windowWidth) / 2.0f;
	m_rotationCenterY = (isFullScreen ? fullScreenHeight : windowHeight) / 2.0f;
}

void CameraHooks::updateFollowRotation(Ped* playerPed)
{
	if (!m_followRotation) return;
	if (!playerPed) return;

	if (playerPed->gameObject) {
		m_destAngle = gtaAngleToFloat(playerPed->gameObject->spriteRotation) + M_PI;
		return;
	}

	Car* playerCar = playerPed->currentCar;
	if (!playerCar || !playerCar->sprite) return;

	m_destAngle = gtaAngleToFloat(playerCar->sprite->rotation) + M_PI;
}

void CameraHooks::update(CameraOrPhysics* gameCamera)
{
	if (m_mode == CameraHookMode::Disabled) return;
	updateRotationCenter();

	Ped* playerPed = fnGetPedByID(1);

	if (gameCamera) {
		m_gameCameraZ = FloatDecode(gameCamera->cameraPos.z);
		m_gameCameraField60 = FloatDecode(gameCamera->altMovingArrowsRelated);
		SCR_f playerOffset = (playerPed ? playerPed->z : 0);
		m_horRotationCenterZ = FloatDecode(playerOffset) - 1.0f;
	}

	updateFollowRotation(playerPed);

	m_angle = moveAngleTowards(m_angle, m_destAngle, rotationSpeed);
}

void CameraHooks::setForceClearScreen(bool value)
{
	m_forceClearScreen = value;

	if (value) { // hook if not already
		HookHelper::HookFunctionCall(0x00461977, (DWORD)clearScreen, false);
	}
}

void CameraHooks::setMode(CameraHookMode mode)
{
	m_mode = mode;

	if (m_mode != CameraHookMode::Disabled) { // hook if not already
		HookHelper::HookLibraryFunctionCall(0x005952bc, (DWORD)drawTile, m_drawTileOrig);
		HookHelper::HookLibraryFunctionCall(0x005952c4, (DWORD)drawQuad, m_drawQuadOrig);
		HookHelper::HookLibraryFunctionCall(0x005952d0, (DWORD)drawTriangle, m_drawTriangleOrig);
		updateRotationCenter(true);
	}
}

void CameraHooks::setFollowRotation(bool value)
{
	m_followRotation = value;
}

void CameraHooks::setAngle(float angle)
{
	m_destAngle = angle;
	m_angle = angle;
}

void CameraHooks::addAngle(float delta)
{
	m_destAngle += delta;
	m_angle = m_destAngle; // no smoothing here
}

void CameraHooks::setHorAngle(float angle)
{
	m_horAngle = angle;
}

void CameraHooks::setHorRotationCenterZ(float val)
{
	m_horRotationCenterZ = val;
}
