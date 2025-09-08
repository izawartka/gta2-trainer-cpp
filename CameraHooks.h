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
	static float m_gameCameraX;
	static float m_gameCameraY;
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
	static float m_additionalZOffset;
	static struct GTAVertex m_vertexBuf[8];
	static float m_customCameraX;
	static float m_customCameraY;
	static float m_customCameraZ;
	static int m_renderDistance;
	static int (*m_renderQueue)[2];
	static size_t m_renderQueueSize;
	static int m_lastLayerIndex;
	static bool m_enableCustomDrawMapLayer;

	static float normalizeAngle(float angle);
	static float moveAngleTowards(float currentAngle, float destAngle, float speedRad);
	static float gtaAngleToFloat(short angle);

	static void rotateVertex(GTAVertex& vertex);
	static void applyCustomCulling(GTAVertex* vertexArr, int count);
	static void reverseDiagonalTile(GTAVertex* vertexArr);
	static void rotateTile(GTAVertex* vertexArr);
	static void rotateQuad(uint32_t flags, GTAVertex** vertexArrPtr);
	static void rotateTriangle(GTAVertex* vertexArr);
	static void __fastcall customDrawMapLayer(S12* param_1, int in_edx);
	static void createRenderQueue();
	static bool safeAddToRenderQueue(int x, int y);

	static void drawTile(void);
	static void drawQuad(void);
	static void drawTriangle(void);
	static void clearScreen(void);
	static void drawMapLayer(void);

	static void updateRotationCenter(bool force = false);
	static void updateFollowRotation(Ped* playerPed);
	static void updateCustomCameraPos();

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
	static void setAdditionalZOffset(float val);
	static void setRenderDistance(int val);

	static CameraHookMode getMode() { return m_mode; }
};
