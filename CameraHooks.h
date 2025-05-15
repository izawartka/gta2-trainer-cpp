#pragma once
#include "gta2dll.h"
#include "gta2.h"

class CameraHooks {
	static constexpr float rotationSpeed = 0.15f;

	static bool m_enabled;
	static bool m_wasFullScreen;
	static float m_destAngle;
	static float m_angle;
	static DWORD m_drawTileOrig;
	static DWORD m_drawQuadOrig;
	static DWORD m_drawTriangleOrig;
	static float m_rotationCenterX;
	static float m_rotationCenterY;
	static struct QuadVertex m_vertexBuf[8];

	static float normalizeAngle(float angle);
	static float moveAngleTowards(float currentAngle, float destAngle, float speedRad);
	static float gtaAngleToFloat(short angle);

	static void rotatePoint(float* xAddr, float* yAddr);
	static void rotateTile(QuadVertex* vertexArr);
	static void rotateQuad(uint32_t flags, QuadVertex** vertexArrPtr);
	static void rotateTriangle(QuadVertex* vertexArr);

	static void drawTile(void);
	static void drawQuad(void);
	static void drawTriangle(void);

	static void updateRotationCenter(bool force = false);

public:
	static void init();
	static void setEnabled(bool enabled);
	static void update();
};
