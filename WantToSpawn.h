#pragma once

class WantToSpawn {
public:
	int x;
	int y;
	int z;
	int rot;
	int model;

	WantToSpawn();
	WantToSpawn(int x, int y, int z, int rot, int model);
	~WantToSpawn();

};