#pragma once

class WantToSpawn {
private:
	short color;
public:
	int x;
	int y;
	int z;
	int rot;
	int model;

	WantToSpawn(int x, int y, int z, int rot, int model, short color = -1);
	short GetColor();
	WantToSpawn();
	~WantToSpawn();

};