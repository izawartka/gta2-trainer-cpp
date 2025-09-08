#include "pch.h"
#include "CameraHooks.h"
#include "HookHelper.h"
#include "gta2.h"
#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdexcept>

CameraHookMode CameraHooks::m_mode = CameraHookMode::Disabled;
bool CameraHooks::m_followRotation = false;
bool CameraHooks::m_disableCulling = false;
bool CameraHooks::m_forceClearScreen = false;
float CameraHooks::m_gameCameraX = 0;
float CameraHooks::m_gameCameraY = 0;
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
float CameraHooks::m_additionalZOffset = 0.0f;
struct GTAVertex CameraHooks::m_vertexBuf[8];
float CameraHooks::m_customCameraX = 0.0f;
float CameraHooks::m_customCameraY = 0.0f;
float CameraHooks::m_customCameraZ = 0.0f;
int CameraHooks::m_renderDistance = 8;
int (*CameraHooks::m_renderQueue)[2] = nullptr;
size_t CameraHooks::m_renderQueueSize = 0;
int CameraHooks::m_lastLayerIndex = 10;
bool CameraHooks::m_enableCustomDrawMapLayer = false;

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

		z2 += m_horRotationCenterZ + m_additionalZOffset;

		// Convert back to screen space
		z2 = 1.0f / (m_gameCameraZ + 8.0f - z2);
		x2 = x2 * m_gameCameraField60 * z2;
		y2 = y2 * m_gameCameraField60 * z2;
	}

	vertex.x = x2 + m_rotationCenterX;
	vertex.y = y2 + m_rotationCenterY;
	vertex.z = z2 + m_rotationCenterZ;
}

void CameraHooks::applyCustomCulling(GTAVertex* vertexArr, int count)
{
	if (m_mode != CameraHookMode::Full3D) return;
	bool culled = false;

	// backface culling
	float ax = vertexArr[1].x - vertexArr[0].x;
	float ay = vertexArr[1].y - vertexArr[0].y;
	float bx = vertexArr[2].x - vertexArr[0].x;
	float by = vertexArr[2].y - vertexArr[0].y;
	float cross = ax * by - ay * bx;
	if (cross < 0.0f) culled = true;

	// frustum culling
	if (!culled) {
		for (int i = 0; i < count; i++) {
			if (vertexArr[i].z < 0.0f) {
				culled = true;
				break;
			}
		}
	}

	if (!culled) return;

	for (int i = 0; i < count; i++) {
		vertexArr[i].x = 0.0f;
		vertexArr[i].y = 0.0f;
		vertexArr[i].z = 0.0f;
	}
}

void CameraHooks::reverseDiagonalTile(GTAVertex* vertexArr)
{
	GTAVertex worldSpaceVerts[3];
	memcpy(worldSpaceVerts, vertexArr, sizeof(GTAVertex) * 3);

	for (int i = 0; i < 3; i++) {
		GTAVertex& vertex = worldSpaceVerts[i];
		float x = vertex.x - m_rotationCenterX;
		float y = vertex.y - m_rotationCenterY;
		float z = vertex.z - m_rotationCenterZ;

		// Convert from screen space to world space
		x = x / (m_gameCameraField60 * z);
		y = y / (m_gameCameraField60 * z);
		z = m_gameCameraZ + 8.0f - (1.0f / z);

		worldSpaceVerts[i].x = x + m_rotationCenterX;
		worldSpaceVerts[i].y = y + m_rotationCenterY;
		worldSpaceVerts[i].z = z + m_rotationCenterZ;
	}

	float ax = worldSpaceVerts[1].x - worldSpaceVerts[0].x;
	float ay = worldSpaceVerts[1].y - worldSpaceVerts[0].y;
	float bx = worldSpaceVerts[2].x - worldSpaceVerts[0].x;
	float by = worldSpaceVerts[2].y - worldSpaceVerts[0].y;
	float cross = ax * by - ay * bx;

	// if the face is facing back even in world coords, reverse it
	if (cross < 0.0f) {
		std::swap(vertexArr[1], vertexArr[2]);
	}
}

void CameraHooks::rotateTile(GTAVertex* vertexArr) {
	if (m_mode == CameraHookMode::Disabled) return;

	for (int i = 0; i < 4; i++) {
		rotateVertex(vertexArr[i]);
	}

	applyCustomCulling(vertexArr, 4);
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

	applyCustomCulling(m_vertexBuf, 4);
}

void CameraHooks::rotateTriangle(GTAVertex* vertexArr) {
	if (m_mode == CameraHookMode::Disabled) return;

	reverseDiagonalTile(vertexArr);

	for (int i = 0; i < 3; i++) {
		rotateVertex(vertexArr[i]);
	}

	applyCustomCulling(vertexArr, 3);
}

void __fastcall CameraHooks::customDrawMapLayer(S12* s12, int in_edx) {
	int layer = *(int*)ptrToCurrentMapLayer;
	if (layer <= m_lastLayerIndex) {
		createRenderQueue();
	}
	m_lastLayerIndex = layer;

	for (int i = 0; i < m_renderQueueSize; i++) {
		int* pos = m_renderQueue[i];
		fnDrawTileBlock(s12, in_edx, &pos[0], &pos[1]);
	}
}

void CameraHooks::createRenderQueue()
{
	if (m_renderQueue != nullptr) {
		delete[] m_renderQueue;
		m_renderQueueSize = 0;
	}

	size_t queueSize = (2 * m_renderDistance + 1) * (2 * m_renderDistance + 1);
	m_renderQueue = new int[queueSize][2];

	int ccX = (int)m_customCameraX;
	int ccY = (int)m_customCameraY;
	int gcX = (int)m_gameCameraX;
	int gcY = (int)m_gameCameraY;

	int maxRadX = abs(gcX - ccX) + m_renderDistance;
	int maxRadY = abs(gcY - ccY) + m_renderDistance;
	int maxRad = max(maxRadX, maxRadY);

	for (int r = maxRad; r >= 1; r--) {
		for (int i = r; i >= 0; i--) {
			if (i != r && i != 0) {
				safeAddToRenderQueue(ccX - i, ccY - r);
				safeAddToRenderQueue(ccX + r, ccY - i);
				safeAddToRenderQueue(ccX + i, ccY + r);
				safeAddToRenderQueue(ccX - r, ccY + i);
			}
			safeAddToRenderQueue(ccX + i, ccY - r);
			safeAddToRenderQueue(ccX + r, ccY + i);
			safeAddToRenderQueue(ccX - i, ccY + r);
			safeAddToRenderQueue(ccX - r, ccY - i);
		}
	}

	safeAddToRenderQueue(ccX, ccY);
}

bool CameraHooks::safeAddToRenderQueue(int x, int y)
{
	if (x < (int)m_gameCameraX - m_renderDistance) return false;
	if (x > (int)m_gameCameraX + m_renderDistance) return false;
	if (y < (int)m_gameCameraY - m_renderDistance) return false;
	if (y > (int)m_gameCameraY + m_renderDistance) return false;

	int *newElem = m_renderQueue[m_renderQueueSize];
	newElem[0] = x;
	newElem[1] = y;

	m_renderQueueSize++;
	return true;
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

static DWORD drawMapLayerOriginalFn = 0x004720e0;

__declspec(naked) void CameraHooks::drawMapLayer(void)
{
	__asm {
		MOV AL, m_enableCustomDrawMapLayer
		TEST AL, AL
		JNZ customDrawMapLayer
		JMP drawMapLayerOriginalFn
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

void CameraHooks::updateCustomCameraPos()
{
	float baseX = m_gameCameraX;
	float baseY = m_gameCameraY;
	float baseZ = m_gameCameraZ + 8.0f - m_additionalZOffset;

	float horizontalY = sin(m_horAngle) * (baseZ - m_horRotationCenterZ);
	float horizontalZ = cos(m_horAngle) * (baseZ - m_horRotationCenterZ);

	float verticalX = horizontalY * sin(m_angle);
	float verticalY = horizontalY * cos(m_angle);

	m_customCameraX = baseX + verticalX;
	m_customCameraY = baseY + verticalY;
	m_customCameraZ = m_horRotationCenterZ + horizontalZ;
}

void CameraHooks::update(CameraOrPhysics* gameCamera)
{
	if (m_mode == CameraHookMode::Disabled) return;
	updateRotationCenter();

	Ped* playerPed = fnGetPedByID(1);

	updateFollowRotation(playerPed);

	m_angle = moveAngleTowards(m_angle, m_destAngle, rotationSpeed);

	if (gameCamera) {
		m_gameCameraX = FloatDecode(gameCamera->cameraPos.x);
		m_gameCameraY = FloatDecode(gameCamera->cameraPos.y);
		m_gameCameraZ = FloatDecode(gameCamera->cameraPos.z);
		m_gameCameraField60 = FloatDecode(gameCamera->altMovingArrowsRelated);
		m_horRotationCenterZ = FloatDecode(playerPed ? playerPed->z : 0) + 0.5f;
		updateCustomCameraPos();
	}
}

void CameraHooks::setForceClearScreen(bool value)
{
	m_forceClearScreen = value;

	if (value) { // hook if not already
		HookHelper::HookFunctionCall(0x00461977, (DWORD)clearScreen, false);
	}
}

static HookHelper::HookStruct disableCullingHooks[] = {
	{0x0046c661, 6}, // DrawLeftTile
	{0x0046c327, 6},
	{0x0046c495, 6},
	{0x0046de19, 6}, // DrawBottomTile
	{0x0046da31, 6},
	{0x0046dbfa, 6},
	{0x0046cc71, 6}, // DrawRightTile
	{0x0046c87f, 6},
	{0x0046ca4d, 6},
	{0x0046d1d2, 6}, // DrawTopTile
	{0x0046ce99, 6},
	{0x0046d006, 6},

	{0x0046d581, 6}, // SlopTile1
	{0x0046d597, 6},
	{0x0046d711, 6}, // SlopTile2
	{0x0046d727, 6},
	{0x0046d8d3, 6}, // SlopTile3
	{0x0046d423, 6}, // SlopTile4
	{0x004700e9, 6}, // SlopTile5
	{0x004702d9, 6}, // SlopTile6
	{0x004704c9, 6}, // SlopTile7
	{0x004706a9, 6}, // SlopTile8
};

void CameraHooks::setDisableCulling(bool value)
{
	if (m_disableCulling == value) return;

	m_disableCulling = value;

	size_t count = sizeof(disableCullingHooks) / sizeof(disableCullingHooks[0]);
	HookHelper::ReplaceMultipleWithNoOps(disableCullingHooks, count, !value);
}

void CameraHooks::setMode(CameraHookMode mode)
{
	m_mode = mode;

	if (m_mode != CameraHookMode::Disabled) { // hook if not already
		HookHelper::HookLibraryFunctionCall(0x005952bc, (DWORD)drawTile, m_drawTileOrig);
		HookHelper::HookLibraryFunctionCall(0x005952c4, (DWORD)drawQuad, m_drawQuadOrig);
		HookHelper::HookLibraryFunctionCall(0x005952d0, (DWORD)drawTriangle, m_drawTriangleOrig);
		HookHelper::HookFunctionCall(0x00472535, (DWORD)drawMapLayer, true);
		updateRotationCenter(true);
	}

	m_enableCustomDrawMapLayer = (m_mode == CameraHookMode::Full3D);
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

void CameraHooks::setAdditionalZOffset(float val)
{
	m_additionalZOffset = val;
}

void CameraHooks::setRenderDistance(int val)
{
	m_renderDistance = val;
}
