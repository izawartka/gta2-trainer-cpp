#include "../pch.h"
#include "LiveTableData.h"
#include "../gta2.h"

const CString LT_MODE_STR[] = {
    L"Peds",
    L"Cars"
};

const CString LT_DATA_TYPE_STR[] = {
    L"INT",
    L"UINT",
    L"SCR_FLOAT",
    L"BOOLEAN",
    L"ADDRESS",
    L"HEX"
};

const LiveTableData ltPedData[] = {
    { L"ID", 30, 4, LT_DATA_TYPE_UINT, 1, new int[1] {0x200}, true },
    { L"Address", 80, 4, LT_DATA_TYPE_ADDRESS, 0, new int[0] {}, true },
    { L"X", 46, 4, LT_DATA_TYPE_SCR_FLOAT, 3, new int[3] {0x168, 0x80, 0x14}, true },
    { L"Y", 46, 4, LT_DATA_TYPE_SCR_FLOAT, 3, new int[3] {0x168, 0x80, 0x18}, true },
    { L"Z", 46, 4, LT_DATA_TYPE_SCR_FLOAT, 3, new int[3] {0x168, 0x80, 0x1c}, true },
    { L"Car", 80, 4, LT_DATA_TYPE_ADDRESS, 1, new int[1] {0x16c}, true },
    { L"Health", 40, 2, LT_DATA_TYPE_UINT, 1, new int[1] {0x216}, true },
    { L"Remap", 40, 1, LT_DATA_TYPE_UINT, 1, new int[1] {0x244}, true },
    { L"Weapon", 40, 4, LT_DATA_TYPE_UINT, 2, new int[2] {0x170, 0x1c}, true },
    { L"Occupation", 40, 4, LT_DATA_TYPE_UINT, 1, new int[1] {0x240}, true },
    { L"Invulnerability", 40, 2, LT_DATA_TYPE_UINT, 1, new int[1] {0x208} },
    { L"Cop value", 40, 2, LT_DATA_TYPE_UINT, 1, new int[1] {0x20a} },
    { L"Elvis or target", 80, 4, LT_DATA_TYPE_ADDRESS, 1, new int[1] {0x164} },
    { L"Target car for enter", 80, 4, LT_DATA_TYPE_ADDRESS, 1, new int[1] {0x154} },
    { L"Ped ref", 80, 4, LT_DATA_TYPE_ADDRESS, 1, new int[1] {0x148} },
    { L"Car ref 2", 80, 4, LT_DATA_TYPE_ADDRESS, 1, new int[1] {0x150} },
    { L"Car ref", 80, 4, LT_DATA_TYPE_ADDRESS, 1, new int[1] {0x140} },
    { L"Elvis something", 80, 4, LT_DATA_TYPE_ADDRESS, 1, new int[1] {0x2c} },
    { L"Timer to action", 40, 2, LT_DATA_TYPE_UINT, 1, new int[1] {0x218} },
    { L"Timer to action 2", 40, 1, LT_DATA_TYPE_UINT, 1, new int[1] {0x225} },
    { L"Bitstate", 50, 4, LT_DATA_TYPE_HEX, 1, new int[1] {0x21c} },
    { L"Bitstate 2", 50, 4, LT_DATA_TYPE_HEX, 1, new int[1] {0x238} },
    { L"Body shape", 50, 4, LT_DATA_TYPE_UINT, 1, new int[1] {0x26c} },
    { L"State 1", 50, 4, LT_DATA_TYPE_UINT, 1, new int[1] {0x274} },
    { L"State 1_2", 50, 4, LT_DATA_TYPE_UINT, 1, new int[1] {0x27c} },
    { L"State 2", 50, 4, LT_DATA_TYPE_UINT, 1, new int[1] {0x278} },
    { L"State 2_2", 50, 4, LT_DATA_TYPE_UINT, 1, new int[1] {0x280} },
    { L"Objective", 50, 4, LT_DATA_TYPE_UINT, 1, new int[1] {0x258} },
    { L"State 4", 50, 4, LT_DATA_TYPE_UINT, 1, new int[1] {0x284} },
    { L"Threat search", 50, 4, LT_DATA_TYPE_UINT, 1, new int[1] {0x288} },
    { L"Threat reaction", 40, 4, LT_DATA_TYPE_UINT, 1, new int[1] {0x28c} }
};

const int ltPedDataCount = sizeof(ltPedData) / sizeof(ltPedData[0]);

const LiveTableData ltCarData[] = {
    { L"ID", 30, 4, LT_DATA_TYPE_UINT, 1, new int[1] {0x6C}, true },
    { L"Address", 80, 4, LT_DATA_TYPE_ADDRESS, 0, new int[0] {}, true },
    { L"X", 46, 4, LT_DATA_TYPE_SCR_FLOAT, 2, new int[2] {0x58, 0x30}, true },
    { L"Y", 46, 4, LT_DATA_TYPE_SCR_FLOAT, 2, new int[2] {0x58, 0x34}, true },
    { L"Z", 46, 4, LT_DATA_TYPE_SCR_FLOAT, 2, new int[2] {0x58, 0x6C}, true },
    { L"Rotation", 46, 2, LT_DATA_TYPE_UINT, 2, new int[2] {0x58, 0x58}, true },
    { L"Driver", 80, 4, LT_DATA_TYPE_ADDRESS, 1, new int[1] {0x54}, true },
    { L"Damage", 40, 2, LT_DATA_TYPE_UINT, 1, new int[1] {0x74}, true },
    { L"Model", 40, 4, LT_DATA_TYPE_UINT, 1, new int[1] {0x84}, true },
    { L"Engine state", 40, 4, LT_DATA_TYPE_UINT, 1, new int[1] {0x9C}, true },
    { L"Car physics", 80, 4, LT_DATA_TYPE_ADDRESS, 1, new int[1] {0x58} },
    { L"Sprite", 80, 4, LT_DATA_TYPE_ADDRESS, 1, new int[1] {0x50} },
    { L"Physics bitmask", 40, 4, LT_DATA_TYPE_HEX, 1, new int[1] {0x78} },
    { L"Mask", 40, 4, LT_DATA_TYPE_UINT, 1, new int[1] {0x88} },
    { L"Brake", 20, 1, LT_DATA_TYPE_BOOLEAN, 2, new int[2] {0x58, 0x91} },
    { L"Handbrake", 20, 1, LT_DATA_TYPE_BOOLEAN, 2, new int[2] {0x58, 0x92} },
    { L"Forward gas", 20, 1, LT_DATA_TYPE_BOOLEAN, 2, new int[2] {0x58, 0x93} },
    { L"Backward gas", 20, 1, LT_DATA_TYPE_BOOLEAN, 2, new int[2] {0x58, 0x94} },
    { L"Front skid", 40, 4, LT_DATA_TYPE_UINT, 2, new int[2] {0x58, 0x84} },
    { L"Rear skid", 40, 4, LT_DATA_TYPE_UINT, 2, new int[2] {0x58, 0x88} },
    { L"Pointing angle", 50, 4, LT_DATA_TYPE_INT, 2, new int[2] {0x58, 0x78} },
};

const int ltCarDataCount = sizeof(ltCarData) / sizeof(ltCarData[0]);

const LiveTableData* ltData[] = {
    ltPedData,
    ltCarData
};

const int ltDataCount[] = {
    ltPedDataCount,
    ltCarDataCount
};

const int ltItemSize[] = {
	sizeof(Ped),
	sizeof(Car)
};