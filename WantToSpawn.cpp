#include "pch.h"
#include "WantToSpawn.h"

WantToSpawn::WantToSpawn(int x, int y, int z, int rot, int model, short color)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->rot = rot;
	this->model = model;
	this->color = color;
}

short WantToSpawn::GetColor()
{
	if (this->color == -2) {
		return rand() % 36;
	}

	return this->color;
}

WantToSpawn::WantToSpawn()
{

}

WantToSpawn::~WantToSpawn()
{

}