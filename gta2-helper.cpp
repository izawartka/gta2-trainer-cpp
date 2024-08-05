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

Roof* getCarRoofWithSpriteIfExists(Roof* startroof, short spritetype)
{
	if (!startroof)
		return 0;
	if (startroof->sprite->sprite == spritetype)
		return startroof;
	if (startroof->next)
		return getCarRoofWithSpriteIfExists(startroof->next, spritetype);
	return 0;
}

Roof* getCarLastRoof(Roof* startroof)
{
	if (!startroof)
		return 0;
	if (startroof->next)
		return getCarLastRoof(startroof->next);
	return startroof;
}

Car* fnGetCarByID(int id) {
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
	int distancefromPed = 0;
	int nearestPedDistance = 16384000;
	Ped* nearestPed = 0;
	PedManager_S25* manager = ByPtr(PedManager_S25, ptrToPedManager);
	Ped* lastPed = manager->lastPedInArray;

	for (int i = 0; i <= lastPed->id; i++)
	{
		Ped* foundPed = fnGetPedByID(i);

		if(!foundPed) continue;
		if(foundPed == basePed) continue;

		SCR_f x;
		SCR_f y;

		if (foundPed->currentCar) {
			if(!foundPed->currentCar->sprite) continue;

			x = foundPed->currentCar->sprite->x;
			y = foundPed->currentCar->sprite->y;
		}
		else {
			x = foundPed->x;
			y = foundPed->y;
		}

		distancefromPed =
			sqrt(
				pow(x - basePed->x, 2) +
				pow(y - basePed->y, 2)
			);

		if (distancefromPed <= nearestPedDistance)
		{
			nearestPedDistance = distancefromPed;
			nearestPed = foundPed;
		}
	}
	return nearestPed;
}

Car* FindTheNearestCar(Ped* basePed)
{
	Car* tempcar = 0;
	int distancefromCar = 0;
	int nearestCarDistance = 16384000;
	Car* nearestCar = 0;
	auto prefab = ByPtr(CarsPrefab, ptrToCarsPrefabs);
	auto lastCar = prefab->lastCar;

	for (int i = 0; i <= lastCar->id; i++)
	{
		tempcar = fnGetCarByID(i);
		if (tempcar && tempcar->sprite && tempcar->sprite->x)
		{
			distancefromCar =
				sqrt(
					pow(tempcar->sprite->x - basePed->x, 2) +
					pow(tempcar->sprite->y - basePed->y, 2)
				);
			if (distancefromCar <= nearestCarDistance)
			{
				nearestCarDistance = distancefromCar;
				nearestCar = tempcar;
			}
		}
	}
	return nearestCar;
}

SCR_f* GetPointInADistance(SCR_f baseX, SCR_f baseY, short angle, SCR_f distance) {
	SCR_f targetXY[2];
	double nAngle = angle / 4.0 + 270.0;
	targetXY[0] = baseX + (cos(nAngle * 0.017453f) * distance);
	targetXY[1] = baseY - (sin(nAngle * 0.017453f) * distance);
	return targetXY;
}

POINT ConvertGameWorldCoordinateToScreen(SCR_f gameX, SCR_f gameY) {
	POINT p;
	int width = *(int*)0x00673578;
	int height = *(int*)0x006732e8;

	auto pp = ByPtr(CameraOrPhysics, ptrToPlayerPhysics);

	double right = FloatDecode(pp->cameraBoundaries.right);
	double left = FloatDecode(pp->cameraBoundaries.left);
	double widthX = right - left;
	double gameUnitsToScreenProportionX = (double)width / widthX;
	double targetX = FloatDecode(gameX) - left; // offset from left

	double top = FloatDecode(pp->cameraBoundaries.top);
	double bottom = FloatDecode(pp->cameraBoundaries.bottom);
	double heightY = bottom - top;
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

bool IsPointSafe(SCR_f x, SCR_f y, SCR_f z)
{
	if(x < 1 * 16384) return false;
	if(x > 254 * 16384) return false;
	if(y < 1 * 16384) return false;
	if(y > 254 * 16384) return false;
	if(z < 0 * 16384) return false;
	if(z > 7 * 16384) return false;

	return true;
}

void ClampPointToSafe(SCR_f &x, SCR_f &y)
{
	if(x < 1 * 16384) x = 1 * 16384;
	if(x > 254 * 16384) x = 254 * 16384;
	if(y < 1 * 16384) y = 1 * 16384;
	if(y > 254 * 16384) y = 254 * 16384;
}

void ClampPointToSafe(SCR_f& x, SCR_f& y, SCR_f& z)
{
	ClampPointToSafe(x, y);
	if(z < 0 * 16384) z = 0 * 16384;
	if(z > 7 * 16384) z = 7 * 16384;
}