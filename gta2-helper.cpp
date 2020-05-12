#include "pch.h"
#include "gta2-helper.h"

void fnShowCustomTextMessage(WCHAR* message) {
	auto locales = ByPtr(LocaleSettings, ptrToS2LocalesSettings);
	auto locale = locales->ptrToLocales;

	auto original = locale->text;
	locale->text = message;
	fnShowMessageToPlayer(3, "1001");
	locale->text = original;
}

Car* fnGetCarById(int id) {
	auto prefab = ByPtr(CarsPrefab, ptrToCarsPrefabs);
	auto tcar = prefab->lastCar;
	Car* car = 0;
	while (tcar)
	{
		if (tcar->id == id) {
			car = tcar;
			break;
		}
		tcar = tcar->lastCar;
	}
	if (car) return car;
	else return 0;
}

SCR_f FloatEncode(double x) {
	return x * 16384;
}

double FloatDecode(SCR_f x) {
	return (double)x / 16384.0;
}

Ped* FindTheNearestPed(Ped* basePed)
{
	Ped* tempped = 0;
	int distancefromPed = 0;
	int nearestPedDistance = 16384000;
	Ped* nearestPed = 0;

	for (int i = 2; i < 255; i++)
	{
		tempped = fnGetPedByID(i);
		if (tempped && tempped->x)
		{
			distancefromPed =
				sqrt(
					pow(tempped->x - basePed->x, 2) +
					pow(tempped->y - basePed->y, 2)
				);
			if (distancefromPed <= nearestPedDistance)
			{
				nearestPedDistance = distancefromPed;
				nearestPed = tempped;
			}
		}
	}
	return nearestPed;
}

POINT ConvertGameWorldCoordinateToScreen(SCR_f gameX, SCR_f gameY) {
	POINT p;
	int width = *(int*)0x00673578;
	int height = *(int*)0x006732e8;

	auto pp = ByPtr(PlayerPhysics, ptrToPlayerPhysics);

	auto right = FloatDecode(pp->rightOfTheScreenX);
	auto left = FloatDecode(pp->leftOfTheScreenX);
	auto widthX = right - left;
	double gameUnitsToScreenProportionX = (double)width / widthX;
	double targetX = FloatDecode(gameX) - left; // offset from left

	auto top = FloatDecode(pp->topOfTheScreenY);
	auto bottom = FloatDecode(pp->bottomOfTheSceenY);
	auto heightY = bottom - top;
	double gameUnitsToScreenProportionY = (double)height / heightY;
	double targetY = FloatDecode(gameY) - top; // offset from top 

	double centerX = (right - left) / 2.0 + left;
	double centerY = (bottom - top) / 2.0 + top;
	const double magic = 50;
	const int magic2 = 800;
	double zoom = (double)widthX / 9.0;
	double cameraCorrectionX = (FloatDecode(gameX) - centerX) / magic;
	double cameraCorrectionY = (FloatDecode(gameY) - centerY) / magic;

	p.x = (long)(targetX * gameUnitsToScreenProportionX + cameraCorrectionX * magic2 / zoom);
	p.y = (long)(targetY * gameUnitsToScreenProportionY + cameraCorrectionY * magic2 / zoom);
	return p;
}