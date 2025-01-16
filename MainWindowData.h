#pragma once
#ifndef SPAWNING_DATA
#define SPAWNING_DATA

struct WantToSpawn {
	int x;
	int y;
	int z;
	int rot;
	unsigned int model;
	short color = -1;
	bool miniCar = false;
};

const LPCTSTR objectsCategories[] = {
		L"Basic objects",           // 0
		L"Weapon collectibles",     // 1
		L"Car Weapon collectibles", // 2
		L"Power-Ups",				// 3
		L"Skids",					// 4
		L"Projectiles",				// 5
		L"Phones",					// 6
		L"Others",					// 7
		L"Invisible",				// 8
		L"Basic objects (other states)" // 9
};

struct CatMenuItem {
	char category;
	wchar_t* name;
	DWORD id;
};

struct MenuItem {
	wchar_t* name;
	DWORD id;
};

const CatMenuItem objects[] = {
	{0, L"BIN_LID", 1},
	{0, L"BOLLARD", 2},
	{0, L"CONE", 3},
	{0, L"BOXES", 4},
	{0, L"BLASTER", 5},
	{0, L"RUBBISH", 6},
	{0, L"BIN", 7},
	{9, L"ANIMATING_OIL", 8},
	{0, L"OIL", 9},
	{0, L"MINE", 10},
	{0, L"BUSH", 11},
	{0, L"CRATE", 12},
	{0, L"FOOTY", 13},
	{0, L"HARDBOX", 14},
	{0, L"NEWSDIS", 15},
	{0, L"OILDRUM", 16},
	{0, L"TYRE", 17},
	{0, L"HYDRANT_LID", 18},
	{0, L"HYDRANT", 19},
	{0, L"HYDRANT_UNLID", 20},
	{0, L"ROADBLOCK", 21},
	{0, L"BENCH", 22},
	{0, L"PACKAGE", 23},
	//{0, L"UNKNOWN_OBJ", 24},
	{8, L"TOWER", 25},
	//{0, L"EXPLODE_MEDIUM", 42},
	{9, L"MOVING_PACKAGE", 43}, // unofficial name
	{9, L"DEAD_PACKAGE", 44},  // unofficial name
	{9, L"MOVING_BENCH", 45}, // unofficial name
	{9, L"DEAD_BENCH", 46},  // unofficial name
	{9, L"MOVING_ROADBLOCK", 47}, // unofficial name
	{9, L"DEAD_ROADBLOCK", 48},  // unofficial name
	{9, L"MOVING_HYDRANT_LID", 49}, // unofficial name
	{9, L"ANIMATING_CRATE", 50}, // unofficial name
	{9, L"DEAD_CRATE", 51}, // unofficial name
	{9, L"DEAD_BOXES", 52}, // unofficial name
	{9, L"DEAD_CONE", 53}, // unofficial name
	{9, L"DEAD_BLASTER", 54}, // unofficial name
	{9, L"DEAD_BUSH", 55}, // unofficial name
	{9, L"MOVING_FOOTY", 56}, // unofficial name
	{9, L"MOVING_HARDBOX", 57}, // unofficial name
	{9, L"DEAD_HARDBOX", 58},  // unofficial name
	{9, L"MOVING_NEWSDIS", 59}, // unofficial name
	{9, L"DEAD_NEWSDIS", 60},  // unofficial name
	{9, L"MOVING_OILDRUM", 61}, // unofficial name
	{9, L"DEAD_OILDRUM", 62},  // unofficial name
	{9, L"MOVING_TYRE", 63}, // unofficial name
	{1, L"MOVING_COLLECT_00 (Pistol)", 64},
	{1, L"MOVING_COLLECT_01 (S-Uzi)", 65},
	{1, L"MOVING_COLLECT_02 (Rocket Launcher)", 66},
	{1, L"MOVING_COLLECT_03 (ElectroGun)", 67},
	{1, L"MOVING_COLLECT_04 (Molotov Coctail)", 68},
	{1, L"MOVING_COLLECT_05 (Grenade)", 69},
	{1, L"MOVING_COLLECT_06 (Shotgun)", 70},
	{1, L"MOVING_COLLECT_07 (ElectroBaton !)", 71},
	{1, L"MOVING_COLLECT_08 (Flamethrower)", 72},
	{1, L"MOVING_COLLECT_09 (Silenced S-Uzi)", 73},
	{1, L"MOVING_COLLECT_10 (Dual Pistol)", 74},
	{1, L"MOVING_COLLECT_11 (Letter L)", 75},
	{1, L"MOVING_COLLECT_12 (Letter M)", 76},
	{1, L"MOVING_COLLECT_13 (Letter N)", 77},
	{1, L"MOVING_COLLECT_14 (Letter O)", 78},
	{2, L"MOVING_COLLECT_15 (Vehicle bomb)", 79},
	{2, L"MOVING_COLLECT_16 (Vehicle Oil Slick)", 80},
	{2, L"MOVING_COLLECT_17 (Vehicle Mine)", 81},
	{2, L"MOVING_COLLECT_18 (Vehicle Machine Gun)", 82},
	{2, L"MOVING_COLLECT_19 (Tank Cannon)", 83},
	{2, L"MOVING_COLLECT_20 (Water Cannon)", 84},
	{2, L"MOVING_COLLECT_21 (Vehicle Flamethrower)", 85},
	{2, L"MOVING_COLLECT_22 (Jeep Turret)", 86},
	{2, L"MOVING_COLLECT_23 (Instant Vehicle Bomb)", 87},
	{2, L"MOVING_COLLECT_24 (Letter J)", 88},
	{2, L"MOVING_COLLECT_25 (Letter K)", 89},
	{2, L"MOVING_COLLECT_26 (Letter L)", 90},
	{2, L"MOVING_COLLECT_27 (Letter M)", 91},
	{3, L"MOVING_COLLECT_28 (Multiplier +1)", 92},
	{3, L"MOVING_COLLECT_29 (Life +1)", 93},
	{3, L"MOVING_COLLECT_30 (Health)", 94},
	{3, L"MOVING_COLLECT_31 (Armor)", 95},
	{3, L"MOVING_COLLECT_32 (Get Outta Jail Free Card)", 96},
	{3, L"MOVING_COLLECT_33 (Cop Bribe)", 97},
	{3, L"MOVING_COLLECT_34 (Invulnerability*)", 98},
	{3, L"MOVING_COLLECT_35 (Double Damage)", 99},
	{3, L"MOVING_COLLECT_36 (Fast Reload)", 100},
	{3, L"MOVING_COLLECT_37 (ElectroFingers)", 101},
	{3, L"MOVING_COLLECT_38 (Respect!)", 102},
	{3, L"MOVING_COLLECT_39 (Invisibility)", 103},
	{3, L"MOVING_COLLECT_40 (Instant Gang)", 104},
	{3, L"MOVING_COLLECT_41 (Letter N)", 105},
	{3, L"MOVING_COLLECT_42 (Letter O)", 106},
	{3, L"MOVING_COLLECT_43 (Letter P)", 107},
	{3, L"MOVING_COLLECT_44 (Letter Q)", 108},
	{7, L"SMALL_ARROW", 109},
	{7, L"BLOOD_SPARK", 111},
	{8, L"PARTICLE_SYSTEM", 113},
	{7, L"FIREJET", 114},
	{4, L"SMALL_BROWN_SKID", 116},
	{4, L"SMALL_GREY_SKID", 117},
	{4, L"SMALL_RED_SKID", 118},
	{4, L"MEDIUM_BROWN_SKID", 119},
	{4, L"MEDIUM_GREY_SKID", 120},
	{4, L"MEDIUM_RED_SKID", 121},
	{8, L"CAR_CROSSING", 122},
	{9, L"MOVING_BUSH", 123},
	{4, L"BIG_WHITE_SKID", 124},
	{4, L"MEDIUM_WHITE_SKID", 125},
	{4, L"SMALL_WHITE_SKID", 126},
	{5, L"ROCKET", 128},
	{8, L"BUS_STOP_MARKER", 129},
	{8, L"CAR_SHOP", 130},
	{8, L"BUSY_CAR_SHOP", 131},
	{8, L"CAR_BOMB", 132},
	{5, L"MOLOTOV_MOVING", 138},
	{4, L"HUGE_RED_SKID", 144},
	{4, L"HUGE_WHITE_SKID", 145},
	{4, L"HUGE_BROWN_SKID", 146},
	{4, L"HUGE_GREY_SKID", 147},
	{7, L"TANKTOP", 148},
	{7, L"ANTENNA", 149},
	{9, L"ANIMATING_RUBBISH", 151},
	{9, L"DEAD_RUBBISH", 152},
	{9, L"MOVING_CONE", 155},
	{9, L"MOVING_BLASTER", 156}, // unofficial name
	{9, L"MOVING_BIN", 157}, // unofficial name
	{9, L"MOVING_BIN_LID", 158},
	{8, L"SAVE_POINT", 161}, // unofficial name
	{6, L"PHONE", 163},
	{6, L"PHONE_RINGING", 164},
	//{9, L"DEAD_MINE", 165}, // unofficial name // invisible and unsure
	{6, L"PHONE_DEAD", 174},
	{7, L"BRIEFCASE", 175},
	{6, L"RED_PHONE", 176},
	{6, L"RED_PHONE_RINGING", 177},
	{6, L"YELLOW_PHONE", 178},
	{6, L"YELLOW_PHONE_RINGING", 179},
	{6, L"GREEN_PHONE", 180},
	{6, L"GREEN_PHONE_RINGING", 181},
	{5, L"GRENADE", 182},
	{5, L"SHOT", 192},
	{5, L"FLAMING_BULLET", 194},
	{7, L"FIRE", 197},
	{5, L"WATER_BULLET", 198},
	{7, L"BOMB", 247},
	{4, L"BIG_BROWN_SKID", 249},
	{4, L"BIG_GREY_SKID", 250},
	{4, L"BIG_RED_SKID", 253},
	{5, L"BULLET", 254},
	{7, L"TRAFFIC_LIGHT", 255},
	{7, L"RED_FOOTPRINTS", 256},
	{7, L"BLOOD", 257},
	{8, L"CROSSING", 258},
	{7, L"SPARK", 259},
	{5, L"PISTOL_BULLET", 265},
	{3, L"BONUS_TOKEN", 266},
	{5, L"TASSER_BULLET", 277},
	{8, L"SOUND_INSTANT", 279},
	{8, L"INVISIBLE_TARGET", 280},
	{0, L"POWERGEN", 281},
	{9, L"POWERGEN_DEAD", 282},
	{8, L"INVISIBLE_DESTRUCTIBLE", 283},
	{7, L"GENLITE", 284},
	{8, L"INVISIBLE_DEAD", 285},
	{3, L"KILL_FRENZY", 286},
	{8, L"TUNNEL_BLOCKER", 294},
	{3, L"REMOTE", 295}
};

const LPCTSTR carsCategories[] = {
	L"A-I", // 0
	L"J-S", // 1
	L"T-Z", // 2
};

const CatMenuItem cars[] = {
	{0, L"ALFA", 0},
	{0, L"ALLARD", 1},
	{0, L"AMDB4", 2},
	{0, L"APC", 3},
	{0, L"BANKVAN", 4},
	{0, L"BMW", 5},
//  {0, L"BOXCAR", 6},
	{0, L"BOXTRUCK",7},
	{0, L"BUG", 8},
	{0, L"BUICK", 10},
	{0, L"BUS", 11},
	{0, L"COPCAR", 12},
	{0, L"DART", 13},
	{0, L"EDSEL", 14},
	{0, L"EDSELFBI", 84},
	{0, L"FIAT", 16},
	{0, L"FIRETRUK", 17},
	{0, L"GRAHAM", 18},
	{0, L"GT24640", 19},
	{0, L"GTRUCK", 21},
	{0, L"GUNJEEP", 22},
	{0, L"HOTDOG", 23},
	{0, L"HOTDOG_D1", 24},
	{0, L"HOTDOG_D2", 25},
	{0, L"HOTDOG_D3", 26},
	{0, L"HOTDOG_D4", 85},
	{0, L"ICECREAM", 27},
	{0, L"ISETLIMO", 28},
	{0, L"ISETTA", 29},
	{1, L"JEEP", 30},
	{1, L"JEFFREY", 31},
	{1, L"KRSNABUS", 86},
	{1, L"LIMO", 32},
	{1, L"LIMO2", 33},
	{1, L"MEDICAR", 34},
	{1, L"MERC", 35},
	{1, L"MESSER", 36},
	{1, L"MIURA", 37},
	{1, L"MONSTER", 38},
	{1, L"MORGAN", 39},
	{1, L"MORRIS", 40},
	{1, L"PICKUP", 41},
	{1, L"RTYPE", 42},
	{1, L"SPIDER", 44},
	{1, L"SPRITE", 45},
	{1, L"STINGRAY", 46},
	{1, L"STRATOS", 47},
	{1, L"STRATOSB", 48},
	{1, L"STRIPETB", 49},
	{1, L"STYPE", 50},
	{1, L"STYPECAB", 51},
	{1, L"SWATVAN", 52},
	{2, L"T2000GT", 53},
	{2, L"TANK", 54},
	{2, L"TANKER", 55},
	{2, L"TAXI", 56},
	{2, L"TBIRD", 57},
	{2, L"TOWTRUCK", 58},
//  {2, L"TRAIN", 59},
//  {2, L"TRAINCAB", 60},
//  {2, L"TRAINFB", 61},
	{2, L"TRANCEAM", 62},
	{2, L"TRUKCAB1", 63},
	{2, L"TRUKCAB2", 64},
	{2, L"TRUKCONT", 65},
	{2, L"TRUKTRNS", 66},
	{2, L"TVVAN", 67},
	{2, L"VAN", 68},
	{2, L"VESPA", 69},
	{2, L"VTYPE", 70},
	{2, L"WBTWIN", 71},
	{2, L"WRECK0", 72},
	{2, L"WRECK1", 73},
	{2, L"WRECK2", 74},
	{2, L"WRECK3", 75},
	{2, L"WRECK4", 76},
	{2, L"WRECK5", 77},
	{2, L"WRECK6", 78},
	{2, L"WRECK7", 79},
	{2, L"WRECK8", 80},
	{2, L"WRECK9", 81},
	{2, L"XK120", 82},
	{2, L"ZCX5", 83}
};

struct CarEmblem {
	wchar_t* name;
	short id;
};

const CarEmblem carEmblems[] = {
	{L"None", 0},
	{L"Loonies", 294},
	{L"Yakuza", 295},
	{L"Zaibatsu", 296},
	{L"Rednecks", 297},
	{L"Scientists", 298},
	{L"Krishna", 299},
	{L"Russians", 300},
	{L"Bomb", 8},
};

const MenuItem weapons[] = {
	{L"Pistol", 0},
	{L"S-Uzi", 1},
	{L"Rocket Launcher", 2},
	{L"ElectroGun", 3},
	{L"Molotov Coctail", 4},
	{L"Grenade", 5},
	{L"Shotgun", 6},
	{L"ElectroBaton (!)", 7},
	{L"Flamethrower", 8},
	{L"Silenced S-Uzi", 9},
	{L"Dual Pistol", 10},
	{L"Letter L", 11},
	{L"Letter M", 12},
	{L"Letter N", 13},
	{L"Letter O", 14}
};

const MenuItem carWeapons[] = {
	{L"Vehicle bomb", 0},
	{L"Vehicle Oil Slick", 1},
	{L"Vehicle Mine", 2},
	{L"Vehicle Machine Gun", 3},
	{L"Tank Cannon", 4},
	{L"Water Cannon", 5},
	{L"Vehicle Flamethrower", 6},
	{L"Jeep Turret", 7},
	{L"Instant Vehicle Bomb", 8},
	{L"Letter J", 9},
	{L"Letter K", 10},
	{L"Letter L", 11},
	{L"Letter M", 12}
};

const MenuItem vocals[] = {
	{L"INSANE STUNT BONUS", 1},
	{L"GRAND THEFT AUTO", 2},
	{L"WIPEOUT", 3},
	{L"EXPEDITIOUS EXECUTION", 4},
	{L"GENOCIDE", 5},
	{L"COP KILLA", 6},
	{L"CAR JACKA", 7},
	{L"ELVIS HAS LEFT THE BUILDING", 8},
	{L"ACCURACY BONUS", 9},
	{L"BACK TO FRONT BONUS", 10},
	{L"MEDICAL EMERGENCY", 11},
	{L"KILL FRENZY", 12},
	{L"BUSTED", 17},
	{L"FRENZY FAILED", 18},
	{L"FRENZY PASSED", 19},
	{L"FRYING TONIGHT", 20},
	{L"GAME OVER", 21},
	{L"JOB COMPLETE", 22},
	{L"JOB FAILED", 23},
	{L"AND REMEMBER, RESPECT IS EVERYTHING", 24},
	{L"SHOCKING", 25},
	{L"MMM... SOMETHIN'S COOKIN", 26},
	{L"TIME'S UP, PAL", 27},
	{L"TOASTED", 28},
	{L"WASTED", 29},
	{L"BOMB ARMED", 30},
	{L"LAUGH6", 31},
	{L"LAUGH (random)", 32},
	{L"RACE OVER", 33},
	{L"SECOND LAP", 34},
	{L"FINAL LAP", 35},
	{L"RACE ON", 36},
	{L"MULTIPLIER X2", 37},
	{L"MULTIPLIER X3", 38},
	{L"MULTIPLIER X4", 39},
	{L"MULTIPLIER X5", 40},
	{L"MULTIPLIER X6", 41},
	{L"TIME OUT", 42},
	{L"YOUR TIME IS EXTENDED", 43},
	{L"TIME'S UP, PAL (duplicate)", 44},
	{L"OH SORRY ABOUT THAT... DID THAT HURT?", 45},
	{L"NICE WORK", 46},
	{L"CHOCTASTIC", 47},
	{L"RASPBERRY RIPPLE", 48},
	{L"YOU SHOT YOUR LOAD", 49},
	{L"OH... DID THAT HURT?", 50},
	{L"DEATH TO ICE CREAM VANS", 51},
	{L"CRISPY CRITTER", 52},
	{L"YOU'RE TOAST, BUDDY", 53},
	{L"EAT LEADEN DEATH, PUNK", 54},
	{L"THAT'S GONNA HURT", 55},
	{L"SORRY ABOUT THAT", 56},
	{L"XIN LOI, MY MAN", 57},
	{L"DAMN SUNDAY DRIVERS", 58},
	{L"SUCK IT AND SEE", 59},
	{L"TASTE MY WRATH, ICE-CREAM BOY", 60},
	{L"HALLELUJAH! ANOTHER SOUL SAVED", 61},
	{L"DAMNATION! NO DONATION, NO SALVATION", 62}
};

const MenuItem nativeCheats[] = {
	{L"Do blood", 0x51},
	{L"Show objects IDs", 0x52},
	{L"Skip traffic lights", 0x53},
	{L"Skip buses", 0x54},
	{L"Show counters", 0x55},
	{L"Skip particles", 0x56},
	//{L"Skip trains", 0x57}, // crashes the game;v
	{L"Show input", 0x58},
	{L"Skip right tiles", 0x59},
	{L"Show hidden faces", 0x5A},
	{L"No traffic", 0x5B},
	{L"Unlock all levels", 0x5C},
	//{L"Exploding on", 0x5D}, // doesn't seem to work and is being overwritten
	{L"No police", 0x5E},
	{L"Skip bottom tiles", 0x5F},
	//{L"Do Police 1", 0x60}, // no effect observed
	{L"Infinite lives", 0x61},
	//{L"Unknown 0x62"}, // unused
	{L"Log random", 0x63},
	{L"No HUD", 0x64},
	//{L"Double damage", 0x65}, // requires restart
	{L"Log missions", 0x66},
	{L"Skip left tiles", 0x67},
	//{L"Do corner window", 0x68}, // no effect ovserved
	{L"No pedestrians", 0x69},
	//{L"Unknown 0x6A", 0x6A}, // probably unused
	{L"No ambulances", 0x6B},
	//{L"Skip window check", 0x6C}, // probably unused
	{L"Mini cars", 0x6D},
	//{L"Give basic weapons", 0x6E}, // no effect observed
	{L"Show Imaginary Things", 0x6F},
	//{L"Give electric gun", 0x70}, // requires restart
	{L"Invulnerability", 0x71},
	{L"No audio", 0x72},
	//{L"Unknown 0x73", 0x73}, // GXT relacted, unused
	//{L"Get all weapons", 0x74}, // requires restart
	{L"No annoying chars", 0x75},
	{L"Show player names", 0x76}, // test needed
	{L"Log DirectInput", 0x77},
	{L"No slopes tiles", 0x78},
	{L"Show FPS", 0x79},
	{L"Log random extra", 0x7A},
	// {L"Multiplier x10", 0x7B}, // requires restart
	// 0x7C - Skip frontend
	{L"Do Brian test", 0x7D},
	// 0x7E - Do load savegame
	{L"Show car horn", 0x7F},
	{L"Do test", 0x80},
	{L"Show drawing info", 0x81},
	{L"Show camera info", 0x82},
	// {L"Get outta jail free card", 0x83}, // requires restart
	// {L"Free shopping", 0x84}, // requires restart
	{L"Show vehicle info", 0x85},
	// 0x86 - Ignore replay header
	{L"Debug keys", 0x87},
	{L"Insane speed", 0x88},
	{L"Show junctions IDs", 0x89},
	// {L"Max respect", 0x8A}, // requires restart
	{L"Skip fire engines", 0x8B},
	{L"No top tiles", 0x8C},
	{L"Show ped info", 0x8D},
	// {L"Invisibility", 0x8E}, // requires restart
	// {L"Health 99", 0x8F}, // requires restart
	{L"Skip tiles", 0x90},
	{L"Log input", 0x91},
	// {L"Unknown 0x92", 0x92}, // replay related
	// {L"Aggresive peds", 0x93}, // requires restart
	{L"Don't get car back", 0x94}, // test needed
	{L"Show traffic info", 0x95},
	{L"Show traffic lights info", 0x96},
	// 0x97 - Give money on start
	// {L"Unknown 0x98", 0x98}, // probably unused
	{L"Log routefinder", 0x99},
	{L"Do text ID test", 0x9A},
	// 0x9B - Give flamethrower
	{L"Skip lid", 0x9C},
	// {L"Do Police 2", 0x9D}, // no effect ovserved
	{L"Keep weapons after death", 0x9E},
	{L"Only elvis peds", 0x9F},
	{L"Nekkid peds", 0xA0},
	{L"Show peds IDs", 0xA1},
	// 0xA2 - Unknown, requires restart
	// 0xA3 - Replay related
	// 0xA4 - Skip replay sync check
	{L"Show brief number", 0xA5},
	// {L"$9,000,000", 0xA6}, // requires restart
	{L"Show cycle", 0xA7},
	{L"Do sync check", 0xA8},
	// {L"Do Police 3", 0xA9}, // no effect observed
	// 0xAA - Play replay
	{L"Skip quit confirm", 0xAB},
	{L"Limit recycling", 0xAC}, // test needed
	// 0xAD - Exit after replay
	// {L"Skip missions", 0xAE}, // crashes the game
	{L"Skip skidmarks", 0xAF},
	{L"Log collisions", 0xB0},
	{L"Show collision box", 0xB1}, // ?
	{L"Show all arrows", 0xB2},
	{L"Kill phones on answer", 0xB3}, // ?
};

struct PedProperty {
	wchar_t* name;
	UINT id;
};

const PedProperty occupations[] = {
	{L"0 - Player", 0},
	{L"1", 1},
	{L"2", 2},
	{L"3 - Dummy", 3},
	{L"4 - Mission driver ?", 4},
	{L"5 - Driver ?", 5},
	{L"7", 7},
	{L"8 - Bus passenger", 8},
	{L"9 - Train passenger", 9},
	{L"10", 10}, // crashes the game
	{L"11", 11},
	{L"12", 12},
	{L"13 - Angry driver ?", 13},
	{L"14 - Psycho ?", 14},
	{L"15 - Mugger", 15},
	{L"16 - Car thief", 16},
	{L"17", 17},
	{L"18 - Criminal ?", 18},
	{L"19 - Gang member", 19},
	{L"20", 20},
	{L"21", 21},
	{L"22 - Elvis", 22},
	{L"23 - Medic", 23},
	{L"24 - Cop in car", 24},
	{L"25 - SWAT in car", 25},
	{L"26 - FBI in car", 26},
	{L"27 - Army in Jeep", 27},
	{L"28 - Guard", 28},
	{L"29 - Cop on foot", 29},
	{L"30", 30},
	{L"31 - Army on foot", 31},
	{L"32 - Guard against player ?", 32},
	{L"33 - Criminal type 1 ?", 33},
	{L"34 - Criminal type 2 ?", 34},
	{L"35 - Special group member", 35},
	{L"36 - Tank driver ?", 36},
	{L"37 - FBI in a roadblock", 37},
	{L"38 - Fireman ?", 38},
	{L"39 - Army in a roadblock", 39},
	{L"40", 40},
	{L"41 - Drone ?", 41},
	{L"42 - Driver (get outta my car!)", 42},
	{L"43 - Stand still bloke ?", 43},
	{L"44 - Elvis leader ?", 44},
	{L"45 - Refugees ?", 45},
	{L"46 - Any law enforcement ?", 46},
	{L"47 - Any emergency service ?", 47},
	{L"48 - Any gang member ?", 48},
	{L"49 - Any Elvis ?", 49},
	{L"50", 50},
	{L"51", 51}
};

const PedProperty pedBodyShapes[] = {
	{L"Ped", 0},
	{L"Armored", 1},
	{L"Heavily armored", 2}
};

const PedProperty pedRemaps[] = {
	{L"Blue police", 0},
	{L"Green police", 1},
	{L"Red police", 2},
	{L"Yellow police", 3},
	{L"Khaki police", 4},
	{L"Red head Redneck", 5},
	{L"Blond head Redneck", 6},
	{L"Yellow Scientist", 7},
	{L"Zaibatsu", 8},
	{L"Kristna", 9},
	{L"Russian", 10},
	{L"Loony", 11},
	{L"Elvis", 12},
	{L"Yakuza", 13},
	{L"Fireman", 14},
	{L"Car thief", 15},
	{L"Medic", 16},
	{L"Mugger", 17},
	{L"Dummy 2", 18},
	{L"Dummy 3", 19},
	{L"Dummy 4", 20},
	{L"Dummy 5", 21},
	{L"Prison uniform", 22},
	{L"Hulk 1", 23},
	{L"Hulk 2", 24},
	{L"Player", 25},
	{L"Naked dummy", 26},
	{L"Dummy 6", 27},
	{L"Dummy 7", 28},
	{L"Dummy 8", 29},
	{L"Dummy 9", 30},
	{L"Dummy 10", 31},
	{L"Dummy 11", 32},
	{L"Dummy 12", 33},
	{L"Dummy 13", 34},
	{L"Dummy 14", 35},
	{L"Dummy 15", 36},
	{L"Dummy 16", 37},
	{L"Dummy 17", 38},
	{L"Dummy 18", 39},
	{L"Dummy 19", 40},
	{L"Dummy 20", 41},
	{L"Dummy 21", 42},
	{L"Dummy 22", 43},
	{L"Dummy 23", 44},
	{L"Dummy 24", 45},
	{L"Dummy 25", 46},
	{L"Dummy 26", 47},
	{L"Dummy 27", 48},
	{L"Dummy 28", 49},
	{L"Dummy 29", 50},
	{L"Dummy 30", 51},
	{L"Dummy 31", 52}
};

const PedProperty pedThreatSearch[] = {
	{L"No threats", 0},
	{L"In line of sight", 1},
	{L"In nearby area", 2},
	{L"Area (player threat only)", 3},
	{L"Sight (player threat only)", 4},
	{L"Area (player only)", 5},
	{L"Sight (player only)", 6}
};

const PedProperty pedThreatReactions[] = {
	{L"No reaction", 0},
	{L"React as emergency", 1},
	{L"React as normal", 2},
	{L"Run away", 3}
};

typedef enum PED_OBJ_TARGET_TYPE {
	PED_OBJ_TARGET_TYPE_NONE = 0,
	PED_OBJ_TARGET_TYPE_PED = 1,
	PED_OBJ_TARGET_TYPE_CAR = 2,
	PED_OBJ_TARGET_TYPE_OBJ = 3,
	PED_OBJ_TARGET_TYPE_COORDS = 4,
} PED_OBJ_TARGET_TYPE;

struct PedObjectiveProperty {
	wchar_t* name;
	UINT id;
	PED_OBJ_TARGET_TYPE targetType;
};

const PedObjectiveProperty pedObjectives[] = {
	{L"No objective", 0, PED_OBJ_TARGET_TYPE_NONE},
	{L"Flee on foot till safe", 1, PED_OBJ_TARGET_TYPE_NONE},
	{L"Flee char on foot till safe", 2, PED_OBJ_TARGET_TYPE_PED},
	{L"Flee char on foot always", 3, PED_OBJ_TARGET_TYPE_PED},
	{L"4 - ?", 4, PED_OBJ_TARGET_TYPE_PED},
	{L"5 - ?", 5, PED_OBJ_TARGET_TYPE_PED},
	{L"6 - ?", 6, PED_OBJ_TARGET_TYPE_PED},
	{L"7 - ?", 7, PED_OBJ_TARGET_TYPE_NONE},
	{L"8 - ?", 8, PED_OBJ_TARGET_TYPE_NONE},
	{L"9 - ?", 9, PED_OBJ_TARGET_TYPE_NONE},
	{L"10 - ?", 10, PED_OBJ_TARGET_TYPE_NONE},
	{L"11 - ?", 11, PED_OBJ_TARGET_TYPE_NONE},
	{L"Go to area on foot", 12, PED_OBJ_TARGET_TYPE_COORDS},
	{L"13 - ?", 13, PED_OBJ_TARGET_TYPE_NONE},
	{L"Go to area in car", 14, PED_OBJ_TARGET_TYPE_COORDS},
	{L"15 - ?", 15, PED_OBJ_TARGET_TYPE_NONE},
	{L"Go to char on foot", 16, PED_OBJ_TARGET_TYPE_PED},
	{L"17 - ?", 17, PED_OBJ_TARGET_TYPE_NONE},
	{L"18 - ?", 18, PED_OBJ_TARGET_TYPE_NONE},
	{L"Kill char any means", 19, PED_OBJ_TARGET_TYPE_PED},
	{L"Kill char on foot", 20, PED_OBJ_TARGET_TYPE_PED},
	{L"21 - ?", 21, PED_OBJ_TARGET_TYPE_CAR},
	{L"22 - ?", 22, PED_OBJ_TARGET_TYPE_CAR},
	{L"Beat / rob char", 23, PED_OBJ_TARGET_TYPE_PED},
	{L"Guard spot", 24, PED_OBJ_TARGET_TYPE_COORDS},
	{L"Guard current area", 25, PED_OBJ_TARGET_TYPE_NONE},
	{L"Wait on foot", 26, PED_OBJ_TARGET_TYPE_NONE},
	{L"Wait in car", 27, PED_OBJ_TARGET_TYPE_CAR},
	{L"28 - ?", 28, PED_OBJ_TARGET_TYPE_NONE},
	{L"29 - ?", 29, PED_OBJ_TARGET_TYPE_NONE},
	{L"30 - ?", 30, PED_OBJ_TARGET_TYPE_NONE},
	{L"Medic related", 31, PED_OBJ_TARGET_TYPE_PED}, // not working but medics do have it when healing peds
	{L"32 - ?", 32, PED_OBJ_TARGET_TYPE_NONE},
	{L"33 - ?", 33, PED_OBJ_TARGET_TYPE_NONE},
	{L"34 - ?", 34, PED_OBJ_TARGET_TYPE_NONE},
	{L"Enter car", 35, PED_OBJ_TARGET_TYPE_CAR},
	{L"Leave car", 36, PED_OBJ_TARGET_TYPE_CAR},
	{L"37 - ?", 37, PED_OBJ_TARGET_TYPE_NONE},
	{L"38 - ?", 38, PED_OBJ_TARGET_TYPE_NONE},
	{L"39 - ?", 39, PED_OBJ_TARGET_TYPE_NONE},
	{L"40 - ?", 40, PED_OBJ_TARGET_TYPE_NONE},
	{L"41 - ?", 41, PED_OBJ_TARGET_TYPE_NONE},
	{L"42 - ?", 42, PED_OBJ_TARGET_TYPE_NONE},
	{L"43 - ?", 43, PED_OBJ_TARGET_TYPE_NONE},
	{L"44 - ?", 44, PED_OBJ_TARGET_TYPE_NONE},
	{L"45 - ?", 45, PED_OBJ_TARGET_TYPE_NONE},
	{L"46 - ?", 46, PED_OBJ_TARGET_TYPE_NONE},
	{L"47 - ?", 47, PED_OBJ_TARGET_TYPE_NONE},
	{L"48 - ?", 48, PED_OBJ_TARGET_TYPE_NONE},
	{L"49 - ?", 49, PED_OBJ_TARGET_TYPE_NONE},
	{L"50 - ?", 50, PED_OBJ_TARGET_TYPE_NONE},
	{L"Staying in police car related", 51, PED_OBJ_TARGET_TYPE_CAR},
	{L"52 - ?", 52, PED_OBJ_TARGET_TYPE_NONE},
	{L"53 - ?", 53, PED_OBJ_TARGET_TYPE_NONE},
	{L"54 - ? ", 54, PED_OBJ_TARGET_TYPE_NONE},
	{L"Follow car in car", 55, PED_OBJ_TARGET_TYPE_CAR},
	{L"Follow car on foot", 56, PED_OBJ_TARGET_TYPE_CAR},
//	{L"Fire at object from tank", 57, PED_OBJ_TARGET_TYPE_OBJ}, // objects as target are not supported yet
//	{L"Destroy object", 58, PED_OBJ_TARGET_TYPE_OBJ},
	{L"Destroy car", 59, PED_OBJ_TARGET_TYPE_CAR}
};

struct PedPreset {
	wchar_t* name;
	PED_REMAP2 shape;
	PED_REMAP remap;
	WEAPON_INDEX weapon;
	short health;
	PED_OCUPATION occupation;
	PED_OBJECTIVE objective;
	ushort objTimer;
	PED_THREAT_SEARCH threatSearch;
	PED_THREAT_REACTION threatReaction;
	int aiValues[10];
	// 0 - state (0x278)
	// 1 - state2 (0x27c)
	// 2 - bitstate (0x21c)
	// 3 - bitstate2 (0x238)
	// 4 - reserved
	// 5 - reserved
	// 6 - reserved
	// 7 - reserved
	// 8 - reserved
	// 9 - reserved
	bool playerLeader = false;
	bool inCar = false;
};
const int aiValuesCount = sizeof(PedPreset::aiValues) / sizeof(PedPreset::aiValues[0]);

const PedPreset pedPresets[] = {
	{
		L"Dummy",
		(PED_REMAP2)0,
		(PED_REMAP)27,
		(WEAPON_INDEX)-1,
		50,
		(PED_OCUPATION)3,
		(PED_OBJECTIVE)0,
		9999,
		PED_THREAT_SEARCH_AREA,
		PED_THREAT_REACTION_RUN_AWAY,
		{0, 0, 1, 3, -1, -1, -1, -1, -1, -1}
	},
	{
		L"Following car in car",
		(PED_REMAP2)0,
		(PED_REMAP)37,
		(WEAPON_INDEX)-1,
		50,
		(PED_OCUPATION)18,
		(PED_OBJECTIVE)55,
		9999,
		PED_THREAT_SEARCH_NO_THREATS,
		PED_THREAT_REACTION_NO_REACTION,
		{0, 0, 1, 5, -1, -1, -1, -1, -1, -1},
		false,
		true
	},
	{
		L"Cop", // on foot
		(PED_REMAP2)2,
		(PED_REMAP)0,
		(WEAPON_INDEX)-1,
		50,
		(PED_OCUPATION)29,
		(PED_OBJECTIVE)0,
		9999,
		PED_THREAT_SEARCH_LINE_OF_SIGHT,
		PED_THREAT_REACTION_REACT_AS_EMERGENCY,
		{0, 0, 1, 3, -1, -1, -1, -1, -1, -1}
	},
	{
		L"Mugger",
		(PED_REMAP2)0,
		(PED_REMAP)17,
		(WEAPON_INDEX)-1,
		50,
		(PED_OCUPATION)15,
		(PED_OBJECTIVE)23,
		9999,
		PED_THREAT_SEARCH_AREA,
		PED_THREAT_REACTION_RUN_AWAY,
		{0, 0, 1, 3, -1, -1, -1, -1, -1, -1}
	},
	{
		L"Car thief",
		(PED_REMAP2)0,
		(PED_REMAP)15,
		(WEAPON_INDEX)-1,
		50,
		(PED_OCUPATION)16,
		(PED_OBJECTIVE)0,
		0,
		PED_THREAT_SEARCH_AREA,
		PED_THREAT_REACTION_RUN_AWAY,
		{0, 0, 1, 3, -1, -1, -1, -1, -1, -1}
	},
	{
		L"FBI",
		(PED_REMAP2)1,
		(PED_REMAP)8,
		(WEAPON_INDEX)9,
		250,
		(PED_OCUPATION)26,
		(PED_OBJECTIVE)0,
		9999,
		PED_THREAT_SEARCH_LINE_OF_SIGHT,
		PED_THREAT_REACTION_REACT_AS_EMERGENCY,
		{0, 0, 1, 4, -1, -1, -1, -1, -1, -1}
	},
	{
		L"Bodyguard",
		(PED_REMAP2)1,
		(PED_REMAP)25,
		(WEAPON_INDEX)1,
		50,
		(PED_OCUPATION)35,
		(PED_OBJECTIVE)0,
		9999,
		PED_THREAT_SEARCH_LINE_OF_SIGHT,
		PED_THREAT_REACTION_REACT_AS_NORMAL,
		{0, 0, 1, 4, -1, -1, -1, -1, -1, -1},
		true
	},
	{
		L"Anti-player guard",
		(PED_REMAP2)1,
		(PED_REMAP)8,
		(WEAPON_INDEX)1,
		100,
		(PED_OCUPATION)28,
		(PED_OBJECTIVE)24,
		9999,
		PED_THREAT_SEARCH_AREA_PLAYER_ONLY,
		PED_THREAT_REACTION_REACT_AS_NORMAL,
		{0, 0, 1, 3, -1, -1, -1, -1, -1, -1}
	}
};

#endif