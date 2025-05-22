#pragma once
#include "gta2dll.h"
#include "gta2.h"

enum class CameraHookMode {
	Disabled = 0,
	Rotate,
	Full3D
};

class CameraHooks {
	static constexpr float rotationSpeed = 0.25f;

	static CameraHookMode m_mode;
	static bool m_disableCulling;
	static bool m_followRotation;
	static bool m_forceClearScreen;
	static float m_gameCameraZ;
	static float m_gameCameraField60;
	static bool m_enabled;
	static bool m_wasFullScreen;
	static float m_destAngle;
	static float m_angle;
	static float m_horAngle;
	static DWORD m_drawTileOrig;
	static DWORD m_drawQuadOrig;
	static DWORD m_drawTriangleOrig;
	static float m_rotationCenterX;
	static float m_rotationCenterY;
	static float m_rotationCenterZ;
	static float m_horRotationCenterZ;
	static struct GTAVertex m_vertexBuf[8];

	static float normalizeAngle(float angle);
	static float moveAngleTowards(float currentAngle, float destAngle, float speedRad);
	static float gtaAngleToFloat(short angle);

	static void rotateVertex(GTAVertex& vertex);
	static void rotateTile(GTAVertex* vertexArr);
	static void rotateQuad(uint32_t flags, GTAVertex** vertexArrPtr);
	static void rotateTriangle(GTAVertex* vertexArr);

	static void drawTile(void);
	static void drawQuad(void);
	static void drawTriangle(void);
	static void clearScreen(void);

	static void updateRotationCenter(bool force = false);
	static void updateFollowRotation(Ped* playerPed);

public:
	static void update(CameraOrPhysics* gameCamera);

	static void setForceClearScreen(bool value);
	static void setDisableCulling(bool value);
	static void setMode(CameraHookMode mode);
	static void setFollowRotation(bool value);
	static void setAngle(float angle);
	static void addAngle(float delta);
	static void setHorAngle(float angle);
	static void setHorRotationCenterZ(float val);

	static CameraHookMode getMode() { return m_mode; }
};
