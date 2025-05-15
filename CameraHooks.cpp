#include "pch.h"
#include "CameraHooks.h"
#include "HookHelper.h"
#include "gta2.h"
#define _USE_MATH_DEFINES
#include <math.h>

bool CameraHooks::m_enabled = false;
bool CameraHooks::m_wasFullScreen = false;
float CameraHooks::m_destAngle = 0.0f;
float CameraHooks::m_angle = 0.0f; // in radians
DWORD CameraHooks::m_drawTileOrig = 0;
DWORD CameraHooks::m_drawQuadOrig = 0;
DWORD CameraHooks::m_drawTriangleOrig = 0;
float CameraHooks::m_rotationCenterX = 0.0f;
float CameraHooks::m_rotationCenterY = 0.0f;
struct QuadVertex CameraHooks::m_vertexBuf[8];

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

void CameraHooks::rotatePoint(float* xAddr, float* yAddr) {
	float ox = *xAddr - m_rotationCenterX;
	float oy = *yAddr - m_rotationCenterY;

	float nx = ox * cos(m_angle) - oy * sin(m_angle);
	float ny = ox * sin(m_angle) + oy * cos(m_angle);

	*xAddr = nx + m_rotationCenterX;
	*yAddr = ny + m_rotationCenterY;
}

void CameraHooks::rotateTile(QuadVertex* vertexArr) {
	if (!m_enabled) return;

	for (int i = 0; i < 4; i++) {
		rotatePoint(&vertexArr[i].x, &vertexArr[i].y);
	}
}

void CameraHooks::rotateQuad(uint32_t flags, QuadVertex** vertexArrPtr) {
	if (!m_enabled) return;
	if ((flags & 0x20000) != 0) return; // do not affect UI

	// car lights bug fix
	memcpy(m_vertexBuf, *vertexArrPtr, sizeof(m_vertexBuf));
	*vertexArrPtr = &m_vertexBuf[0];

	for (int i = 0; i < 4; i++) {
		rotatePoint(&m_vertexBuf[i].x, &m_vertexBuf[i].y);
	}
}

void CameraHooks::rotateTriangle(QuadVertex* vertexArr) {
	if (!m_enabled) return;

	for (int i = 0; i < 3; i++) {
		rotatePoint(&vertexArr[i].x, &vertexArr[i].y);
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

void CameraHooks::init()
{
	HookHelper::HookLibraryFunctionCall(0x005952bc, (DWORD)drawTile, m_drawTileOrig);
	HookHelper::HookLibraryFunctionCall(0x005952c4, (DWORD)drawQuad, m_drawQuadOrig);
	HookHelper::HookLibraryFunctionCall(0x005952d0, (DWORD)drawTriangle, m_drawTriangleOrig);
	updateRotationCenter(true);
}

void CameraHooks::setEnabled(bool enabled)
{
	if (!m_enabled) m_angle = 0;
	m_enabled = enabled;
}

void CameraHooks::update()
{
	if (!m_enabled) return;
	updateRotationCenter();

	m_angle = moveAngleTowards(m_angle, m_destAngle, rotationSpeed);

	Ped* playerPed = fnGetPedByID(1);
	if (!playerPed) return;

	if (playerPed->gameObject) {
		m_destAngle = gtaAngleToFloat(playerPed->gameObject->spriteRotation) + M_PI;
		return;
	}

	Car* playerCar = playerPed->currentCar;
	if (!playerCar || !playerCar->sprite) return;

	m_destAngle = gtaAngleToFloat(playerCar->sprite->rotation) + M_PI;
}
