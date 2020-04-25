typedef unsigned char   undefined;

typedef unsigned int    ImageBaseOffset32;
typedef unsigned char    byte;
typedef unsigned int    dword;
typedef long long    longlong;
typedef unsigned char    uchar;
typedef unsigned int    uint;
typedef unsigned int    uint3;
typedef unsigned long    ulong;
typedef unsigned long long    ulonglong;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined8;
typedef unsigned short    ushort;
typedef unsigned short    word;
typedef uchar bbool;

typedef struct Position Position, *PPosition;

typedef struct Position Pos;

struct Position {
    short rotation;
    undefined field_0x2;
    undefined field_0x3;
    struct Position * prev;
    int field_0x8;
    struct Position * next;
    int field_0x10;
    int x; /* Created by retype action */
    int y; /* Created by retype action */
    int z; /* Created by retype action */
    short incFromS20;
    short field_0x22;
    short carColor;
    undefined field_0x26;
    undefined field_0x27;
    int field_0x28;
    byte field_0x2c;
    undefined field_0x2d;
    undefined field_0x2e;
    undefined field_0x2f;
    int field_0x30;
    int field_0x34;
    byte field_0x38;
    byte field_0x39;
    undefined field_0x3a;
    undefined field_0x3b;
};

typedef undefined1 u1;

typedef undefined2 u2;

typedef undefined4 u4;

typedef struct Car Car, *PCar;

typedef enum CAR_LIGHTS_AND_DOORS_BITSTATE {
    BAGAGE_DOORS_OPEN1=2048,
    BAGAGE_DOORS_OPEN2=4096,
    BAGAGE_DOORS_OPEN3=8192,
    BAGAGE_DOORS_OPEN4=16384,
    BAGAGE_DOORS_SET2_OPEN1=268435456,
    BAGAGE_DOORS_SET2_OPEN2=536870912,
    BAGAGE_DOORS_SET2_OPEN3=1073741824,
    BAGAGE_DOORS_SET2_OPEN4=2147483648,
    BRAKES_LIGHT_LEFT=32,
    BRAKES_LIGHT_RIGHT=4194304,
    CABIN_FRONT_LEFT_LIGHT_IS_ON=65536,
    CABIN_REAR_LEFT_LIGHT_IS_ON=262144,
    CABIN_REAR_RIGHT_LIGHT_IS_ON=131072,
    CABIN__FRONT_RIGHT_LIGHT_IS_ON=32768,
    FRONT_GLASS_IS_BROKEN=16,
    FRONT_LEFT_LIGHT_IS_TURNED_ON=64,
    LEFT_FRONT_DOOR_IS_OPEN1=128,
    LEFT_FRONT_DOOR_IS_OPEN2=256,
    LEFT_FRONT_DOOR_IS_OPEN3=512,
    LEFT_FRONT_DOOR_IS_OPEN4=1024,
    LEFT_FRONT_LIGHT_IS_BROKEN=4,
    LEFT_REAR_LIGHT_IS_BROKEN=2,
    RIGHT_FRONT_DOOR_OPEN1=16777216,
    RIGHT_FRONT_DOOR_OPEN2=33554432,
    RIGHT_FRONT_DOOR_OPEN3=67108864,
    RIGHT_FRONT_DOOR_OPEN4=134217728,
    RIGHT_FRONT_LIGHT_IS_BROKEN=8,
    RIGHT_FRONT_LIGHT_IS_ON=8388608,
    RIGHT_REAR_LIGHT_IS_BROKEN=1,
    UNBROKEN_TURNED_OFF=0,
    UNK_100000=1048576,
    UNK_200000=2097152,
    UNK_80000=524288
} CAR_LIGHTS_AND_DOORS_BITSTATE;

typedef struct Ped Ped, *PPed;

typedef struct MaybeCarEngine MaybeCarEngine, *PMaybeCarEngine;

typedef enum CAR_MODEL {
    ALFA=0,
    ALLARD=1,
    AMDB4=2,
    APC=3,
    BANKVAN=4,
    BMW=5,
    BOXCAR=6,
    BOXTRUCK=7,
    BUG=8,
    BUICK=10,
    BUS=11,
    CAR15=15,
    CAR20=20,
    CAR43=43,
    CAR9=9,
    COPCAR=12,
    DART=13,
    EDSEL=14,
    EDSELFBI=84,
    FIAT=16,
    FIRETRUK=17,
    GRAHAM=18,
    GT24640=19,
    GTRUCK=21,
    GUNJEEP=22,
    HOTDOG=23,
    HOTDOG_D1=24,
    HOTDOG_D2=25,
    HOTDOG_D3=26,
    HOTDOG_D4=85,
    ICECREAM=27,
    ISETLIMO=28,
    ISETTA=29,
    JEEP=30,
    JEFFREY=31,
    KRSNABUS=86,
    LIMO=32,
    LIMO2=33,
    MEDICAR=34,
    MERC=35,
    MESSER=36,
    MIURA=37,
    MONSTER=38,
    MORGAN=39,
    MORRIS=40,
    PICKUP=41,
    RTYPE=42,
    SPIDER=44,
    SPRITE=45,
    STINGRAY=46,
    STRATOS=47,
    STRATOSB=48,
    STRIPETB=49,
    STYPE=50,
    STYPECAB=51,
    SWATVAN=52,
    T2000GT=53,
    TANK=54,
    TANKER=55,
    TAXI=56,
    TBIRD=57,
    TOWTRUCK=58,
    TRAIN=59,
    TRAINCAB=60,
    TRAINFB=61,
    TRANCEAM=62,
    TRUKCAB1=63,
    TRUKCAB2=64,
    TRUKCONT=65,
    TRUKTRNS=66,
    TVVAN=67,
    VAN=68,
    VESPA=69,
    VTYPE=70,
    WBTWIN=71,
    WRECK0=72,
    WRECK1=73,
    WRECK2=74,
    WRECK3=75,
    WRECK4=76,
    WRECK5=77,
    WRECK6=78,
    WRECK7=79,
    WRECK8=80,
    WRECK9=81,
    XK120=82,
    ZCX5=83
} CAR_MODEL;

typedef enum CAR_ENGINE_STATE {
    BROKEN_DOESNT_WORK=0,
    ENGINE_OFF=1,
    ENGINE_OFF2=6,
    ENGINE_ON=3,
    LIGHTS_ON_BUT_ENGINE_OFF_NO_FUEL=7,
    REL_TO_CAR_SIREN=4,
    TURNING_OFF=2,
    TURN_ENGINE_OFF=5
} CAR_ENGINE_STATE;

typedef enum TRAFFIC_CAR_TYPE {
    TRAFFIC_4=4,
    TRAFFIC_5=5,
    TRAFFIC_7=7,
    TRAFFIC_9=9,
    TRAFFIC_MISSION_CAR=8,
    TRAFFIC_PROT_RECYCLED_CAR=2,
    TRAFFIC_REGULAR=1,
    TRAFFIC_UNIT_CAR=6,
    TRAFFIC_a=10
} TRAFFIC_CAR_TYPE;

typedef enum CAR_SIREN_STATE {
    CAR_ALARM=8,
    SIREN_OFF=2,
    SIREN_ON=4,
    SIREN_UNK1=1,
    SIREN_UNK_10=16
} CAR_SIREN_STATE;

typedef enum HORN {
    HORN_ON=248
} HORN;

typedef struct WEAPON_PLAYER_LIST WEAPON_PLAYER_LIST, *PWEAPON_PLAYER_LIST;

typedef struct Sprite Sprite, *PSprite;

typedef struct WEAPON_STRUCT WEAPON_STRUCT, *PWEAPON_STRUCT;

typedef enum PED_BIT_STATE {
    PED_BIT_STATE_ARMED=128,
    PED_BIT_STATE_FIRING_FROM_GUN=2048,
    PED_BIT_STATE_FOLLOW_CAR_TO_GET_IN=65536,
    PED_BIT_STATE_GETING_IN_OR_OUT_CAR=134217728,
    PED_BIT_STATE_TOGGLED_ON_WHEN_FIRST_TIME_ATTACK_A_PED=4,
    PED_BIT_STATE_UNARMED=512,
    PED_BIT_STATE_UNK_1_ALWAYS1=1,
    PED_BIT_STATE_UNK_2000=8192,
    PED_BIT_STATE_ZERO_ON_START_GAME_BUT_TOGGLED_ON_FIRST_CAR_ENTER=32768
} PED_BIT_STATE;

typedef enum OCUPATION {
    ANY_ELVIS=49,
    ANY_EMERGENCY_SERVICE_MAN=47,
    ANY_GANG_MEMBER=48,
    ANY_LAW_ENFORCEMENT=46,
    ARMYARMY=27,
    BANK_ROBBER=17,
    CARTHIEF=16,
    CRIMINAL=18,
    CRIMINAL_TYPE1=33,
    CRIMINAL_TYPE2=34,
    DRIVER=5,
    DRIVER2=10,
    DRIVER3=50,
    DRONE=41,
    DUMMY=3,
    ELVIS=22,
    ELVIS_LEADER=44,
    EMPTY=1,
    FBI=26,
    FIREMAN=38,
    GUARD=28,
    GUARD_AGAINST_PLAYER=32,
    MUGGER=15,
    NO_OCCUPATION=51,
    PLAYER=0,
    POLICE=24,
    PSYCHO=14,
    REFUGEES=45,
    ROAD_BLOCK_TANK_MAN=39,
    SPECIAL_GROUP_MEMBER=35,
    STAND_STILL_BLOKE=43,
    SWAT=25,
    TANK_DRIVER=36,
    UNKNOWN_OCUPATION13=19,
    UNKNOWN_OCUPATION17=23,
    UNKNOWN_OCUPATION2=2,
    UNKNOWN_OCUPATION4=4,
    UNKNOWN_OCUPATION8=8,
    UNKNOWN_OCUPATION9=9,
    UNK_REL_TO_POLICE1=29,
    UNK_REL_TO_POLICE2=30,
    UNK_REL_TO_POLICE3=31,
    UNK_REL_TO_POLICE4=37
} OCUPATION;

typedef enum PED_STATE3 {
    PED_STATE3_COP=54,
    PED_STATE3_ENTERING_TO_CAR=35,
    PED_STATE3_GANG_MEMBER=13,
    PED_STATE3_GETTING_OUT_FROM_CAR=36,
    PED_STATE3_UNK1=1,
    PED_STATE3_UNK10=16,
    PED_STATE3_UNK13=19,
    PED_STATE3_UNK14=20,
    PED_STATE3_UNK16=22,
    PED_STATE3_UNK17=23,
    PED_STATE3_UNK18=24,
    PED_STATE3_UNK19=25,
    PED_STATE3_UNK1a=26,
    PED_STATE3_UNK1b=27,
    PED_STATE3_UNK1f=31,
    PED_STATE3_UNK2=2,
    PED_STATE3_UNK20=32,
    PED_STATE3_UNK21=33,
    PED_STATE3_UNK22=34,
    PED_STATE3_UNK25=37,
    PED_STATE3_UNK26=38,
    PED_STATE3_UNK2a=42,
    PED_STATE3_UNK2b=43,
    PED_STATE3_UNK3=3,
    PED_STATE3_UNK33=51,
    PED_STATE3_UNK34=52,
    PED_STATE3_UNK37=55,
    PED_STATE3_UNK38=56,
    PED_STATE3_UNK39=57,
    PED_STATE3_UNK3a=58,
    PED_STATE3_UNK3b=59,
    PED_STATE3_UNK3c=60,
    PED_STATE3_UNK3d_REL_TO_MISSION_ARROWS=61,
    PED_STATE3_UNK6=6,
    PED_STATE3_UNK8=8,
    PED_STATE3_UNKa=10,
    PED_STATE3_UNKc=12,
    PED_STATE3_UNKe=14
} PED_STATE3;

typedef enum PED_STATE {
    PED_STATE_DRIVING_A_CAR=10,
    PED_STATE_ENTERING_INTO_CAR=3,
    PED_STATE_FALL_ON_GROUND=8,
    PED_STATE_GETTING_OUT_FROM_CAR=4,
    PED_STATE_GOING_TO_CAR=2,
    PED_STATE_STAYING=7,
    PED_STATE_WALK=0,
    PED_STATE_WASTED=9
} PED_STATE;

typedef enum PED_STATE2 {
    PED_STATE2_DRIVING=10,
    PED_STATE2_ENTERING_TO_CAR=6,
    PED_STATE2_FOLLOWING_A_CAR=4,
    PED_STATE2_GETTING_OUT_FROM_CAR=7,
    PED_STATE2_STAYING=14,
    PED_STATE2_UNK_16=22,
    PED_STATE2_UNK_f=15,
    PED_STATE2_WALKING=0
} PED_STATE2;

typedef enum WEAPON_INDEX {
    ARMY_GUN_JEEP=22,
    CAR_SMG=9,
    ELECTRO_BATTON=7,
    FIRE_TRUCK_GUN=20,
    FLAMETHROWER=8,
    GRENADE=5,
    MOLOTOV=4,
    PISTOL=0,
    ROCKET=2,
    SHOCKER=3,
    SHOTGUN=6,
    SMG=1,
    TANK_MAIN_GUN=19
} WEAPON_INDEX;

struct WEAPON_PLAYER_LIST {
    undefined field_0x0;
    undefined field_0x1;
    undefined field_0x2;
    undefined field_0x3;
    undefined field_0x4;
    undefined field_0x5;
    undefined field_0x6;
    undefined field_0x7;
    short field_0x8;
    undefined field_0xa;
    undefined field_0xb;
    undefined field_0xc;
    undefined field_0xd;
    undefined field_0xe;
    undefined field_0xf;
    undefined field_0x10;
    undefined field_0x11;
    undefined field_0x12;
    undefined field_0x13;
    undefined field_0x14;
    undefined field_0x15;
    undefined field_0x16;
    undefined field_0x17;
    undefined field_0x18;
    undefined field_0x19;
    undefined field_0x1a;
    undefined field_0x1b;
    undefined field_0x1c;
    undefined field_0x1d;
    undefined field_0x1e;
    undefined field_0x1f;
    undefined field_0x20;
    undefined field_0x21;
    undefined field_0x22;
    undefined field_0x23;
    undefined field_0x24;
    undefined field_0x25;
    undefined field_0x26;
    undefined field_0x27;
    undefined field_0x28;
    undefined field_0x29;
    undefined field_0x2a;
    undefined field_0x2b;
    undefined field_0x2c;
    undefined field_0x2d;
    undefined field_0x2e;
    undefined field_0x2f;
    undefined field_0x30;
    undefined field_0x31;
    undefined field_0x32;
    undefined field_0x33;
    undefined field_0x34;
    undefined field_0x35;
    undefined field_0x36;
    undefined field_0x37;
    undefined field_0x38;
    undefined field_0x39;
    undefined field_0x3a;
    undefined field_0x3b;
    undefined field_0x3c;
    undefined field_0x3d;
    undefined field_0x3e;
    undefined field_0x3f;
    undefined field_0x40;
    undefined field_0x41;
    undefined field_0x42;
    undefined field_0x43;
    undefined field_0x44;
    undefined field_0x45;
    undefined field_0x46;
    undefined field_0x47;
    undefined field_0x48;
    undefined field_0x49;
    undefined field_0x4a;
    undefined field_0x4b;
    undefined field_0x4c;
    undefined field_0x4d;
    undefined field_0x4e;
    undefined field_0x4f;
    uint bitMask;
    undefined field_0x54[1732];
    struct WEAPON_STRUCT * weapons[36]; /* Created by retype action */
    undefined field_0x77e;
    undefined field_0x77f;
    undefined field_0x780;
    undefined field_0x781;
    undefined field_0x782;
    undefined field_0x783;
    undefined field_0x784;
    undefined field_0x785;
    undefined field_0x786;
    undefined field_0x787;
    short count; /* Created by retype action */
};

struct Sprite {
    uint id;
    int field_0x4;
    uint state1;
    int field_0xc;
    uint relToId;
    int field_0x14;
    uint field_0x18;
    int field_0x1c;
    undefined field_0x20;
    undefined field_0x21;
    undefined field_0x22;
    undefined field_0x23;
    ushort maybe_id; /* maybe color */
    undefined field_0x26;
    undefined field_0x27;
    undefined field_0x28;
    undefined field_0x29;
    undefined field_0x2a;
    undefined field_0x2b;
    undefined field_0x2c;
    undefined field_0x2d;
    undefined field_0x2e;
    undefined field_0x2f;
    undefined field_0x30;
    undefined field_0x31;
    undefined field_0x32;
    undefined field_0x33;
    undefined field_0x34;
    undefined field_0x35;
    undefined field_0x36;
    undefined field_0x37;
    int field_0x38;
    int field_0x3c;
    short spriteRotation;
    short field_0x42;
    u1 field_0x44;
    undefined field_0x45;
    short field_0x46;
    undefined field_0x48;
    undefined field_0x49;
    short unknownIdleTimer;
    undefined field_0x4c;
    undefined field_0x4d;
    undefined field_0x4e;
    undefined field_0x4f;
    undefined field_0x50;
    undefined field_0x51;
    undefined field_0x52;
    undefined field_0x53;
    undefined field_0x54;
    undefined field_0x55;
    undefined field_0x56;
    undefined field_0x57;
    uint bit1;
    undefined field_0x5c;
    undefined field_0x5d;
    undefined field_0x5e;
    undefined field_0x5f;
    undefined4 field_0x60;
    undefined4 field_0x64;
    byte field_0x68;
    undefined field_0x69;
    undefined field_0x6a;
    undefined field_0x6b;
    int field_0x6c;
    undefined field_0x70;
    undefined field_0x71;
    undefined field_0x72;
    undefined field_0x73;
    undefined field_0x74;
    undefined field_0x75;
    undefined field_0x76;
    undefined field_0x77;
    struct Sprite * MaybeNext;
    struct Ped * ped;
    struct Position * actualPosition;
    undefined field_0x84;
    undefined field_0x85;
    undefined field_0x86;
    undefined field_0x87;
    undefined field_0x88;
    undefined field_0x89;
    undefined field_0x8a;
    undefined field_0x8b;
    undefined field_0x8c;
    undefined field_0x8d;
    undefined field_0x8e;
    undefined field_0x8f;
    int field_0x90;
    void * field_0x94;
    undefined field_0x98;
    undefined field_0x99;
    undefined field_0x9a;
    undefined field_0x9b;
    undefined field_0x9c;
    undefined field_0x9d;
    undefined field_0x9e;
    undefined field_0x9f;
    undefined field_0xa0;
    undefined field_0xa1;
    undefined field_0xa2;
    undefined field_0xa3;
    undefined field_0xa4;
    undefined field_0xa5;
    undefined field_0xa6;
    undefined field_0xa7;
    undefined field_0xa8;
    undefined field_0xa9;
    undefined field_0xaa;
    undefined field_0xab;
    undefined field_0xac;
    undefined field_0xad;
    undefined field_0xae;
    undefined field_0xaf;
    int field_0xb0;
};

struct Car {
    undefined field_0x0;
    undefined field_0x1;
    undefined field_0x2;
    undefined field_0x3;
    undefined field_0x4;
    undefined field_0x5;
    undefined field_0x6;
    undefined field_0x7;
    enum CAR_LIGHTS_AND_DOORS_BITSTATE carLights;
    undefined field_0xc;
    undefined field_0xd;
    undefined field_0xe;
    undefined field_0xf;
    undefined field_0x10;
    undefined field_0x11;
    undefined field_0x12;
    undefined field_0x13;
    undefined field_0x14;
    undefined field_0x15;
    undefined field_0x16;
    undefined field_0x17;
    undefined field_0x18;
    undefined field_0x19;
    undefined field_0x1a;
    undefined field_0x1b;
    undefined field_0x1c;
    undefined field_0x1d;
    undefined field_0x1e;
    undefined field_0x1f;
    undefined field_0x20;
    undefined field_0x21;
    undefined field_0x22;
    undefined field_0x23;
    uint bitMask2;
    undefined field_0x28;
    undefined field_0x29;
    undefined field_0x2a;
    undefined field_0x2b;
    undefined field_0x2c;
    undefined field_0x2d;
    undefined field_0x2e;
    undefined field_0x2f;
    undefined field_0x30;
    undefined field_0x31;
    undefined field_0x32;
    undefined field_0x33;
    undefined field_0x34;
    undefined field_0x35;
    undefined field_0x36;
    undefined field_0x37;
    undefined field_0x38;
    undefined field_0x39;
    undefined field_0x3a;
    undefined field_0x3b;
    int field_0x3c;
    undefined field_0x40;
    undefined field_0x41;
    undefined field_0x42;
    undefined field_0x43;
    undefined field_0x44;
    undefined field_0x45;
    undefined field_0x46;
    undefined field_0x47;
    undefined field_0x48;
    undefined field_0x49;
    undefined field_0x4a;
    undefined field_0x4b;
    int field_0x4c;
    struct Position * position;
    struct Ped * driver; /* Created by retype action */
    struct MaybeCarEngine * maybeEngine;
    void * field_0x5c;
    void * field_0x60;
    void * field_0x64;
    undefined field_0x68;
    undefined field_0x69;
    undefined field_0x6a;
    undefined field_0x6b;
    uint id;
    int driverPedId; /* Created by retype action */
    short carDamage;
    short field_0x76;
    byte bitMask;
    undefined field_0x79;
    undefined field_0x7a;
    undefined field_0x7b;
    uint field_0x7c;
    undefined field_0x80;
    undefined field_0x81;
    undefined field_0x82;
    undefined field_0x83;
    enum CAR_MODEL carModel;
    uint mask;
    undefined field_0x8c;
    byte field_0x8d;
    undefined field_0x8e;
    undefined field_0x8f;
    undefined field_0x90;
    undefined field_0x91;
    undefined field_0x92;
    undefined field_0x93;
    undefined field_0x94;
    undefined field_0x95;
    undefined field_0x96;
    undefined field_0x97;
    byte locksDoor; /* 1 - locked, 2 - unlocked */
    undefined field_0x99;
    undefined field_0x9a;
    undefined field_0x9b;
    enum CAR_ENGINE_STATE engineState;
    enum TRAFFIC_CAR_TYPE trafficCarType;
    enum CAR_SIREN_STATE sirenState;
    undefined field_0xa5;
    undefined field_0xa6;
    enum HORN horn;
};

struct WEAPON_STRUCT {
    short ammo;
    byte timeToReload;
    undefined field_0x3;
    int field_0x4;
    undefined field_0x8;
    undefined field_0x9;
    undefined field_0xa;
    undefined field_0xb;
    undefined field_0xc;
    undefined field_0xd;
    undefined field_0xe;
    undefined field_0xf;
    undefined field_0x10;
    undefined field_0x11;
    undefined field_0x12;
    undefined field_0x13;
    int carId; /* Created by retype action */
    struct WEAPON_STRUCT * nextWeapon;
    enum WEAPON_INDEX id;
    undefined field_0x20;
    undefined field_0x21;
    undefined field_0x22;
    undefined field_0x23;
    struct Ped * ped;
    undefined field_0x28;
    undefined field_0x29;
    undefined field_0x2a;
    undefined field_0x2b;
    byte field_0x2c;
    undefined field_0x2d;
    undefined field_0x2e;
    undefined field_0x2f;
};

struct MaybeCarEngine {
    undefined field_0x0;
    undefined field_0x1;
    undefined field_0x2;
    undefined field_0x3;
    undefined field_0x4;
    undefined field_0x5;
    undefined field_0x6;
    undefined field_0x7;
    undefined field_0x8;
    undefined field_0x9;
    undefined field_0xa;
    undefined field_0xb;
    struct MaybeCarEngine * next;
    int field_0x10[2][4];
    undefined field_0x30;
    undefined field_0x31;
    undefined field_0x32;
    undefined field_0x33;
    undefined field_0x34;
    undefined field_0x35;
    undefined field_0x36;
    undefined field_0x37;
    undefined field_0x38;
    undefined field_0x39;
    undefined field_0x3a;
    undefined field_0x3b;
    undefined field_0x3c;
    undefined field_0x3d;
    undefined field_0x3e;
    undefined field_0x3f;
    undefined field_0x40;
    undefined field_0x41;
    undefined field_0x42;
    undefined field_0x43;
    undefined field_0x44;
    undefined field_0x45;
    undefined field_0x46;
    undefined field_0x47;
    undefined field_0x48;
    undefined field_0x49;
    undefined field_0x4a;
    undefined field_0x4b;
    undefined field_0x4c;
    undefined field_0x4d;
    undefined field_0x4e;
    undefined field_0x4f;
    undefined field_0x50;
    undefined field_0x51;
    undefined field_0x52;
    undefined field_0x53;
    undefined field_0x54;
    undefined field_0x55;
    undefined field_0x56;
    undefined field_0x57;
    undefined field_0x58;
    undefined field_0x59;
    undefined field_0x5a;
    undefined field_0x5b;
    void * prev;
    undefined field_0x60;
    undefined field_0x61;
    undefined field_0x62;
    undefined field_0x63;
    undefined field_0x64;
    undefined field_0x65;
    undefined field_0x66;
    undefined field_0x67;
    undefined field_0x68;
    undefined field_0x69;
    undefined field_0x6a;
    undefined field_0x6b;
    undefined field_0x6c;
    undefined field_0x6d;
    undefined field_0x6e;
    undefined field_0x6f;
    undefined field_0x70;
    undefined field_0x71;
    undefined field_0x72;
    undefined field_0x73;
    undefined field_0x74;
    undefined field_0x75;
    undefined field_0x76;
    undefined field_0x77;
    undefined field_0x78;
    undefined field_0x79;
    undefined field_0x7a;
    undefined field_0x7b;
    undefined field_0x7c;
    undefined field_0x7d;
    undefined field_0x7e;
    undefined field_0x7f;
    undefined field_0x80;
    undefined field_0x81;
    undefined field_0x82;
    undefined field_0x83;
    undefined field_0x84;
    undefined field_0x85;
    undefined field_0x86;
    undefined field_0x87;
    undefined field_0x88;
    undefined field_0x89;
    undefined field_0x8a;
    undefined field_0x8b;
    undefined field_0x8c;
    undefined field_0x8d;
    undefined field_0x8e;
    undefined field_0x8f;
    undefined field_0x90;
    undefined field_0x91;
    byte field_0x92;
    undefined field_0x93;
    undefined field_0x94;
    undefined field_0x95;
    undefined field_0x96;
    undefined field_0x97;
    undefined field_0x98;
    undefined field_0x99;
    undefined field_0x9a;
    undefined field_0x9b;
    undefined field_0x9c;
    undefined field_0x9d;
    undefined field_0x9e;
    undefined field_0x9f;
    undefined field_0xa0;
    undefined field_0xa1;
    undefined field_0xa2;
    undefined field_0xa3;
    undefined field_0xa4;
    undefined field_0xa5;
    undefined field_0xa6;
    undefined field_0xa7;
    undefined field_0xa8;
    undefined field_0xa9;
    undefined field_0xaa;
    undefined field_0xab;
    undefined field_0xac;
    undefined field_0xad;
    undefined field_0xae;
    undefined field_0xaf;
};

struct Ped {
    byte field_0x0;
    byte field_0x1;
    undefined field_0x2;
    undefined field_0x3;
    struct Ped * unknownPedsArr;
    struct Ped * field_0x8;
    undefined field_0xc;
    undefined field_0xd;
    undefined field_0xe;
    undefined field_0xf;
    undefined field_0x10;
    undefined field_0x11;
    undefined field_0x12;
    undefined field_0x13;
    undefined field_0x14;
    undefined field_0x15;
    undefined field_0x16;
    undefined field_0x17;
    undefined field_0x18;
    undefined field_0x19;
    undefined field_0x1a;
    undefined field_0x1b;
    undefined field_0x1c;
    undefined field_0x1d;
    undefined field_0x1e;
    undefined field_0x1f;
    undefined field_0x20;
    undefined field_0x21;
    undefined field_0x22;
    undefined field_0x23;
    undefined field_0x24;
    undefined field_0x25;
    undefined field_0x26;
    undefined field_0x27;
    undefined field_0x28;
    undefined field_0x29;
    undefined field_0x2a;
    undefined field_0x2b;
    struct Ped * elvisSomething;
    undefined field_0x30;
    byte lenOfForPedsArray;
    undefined field_0x32;
    undefined field_0x33;
    undefined field_0x34;
    undefined field_0x35;
    undefined field_0x36;
    undefined field_0x37;
    undefined field_0x38;
    undefined field_0x39;
    undefined field_0x3a;
    undefined field_0x3b;
    undefined field_0x3c;
    undefined field_0x3d;
    undefined field_0x3e;
    undefined field_0x3f;
    undefined field_0x40;
    undefined field_0x41;
    undefined field_0x42;
    undefined field_0x43;
    undefined field_0x44;
    undefined field_0x45;
    undefined field_0x46;
    undefined field_0x47;
    undefined field_0x48;
    undefined field_0x49;
    undefined field_0x4a;
    undefined field_0x4b;
    undefined field_0x4c;
    undefined field_0x4d;
    undefined field_0x4e;
    undefined field_0x4f;
    undefined field_0x50;
    undefined field_0x51;
    undefined field_0x52;
    undefined field_0x53;
    undefined field_0x54;
    undefined field_0x55;
    undefined field_0x56;
    undefined field_0x57;
    undefined field_0x58;
    undefined field_0x59;
    undefined field_0x5a;
    undefined field_0x5b;
    undefined field_0x5c;
    undefined field_0x5d;
    undefined field_0x5e;
    undefined field_0x5f;
    undefined field_0x60;
    undefined field_0x61;
    undefined field_0x62;
    undefined field_0x63;
    undefined field_0x64;
    undefined field_0x65;
    undefined field_0x66;
    undefined field_0x67;
    undefined field_0x68;
    undefined field_0x69;
    undefined field_0x6a;
    undefined field_0x6b;
    undefined field_0x6c;
    undefined field_0x6d;
    undefined field_0x6e;
    undefined field_0x6f;
    undefined field_0x70;
    undefined field_0x71;
    undefined field_0x72;
    undefined field_0x73;
    undefined field_0x74;
    undefined field_0x75;
    undefined field_0x76;
    undefined field_0x77;
    undefined field_0x78;
    undefined field_0x79;
    undefined field_0x7a;
    undefined field_0x7b;
    undefined field_0x7c;
    undefined field_0x7d;
    undefined field_0x7e;
    undefined field_0x7f;
    undefined field_0x80;
    undefined field_0x81;
    undefined field_0x82;
    undefined field_0x83;
    undefined field_0x84;
    undefined field_0x85;
    undefined field_0x86;
    undefined field_0x87;
    undefined field_0x88;
    undefined field_0x89;
    undefined field_0x8a;
    undefined field_0x8b;
    undefined field_0x8c;
    undefined field_0x8d;
    undefined field_0x8e;
    undefined field_0x8f;
    undefined field_0x90;
    undefined field_0x91;
    undefined field_0x92;
    undefined field_0x93;
    undefined field_0x94;
    undefined field_0x95;
    undefined field_0x96;
    undefined field_0x97;
    undefined field_0x98;
    undefined field_0x99;
    undefined field_0x9a;
    undefined field_0x9b;
    undefined field_0x9c;
    undefined field_0x9d;
    undefined field_0x9e;
    undefined field_0x9f;
    undefined field_0xa0;
    undefined field_0xa1;
    undefined field_0xa2;
    undefined field_0xa3;
    undefined field_0xa4;
    undefined field_0xa5;
    undefined field_0xa6;
    undefined field_0xa7;
    undefined field_0xa8;
    undefined field_0xa9;
    undefined field_0xaa;
    undefined field_0xab;
    undefined field_0xac;
    undefined field_0xad;
    undefined field_0xae;
    undefined field_0xaf;
    undefined field_0xb0;
    undefined field_0xb1;
    undefined field_0xb2;
    undefined field_0xb3;
    undefined field_0xb4;
    undefined field_0xb5;
    undefined field_0xb6;
    undefined field_0xb7;
    undefined field_0xb8;
    undefined field_0xb9;
    undefined field_0xba;
    undefined field_0xbb;
    undefined field_0xbc;
    undefined field_0xbd;
    undefined field_0xbe;
    undefined field_0xbf;
    undefined field_0xc0;
    undefined field_0xc1;
    undefined field_0xc2;
    undefined field_0xc3;
    undefined field_0xc4;
    undefined field_0xc5;
    undefined field_0xc6;
    undefined field_0xc7;
    undefined field_0xc8;
    undefined field_0xc9;
    undefined field_0xca;
    undefined field_0xcb;
    undefined field_0xcc;
    undefined field_0xcd;
    undefined field_0xce;
    undefined field_0xcf;
    undefined field_0xd0;
    undefined field_0xd1;
    undefined field_0xd2;
    undefined field_0xd3;
    undefined field_0xd4;
    undefined field_0xd5;
    undefined field_0xd6;
    undefined field_0xd7;
    undefined field_0xd8;
    undefined field_0xd9;
    undefined field_0xda;
    undefined field_0xdb;
    undefined field_0xdc;
    undefined field_0xdd;
    undefined field_0xde;
    undefined field_0xdf;
    undefined field_0xe0;
    undefined field_0xe1;
    undefined field_0xe2;
    undefined field_0xe3;
    undefined field_0xe4;
    undefined field_0xe5;
    undefined field_0xe6;
    undefined field_0xe7;
    undefined field_0xe8;
    undefined field_0xe9;
    undefined field_0xea;
    undefined field_0xeb;
    undefined field_0xec;
    undefined field_0xed;
    undefined field_0xee;
    undefined field_0xef;
    undefined field_0xf0;
    undefined field_0xf1;
    undefined field_0xf2;
    undefined field_0xf3;
    undefined field_0xf4;
    undefined field_0xf5;
    undefined field_0xf6;
    undefined field_0xf7;
    undefined field_0xf8;
    undefined field_0xf9;
    undefined field_0xfa;
    undefined field_0xfb;
    undefined field_0xfc;
    undefined field_0xfd;
    undefined field_0xfe;
    undefined field_0xff;
    undefined field_0x100;
    undefined field_0x101;
    undefined field_0x102;
    undefined field_0x103;
    undefined field_0x104;
    undefined field_0x105;
    undefined field_0x106;
    undefined field_0x107;
    undefined field_0x108;
    undefined field_0x109;
    undefined field_0x10a;
    undefined field_0x10b;
    undefined field_0x10c;
    undefined field_0x10d;
    undefined field_0x10e;
    undefined field_0x10f;
    undefined field_0x110;
    undefined field_0x111;
    undefined field_0x112;
    undefined field_0x113;
    undefined field_0x114;
    undefined field_0x115;
    undefined field_0x116;
    undefined field_0x117;
    undefined field_0x118;
    undefined field_0x119;
    undefined field_0x11a;
    undefined field_0x11b;
    undefined field_0x11c;
    undefined field_0x11d;
    undefined field_0x11e;
    undefined field_0x11f;
    undefined field_0x120;
    undefined field_0x121;
    undefined field_0x122;
    undefined field_0x123;
    undefined field_0x124;
    undefined field_0x125;
    undefined field_0x126;
    undefined field_0x127;
    undefined field_0x128;
    undefined field_0x129;
    undefined field_0x12a;
    undefined field_0x12b;
    short field_0x12c;
    short field_0x12e;
    short field_0x130;
    undefined field_0x132;
    undefined field_0x133;
    short field_0x134;
    undefined field_0x136;
    undefined field_0x137;
    int field_0x138;
    int field_0x13c;
    struct Car * refCar;
    int field_0x144;
    int field_0x148;
    int field_0x14c;
    int field_0x150;
    struct Car * field_0x154;
    int field_0x158;
    struct WEAPON_PLAYER_LIST * playerWeapons;
    struct Ped * nextPed;
    struct Ped * ElvisOrTarget; /* Created by retype action */
    struct Sprite * pedSprite;
    struct Car * currentCar;
    struct WEAPON_STRUCT * selectedWeapon;
    void * ptrToWeapon;
    int field_0x178;
    int field_0x17c;
    int field_0x180;
    int field_0x184;
    undefined field_0x188;
    undefined field_0x189;
    undefined field_0x18a;
    undefined field_0x18b;
    int field_0x18c;
    int field_0x190;
    int field_0x194;
    undefined field_0x198;
    undefined field_0x199;
    undefined field_0x19a;
    undefined field_0x19b;
    undefined field_0x19c;
    undefined field_0x19d;
    undefined field_0x19e;
    undefined field_0x19f;
    int field_0x1a0;
    int field_0x1a4;
    struct Ped * elvisLeader;
    int x;
    int y;
    int z;
    struct Ped * field_0x1b8;
    struct Ped * field_0x1bc;
    struct Ped * field_0x1c0;
    struct Ped * field_0x1c4;
    struct Ped * field_0x1c8;
    struct Ped * field_0x1cc;
    void * field_0x1d0;
    void * field_0x1d4;
    void * field_0x1d8;
    int field_0x1dc;
    int field_0x1e0;
    int field_0x1e4;
    undefined field_0x1e8;
    undefined field_0x1e9;
    undefined field_0x1ea;
    undefined field_0x1eb;
    undefined field_0x1ec;
    undefined field_0x1ed;
    undefined field_0x1ee;
    undefined field_0x1ef;
    int field_0x1f0;
    int field_0x1f4;
    undefined field_0x1f8;
    undefined field_0x1f9;
    undefined field_0x1fa;
    undefined field_0x1fb;
    undefined field_0x1fc;
    undefined field_0x1fd;
    undefined field_0x1fe;
    undefined field_0x1ff;
    int id;
    int somePedId;
    ushort Invulnerability; /* 9999 = infinity */
    short copValue; /* 600 = 1 star, 1600 = 2 */
    short field_0x20c;
    short field_0x20e;
    short field_0x210;
    undefined field_0x212;
    undefined field_0x213;
    undefined field_0x214;
    undefined field_0x215;
    short health;
    short incrTo9999;
    short field_0x21a;
    enum PED_BIT_STATE bitStateInvisOnFireEtc; /* invisibilty, electrofingers on fire and more  */
    undefined field_0x220;
    undefined field_0x221;
    undefined field_0x222;
    undefined field_0x223;
    byte field_0x224;
    byte field_0x225;
    byte field_0x226;
    byte field_0x227;
    byte field_0x228;
    byte field_0x229;
    undefined field_0x22a;
    undefined field_0x22b;
    int field_0x22c;
    int field_0x230;
    byte eq99;
    undefined field_0x235;
    undefined field_0x236;
    undefined field_0x237;
    uint bitState2;
    byte field_0x23c;
    undefined field_0x23d;
    undefined field_0x23e;
    undefined field_0x23f;
    enum OCUPATION occupation;
    byte field_0x244;
    undefined field_0x245;
    undefined field_0x246;
    undefined field_0x247;
    int field_0x248;
    byte field_0x24c;
    undefined field_0x24d;
    undefined field_0x24e;
    undefined field_0x24f;
    int field_0x250;
    undefined field_0x254;
    undefined field_0x255;
    undefined field_0x256;
    undefined field_0x257;
    enum PED_STATE3 state3;
    int field_0x25c;
    byte field_0x260;
    byte field_0x261;
    byte field_0x262;
    byte field_0x263;
    byte field_0x264;
    byte field_0x265;
    undefined field_0x266;
    byte field_0x267;
    undefined field_0x268;
    undefined field_0x269;
    byte field_0x26a;
    undefined field_0x26b;
    int field_0x26c;
    int field_0x270;
    enum CAR_MODEL gangCarModel;
    enum PED_STATE state;
    enum PED_STATE2 state2;
    enum PED_STATE state1_2; /* 0 on start, 3 when getting to a car */
    enum PED_STATE2 state2_2;
    int field_0x288;
    int field_0x28c;
    int relToMultiplayer;
};

typedef enum CAR_UNK_TYPE {
    FIRE_TRACK_CARS=5,
    MISSION_CARS=8,
    UNIT_CARS=6,
    UNK_CARS_1=1,
    UNK_CARS_2=2,
    UNK_CARS_3=3,
    UNK_CARS_4=4,
    UNK_CARS_7=7,
    UNK_CARS_9=9,
    UNK_CARS_a=10
} CAR_UNK_TYPE;

typedef enum CAR_UPGRADE {
    UPGRADE_10k_OIL=16,
    UPGRADE_25k_GUN=18,
    UPGRADE_50k=17,
    UPGRADE_5k_PAINT_SUICIDE=15,
    UPGRADE_FREE=0
} CAR_UPGRADE;

typedef struct CarManager CarManager, *PCarManager;

struct CarManager {
    undefined field_0x0;
    undefined field_0x1;
    undefined field_0x2;
    undefined field_0x3;
    undefined4 field_0x4;
    byte field_0x8;
    byte field_0x9;
    byte field_0xa;
    byte field_0xb;
    undefined4 field_0xc;
    short field_0x10;
    undefined field_0x12;
    undefined field_0x13;
    undefined4 field_0x14;
    undefined field_0x18;
    undefined field_0x19;
    byte field_0x1a;
    undefined field_0x1b;
    undefined4 field_0x1c;
    undefined4 field_0x20;
    undefined4 field_0x24;
    undefined4 recycledCars;
    undefined4 unkCarType4Counter;
    undefined4 unkCarType5Counter;
    undefined4 unitCars;
    undefined4 unkCarType7Counter;
    undefined4 missionCars;
    undefined4 protRecycledCars;
    undefined4 unkCarType9Counter;
    int unkCarTypeACounter;
    undefined4 field_0x4c;
    undefined4 field_0x50;
    byte field_0x54;
    byte inc;
    undefined field_0x56;
    undefined field_0x57;
    undefined4 field_0x58;
    byte field_0x5c;
    undefined field_0x5d;
    undefined field_0x5e;
    undefined field_0x5f;
    undefined4 field_0x60;
    undefined4 field_0x64;
    byte field_0x68;
    bbool do_free_shoping;
};

typedef struct MaybeCarEngineHolder MaybeCarEngineHolder, *PMaybeCarEngineHolder;

struct MaybeCarEngineHolder {
    struct MaybeCarEngine * firstElement;
    struct MaybeCarEngine * arr306;
};

typedef enum CHEATS {
    ARSESTAR=293617,
    BUCKFAST=296845,
    COCKTART=293033,
    CUTIE1=211561,
    DANISGOD=281903,
    DAVEMOON=287647,
    EATSOUP=288123,
    FISHFLAP=285423,
    FLAMEON=286402,
    GAOLLOT=282904,
    GINGERR=286536,
    GODOFGTA=300913,
    GOREFEST=296159,
    GOURANGA=299874,
    HUNSRUS=307852,
    IAMDAVEJ=288557,
    JAILBAIT=282094,
    LASVEGAS=289768,
    MADEMAN=267793,
    MUCHCASH=301620,
    NEKKID=225122,
    RSJABBER=293115,
    SCHURULZ=316868,
    SECRET_CHEAT=302198,
    SEGARULZ=305547,
    TUMYFROG=329533,
    UKGAMER=285484,
    VOLTFEST=318071
} CHEATS;

typedef enum DEATH_REASON {
    FRIED=2,
    NICKED=3,
    SHOCKED=4,
    WASTED=1,
    WASTED0=0
} DEATH_REASON;

typedef enum GAME_STATUS {
    GAME_PAUSED=2,
    GAME_RUN=1
} GAME_STATUS;

typedef enum GTA_ERROR_CODE {
    GTA_ERROR_CODE_NO_LEVELSTART_DECLARATION_IN_SCRIPTFILE=65,
    GTA_ERROR_CODE_OUT_OF_MEMORY=32,
    GTA_ERROR_CODE_PLAYER_PED_TWICE=66,
    GTA_ERROR_CODE_SCR_NAME_DOESNT_MATCH=21,
    GTA_ERROR_CODE_TOO_MANY_DOORS=2020,
    GTA_ERROR_CODE_UNABLE_TO_CLOSE_REGISTRY_KEY=42,
    GTA_ERROR_CODE_UNABLE_TO_SET_REGISTRY_VALUE=46,
    GTA_ERROR_CODE_UNK1=1
} GTA_ERROR_CODE;

typedef enum KEY_NAME {
    KEY_INCR_COP_LEVEL=5,
    KEY_INCR_RESPECT_GANG1=2,
    KEY_INCR_RESPECT_GANG2=3,
    KEY_INCR_RESPECT_GANG3=4,
    KEY_PAUSE=64,
    KEY_QUIT=1,
    KEY_RESET_COP_LEVEL=6,
    KEY_SHOW_PED_INFO=46,
    KEY_UNK_3b=59,
    KEY_UNK_3c=60,
    KEY_UNK_DEBUG_47=71,
    KEY_UNK_DEBUG_48=72,
    KEY_UNK_DEBUG_49=73,
    KEY_UNK_DEBUG_4a=74,
    KEY_UNK_DEBUG_4b=75,
    KEY_UNK_DEBUG_4c=76,
    KEY_UNK_DEBUG_4d=77,
    KEY_UNK_DEBUG_4e=78,
    KEY_UNK_DEBUG_4f=79,
    KEY_UNK_DEBUG_50=80,
    KEY_UNK_DEBUG_52=82,
    KEY_UNK_DEBUG_53=83,
    KEY_UNK_DEBUG_57=87,
    KEY_UNK_DEBUG_58=88,
    KEY_UNK_DEBUG_b5=181,
    KEY_UNK_DEBUG_c7=199,
    KEY_UNK_DEBUG_c9=201,
    KEY_UNK_DEBUG_d1=209,
    KEY_VOLUME_MINUS=61,
    KEY_VOLUME_PLUS=62
} KEY_NAME;

typedef enum KEYBOARD_STATE {
    KEY_STATE_ALT=1024,
    KEY_STATE_ATTACK=16,
    KEY_STATE_ENTER=32,
    KEY_STATE_JUMP=64,
    KEY_STATE_MOVE_BACKWARD=2,
    KEY_STATE_MOVE_FORWARD=1,
    KEY_STATE_ROTATE_LEFT=4,
    KEY_STATE_ROTATE_RIGHT=8,
    KEY_STATE_TAB=512
} KEYBOARD_STATE;

typedef enum PLAYER_MOVEMENT_STATE {
    BACKWARD=2,
    CTRL_ATTACK=16,
    CTRL_ENTER_EXIT=32,
    CTRL_FORWARD=1,
    CTRL_JUMP_HANDBRAKE=64,
    CTRL_NOT_MOVING=0,
    CTRL_RIGHT=8,
    CTRL_SPECIAL_1=512,
    CTRL_SPECIAL_2=1024,
    CTRL_WEAPON_NEXT=256,
    CTRL_WEAPON_PREV=128,
    LEFT=4
} PLAYER_MOVEMENT_STATE;

typedef enum SAVE_SLOT_UNCLEAR_UI_OR_SCRIPTS_VALUE_ID { /* Maybe used in scrtipts? Or UI related */
    MONEY_MULTIPLIER=116,
    PLAYER_LIVES=115,
    PLAYER_MONEY=158
} SAVE_SLOT_UNCLEAR_UI_OR_SCRIPTS_VALUE_ID;

typedef enum VOCAL {
    VOCAL_ACCURACY_BONUS_=9,
    VOCAL_AND_REMEMBER__RESPECT_IS_EVERYTHING_=24,
    VOCAL_BACK_TO_FRONT_BONUS_=10,
    VOCAL_BUSTED_=17,
    VOCAL_CAR_JACKA_=7,
    VOCAL_CHOCTASTIC=47,
    VOCAL_COP_KILLA_=6,
    VOCAL_CRISPY_CRITTER=52,
    VOCAL_DAMNATION__NO_DONATION__NO_SALVATION_=62,
    VOCAL_DAMN_SUNDAY_DRIVERS_=58,
    VOCAL_DEATH_TO_ICE_CREAM_VANS_=51,
    VOCAL_EAT_LEADEN_DEATH__PUNK_=54,
    VOCAL_ELVIS_HAS_LEFT_THE_BUILDING_=8,
    VOCAL_EXPEDITIOUS_EXECUTION=4,
    VOCAL_FINAL_LAP=35,
    VOCAL_FRENZY_FAILED_=18,
    VOCAL_FRENZY_PASSED_=19,
    VOCAL_FRYING_TONIGHT_=20,
    VOCAL_GAME_OVER=21,
    VOCAL_GENOCIDE=5,
    VOCAL_GRAND_THEFT_AUTO_=2,
    VOCAL_GREAT__120_PEOPLE_DOWN__MULTIPLIER_X5=40,
    VOCAL_HALLELUJAH__ANOTHER_SOUL_SAVED_=61,
    VOCAL_HEY__30_PEOPLE_DOWN__MULTIPLIER_X2=37,
    VOCAL_INSANE_STUNT_BONUS_=1,
    VOCAL_JOB_COMPLETE=22,
    VOCAL_JOB_FAILED=23,
    VOCAL_KILL_FRENZY_=12,
    VOCAL_LAUGH__changes_each_time_you_play_it_=32,
    VOCAL_MEDICAL_EMERGENCY_=11,
    VOCAL_MMM____SOMETHIN_S_COOKIN_=26,
    VOCAL_NICE__90_PEOPLE_DOWN__MULTIPLIER_X4=39,
    VOCAL_Nice_work=46,
    VOCAL_OOH__60_PEOPLE_DOWN__MULTIPLIER_X3=38,
    VOCAL_OOH____DID_THAT_HURT_=50,
    VOCAL_OUTSTANDING__150_PEOPLE_DOWN__MULTIPLIER_X6=41,
    VOCAL_Oh__sorry_about_that____Did_that_hurt_=45,
    VOCAL_RACE_ON=36,
    VOCAL_RACE_OVER=33,
    VOCAL_RASPBERRY_RIPPLE=48,
    VOCAL_SECOND_LAP=34,
    VOCAL_SHOCKING_=25,
    VOCAL_SORRY_ABOUT_THAT_=56,
    VOCAL_SUCK_IT_AND_SEE_=59,
    VOCAL_TASTE_MY_WRATH__ICE_CREAM_BOY_=60,
    VOCAL_THAT_S_GOTTA_HURT_=55,
    VOCAL_TIMES_UP__PAL_=27,
    VOCAL_TIME_OUT=42,
    VOCAL_TIME_S_UP__PAL___duplicate_=44,
    VOCAL_TOASTED_=28,
    VOCAL_WASTED=29,
    VOCAL_WIPEOUT=3,
    VOCAL_XIN_LOI__MY_MAN_=57,
    VOCAL_YOUR_TIME_IS_EXTENDED=43,
    VOCAL_YOU_RE_TOAST__BUDDY_=53,
    VOCAL_YOU_SHOT_YOUR_LOAD=49,
    VOCAL_bombarmed=30,
    VOCAL_laugh6=31
} VOCAL;

typedef struct Ambulance Ambulance, *PAmbulance;

typedef struct AmbulanceSub AmbulanceSub, *PAmbulanceSub;

struct AmbulanceSub {
    byte field_0x0;
    byte field_0x1;
    byte field_0x2;
    undefined1 field_0x3;
    int field_0x4;
    int field_0x8;
    int field_0xc;
    int field_0x10;
    byte field_0x14;
    undefined1 field_0x15;
    short field_0x16;
    int field_0x18;
    byte field_0x1c;
    byte field_0x1d;
    undefined1 field_0x1e;
    undefined1 field_0x1f;
};

struct Ambulance {
    undefined field_0x0;
    byte maybeIndex;
    undefined field_0x2;
    undefined field_0x3;
    undefined field_0x4;
    undefined field_0x5;
    undefined field_0x6;
    undefined field_0x7;
    undefined field_0x8;
    undefined field_0x9;
    undefined field_0xa;
    undefined field_0xb;
    undefined field_0xc;
    undefined field_0xd;
    undefined field_0xe;
    undefined field_0xf;
    undefined field_0x10;
    undefined field_0x11;
    undefined field_0x12;
    undefined field_0x13;
    undefined field_0x14;
    undefined field_0x15;
    undefined field_0x16;
    undefined field_0x17;
    undefined field_0x18;
    undefined field_0x19;
    undefined field_0x1a;
    undefined field_0x1b;
    undefined field_0x1c;
    undefined field_0x1d;
    undefined field_0x1e;
    undefined field_0x1f;
    undefined field_0x20;
    undefined field_0x21;
    undefined field_0x22;
    undefined field_0x23;
    undefined field_0x24;
    undefined field_0x25;
    undefined field_0x26;
    undefined field_0x27;
    undefined field_0x28;
    undefined field_0x29;
    undefined field_0x2a;
    undefined field_0x2b;
    undefined field_0x2c;
    undefined field_0x2d;
    undefined field_0x2e;
    undefined field_0x2f;
    undefined field_0x30;
    undefined field_0x31;
    undefined field_0x32;
    undefined field_0x33;
    undefined field_0x34;
    undefined field_0x35;
    undefined field_0x36;
    undefined field_0x37;
    undefined field_0x38;
    undefined field_0x39;
    undefined field_0x3a;
    undefined field_0x3b;
    undefined field_0x3c;
    undefined field_0x3d;
    undefined field_0x3e;
    undefined field_0x3f;
    undefined field_0x40;
    undefined field_0x41;
    undefined field_0x42;
    undefined field_0x43;
    undefined field_0x44;
    undefined field_0x45;
    undefined field_0x46;
    undefined field_0x47;
    undefined field_0x48;
    undefined field_0x49;
    undefined field_0x4a;
    undefined field_0x4b;
    undefined field_0x4c;
    undefined field_0x4d;
    undefined field_0x4e;
    undefined field_0x4f;
    undefined field_0x50;
    undefined field_0x51;
    undefined field_0x52;
    undefined field_0x53;
    undefined field_0x54;
    undefined field_0x55;
    undefined field_0x56;
    undefined field_0x57;
    undefined field_0x58;
    undefined field_0x59;
    undefined field_0x5a;
    undefined field_0x5b;
    undefined field_0x5c;
    undefined field_0x5d;
    undefined field_0x5e;
    undefined field_0x5f;
    undefined field_0x60;
    undefined field_0x61;
    undefined field_0x62;
    undefined field_0x63;
    undefined field_0x64;
    undefined field_0x65;
    undefined field_0x66;
    undefined field_0x67;
    undefined field_0x68;
    undefined field_0x69;
    undefined field_0x6a;
    undefined field_0x6b;
    undefined field_0x6c;
    undefined field_0x6d;
    undefined field_0x6e;
    undefined field_0x6f;
    undefined field_0x70;
    undefined field_0x71;
    undefined field_0x72;
    undefined field_0x73;
    undefined field_0x74;
    undefined field_0x75;
    undefined field_0x76;
    undefined field_0x77;
    undefined field_0x78;
    undefined field_0x79;
    undefined field_0x7a;
    undefined field_0x7b;
    undefined field_0x7c;
    undefined field_0x7d;
    undefined field_0x7e;
    undefined field_0x7f;
    undefined field_0x80;
    undefined field_0x81;
    undefined field_0x82;
    undefined field_0x83;
    undefined field_0x84;
    undefined field_0x85;
    undefined field_0x86;
    undefined field_0x87;
    undefined field_0x88;
    undefined field_0x89;
    undefined field_0x8a;
    undefined field_0x8b;
    undefined field_0x8c;
    undefined field_0x8d;
    undefined field_0x8e;
    undefined field_0x8f;
    undefined field_0x90;
    undefined field_0x91;
    undefined field_0x92;
    undefined field_0x93;
    undefined field_0x94;
    undefined field_0x95;
    undefined field_0x96;
    undefined field_0x97;
    undefined field_0x98;
    undefined field_0x99;
    undefined field_0x9a;
    undefined field_0x9b;
    undefined field_0x9c;
    undefined field_0x9d;
    undefined field_0x9e;
    undefined field_0x9f;
    undefined field_0xa0;
    undefined field_0xa1;
    undefined field_0xa2;
    undefined field_0xa3;
    undefined field_0xa4;
    undefined field_0xa5;
    undefined field_0xa6;
    undefined field_0xa7;
    undefined field_0xa8;
    undefined field_0xa9;
    undefined field_0xaa;
    undefined field_0xab;
    undefined field_0xac;
    undefined field_0xad;
    undefined field_0xae;
    undefined field_0xaf;
    undefined field_0xb0;
    undefined field_0xb1;
    undefined field_0xb2;
    undefined field_0xb3;
    undefined field_0xb4;
    undefined field_0xb5;
    undefined field_0xb6;
    undefined field_0xb7;
    undefined field_0xb8;
    undefined field_0xb9;
    undefined field_0xba;
    undefined field_0xbb;
    undefined field_0xbc;
    undefined field_0xbd;
    undefined field_0xbe;
    undefined field_0xbf;
    undefined field_0xc0;
    undefined field_0xc1;
    undefined field_0xc2;
    undefined field_0xc3;
    undefined field_0xc4;
    undefined field_0xc5;
    undefined field_0xc6;
    undefined field_0xc7;
    undefined field_0xc8;
    undefined field_0xc9;
    undefined field_0xca;
    undefined field_0xcb;
    undefined field_0xcc;
    undefined field_0xcd;
    undefined field_0xce;
    undefined field_0xcf;
    struct AmbulanceSub arr[2];
};

typedef struct FrontEnd FrontEnd, *PFrontEnd;

struct FrontEnd {
    undefined field_0x0;
    undefined field_0x1;
    undefined field_0x2;
    undefined field_0x3;
    undefined field_0x4;
    undefined field_0x5;
    undefined field_0x6;
    undefined field_0x7;
    int field_0x8;
    undefined field_0xc;
    undefined field_0xd;
    undefined field_0xe;
    byte field_0xf;
    undefined field_0x10;
    undefined field_0x11;
    undefined field_0x12;
    undefined field_0x13;
    undefined field_0x14;
    undefined field_0x15;
    undefined field_0x16;
    undefined field_0x17;
    undefined field_0x18;
    undefined field_0x19;
    undefined field_0x1a;
    byte field_0x1b;
    undefined field_0x1c[227];
    undefined4 field_0xff;
    undefined field_0x103;
    undefined field_0x104;
    undefined field_0x105;
    undefined field_0x106;
    undefined field_0x107;
    int field_0x108;
    byte field_0x10c;
    undefined field_0x10d;
    undefined field_0x10e;
    undefined field_0x10f;
    int movie1;
    int field_0x114;
    int field_0x118;
    undefined field_0x11c;
    undefined field_0x11d;
    short doPlayMovies;
    undefined field_0x120[3134];
    short plyrslot;
    short plyrslot2;
    undefined field_0xd62[48186];
    short field_0xc99c;
    byte field_0xc99e;
    byte field_0xc99f;
    short bufSize_256;
    short short_eq_5;
    int field_0xc9a4;
    int field_0xc9a8;
    int field_0xc9ac;
    int field_0xc9b0;
    short field_0xc9b4;
    byte field_0xc9b6; /* Created by retype action */
    byte field_0xc9b7;
    byte field_0xc9b8;
    byte field_0xc9b9;
    byte field_0xc9ba;
    undefined field_0xc9bb;
    byte field_0xc9bc;
    byte field_0xc9bd;
    byte field_0xc9be;
    byte field_0xc9bf;
    byte field_0xc9c0;
    byte field_0xc9c1;
    byte field_0xc9c2;
    byte field_0xc9c3;
    byte field_0xc9c4;
    dword time;
    byte field_0xc9c9;
    byte field_0xc9ca;
    undefined field_0xc9cb[9194];
    undefined1 vector_8; /* Created by retype action */
    undefined field_0xedb6[62];
    byte movie2;
    undefined field_0xedf5;
    short field_0xedf6;
    byte field_0xedf8;
    byte field_0xedf9;
    undefined field_0xedfa[64802];
    short field_0x1eb1c;
    undefined field_0x1eb1e;
    undefined field_0x1eb1f;
    int unkPtr;
    short field_0x1eb24;
    undefined field_0x1eb26;
    undefined field_0x1eb27;
    undefined field_0x1eb28;
    undefined field_0x1eb29;
    undefined field_0x1eb2a;
    undefined field_0x1eb2b;
    undefined field_0x1eb2c;
    undefined field_0x1eb2d;
    byte buf8[8];
    byte field_0x1eb36;
    byte field_0x1eb37;
    byte field_0x1eb38;
    byte field_0x1eb39;
    byte field_0x1eb3a;
    byte field_0x1eb3b;
    undefined field_0x1eb3c;
    undefined field_0x1eb3d;
    undefined field_0x1eb3e;
    undefined field_0x1eb3f;
};

typedef struct Game Game, *PGame;


typedef struct XYZ XYZ, *PXYZ;
typedef struct Player Player, *PPlayer;

typedef struct SaveSlotAnimatedValue SaveSlotAnimatedValue, *PSaveSlotAnimatedValue;

typedef struct S26 S26, *PS26;

struct Game { /* S8 */
    enum GAME_STATUS gameStatus; /* 1 - run, 2 - pause game */
    struct Save * saveSlotArr[6];
    struct Save * currentSaveSlot2;
    byte field_0x20;
    byte field_0x21;
    byte field_0x22;
    byte length;
    char slotIndex;
    undefined field_0x25;
    undefined field_0x26;
    undefined field_0x27;
    int field_0x28;
    int relatedToQuitGame;
    byte compensationFPSTime;
    undefined field_0x31;
    undefined field_0x32;
    undefined field_0x33;
    int field_0x34;
    struct Save * CurrentSaveSlot; /* Created by retype action */
    undefined field_0x3c;
    undefined field_0x3d;
    undefined field_0x3e;
    undefined field_0x3f;
};

struct SaveSlotAnimatedValue { /* Used for animate changing of values */
    int value;
    undefined field_0x4;
    undefined field_0x5;
    undefined field_0x6;
    undefined field_0x7;
    undefined field_0x8;
    undefined field_0x9;
    undefined field_0xa;
    undefined field_0xb;
    undefined field_0xc;
    undefined field_0xd;
    undefined field_0xe;
    undefined field_0xf;
    byte accuracyCount;
    undefined field_0x11;
    undefined field_0x12;
    undefined field_0x13;
    int reverseCount;
    undefined field_0x18;
    undefined field_0x19;
    undefined field_0x1a;
    undefined field_0x1b;
    undefined field_0x1c;
    undefined field_0x1d;
    undefined field_0x1e;
    undefined field_0x1f;
    struct Player * ptrToSaveSlot;
    undefined field_0x24;
    undefined field_0x25;
    undefined field_0x26;
    undefined field_0x27;
    undefined field_0x28;
    undefined field_0x29;
    short maxDigitsInValue;
    short min;
    short digitOffsetForAnimationOfChange;
    int max;
    undefined field_0x34;
    undefined field_0x35;
    short id;
};

struct S26 {
    undefined field_0x0;
    undefined field_0x1;
    undefined field_0x2;
    undefined field_0x3;
    undefined field_0x4;
    undefined field_0x5;
    undefined field_0x6;
    undefined field_0x7;
    undefined field_0x8;
    undefined field_0x9;
    undefined field_0xa;
    undefined field_0xb;
    undefined field_0xc;
    undefined field_0xd;
    undefined field_0xe;
    undefined field_0xf;
    undefined field_0x10;
    undefined field_0x11;
    undefined field_0x12;
    undefined field_0x13;
    undefined field_0x14;
    undefined field_0x15;
    undefined field_0x16;
    undefined field_0x17;
    undefined field_0x18;
    undefined field_0x19;
    undefined field_0x1a;
    undefined field_0x1b;
    undefined field_0x1c;
    undefined field_0x1d;
    undefined field_0x1e;
    undefined field_0x1f;
    undefined field_0x20;
    undefined field_0x21;
    undefined field_0x22;
    undefined field_0x23;
    undefined field_0x24;
    undefined field_0x25;
    undefined field_0x26;
    undefined field_0x27;
    undefined field_0x28;
    undefined4 field_0x29;
    undefined4 field_0x2d;
    byte field_0x31;
    undefined field_0x32;
    undefined field_0x33;
    undefined field_0x34;
    undefined field_0x35;
    undefined field_0x36;
    undefined field_0x37;
    int relToCopStars;
};

struct XYZ {
    int x;
    int y;
    int z;
    int field_0xc;
    int x2;
    int y2;
    int z2;
    int field_0x1c;
    undefined field_0x20;
    undefined field_0x21;
    undefined field_0x22;
    undefined field_0x23;
    undefined field_0x24;
    undefined field_0x25;
    undefined field_0x26;
    undefined field_0x27;
    undefined field_0x28;
    undefined field_0x29;
    undefined field_0x2a;
    undefined field_0x2b;
    undefined field_0x2c;
    undefined field_0x2d;
    undefined field_0x2e;
    undefined field_0x2f;
    undefined field_0x30;
    undefined field_0x31;
    undefined field_0x32;
    undefined field_0x33;
    undefined field_0x34;
    undefined field_0x35;
    undefined field_0x36;
    undefined field_0x37;
    undefined field_0x38;
    undefined field_0x39;
    undefined field_0x3a;
    undefined field_0x3b;
    int field_0x3c;
    undefined field_0x40;
    undefined field_0x41;
    undefined field_0x42;
    undefined field_0x43;
    undefined field_0x44;
    undefined field_0x45;
    undefined field_0x46;
    undefined field_0x47;
    undefined field_0x48;
    undefined field_0x49;
    undefined field_0x4a;
    undefined field_0x4b;
    undefined field_0x4c;
    undefined field_0x4d;
    undefined field_0x4e;
    undefined field_0x4f;
    undefined field_0x50;
    undefined field_0x51;
    undefined field_0x52;
    undefined field_0x53;
    undefined field_0x54;
    undefined field_0x55;
    undefined field_0x56;
    undefined field_0x57;
    undefined field_0x58;
    undefined field_0x59;
    undefined field_0x5a;
    undefined field_0x5b;
    undefined field_0x5c;
    undefined field_0x5d;
    undefined field_0x5e;
    undefined field_0x5f;
    undefined field_0x60;
    undefined field_0x61;
    undefined field_0x62;
    undefined field_0x63;
    undefined field_0x64;
    undefined field_0x65;
    undefined field_0x66;
    undefined field_0x67;
    uint width;
    uint height; /* Created by retype action */
    uint halfWidth;
    uint halfHeight;
    undefined field_0x78;
    undefined field_0x79;
    undefined field_0x7a;
    undefined field_0x7b;
    undefined field_0x7c;
    undefined field_0x7d;
    undefined field_0x7e;
    undefined field_0x7f;
    undefined field_0x80;
    undefined field_0x81;
    undefined field_0x82;
    undefined field_0x83;
    undefined field_0x84;
    undefined field_0x85;
    undefined field_0x86;
    undefined field_0x87;
    undefined field_0x88;
    undefined field_0x89;
    undefined field_0x8a;
    undefined field_0x8b;
    undefined field_0x8c;
    undefined field_0x8d;
    undefined field_0x8e;
    undefined field_0x8f;
    undefined field_0x90;
    undefined field_0x91;
    undefined field_0x92;
    undefined field_0x93;
    undefined field_0x94;
    undefined field_0x95;
    undefined field_0x96;
    undefined field_0x97;
    int xx;
    int yy;
    int zz;
    int field_0xa4;
    undefined field_0xa8;
    undefined field_0xa9;
    undefined field_0xaa;
    undefined field_0xab;
    undefined4 field_0xac;
    undefined4 field_0xb0;
    undefined4 field_0xb4;
    undefined4 field_0xb8;
    undefined field_0xbc;
    undefined field_0xbd;
    undefined field_0xbe;
    undefined field_0xbf;
    undefined field_0xc0;
    undefined field_0xc1;
    undefined field_0xc2;
    undefined field_0xc3;
    undefined field_0xc4;
    undefined field_0xc5;
    undefined field_0xc6;
    undefined field_0xc7;
    undefined field_0xc8;
    undefined field_0xc9;
    undefined field_0xca;
    undefined field_0xcb;
    undefined field_0xcc;
    undefined field_0xcd;
    undefined field_0xce;
    undefined field_0xcf;
    undefined field_0xd0;
    undefined field_0xd1;
    undefined field_0xd2;
    undefined field_0xd3;
    undefined field_0xd4;
    undefined field_0xd5;
    undefined field_0xd6;
    undefined field_0xd7;
    undefined field_0xd8;
    undefined field_0xd9;
    undefined field_0xda;
    undefined field_0xdb;
    undefined field_0xdc;
    undefined field_0xdd;
    undefined field_0xde;
    undefined field_0xdf;
    undefined field_0xe0;
    undefined field_0xe1;
    undefined field_0xe2;
    undefined field_0xe3;
    undefined field_0xe4;
    undefined field_0xe5;
    undefined field_0xe6;
    undefined field_0xe7;
    undefined field_0xe8;
    undefined field_0xe9;
    undefined field_0xea;
    undefined field_0xeb;
    undefined field_0xec;
    undefined field_0xed;
    undefined field_0xee;
    undefined field_0xef;
    undefined field_0xf0;
    undefined field_0xf1;
    undefined field_0xf2;
    undefined field_0xf3;
    undefined field_0xf4;
    undefined field_0xf5;
    undefined field_0xf6;
    undefined field_0xf7;
    undefined field_0xf8;
    undefined field_0xf9;
    undefined field_0xfa;
    undefined field_0xfb;
    undefined field_0xfc;
    undefined field_0xfd;
    undefined field_0xfe;
    undefined field_0xff;
};

struct Save {
    undefined field_0x0;
    undefined field_0x1;
    undefined field_0x2;
    undefined field_0x3;
    enum KEYBOARD_STATE keyboardKeys;
    short field_0x8;
    short field_0xa;
    int field_0xc;
    struct Ped * playerPed3;
    short field_0x14;
    short field_0x16;
    short field_0x18;
    undefined field_0x1a;
    undefined field_0x1b;
    undefined field_0x1c;
    undefined field_0x1d;
    undefined field_0x1e;
    undefined field_0x1f;
    undefined field_0x20;
    undefined field_0x21;
    undefined field_0x22;
    byte field_0x23;
    undefined field_0x24;
    undefined field_0x25;
    undefined field_0x26;
    undefined field_0x27;
    byte unknown2;
    byte field_0x29;
    short field_0x2a;
    short field_0x2c;
    byte saveSlotIndex;
    byte field_0x2f;
    byte field_0x30;
    byte field_0x31;
    undefined field_0x32;
    undefined field_0x33;
    int field_0x34;
    int field_0x38;
    int field_0x3c;
    undefined field_0x40;
    undefined field_0x41;
    undefined field_0x42;
    undefined field_0x43;
    enum DEATH_REASON deathReason;
    byte field_0x48;
    undefined field_0x49;
    undefined field_0x4a;
    undefined field_0x4b;
    void * field_0x4c;
    void * field_0x50;
    struct Car * lastCars[3];
    int field_0x60;
    byte field_0x64;
    undefined field_0x65;
    undefined field_0x66;
    undefined field_0x67;
    int someState;
    int field_0x6c;
    byte field_0x70;
    byte field_0x71;
    byte field_0x72;
    byte field_0x73;
    byte field_0x74;
    byte field_0x75;
    byte debugKey1;
    byte debugKey2;
    undefined field_0x78;
    undefined field_0x79;
    undefined field_0x7a;
    undefined field_0x7b;
    undefined field_0x7c;
    undefined field_0x7d;
    undefined field_0x7e;
    undefined field_0x7f;
    undefined field_0x80;
    undefined field_0x81;
    undefined field_0x82;
    undefined field_0x83;
    undefined field_0x84;
    undefined field_0x85;
    undefined field_0x86;
    undefined field_0x87;
    undefined field_0x88;
    undefined field_0x89;
    undefined field_0x8a;
    undefined field_0x8b;
    undefined field_0x8c;
    undefined field_0x8d;
    undefined field_0x8e;
    byte field_0x8f;
    struct XYZ xyz;
    struct Ped * playerPed;
    undefined field_0xc8;
    undefined field_0xc9;
    undefined field_0xca;
    undefined field_0xcb;
    undefined field_0xcc;
    undefined field_0xcd;
    undefined field_0xce;
    undefined field_0xcf;
    undefined field_0xd0;
    undefined field_0xd1;
    undefined field_0xd2;
    undefined field_0xd3;
    undefined field_0xd4;
    undefined field_0xd5;
    undefined field_0xd6;
    undefined field_0xd7;
    undefined field_0xd8;
    undefined field_0xd9;
    undefined field_0xda;
    undefined field_0xdb;
    undefined field_0xdc;
    undefined field_0xdd;
    undefined field_0xde;
    undefined field_0xdf;
    undefined field_0xe0;
    undefined field_0xe1;
    undefined field_0xe2;
    undefined field_0xe3;
    undefined field_0xe4;
    undefined field_0xe5;
    undefined field_0xe6;
    undefined field_0xe7;
    undefined field_0xe8;
    undefined field_0xe9;
    undefined field_0xea;
    undefined field_0xeb;
    undefined field_0xec;
    undefined field_0xed;
    undefined field_0xee;
    undefined field_0xef;
    undefined field_0xf0;
    undefined field_0xf1;
    undefined field_0xf2;
    undefined field_0xf3;
    undefined field_0xf4;
    undefined field_0xf5;
    undefined field_0xf6;
    undefined field_0xf7;
    undefined field_0xf8;
    undefined field_0xf9;
    undefined field_0xfa;
    undefined field_0xfb;
    undefined field_0xfc;
    undefined field_0xfd;
    undefined field_0xfe;
    undefined field_0xff;
    undefined field_0x100;
    undefined field_0x101;
    undefined field_0x102;
    undefined field_0x103;
    undefined field_0x104;
    undefined field_0x105;
    undefined field_0x106;
    undefined field_0x107;
    undefined field_0x108;
    undefined field_0x109;
    undefined field_0x10a;
    undefined field_0x10b;
    undefined field_0x10c;
    undefined field_0x10d;
    undefined field_0x10e;
    undefined field_0x10f;
    undefined field_0x110;
    undefined field_0x111;
    undefined field_0x112;
    undefined field_0x113;
    undefined field_0x114;
    undefined field_0x115;
    undefined field_0x116;
    undefined field_0x117;
    undefined field_0x118;
    undefined field_0x119;
    undefined field_0x11a;
    undefined field_0x11b;
    undefined field_0x11c;
    undefined field_0x11d;
    undefined field_0x11e;
    undefined field_0x11f;
    undefined field_0x120;
    undefined field_0x121;
    undefined field_0x122;
    undefined field_0x123;
    undefined field_0x124;
    undefined field_0x125;
    undefined field_0x126;
    undefined field_0x127;
    int encodedCameraX;
    int encodedCameraY; /* Created by retype action */
    int encodedCameraZ; /* Created by retype action */
    undefined field_0x134;
    undefined field_0x135;
    undefined field_0x136;
    undefined field_0x137;
    undefined field_0x138;
    undefined field_0x139;
    undefined field_0x13a;
    undefined field_0x13b;
    undefined field_0x13c;
    undefined field_0x13d;
    undefined field_0x13e;
    undefined field_0x13f;
    undefined field_0x140;
    undefined field_0x141;
    undefined field_0x142;
    undefined field_0x143;
    undefined field_0x144;
    undefined field_0x145;
    undefined field_0x146;
    undefined field_0x147;
    undefined field_0x148;
    undefined field_0x149;
    undefined field_0x14a;
    undefined field_0x14b;
    struct XYZ xyz2;
    undefined field_0x24c;
    undefined field_0x24d;
    undefined field_0x24e;
    undefined field_0x24f;
    undefined field_0x250;
    undefined field_0x251;
    undefined field_0x252;
    undefined field_0x253;
    undefined field_0x254;
    undefined field_0x255;
    undefined field_0x256;
    undefined field_0x257;
    undefined field_0x258;
    undefined field_0x259;
    undefined field_0x25a;
    undefined field_0x25b;
    undefined field_0x25c;
    undefined field_0x25d;
    undefined field_0x25e;
    undefined field_0x25f;
    undefined field_0x260;
    undefined field_0x261;
    undefined field_0x262;
    undefined field_0x263;
    undefined field_0x264;
    undefined field_0x265;
    undefined field_0x266;
    undefined field_0x267;
    undefined field_0x268;
    undefined field_0x269;
    undefined field_0x26a;
    undefined field_0x26b;
    undefined field_0x26c;
    undefined field_0x26d;
    undefined field_0x26e;
    undefined field_0x26f;
    undefined field_0x270;
    undefined field_0x271;
    undefined field_0x272;
    undefined field_0x273;
    undefined field_0x274;
    undefined field_0x275;
    undefined field_0x276;
    undefined field_0x277;
    undefined field_0x278;
    undefined field_0x279;
    undefined field_0x27a;
    undefined field_0x27b;
    undefined field_0x27c;
    undefined field_0x27d;
    undefined field_0x27e;
    undefined field_0x27f;
    undefined field_0x280;
    undefined field_0x281;
    undefined field_0x282;
    undefined field_0x283;
    undefined field_0x284;
    undefined field_0x285;
    undefined field_0x286;
    undefined field_0x287;
    undefined field_0x288;
    undefined field_0x289;
    undefined field_0x28a;
    undefined field_0x28b;
    undefined field_0x28c;
    undefined field_0x28d;
    undefined field_0x28e;
    undefined field_0x28f;
    undefined field_0x290;
    undefined field_0x291;
    undefined field_0x292;
    undefined field_0x293;
    undefined field_0x294;
    undefined field_0x295;
    undefined field_0x296;
    undefined field_0x297;
    undefined field_0x298;
    undefined field_0x299;
    undefined field_0x29a;
    undefined field_0x29b;
    undefined field_0x29c;
    undefined field_0x29d;
    undefined field_0x29e;
    undefined field_0x29f;
    int auxGameCameraX; /* Created by retype action */
    int auxGameCameraY; /* Created by retype action */
    int auxGameCameraZ;
    undefined field_0x2ac;
    undefined field_0x2ad;
    undefined field_0x2ae;
    undefined field_0x2af;
    undefined field_0x2b0;
    undefined field_0x2b1;
    undefined field_0x2b2;
    undefined field_0x2b3;
    undefined field_0x2b4;
    undefined field_0x2b5;
    undefined field_0x2b6;
    undefined field_0x2b7;
    undefined field_0x2b8;
    undefined field_0x2b9;
    undefined field_0x2ba;
    undefined field_0x2bb;
    undefined field_0x2bc;
    undefined field_0x2bd;
    undefined field_0x2be;
    undefined field_0x2bf;
    undefined field_0x2c0;
    undefined field_0x2c1;
    undefined field_0x2c2;
    undefined field_0x2c3;
    struct Ped * playerPed2;
    struct Ped * pedRelTo_fieldx68;
    int field_0x2cc;
    byte field_0x2d0;
    undefined field_0x2d1;
    undefined field_0x2d2;
    undefined field_0x2d3;
    struct SaveSlotAnimatedValue animatedValues_firstMoney[15];
    undefined field_0x61c;
    undefined field_0x61d;
    undefined field_0x61e;
    undefined field_0x61f;
    undefined field_0x620;
    undefined field_0x621;
    undefined field_0x622;
    undefined field_0x623;
    undefined field_0x624;
    undefined field_0x625;
    undefined field_0x626;
    undefined field_0x627;
    undefined field_0x628;
    undefined field_0x629;
    undefined field_0x62a;
    undefined field_0x62b;
    undefined field_0x62c;
    undefined field_0x62d;
    undefined field_0x62e;
    undefined field_0x62f;
    undefined field_0x630;
    undefined field_0x631;
    undefined field_0x632;
    undefined field_0x633;
    undefined field_0x634;
    undefined field_0x635;
    undefined field_0x636;
    undefined field_0x637;
    undefined field_0x638;
    undefined field_0x639;
    undefined field_0x63a;
    undefined field_0x63b;
    undefined field_0x63c;
    undefined field_0x63d;
    undefined field_0x63e;
    undefined field_0x63f;
    byte unknown;
    undefined field_0x641;
    undefined field_0x642;
    undefined field_0x643;
    struct S26 * field_0x644;
    undefined field_0x648;
    undefined field_0x649;
    undefined field_0x64a;
    undefined field_0x64b;
    undefined field_0x64c;
    undefined field_0x64d;
    undefined field_0x64e;
    undefined field_0x64f;
    undefined field_0x650;
    undefined field_0x651;
    undefined field_0x652;
    undefined field_0x653;
    undefined field_0x654;
    undefined field_0x655;
    undefined field_0x656;
    undefined field_0x657;
    undefined field_0x658;
    undefined field_0x659;
    undefined field_0x65a;
    undefined field_0x65b;
    undefined field_0x65c;
    undefined field_0x65d;
    undefined field_0x65e;
    undefined field_0x65f;
    undefined field_0x660;
    undefined field_0x661;
    undefined field_0x662;
    undefined field_0x663;
    undefined field_0x664;
    undefined field_0x665;
    undefined field_0x666;
    undefined field_0x667;
    undefined field_0x668;
    undefined field_0x669;
    undefined field_0x66a;
    undefined field_0x66b;
    undefined field_0x66c;
    undefined field_0x66d;
    undefined field_0x66e;
    undefined field_0x66f;
    undefined field_0x670;
    undefined field_0x671;
    undefined field_0x672;
    undefined field_0x673;
    undefined field_0x674;
    undefined field_0x675;
    undefined field_0x676;
    undefined field_0x677;
    int field_0x678;
    int field_0x67c;
    ushort incToBe100;
    short eq_1000;
    struct SaveSlotAnimatedValue lives;
    struct SaveSlotAnimatedValue moneyMultiplier;
    undefined field_0x6f4;
    undefined field_0x6f5;
    undefined field_0x6f6;
    undefined field_0x6f7;
    undefined field_0x6f8;
    undefined field_0x6f9;
    undefined field_0x6fa;
    undefined field_0x6fb;
    short field_0x6fc;
    undefined field_0x6fe;
    undefined field_0x6ff;
    short bonus1;
    short bonus2;
    short bonus3;
    short bonus4;
    undefined field_0x708;
    undefined field_0x709;
    short bonus5;
    undefined field_0x70c;
    undefined field_0x70d;
    undefined field_0x70e;
    undefined field_0x70f;
    undefined field_0x710;
    undefined field_0x711;
    undefined field_0x712;
    undefined field_0x713;
    undefined field_0x714;
    undefined field_0x715;
    undefined field_0x716;
    undefined field_0x717;
    int iArr28[28];
    short field_0x788;
    byte field_0x78a;
    undefined field_0x78b;
    int field_0x78c;
    short field_0x790;
    undefined field_0x792;
    undefined field_0x793;
    undefined field_0x794;
    undefined field_0x795;
    undefined field_0x796;
    undefined field_0x797;
    undefined field_0x798;
    undefined field_0x799;
    undefined field_0x79a;
    undefined field_0x79b;
    undefined field_0x79c;
    undefined field_0x79d;
    undefined field_0x79e;
    undefined field_0x79f;
    undefined field_0x7a0;
    undefined field_0x7a1;
    undefined field_0x7a2;
    undefined field_0x7a3;
    undefined field_0x7a4;
    undefined field_0x7a5;
    undefined field_0x7a6;
    undefined field_0x7a7;
    undefined field_0x7a8;
    undefined field_0x7a9;
    undefined field_0x7aa;
    undefined field_0x7ab;
    undefined field_0x7ac;
    undefined field_0x7ad;
    undefined field_0x7ae;
    undefined field_0x7af;
    undefined field_0x7b0;
    undefined field_0x7b1;
    undefined field_0x7b2;
    undefined field_0x7b3;
    undefined field_0x7b4;
    undefined field_0x7b5;
    undefined field_0x7b6;
    undefined field_0x7b7;
    undefined field_0x7b8;
    undefined field_0x7b9;
    undefined field_0x7ba;
    undefined field_0x7bb;
    undefined field_0x7bc;
    undefined field_0x7bd;
    undefined field_0x7be;
    undefined field_0x7bf;
    undefined field_0x7c0;
    undefined field_0x7c1;
    undefined field_0x7c2;
    undefined field_0x7c3;
    undefined field_0x7c4;
    undefined field_0x7c5;
    undefined field_0x7c6;
    undefined field_0x7c7;
    undefined field_0x7c8;
    undefined field_0x7c9;
    undefined field_0x7ca;
    undefined field_0x7cb;
    undefined field_0x7cc;
    undefined field_0x7cd;
    undefined field_0x7ce;
    undefined field_0x7cf;
    undefined field_0x7d0;
    undefined field_0x7d1;
    undefined field_0x7d2;
    undefined field_0x7d3;
    undefined field_0x7d4;
    undefined field_0x7d5;
    undefined field_0x7d6;
    undefined field_0x7d7;
    undefined field_0x7d8;
    undefined field_0x7d9;
    undefined field_0x7da;
    undefined field_0x7db;
    undefined field_0x7dc;
    undefined field_0x7dd;
    undefined field_0x7de;
    undefined field_0x7df;
    undefined field_0x7e0;
    undefined field_0x7e1;
    undefined field_0x7e2;
    undefined field_0x7e3;
    undefined field_0x7e4;
    undefined field_0x7e5;
    undefined field_0x7e6;
    undefined field_0x7e7;
    undefined field_0x7e8;
    undefined field_0x7e9;
    undefined field_0x7ea;
    undefined field_0x7eb;
    undefined field_0x7ec;
    undefined field_0x7ed;
    undefined field_0x7ee;
    undefined field_0x7ef;
    undefined field_0x7f0;
    undefined field_0x7f1;
    undefined field_0x7f2;
    undefined field_0x7f3;
    undefined field_0x7f4;
    undefined field_0x7f5;
    undefined field_0x7f6;
    undefined field_0x7f7;
    undefined field_0x7f8;
    undefined field_0x7f9;
    undefined field_0x7fa;
    undefined field_0x7fb;
    undefined field_0x7fc;
    undefined field_0x7fd;
    undefined field_0x7fe;
    undefined field_0x7ff;
    undefined field_0x800;
    undefined field_0x801;
    undefined field_0x802;
    undefined field_0x803;
    undefined field_0x804;
    undefined field_0x805;
    undefined field_0x806;
    undefined field_0x807;
    undefined field_0x808;
    undefined field_0x809;
    undefined field_0x80a;
    undefined field_0x80b;
    undefined field_0x80c;
    undefined field_0x80d;
    undefined field_0x80e;
    undefined field_0x80f;
    undefined field_0x810;
    undefined field_0x811;
    undefined field_0x812;
    undefined field_0x813;
    undefined field_0x814;
    undefined field_0x815;
    undefined field_0x816;
    undefined field_0x817;
    undefined field_0x818;
    undefined field_0x819;
    undefined field_0x81a;
    undefined field_0x81b;
    undefined field_0x81c;
    undefined field_0x81d;
    undefined field_0x81e;
    undefined field_0x81f;
    undefined field_0x820;
    undefined field_0x821;
    undefined field_0x822;
    undefined field_0x823;
    undefined field_0x824;
    undefined field_0x825;
    undefined field_0x826;
    undefined field_0x827;
    undefined field_0x828;
    undefined field_0x829;
    undefined field_0x82a;
    undefined field_0x82b;
    undefined field_0x82c;
    undefined field_0x82d;
    undefined field_0x82e;
    undefined field_0x82f;
    undefined field_0x830;
    undefined field_0x831;
    undefined field_0x832;
    undefined field_0x833;
    undefined field_0x834;
    undefined field_0x835;
    undefined field_0x836;
    undefined field_0x837;
    undefined field_0x838;
    undefined field_0x839;
    undefined field_0x83a;
    undefined field_0x83b;
    short field_0x83c;
    undefined field_0x83e;
    undefined field_0x83f;
    undefined field_0x840;
    undefined field_0x841;
    undefined field_0x842;
    undefined field_0x843;
    undefined field_0x844;
    undefined field_0x845;
    undefined field_0x846;
    undefined field_0x847;
    undefined field_0x848;
    undefined field_0x849;
    undefined field_0x84a;
    undefined field_0x84b;
    undefined field_0x84c;
    undefined field_0x84d;
    undefined field_0x84e;
    undefined field_0x84f;
    undefined field_0x850;
    undefined field_0x851;
    undefined field_0x852;
    undefined field_0x853;
    undefined field_0x854;
    undefined field_0x855;
    undefined field_0x856;
    undefined field_0x857;
    undefined field_0x858;
    undefined field_0x859;
    undefined field_0x85a;
    undefined field_0x85b;
};

typedef struct GameStats GameStats, *PGameStats;

struct GameStats {
    undefined field_0x0[112];
    uint field_0x70;
    uint field_0x74;
    undefined field_0x78[48];
    int field_0xa8;
    undefined field_0xac[1120];
    int vehicles_hijacked;
    int civilians_run_down;
    int civilians_murdered;
    int lawmen_killed;
    int gang_members_killed;
    undefined field_0x520;
    undefined field_0x521;
    undefined field_0x522;
    undefined field_0x523;
    undefined field_0x524;
    undefined field_0x525;
    undefined field_0x526;
    undefined field_0x527;
    undefined field_0x528;
    undefined field_0x529;
    undefined field_0x52a;
    undefined field_0x52b;
    int auto_damage_cost;
    int fugitive_factor;
    undefined field_0x534;
    undefined field_0x535;
    undefined field_0x536;
    undefined field_0x537;
    undefined field_0x538;
    undefined field_0x539;
    undefined field_0x53a;
    undefined field_0x53b;
    undefined field_0x53c;
    undefined field_0x53d;
    undefined field_0x53e;
    undefined field_0x53f;
};

typedef struct Gang Gang, *PGang;

struct Gang {
    byte field_0x0;
    byte field_0x1;
    undefined field_0x2;
    undefined field_0x3;
    undefined field_0x4;
    undefined field_0x5;
    undefined field_0x6;
    undefined field_0x7;
    undefined field_0x8;
    undefined field_0x9;
    undefined field_0xa;
    undefined field_0xb;
    undefined field_0xc;
    undefined field_0xd;
    undefined field_0xe;
    undefined field_0xf;
    undefined field_0x10;
    undefined field_0x11;
    undefined field_0x12;
    undefined field_0x13;
    undefined field_0x14;
    undefined field_0x15;
    undefined field_0x16;
    undefined field_0x17;
    undefined field_0x18;
    undefined field_0x19;
    undefined field_0x1a;
    undefined field_0x1b;
    undefined field_0x1c;
    undefined field_0x1d;
    undefined field_0x1e;
    undefined field_0x1f;
    undefined field_0x20;
    undefined field_0x21;
    undefined field_0x22;
    undefined field_0x23;
    undefined field_0x24;
    undefined field_0x25;
    undefined field_0x26;
    undefined field_0x27;
    undefined field_0x28;
    undefined field_0x29;
    undefined field_0x2a;
    undefined field_0x2b;
    undefined field_0x2c;
    undefined field_0x2d;
    undefined field_0x2e;
    undefined field_0x2f;
    undefined field_0x30;
    undefined field_0x31;
    undefined field_0x32;
    undefined field_0x33;
    undefined field_0x34;
    undefined field_0x35;
    undefined field_0x36;
    undefined field_0x37;
    undefined field_0x38;
    undefined field_0x39;
    undefined field_0x3a;
    undefined field_0x3b;
    undefined field_0x3c;
    undefined field_0x3d;
    undefined field_0x3e;
    undefined field_0x3f;
    undefined field_0x40;
    undefined field_0x41;
    undefined field_0x42;
    undefined field_0x43;
    undefined field_0x44;
    undefined field_0x45;
    undefined field_0x46;
    undefined field_0x47;
    undefined field_0x48;
    undefined field_0x49;
    undefined field_0x4a;
    undefined field_0x4b;
    undefined field_0x4c;
    undefined field_0x4d;
    undefined field_0x4e;
    undefined field_0x4f;
    undefined field_0x50;
    undefined field_0x51;
    undefined field_0x52;
    undefined field_0x53;
    undefined field_0x54;
    undefined field_0x55;
    undefined field_0x56;
    undefined field_0x57;
    undefined field_0x58;
    undefined field_0x59;
    undefined field_0x5a;
    undefined field_0x5b;
    undefined field_0x5c;
    undefined field_0x5d;
    undefined field_0x5e;
    undefined field_0x5f;
    undefined field_0x60;
    undefined field_0x61;
    undefined field_0x62;
    undefined field_0x63;
    undefined field_0x64;
    undefined field_0x65;
    undefined field_0x66;
    undefined field_0x67;
    undefined field_0x68;
    undefined field_0x69;
    undefined field_0x6a;
    undefined field_0x6b;
    undefined field_0x6c;
    undefined field_0x6d;
    undefined field_0x6e;
    undefined field_0x6f;
    undefined field_0x70;
    undefined field_0x71;
    undefined field_0x72;
    undefined field_0x73;
    undefined field_0x74;
    undefined field_0x75;
    undefined field_0x76;
    undefined field_0x77;
    undefined field_0x78;
    undefined field_0x79;
    undefined field_0x7a;
    undefined field_0x7b;
    undefined field_0x7c;
    undefined field_0x7d;
    undefined field_0x7e;
    undefined field_0x7f;
    undefined field_0x80;
    undefined field_0x81;
    undefined field_0x82;
    undefined field_0x83;
    undefined field_0x84;
    undefined field_0x85;
    undefined field_0x86;
    undefined field_0x87;
    undefined field_0x88;
    undefined field_0x89;
    undefined field_0x8a;
    undefined field_0x8b;
    undefined field_0x8c;
    undefined field_0x8d;
    undefined field_0x8e;
    undefined field_0x8f;
    undefined field_0x90;
    undefined field_0x91;
    undefined field_0x92;
    undefined field_0x93;
    undefined field_0x94;
    undefined field_0x95;
    undefined field_0x96;
    undefined field_0x97;
    undefined field_0x98;
    undefined field_0x99;
    undefined field_0x9a;
    undefined field_0x9b;
    undefined field_0x9c;
    undefined field_0x9d;
    undefined field_0x9e;
    undefined field_0x9f;
    undefined field_0xa0;
    undefined field_0xa1;
    undefined field_0xa2;
    undefined field_0xa3;
    undefined field_0xa4;
    undefined field_0xa5;
    undefined field_0xa6;
    undefined field_0xa7;
    undefined field_0xa8;
    undefined field_0xa9;
    undefined field_0xaa;
    undefined field_0xab;
    undefined field_0xac;
    undefined field_0xad;
    undefined field_0xae;
    undefined field_0xaf;
    undefined field_0xb0;
    undefined field_0xb1;
    undefined field_0xb2;
    undefined field_0xb3;
    undefined field_0xb4;
    undefined field_0xb5;
    undefined field_0xb6;
    undefined field_0xb7;
    undefined field_0xb8;
    undefined field_0xb9;
    undefined field_0xba;
    undefined field_0xbb;
    undefined field_0xbc;
    undefined field_0xbd;
    undefined field_0xbe;
    undefined field_0xbf;
    undefined field_0xc0;
    undefined field_0xc1;
    undefined field_0xc2;
    undefined field_0xc3;
    undefined field_0xc4;
    undefined field_0xc5;
    undefined field_0xc6;
    undefined field_0xc7;
    undefined field_0xc8;
    undefined field_0xc9;
    undefined field_0xca;
    undefined field_0xcb;
    undefined field_0xcc;
    undefined field_0xcd;
    undefined field_0xce;
    undefined field_0xcf;
    undefined field_0xd0;
    undefined field_0xd1;
    undefined field_0xd2;
    undefined field_0xd3;
    undefined field_0xd4;
    undefined field_0xd5;
    undefined field_0xd6;
    undefined field_0xd7;
    undefined field_0xd8;
    undefined field_0xd9;
    undefined field_0xda;
    undefined field_0xdb;
    undefined field_0xdc;
    undefined field_0xdd;
    undefined field_0xde;
    undefined field_0xdf;
    undefined field_0xe0;
    undefined field_0xe1;
    undefined field_0xe2;
    undefined field_0xe3;
    undefined field_0xe4;
    undefined field_0xe5;
    undefined field_0xe6;
    undefined field_0xe7;
    undefined field_0xe8;
    undefined field_0xe9;
    undefined field_0xea;
    undefined field_0xeb;
    undefined field_0xec;
    undefined field_0xed;
    undefined field_0xee;
    undefined field_0xef;
    undefined field_0xf0;
    undefined field_0xf1;
    undefined field_0xf2;
    undefined field_0xf3;
    undefined field_0xf4;
    undefined field_0xf5;
    undefined field_0xf6;
    undefined field_0xf7;
    undefined field_0xf8;
    undefined field_0xf9;
    undefined field_0xfa;
    undefined field_0xfb;
    undefined field_0xfc;
    undefined field_0xfd;
    undefined field_0xfe;
    undefined field_0xff;
    undefined field_0x100;
    byte field_0x101;
    undefined field_0x102;
    undefined field_0x103;
    int field_0x104;
    int field_0x108;
    int field_0x10c;
    byte field_0x110;
    byte field_0x111;
    undefined field_0x112;
    undefined field_0x113;
    undefined field_0x114;
    undefined field_0x115;
    undefined field_0x116;
    undefined field_0x117;
    undefined field_0x118;
    undefined field_0x119;
    undefined field_0x11a;
    undefined field_0x11b;
    byte respect[4];
    short field_0x120;
    undefined field_0x122;
    undefined field_0x123;
    undefined field_0x124;
    undefined field_0x125;
    undefined field_0x126;
    undefined field_0x127;
    undefined field_0x128;
    undefined field_0x129;
    undefined field_0x12a;
    undefined field_0x12b;
    undefined field_0x12c;
    undefined field_0x12d;
    undefined field_0x12e;
    undefined field_0x12f;
    undefined field_0x130;
    undefined field_0x131;
    undefined field_0x132;
    undefined field_0x133;
    undefined field_0x134;
    undefined field_0x135;
    undefined field_0x136;
    undefined field_0x137;
    undefined field_0x138;
    undefined field_0x139;
    undefined field_0x13a;
    undefined field_0x13b;
    int field_0x13c;
    byte field_0x140;
    byte field_0x141;
    undefined field_0x142;
    undefined field_0x143;
};

typedef struct Gangs Gangs, *PGangs;

struct Gangs {
    struct Gang arr[10];
};

typedef struct Menu Menu, *PMenu;

struct Menu {
    char gmpFile[256];
    char styFile[256];
    char styFile2[256];
    char unk2[256];
    byte playerArea;
    byte bonusStage;
    undefined field_0x402;
    byte playerProfile;
    undefined field_0x404;
    undefined field_0x405;
    undefined field_0x406;
    undefined field_0x407;
    undefined field_0x408;
    undefined field_0x409;
    undefined field_0x40a;
    undefined field_0x40b;
    undefined field_0x40c;
    undefined field_0x40d;
    undefined field_0x40e;
    undefined field_0x40f;
    undefined field_0x410;
    undefined field_0x411;
    undefined field_0x412;
    undefined field_0x413;
    undefined field_0x414;
    undefined field_0x415;
    undefined field_0x416;
    undefined field_0x417;
    undefined field_0x418;
    undefined field_0x419;
    undefined field_0x41a;
    undefined field_0x41b;
    undefined field_0x41c;
    undefined field_0x41d;
    undefined field_0x41e;
    undefined field_0x41f;
    undefined field_0x420;
    undefined field_0x421;
    undefined field_0x422;
    undefined field_0x423;
    undefined field_0x424;
    undefined field_0x425;
    undefined field_0x426;
    undefined field_0x427;
    undefined field_0x428;
    undefined field_0x429;
    undefined field_0x42a;
    undefined field_0x42b;
    undefined field_0x42c;
    undefined field_0x42d;
    undefined field_0x42e;
    undefined field_0x42f;
    undefined field_0x430;
    undefined field_0x431;
    undefined field_0x432;
    undefined field_0x433;
    undefined field_0x434;
    undefined field_0x435;
    undefined field_0x436;
    undefined field_0x437;
    undefined field_0x438;
    undefined field_0x439;
    undefined field_0x43a;
    byte field_0x43b;
    short fraglimit;
    undefined field_0x43e;
    undefined field_0x43f;
    undefined field_0x440;
    undefined field_0x441;
    undefined field_0x442;
    undefined field_0x443;
    undefined field_0x444;
    undefined field_0x445;
    undefined field_0x446;
    undefined field_0x447;
    undefined field_0x448;
    undefined field_0x449;
    undefined field_0x44a;
    undefined field_0x44b;
    undefined field_0x44c;
    undefined field_0x44d;
    undefined field_0x44e;
    undefined field_0x44f;
    undefined field_0x450;
    undefined field_0x451;
    undefined field_0x452;
    undefined field_0x453;
    undefined field_0x454;
    undefined field_0x455;
    undefined field_0x456;
    undefined field_0x457;
    undefined field_0x458;
    undefined field_0x459;
    undefined field_0x45a;
    undefined field_0x45b;
    undefined field_0x45c;
    undefined field_0x45d;
    undefined field_0x45e;
    undefined field_0x45f;
    undefined field_0x460;
    undefined field_0x461;
    undefined field_0x462;
    undefined field_0x463;
    undefined field_0x464;
    undefined field_0x465;
    undefined field_0x466;
    undefined field_0x467;
    undefined field_0x468;
    undefined field_0x469;
    undefined field_0x46a;
    undefined field_0x46b;
    undefined field_0x46c;
    undefined field_0x46d;
    undefined field_0x46e;
    undefined field_0x46f;
    undefined field_0x470;
    undefined field_0x471;
    undefined field_0x472;
    undefined field_0x473;
    undefined field_0x474;
    undefined field_0x475;
    undefined field_0x476;
    undefined field_0x477;
    undefined field_0x478;
    undefined field_0x479;
    undefined field_0x47a;
    undefined field_0x47b;
    undefined field_0x47c;
    undefined field_0x47d;
    undefined field_0x47e;
    undefined field_0x47f;
    undefined field_0x480;
    undefined field_0x481;
    undefined field_0x482;
    undefined field_0x483;
    undefined field_0x484;
    undefined field_0x485;
    undefined field_0x486;
    undefined field_0x487;
    undefined field_0x488;
    undefined field_0x489;
    undefined field_0x48a;
    undefined field_0x48b;
    undefined field_0x48c;
    undefined field_0x48d;
    undefined field_0x48e;
    undefined field_0x48f;
    undefined field_0x490;
    undefined field_0x491;
    undefined field_0x492;
    undefined field_0x493;
    undefined field_0x494;
    undefined field_0x495;
    undefined field_0x496;
    undefined field_0x497;
    undefined field_0x498;
    undefined field_0x499;
    undefined field_0x49a;
    undefined field_0x49b;
    int field_0x49c;
    undefined field_0x4a0;
    undefined field_0x4a1;
    undefined field_0x4a2;
    undefined field_0x4a3;
    undefined field_0x4a4;
    undefined field_0x4a5;
    undefined field_0x4a6;
    undefined field_0x4a7;
    undefined field_0x4a8;
    undefined field_0x4a9;
    undefined field_0x4aa;
    undefined field_0x4ab;
    undefined field_0x4ac;
    undefined field_0x4ad;
    undefined field_0x4ae;
    undefined field_0x4af;
    undefined field_0x4b0;
    undefined field_0x4b1;
    undefined field_0x4b2;
    undefined field_0x4b3;
    undefined field_0x4b4;
    undefined field_0x4b5;
    undefined field_0x4b6;
    undefined field_0x4b7;
    undefined field_0x4b8;
    undefined field_0x4b9;
    undefined field_0x4ba;
    undefined field_0x4bb;
    undefined field_0x4bc;
    undefined field_0x4bd;
    undefined field_0x4be;
    undefined field_0x4bf;
    undefined field_0x4c0;
    undefined field_0x4c1;
    undefined field_0x4c2;
    undefined field_0x4c3;
    undefined field_0x4c4;
    undefined field_0x4c5;
    undefined field_0x4c6;
    undefined field_0x4c7;
    undefined field_0x4c8;
    undefined field_0x4c9;
    undefined field_0x4ca;
    undefined field_0x4cb;
    undefined field_0x4cc;
    undefined field_0x4cd;
    undefined field_0x4ce;
    undefined field_0x4cf;
    undefined field_0x4d0;
    undefined field_0x4d1;
    undefined field_0x4d2;
    undefined field_0x4d3;
    undefined field_0x4d4;
    undefined field_0x4d5;
    undefined field_0x4d6;
    undefined field_0x4d7;
    undefined field_0x4d8;
    undefined field_0x4d9;
    undefined field_0x4da;
    undefined field_0x4db;
    undefined field_0x4dc;
    undefined field_0x4dd;
    undefined field_0x4de;
    undefined field_0x4df;
    undefined field_0x4e0;
    undefined field_0x4e1;
    undefined field_0x4e2;
    undefined field_0x4e3;
    undefined field_0x4e4;
    undefined field_0x4e5;
    undefined field_0x4e6;
    undefined field_0x4e7;
    undefined field_0x4e8;
    undefined field_0x4e9;
    undefined field_0x4ea;
    undefined field_0x4eb;
    undefined field_0x4ec;
    undefined field_0x4ed;
    undefined field_0x4ee;
    undefined field_0x4ef;
    undefined field_0x4f0;
    undefined field_0x4f1;
    undefined field_0x4f2;
    undefined field_0x4f3;
    undefined field_0x4f4;
    undefined field_0x4f5;
    undefined field_0x4f6;
    undefined field_0x4f7;
    undefined field_0x4f8;
    undefined field_0x4f9;
    undefined field_0x4fa;
    undefined field_0x4fb;
    undefined field_0x4fc;
    undefined field_0x4fd;
    undefined field_0x4fe;
    undefined field_0x4ff;
    undefined field_0x500;
    undefined field_0x501;
    undefined field_0x502;
    undefined field_0x503;
    undefined field_0x504;
    undefined field_0x505;
    undefined field_0x506;
    undefined field_0x507;
    undefined field_0x508;
    undefined field_0x509;
    undefined field_0x50a;
    undefined field_0x50b;
    undefined field_0x50c;
    undefined field_0x50d;
    undefined field_0x50e;
    undefined field_0x50f;
    undefined field_0x510;
    undefined field_0x511;
    undefined field_0x512;
    undefined field_0x513;
    undefined field_0x514;
    undefined field_0x515;
    undefined field_0x516;
    undefined field_0x517;
    undefined field_0x518;
    undefined field_0x519;
    undefined field_0x51a;
    undefined field_0x51b;
    undefined field_0x51c;
    undefined field_0x51d;
    undefined field_0x51e;
    undefined field_0x51f;
    undefined field_0x520;
    undefined field_0x521;
    undefined field_0x522;
    undefined field_0x523;
    undefined field_0x524;
    undefined field_0x525;
    undefined field_0x526;
    undefined field_0x527;
    undefined field_0x528;
    undefined field_0x529;
    undefined field_0x52a;
    undefined field_0x52b;
    undefined field_0x52c;
    undefined field_0x52d;
    undefined field_0x52e;
    undefined field_0x52f;
    undefined field_0x530;
    undefined field_0x531;
    undefined field_0x532;
    undefined field_0x533;
    undefined field_0x534;
    undefined field_0x535;
    undefined field_0x536;
    undefined field_0x537;
    undefined field_0x538;
    undefined field_0x539;
    undefined field_0x53a;
    undefined field_0x53b;
    undefined field_0x53c;
    undefined field_0x53d;
    undefined field_0x53e;
    undefined field_0x53f;
    undefined field_0x540;
    undefined field_0x541;
    undefined field_0x542;
    undefined field_0x543;
    undefined field_0x544;
    undefined field_0x545;
    undefined field_0x546;
    undefined field_0x547;
    undefined field_0x548;
    undefined field_0x549;
    undefined field_0x54a;
    undefined field_0x54b;
    undefined field_0x54c;
    undefined field_0x54d;
    undefined field_0x54e;
    undefined field_0x54f;
    undefined field_0x550;
    undefined field_0x551;
    undefined field_0x552;
    undefined field_0x553;
    undefined field_0x554;
    undefined field_0x555;
    undefined field_0x556;
    undefined field_0x557;
    undefined field_0x558;
    undefined field_0x559;
    undefined field_0x55a;
    undefined field_0x55b;
    undefined field_0x55c;
    undefined field_0x55d;
    undefined field_0x55e;
    undefined field_0x55f;
    undefined field_0x560;
    undefined field_0x561;
    undefined field_0x562;
    undefined field_0x563;
    undefined field_0x564;
    undefined field_0x565;
    undefined field_0x566;
    undefined field_0x567;
    undefined field_0x568;
    undefined field_0x569;
    undefined field_0x56a;
    undefined field_0x56b;
    undefined field_0x56c;
    undefined field_0x56d;
    undefined field_0x56e;
    undefined field_0x56f;
    undefined field_0x570;
    undefined field_0x571;
    undefined field_0x572;
    undefined field_0x573;
    int unk1;
};

typedef struct Police Police, *PPolice;

typedef struct SPoliceSub SPoliceSub, *PSPoliceSub;

typedef struct PedManager PedManager, *PPedManager;

struct PedManager {
    struct Ped * firstPedInArray;
    struct Ped * lastPedInArray;
    struct Ped peds[200]; /* Created by retype action */
    short MaybePedsInUse;
    undefined field_0x203aa;
    undefined field_0x203ab;
};

struct SPoliceSub {
    undefined field_0x0;
    undefined field_0x1;
    byte field_0x2;
    byte field_0x3;
    byte field_0x4;
    undefined field_0x5;
    undefined field_0x6;
    undefined field_0x7;
    undefined4 field_0x8;
    undefined4 field_0xc;
    struct PedManager * field_0x10;
    undefined4 field_0x14;
    undefined2 field_0x18;
    byte field_0x1a;
    undefined field_0x1b;
    undefined4 field_0x1c;
    undefined field_0x20;
    undefined field_0x21;
    undefined field_0x22;
    undefined field_0x23;
    undefined4 field_0x24;
    byte field_0x28;
    byte field_0x29;
    undefined2 field_0x2a;
    undefined2 field_0x2c;
    undefined field_0x2e;
    undefined field_0x2f;
    undefined4 field_0x30;
    byte field_0x34;
    undefined field_0x35;
    undefined field_0x36;
    undefined field_0x37;
};

struct Police {
    undefined field_0x0;
    undefined field_0x1;
    undefined field_0x2;
    undefined field_0x3;
    struct SPoliceSub arr20[20];
    byte arr124_4[124][4];
    int copLevel;
    byte field_0x658;
    byte field_0x659;
    undefined field_0x65a;
    undefined field_0x65b;
    int field_0x65c;
    undefined field_0x660[333];
    byte numPolicePedsInRangeScreen;
    undefined field_0x7ae;
    undefined field_0x7af;
    undefined field_0x7b0;
    undefined field_0x7b1;
    undefined field_0x7b2;
    undefined field_0x7b3;
    undefined field_0x7b4;
    undefined field_0x7b5;
    undefined field_0x7b6;
    undefined field_0x7b7;
};

typedef enum MAIN_MENU_SOUND {
    BACK_SOUND=5,
    CHEAT_SOUND=9,
    ENTER_SOUND=6,
    LEFT_RIGHT_SOUND=3
} MAIN_MENU_SOUND;

typedef enum PED_BIT_STATE2 {
    PED_BIT_STATE2_FIRING_FROM_GUN=2,
    PED_BIT_STATE2_UNK_4_POLICE=4,
    PED_BIT_STATE2_UNK_5=5,
    PED_BIT_STATE2_UNK_6=6
} PED_BIT_STATE2;

typedef uchar MissionCode[3072];

typedef struct SCR_CAR_DATA_DEC SCR_CAR_DATA_DEC, *PSCR_CAR_DATA_DEC;

typedef struct SCR_CMD_HEADER SCR_CMD_HEADER, *PSCR_CMD_HEADER;

typedef struct SCR_XYZ_f SCR_XYZ_f, *PSCR_XYZ_f;

typedef ushort Uint16;

typedef enum SCR_CMD_TYPE {
    SCRCMD_0=0,
    SCRCMD_1=1,
    SCRCMD_2=2,
    SCRCMD_3=3,
    SCRCMD_4=4,
    SCRCMD_ADD_GROUP=153,
    SCRCMD_ADD_NEW_BLOCK=182,
    SCRCMD_ADD_PATROL_POINT=205,
    SCRCMD_ADD_SCORE1=141,
    SCRCMD_ALT_WANTED_LEVEL=164,
    SCRCMD_AND=72,
    SCRCMD_ANSWER_PHONE=168,
    SCRCMD_ARROW_COLOUR=115,
    SCRCMD_ARROW_DEC=23,
    SCRCMD_CAR_DAMAGE_POS=200,
    SCRCMD_CAR_DEC=9,
    SCRCMD_CAR_DECSET_2D=10,
    SCRCMD_CAR_DECSET_2D_STR=12,
    SCRCMD_CAR_DECSET_3D=11,
    SCRCMD_CAR_DECSET_3D_STR=13,
    SCRCMD_CAR_DRIVE_AWAY=175,
    SCRCMD_CAR_IN_AIR=191,
    SCRCMD_CAR_SUNK=190,
    SCRCMD_CAR_WRECK_IN_LOCATION=189,
    SCRCMD_CHANGE_BLOCK_LID=186,
    SCRCMD_CHANGE_BLOCK_SIDE=185,
    SCRCMD_CHANGE_BLOCK_TYPE=187,
    SCRCMD_CHANGE_CAR_REMAP=155,
    SCRCMD_CHANGE_CHAR_REMAP=156,
    SCRCMD_CHANGE_COLOUR=221,
    SCRCMD_CHANGE_INTENSITY=220,
    SCRCMD_CHANGE_RADIUS=222,
    SCRCMD_CHAR_DEC=6,
    SCRCMD_CHAR_DECSET_2D=7,
    SCRCMD_CHAR_DECSET_3D=8,
    SCRCMD_CHAR_IN_AIR=202,
    SCRCMD_CHAR_SUNK=203,
    SCRCMD_CHAR_TO_BACKDOOR=171,
    SCRCMD_CHAR_TO_DRIVE_CAR=167,
    SCRCMD_CHECK_CAR_BOTH=159,
    SCRCMD_CHECK_CAR_DAMAGE=129,
    SCRCMD_CHECK_CAR_DRIVER=130,
    SCRCMD_CHECK_CAR_MODEL=157,
    SCRCMD_CHECK_CAR_REMAP=158,
    SCRCMD_CHECK_CAR_SPEED=208,
    SCRCMD_CHECK_HEALTH=126,
    SCRCMD_CHECK_MULT=196,
    SCRCMD_CHECK_NUM_LIVES=192,
    SCRCMD_CHECK_PHONE=227,
    SCRCMD_CHECK_PHONETIMER=228,
    SCRCMD_CHECK_RESPECT_GREATER=198,
    SCRCMD_CHECK_RESPECT_IS=231,
    SCRCMD_CHECK_RESPECT_LESS=199,
    SCRCMD_CHECK_SCORE=194,
    SCRCMD_CLEAR_NO_COLLIDE=174,
    SCRCMD_CLEAR_TIMERS=120,
    SCRCMD_CLEAR_WANTED_LEVEL=163,
    SCRCMD_CLOSE_DOOR=178,
    SCRCMD_CONVEYOR_DEC=25,
    SCRCMD_CONVEYOR_DECSET1=26,
    SCRCMD_CONVEYOR_DECSET2=27,
    SCRCMD_COUNTER=21,
    SCRCMD_COUNTER_SET=22,
    SCRCMD_CRANE2TARGET_DEC=39,
    SCRCMD_CRANE_BASIC_DEC=37,
    SCRCMD_CRANE_DEC=36,
    SCRCMD_CRANE_TARGET_DEC=38,
    SCRCMD_CREATE_CAR_2D=43,
    SCRCMD_CREATE_CAR_2D_STR=45,
    SCRCMD_CREATE_CAR_3D=44,
    SCRCMD_CREATE_CAR_3D_STR=46,
    SCRCMD_CREATE_CHAR_2D=41,
    SCRCMD_CREATE_CHAR_3D=42,
    SCRCMD_CREATE_CONVEYOR_2D=53,
    SCRCMD_CREATE_CONVEYOR_3D=54,
    SCRCMD_CREATE_DESTRUCTOR_2D=57,
    SCRCMD_CREATE_DESTRUCTOR_3D=58,
    SCRCMD_CREATE_GENERATOR_2D=55,
    SCRCMD_CREATE_GENERATOR_3D=56,
    SCRCMD_CREATE_LIGHT1=219,
    SCRCMD_CREATE_OBJ_2D=47,
    SCRCMD_CREATE_OBJ_2D_INT=50,
    SCRCMD_CREATE_OBJ_2D_STR=52,
    SCRCMD_CREATE_OBJ_3D=48,
    SCRCMD_CREATE_OBJ_3D_INT=49,
    SCRCMD_CREATE_OBJ_3D_STR=51,
    SCRCMD_CREATE_THREAD=61,
    SCRCMD_CRUSHER_BASIC=40,
    SCRCMD_DECREMENT=97,
    SCRCMD_DELAY=162,
    SCRCMD_DELAY_HERE=161,
    SCRCMD_DELETE_ITEM=140,
    SCRCMD_DESTRUCTOR_DEC=33,
    SCRCMD_DESTRUCTOR_DECSET1=34,
    SCRCMD_DESTRUCTOR_DECSET2=35,
    SCRCMD_DISABLE_THREAD=216,
    SCRCMD_DISPLAY_BRIEF=118,
    SCRCMD_DISPLAY_MESSAGE=117,
    SCRCMD_DISPLAY_TIMER=119,
    SCRCMD_DO_WHILE=66,
    SCRCMD_DRIVER_OUT_CAR=166,
    SCRCMD_ELSE=76,
    SCRCMD_ENABLE_THREAD=215,
    SCRCMD_EXPLODE=142,
    SCRCMD_EXPLODE_BUILDING=143,
    SCRCMD_EXPLODE_ITEM=144,
    SCRCMD_FORWARD_DECLARE=99,
    SCRCMD_FOR_LOOP=65,
    SCRCMD_FUNCTION=67,
    SCRCMD_GENERATOR_DEC=28,
    SCRCMD_GENERATOR_DECSET1=29,
    SCRCMD_GENERATOR_DECSET2=30,
    SCRCMD_GENERATOR_DECSET3=31,
    SCRCMD_GENERATOR_DECSET4=32,
    SCRCMD_GET_CAR_FROM_CRANE=188,
    SCRCMD_GET_CAR_SPEED=206,
    SCRCMD_GET_CHAR_CAR_SPEED=207,
    SCRCMD_GET_MAX_SPEED=209,
    SCRCMD_GET_MULT=197,
    SCRCMD_GET_NUM_LIVES=193,
    SCRCMD_GET_PASSENGER_NUM=201,
    SCRCMD_GET_SCORE=195,
    SCRCMD_GIVE_DRIVER_BRAKE=170,
    SCRCMD_GIVE_WEAPON1=138,
    SCRCMD_GOSUB=78,
    SCRCMD_GOTO=77,
    SCRCMD_HAS_CHAR_DIED=127,
    SCRCMD_IF=74,
    SCRCMD_IF_JUMP=98,
    SCRCMD_INCREMENT=96,
    SCRCMD_IS_CAR_IN_BLOCK=139,
    SCRCMD_IS_CAR_WRECKED=154,
    SCRCMD_IS_CHAR_FIRE_ONSCREEN=165,
    SCRCMD_IS_CHAR_FIRING_AREA=176,
    SCRCMD_IS_CHAR_IN_ANY_CAR=123,
    SCRCMD_IS_CHAR_IN_CAR=121,
    SCRCMD_IS_CHAR_IN_MODEL=122,
    SCRCMD_IS_CHAR_OBJ_FAIL=135,
    SCRCMD_IS_CHAR_OBJ_PASS=134,
    SCRCMD_IS_CHAR_STOPPED=124,
    SCRCMD_IS_CHAR_STUNNED=125,
    SCRCMD_IS_ITEM_ONSCREEN=160,
    SCRCMD_I_MINUS_S=83,
    SCRCMD_I_PLUS_S=80,
    SCRCMD_LAST_WEAPON_HIT=204,
    SCRCMD_LEVELEND=60,
    SCRCMD_LEVELSTART=59,
    SCRCMD_LIGHT_DEC=217,
    SCRCMD_LIGHT_DECSET1=218,
    SCRCMD_LOCATE_CHAR_ANY=145,
    SCRCMD_LOCATE_CHAR_BY_CAR=147,
    SCRCMD_LOCATE_CHAR_ONFOOT=146,
    SCRCMD_LOWER_LEVEL=184,
    SCRCMD_MAKE_CAR_DUMMY=100,
    SCRCMD_MAP_ZONE1=101,
    SCRCMD_MAP_ZONE_SET=102,
    SCRCMD_NOT=71,
    SCRCMD_OBJ_DEC=14,
    SCRCMD_OBJ_DECSET_2D=15,
    SCRCMD_OBJ_DECSET_2D_INT=17,
    SCRCMD_OBJ_DECSET_2D_STR=19,
    SCRCMD_OBJ_DECSET_3D=16,
    SCRCMD_OBJ_DECSET_3D_INT=18,
    SCRCMD_OBJ_DECSET_3D_STR=20,
    SCRCMD_OPEN_DOOR=177,
    SCRCMD_OR=73,
    SCRCMD_PLAYER_PED=5,
    SCRCMD_PLAY_SOUND=172,
    SCRCMD_POINT_ARROW_3D=114,
    SCRCMD_POINT_ARROW_AT=113,
    SCRCMD_REMOVE_ARROW=116,
    SCRCMD_REMOVE_BLOCK=183,
    SCRCMD_RETURN=68,
    SCRCMD_ROAD_ON_OFF=181,
    SCRCMD_SEND_CAR_TO_BLOCK=169,
    SCRCMD_SEND_CHAR_CAR=137,
    SCRCMD_SEND_CHAR_FOOT=136,
    SCRCMD_SET=85,
    SCRCMD_SET_AMBIENT=226,
    SCRCMD_SET_BAD_CAR=105,
    SCRCMD_SET_CARTHIEF=109,
    SCRCMD_SET_CAR_DENSITY=103,
    SCRCMD_SET_CHAR_OBJ1=131,
    SCRCMD_SET_CHAR_OBJ2=132,
    SCRCMD_SET_CHAR_OBJ3=133,
    SCRCMD_SET_CHAR_RESPECT=225,
    SCRCMD_SET_DOOR_AUTO=179,
    SCRCMD_SET_DOOR_INFO=230,
    SCRCMD_SET_DOOR_MANUAL=180,
    SCRCMD_SET_ELVIS=110,
    SCRCMD_SET_GANG=111,
    SCRCMD_SET_GANG_INFO1=223,
    SCRCMD_SET_GANG_RESPECT=224,
    SCRCMD_SET_GOOD_CAR=104,
    SCRCMD_SET_MUGGER=108,
    SCRCMD_SET_NO_COLLIDE=173,
    SCRCMD_SET_PED_DENSITY=107,
    SCRCMD_SET_POLICE_CAR=106,
    SCRCMD_SET_POLICE_PED=112,
    SCRCMD_SET_THREAT_REACT=152,
    SCRCMD_SET_THREAT_SEARCH=151,
    SCRCMD_START_EXEC=63,
    SCRCMD_STOP_EXEC=64,
    SCRCMD_STOP_LOCATE_CHAR_ANY=148,
    SCRCMD_STOP_LOCATE_CHAR_CAR=150,
    SCRCMD_STOP_LOCATE_CHAR_FOOT=149,
    SCRCMD_STOP_PHONE_RING=229,
    SCRCMD_STOP_THREAD=62,
    SCRCMD_STORE_CAR_INFO=128,
    SCRCMD_S_EQUAL_I=94,
    SCRCMD_S_EQUAL_S=95,
    SCRCMD_S_GEQUAL_I=92,
    SCRCMD_S_GEQUAL_S=93,
    SCRCMD_S_GREATER_I=90,
    SCRCMD_S_GREATER_S=91,
    SCRCMD_S_LEQUAL_I=88,
    SCRCMD_S_LEQUAL_S=89,
    SCRCMD_S_LESS_I=86,
    SCRCMD_S_LESS_S=87,
    SCRCMD_S_MINUS_I=82,
    SCRCMD_S_MINUS_S=84,
    SCRCMD_S_PLUS_I=79,
    SCRCMD_S_PLUS_S=81,
    SCRCMD_THEN=75,
    SCRCMD_THREAD_DECLARE1=210,
    SCRCMD_THREAD_DECLARE2=211,
    SCRCMD_THREAD_DECLARE3=212,
    SCRCMD_THREAD_DECLARE4=213,
    SCRCMD_THREAD_DECLARE5=214,
    SCRCMD_THREAD_ID=24,
    SCRCMD_WHILE=69,
    SCRCMD_WHILE_EXEC=70
} SCR_CMD_TYPE;

typedef int Sint32;

typedef Sint32 SCR_f;

struct SCR_CMD_HEADER {
    Uint16 cmd_this;
    enum SCR_CMD_TYPE type;
    Uint16 cmd_next;
    Uint16 return_value;
};

struct SCR_XYZ_f {
    SCR_f x;
    SCR_f y;
    SCR_f z;
};

struct SCR_CAR_DATA_DEC {
    struct SCR_CMD_HEADER head;
    short varname;
    short field_0xa;
    struct SCR_XYZ_f pos;
    short rot;
    short remap;
    ushort carId;
    ushort trailerId; /* 0xFFFF - no trailer */
};

typedef struct SCR_CMD_SIX_PARAMS SCR_CMD_SIX_PARAMS, *PSCR_CMD_SIX_PARAMS;

typedef union U_SCR_TWO_PARAMS U_SCR_TWO_PARAMS, *PU_SCR_TWO_PARAMS;

typedef struct SCR_TWO_SHORTS SCR_TWO_SHORTS, *PSCR_TWO_SHORTS;

struct SCR_TWO_SHORTS {
    short s1;
    short s2;
};

union U_SCR_TWO_PARAMS {
    struct SCR_TWO_SHORTS shorts;
    int i32val;
};

struct SCR_CMD_SIX_PARAMS {
    struct SCR_CMD_HEADER header;
    union U_SCR_TWO_PARAMS params12;
    union U_SCR_TWO_PARAMS params34;
    union U_SCR_TWO_PARAMS params56;
};

typedef struct SCR_PLAYER_PED SCR_PLAYER_PED, *PSCR_PLAYER_PED;

typedef short Sint16;

struct SCR_PLAYER_PED {
    struct SCR_CMD_HEADER header;
    struct Ped * ped;
    struct SCR_XYZ_f pos;
    Uint16 rot;
    Sint16 remap;
};

typedef enum SCR_STRING_DATA_TYPE {
    FILE_NAME_MISSIONS=21,
    GANG_NAME=17,
    ZONE_NAME=10
} SCR_STRING_DATA_TYPE;

typedef struct SCR_STRING_HEADER SCR_STRING_HEADER, *PSCR_STRING_HEADER;

typedef uchar Uint8;

struct SCR_STRING_HEADER {
    Uint16 str_id;
    Uint16 stringIndex;
    enum SCR_STRING_DATA_TYPE datatype;
    undefined field_0x5;
    Uint16 unk2;
    Uint8 len;
    char textStart;
};

typedef struct SCR_STRINGS SCR_STRINGS, *PSCR_STRINGS;

struct SCR_STRINGS {
    ushort len;
    byte buf[5118];
};

typedef struct ScriptFunctionsAddrTable ScriptFunctionsAddrTable, *PScriptFunctionsAddrTable;

typedef void * LPVOID;

struct ScriptFunctionsAddrTable {
    LPVOID * field_0x0;
    LPVOID * field_0x4;
    LPVOID * field_0x8;
    LPVOID * field_0xc;
    LPVOID * field_0x10;
    LPVOID * field_0x14;
    LPVOID * field_0x18;
    LPVOID * field_0x1c;
    LPVOID * field_0x20;
    LPVOID * field_0x24;
    LPVOID * field_0x28;
    LPVOID * field_0x2c;
    LPVOID * field_0x30;
    LPVOID * field_0x34;
    LPVOID * field_0x38;
    LPVOID * field_0x3c;
    LPVOID * field_0x40;
    LPVOID * field_0x44;
    LPVOID * field_0x48;
    LPVOID * field_0x4c;
    LPVOID * field_0x50;
    LPVOID * field_0x54;
    LPVOID * field_0x58;
    LPVOID * field_0x5c;
    LPVOID * field_0x60;
    LPVOID * field_0x64;
    LPVOID * field_0x68;
    LPVOID * field_0x6c;
    LPVOID * field_0x70;
    LPVOID * field_0x74;
    LPVOID * field_0x78;
    LPVOID * field_0x7c;
    LPVOID * field_0x80;
    LPVOID * field_0x84;
    LPVOID * field_0x88;
    LPVOID * field_0x8c;
    LPVOID * field_0x90;
    LPVOID * field_0x94;
    LPVOID * field_0x98;
    LPVOID * field_0x9c;
    LPVOID * field_0xa0;
    LPVOID * field_0xa4;
    LPVOID * field_0xa8;
    LPVOID * field_0xac;
    LPVOID * field_0xb0;
    LPVOID * field_0xb4;
    LPVOID * field_0xb8;
    LPVOID * field_0xbc;
    LPVOID * field_0xc0;
    LPVOID * field_0xc4;
    LPVOID * field_0xc8;
    LPVOID * field_0xcc;
    LPVOID * field_0xd0;
    LPVOID * field_0xd4;
    LPVOID * field_0xd8;
    LPVOID * field_0xdc;
    LPVOID * field_0xe0;
    LPVOID * field_0xe4;
    LPVOID * field_0xe8;
    LPVOID * field_0xec;
    LPVOID * field_0xf0;
    LPVOID * field_0xf4;
    LPVOID * field_0xf8;
    LPVOID * field_0xfc;
    LPVOID * field_0x100;
    LPVOID * field_0x104;
    LPVOID * field_0x108;
    LPVOID * field_0x10c;
    LPVOID * field_0x110;
    LPVOID * field_0x114;
    LPVOID * field_0x118;
    LPVOID * field_0x11c;
    LPVOID * field_0x120;
    LPVOID * field_0x124;
    LPVOID * field_0x128;
    LPVOID * field_0x12c;
    LPVOID * field_0x130;
    LPVOID * field_0x134;
    LPVOID * field_0x138;
    LPVOID * field_0x13c;
    LPVOID * field_0x140;
    LPVOID * field_0x144;
    LPVOID * field_0x148;
    LPVOID * field_0x14c;
    LPVOID * field_0x150;
    LPVOID * field_0x154;
    LPVOID * field_0x158;
    LPVOID * field_0x15c;
    LPVOID * field_0x160;
    LPVOID * field_0x164;
    LPVOID * field_0x168;
    LPVOID * field_0x16c;
    LPVOID * field_0x170;
    LPVOID * field_0x174;
    LPVOID * field_0x178;
    LPVOID * field_0x17c;
    LPVOID * field_0x180;
    LPVOID * field_0x184;
    LPVOID * field_0x188;
    LPVOID * field_0x18c;
    LPVOID * field_0x190;
    LPVOID * field_0x194;
    LPVOID * field_0x198;
    LPVOID * field_0x19c;
    LPVOID * field_0x1a0;
    LPVOID * field_0x1a4;
    LPVOID * field_0x1a8;
    LPVOID * field_0x1ac;
    LPVOID * field_0x1b0;
    LPVOID * field_0x1b4;
    LPVOID * field_0x1b8;
    LPVOID * field_0x1bc;
    LPVOID * field_0x1c0;
    LPVOID * field_0x1c4;
    LPVOID * field_0x1c8;
    LPVOID * field_0x1cc;
    LPVOID * field_0x1d0;
    LPVOID * field_0x1d4;
    LPVOID * field_0x1d8;
    LPVOID * field_0x1dc;
    LPVOID * field_0x1e0;
    LPVOID * field_0x1e4;
    LPVOID * field_0x1e8;
    LPVOID * field_0x1ec;
    LPVOID * field_0x1f0;
    LPVOID * field_0x1f4;
    LPVOID * field_0x1f8;
    LPVOID * field_0x1fc;
    LPVOID * field_0x200;
    LPVOID * field_0x204;
    LPVOID * field_0x208;
    LPVOID * field_0x20c;
    LPVOID * field_0x210;
    LPVOID * field_0x214;
    LPVOID * field_0x218;
    LPVOID * field_0x21c;
    LPVOID * field_0x220;
    LPVOID * field_0x224;
    LPVOID * field_0x228;
    LPVOID * field_0x22c;
    LPVOID * field_0x230;
    LPVOID * field_0x234;
    LPVOID * field_0x238;
    LPVOID * field_0x23c;
    LPVOID * field_0x240;
    LPVOID * field_0x244;
    LPVOID * field_0x248;
    LPVOID * field_0x24c;
    LPVOID * field_0x250;
    LPVOID * field_0x254;
    LPVOID * field_0x258;
    LPVOID * field_0x25c;
    LPVOID * field_0x260;
    LPVOID * field_0x264;
    LPVOID * field_0x268;
    LPVOID * field_0x26c;
    LPVOID * field_0x270;
    LPVOID * field_0x274;
    LPVOID * field_0x278;
    LPVOID * field_0x27c;
    LPVOID * field_0x280;
    LPVOID * field_0x284;
    LPVOID * field_0x288;
    LPVOID * field_0x28c;
    LPVOID * field_0x290;
    LPVOID * field_0x294;
    LPVOID * field_0x298;
    LPVOID * field_0x29c;
    LPVOID * field_0x2a0;
    LPVOID * field_0x2a4;
    LPVOID * field_0x2a8;
    LPVOID * field_0x2ac;
    LPVOID * field_0x2b0;
    LPVOID * field_0x2b4;
    LPVOID * field_0x2b8;
    LPVOID * field_0x2bc;
    LPVOID * field_0x2c0;
    LPVOID * field_0x2c4;
    LPVOID * field_0x2c8;
    LPVOID * field_0x2cc;
    LPVOID * field_0x2d0;
    LPVOID * field_0x2d4;
    LPVOID * field_0x2d8;
    LPVOID * field_0x2dc;
    LPVOID * field_0x2e0;
    LPVOID * field_0x2e4;
    LPVOID * field_0x2e8;
    LPVOID * field_0x2ec;
    LPVOID * field_0x2f0;
    LPVOID * field_0x2f4;
    LPVOID * field_0x2f8;
    LPVOID * field_0x2fc;
    LPVOID * field_0x300;
};

typedef struct AllCarsInfo AllCarsInfo, *PAllCarsInfo;

typedef struct CarInfo CarInfo, *PCarInfo;

typedef enum CarInfoFlags {
    artic_cab=8,
    emerg_lights=2,
    forhire_lights=32,
    ped_jump=1,
    rear_emerg_lights=128,
    roof_decal=64,
    roof_lights=4,
    trailer=16
} CarInfoFlags;

typedef enum CarInfoFlags2 {
    collide_over=1,
    popup=2
} CarInfoFlags2;

typedef struct DoorInfo DoorInfo, *PDoorInfo;

struct DoorInfo {
    undefined field_0x0;
    undefined field_0x1;
};

struct CarInfo {
    undefined field_0x0;
    undefined field_0x1;
    undefined field_0x2;
    undefined field_0x3;
    undefined field_0x4;
    undefined field_0x5;
    byte wreck;
    byte rating;
    undefined field_0x8;
    undefined field_0x9;
    undefined field_0xa;
    undefined field_0xb;
    enum CarInfoFlags info_flags;
    enum CarInfoFlags2 info_flags_2;
    undefined field_0xe;
    undefined field_0xf;
    undefined field_0x10;
    undefined field_0x11;
    undefined field_0x12;
    undefined field_0x13;
    undefined field_0x14;
    undefined field_0x15;
    undefined field_0x16;
    undefined field_0x17;
    undefined field_0x18;
    undefined field_0x19;
    undefined field_0x1a;
    undefined field_0x1b;
    undefined field_0x1c;
    undefined field_0x1d;
    undefined field_0x1e;
    undefined field_0x1f;
    undefined field_0x20;
    undefined field_0x21;
    undefined field_0x22;
    undefined field_0x23;
    undefined field_0x24;
    struct DoorInfo doors[5];
};

struct AllCarsInfo {
    struct CarInfo * cars[256];
    undefined field_0x400;
    undefined field_0x401;
    undefined field_0x402;
    undefined field_0x403;
};

typedef struct ChunkHeader ChunkHeader, *PChunkHeader;

typedef uint UINT32;

struct ChunkHeader {
    char chunk_type[4];
    UINT32 chunk_size;
};

typedef struct PaletteBase PaletteBase, *PPaletteBase;

struct PaletteBase {
    ushort tile;
    ushort sprite;
    ushort car_remap;
    ushort ped_remap;
    ushort code_obj_remap;
    ushort map_obj_remap;
    ushort user_remap;
    ushort font_remap;
};

typedef struct PaletteIndex PaletteIndex, *PPaletteIndex;

struct PaletteIndex {
    Uint16 PaletteIndexArr[16384];
};

typedef struct SpriteBase SpriteBase, *PSpriteBase;

struct SpriteBase {
    ushort car;
    ushort ped;
    ushort code_obj;
    ushort map_obj;
    ushort user;
    ushort font;
};

typedef struct SpriteEntry SpriteEntry, *PSpriteEntry;

struct SpriteEntry {
    void * ptr;
    undefined field_0x4;
    undefined field_0x5;
    uint16 pad;
};

typedef struct Style_S3 Style_S3, *PStyle_S3;

struct Style_S3 {
    short countOfpalettes;
    short relToFontBase;
    short spriteIndexRel;
    short relToMapObjectInfo;
    short size_physical_palette;
    undefined field_0xa;
    undefined field_0xb;
    struct PaletteBase * paletteBase2;
    struct PaletteBase * paletteBase;
    struct SpriteBase * spriteBase2;
    struct SpriteBase * spriteBase;
    void * fontBase;
    void * spriteIndex;
    void * map_object_info;
    struct PaletteIndex * palleteIndex;
    void * physical_palettes;
    int i9;
    void * sprite_graphics;
    undefined4 i13;
    int i10;
    undefined4 i21;
    undefined4 i11;
    undefined4 i14;
    undefined4 i18;
    undefined4 i15;
    undefined4 i20;
    void * car_info_chunk;
    struct AllCarsInfo * allCarsInfo;
    undefined4 i19;
    int i1;
    short short1;
    byte b1;
    undefined field_0x6b;
    int iArr1024[1024];
};

typedef struct StyleFileHeader StyleFileHeader, *PStyleFileHeader;

struct StyleFileHeader {
    char file_type[4];
    Uint16 version_code;
};

typedef struct MaybeWeaponStruct MaybeWeaponStruct, *PMaybeWeaponStruct;

struct MaybeWeaponStruct {
    uint unknownLowValueSomeKindOfType;
    byte f1;
    undefined field_0x5;
    undefined field_0x6;
    undefined field_0x7;
    undefined4 f2;
    struct MaybeWeaponStruct * prev;
    undefined field_0x10;
    undefined field_0x11;
    undefined field_0x12;
    undefined field_0x13;
    undefined4 field_0x14;
    undefined field_0x18;
    undefined field_0x19;
    undefined field_0x1a;
    undefined field_0x1b;
    undefined4 field_0x1c;
    byte field_0x20;
    byte field_0x21;
    undefined field_0x22;
    undefined field_0x23;
    undefined4 field_0x24;
    undefined4 field_0x28;
    byte field_0x2c;
};

typedef struct WeaponRelStruct WeaponRelStruct, *PWeaponRelStruct;

struct WeaponRelStruct {
    undefined field_0x0;
    undefined field_0x1;
    undefined field_0x2;
    undefined field_0x3;
    struct WEAPON_STRUCT weapons[36];
};

typedef struct LocaleSettings LocaleSettings, *PLocaleSettings;

typedef struct S2 S2, *PS2;

struct S2 {
    int f1;
    int f2;
};

struct LocaleSettings {
    void * ptrToLocales;
    int length; /* Created by retype action */
    struct S2 s2;
    char language; /* Created by retype action */
};

typedef struct Object Object, *PObject;

struct Object {
    int field_0x0;
    int field_0x4;
    int field_0x8;
    int field_0xc;
    int field_0x10;
    int field_0x14;
    byte field_0x18;
    undefined field_0x19;
    undefined field_0x1a;
    undefined field_0x1b;
    int field_0x1c;
    int field_0x20;
    undefined field_0x24;
    undefined field_0x25;
    undefined field_0x26;
    undefined field_0x27;
    undefined field_0x28;
    undefined field_0x29;
    undefined field_0x2a;
    undefined field_0x2b;
    undefined field_0x2c;
    undefined field_0x2d;
    undefined field_0x2e;
    undefined field_0x2f;
    undefined field_0x30;
    undefined field_0x31;
    undefined field_0x32;
    undefined field_0x33;
    undefined field_0x34;
    undefined field_0x35;
    undefined field_0x36;
    undefined field_0x37;
    undefined field_0x38;
    undefined field_0x39;
    undefined field_0x3a;
    undefined field_0x3b;
    undefined field_0x3c;
    undefined field_0x3d;
    undefined field_0x3e;
    undefined field_0x3f;
    undefined field_0x40;
    undefined field_0x41;
    undefined field_0x42;
    undefined field_0x43;
    undefined field_0x44;
    undefined field_0x45;
    undefined field_0x46;
    undefined field_0x47;
    undefined field_0x48;
    undefined field_0x49;
    undefined field_0x4a;
    undefined field_0x4b;
    undefined field_0x4c;
    undefined field_0x4d;
    undefined field_0x4e;
    undefined field_0x4f;
    undefined field_0x50;
    undefined field_0x51;
    undefined field_0x52;
    undefined field_0x53;
    int field_0x54;
    struct Pos * field_0x58;
};

typedef struct PositionsArray_S21 PositionsArray_S21, *PPositionsArray_S21;

struct PositionsArray_S21 {
    struct Pos * last;
    struct Pos arr[5031];
};

typedef struct S10 S10, *PS10;

struct S10 {
    undefined field_0x0[46];
    char field_0x2e;
    undefined field_0x2f[29];
    void * field_0x4c;
    undefined field_0x50[10000];
    void * field_0x2760;
    undefined field_0x2764[81];
    undefined1 displayDebugPedInfo; /* Created by retype action */
    undefined field_0x27b6[158];
    undefined1 ptrToSomeStructRelToBIG_LABEL; /* Created by retype action */
    undefined field_0x2855[671];
    int text_speed;
};

typedef struct S11 S11, *PS11;

struct S11 {
    void * field_0x0;
    void * field_0x4;
    undefined field_0x8[792];
    int field_0x320;
    undefined field_0x324;
    undefined field_0x325;
    undefined field_0x326;
    undefined field_0x327;
    undefined4 field_0x328;
    int len;
    void * ptrRelToMap;
    void * probablyArray;
    undefined4 field_0x338;
    undefined4 field_0x33c;
    undefined4 field_0x340;
    undefined4 field_0x344;
    undefined4 field_0x348;
    undefined4 field_0x34c;
    undefined4 field_0x350;
    undefined4 field_0x354;
    undefined4 field_0x358;
    undefined4 field_0x35c;
    undefined4 field_0x360;
    ushort lenOrCounter;
    undefined2 field_0x366;
    byte field_0x368;
    byte field_0x369;
    byte field_0x36a;
    byte field_0x36b;
    byte field_0x36c;
    byte field_0x36d;
    byte field_0x36e;
    byte field_0x36f;
};

typedef struct S12 S12, *PS12;

struct S12 {
    uint bitMask;
    undefined4 field_0x4;
    struct S12 * ptrToS12;
    byte field_0xc;
    byte field_0xd;
    byte field_0xe;
    byte field_0xf;
    byte field_0x10;
    byte field_0x11;
    byte field_0x12;
    byte field_0x13;
    byte field_0x14;
    byte field_0x15;
    byte field_0x16;
    byte field_0x17;
    byte field_0x18;
    byte field_0x19;
    byte field_0x1a;
    byte field_0x1b;
    undefined field_0x1c[12000];
    int field_0x2efc;
    int field_0x2f00;
};

typedef struct S13 S13, *PS13;

struct S13 { /* Display.cpp */
    int field_0x0[7];
};

typedef struct S14 S14, *PS14;

typedef struct S14_sub1 S14_sub1, *PS14_sub1;

struct S14_sub1 {
    int arr30i[30];
    int f1;
    int f2;
};

struct S14 {
    int field_0x0[2];
    int field_0x8[2];
    int field_0x10[2];
    int field_0x18[2];
    int field_0x20[2];
    struct S14_sub1 field_0x28;
    struct S14_sub1 field_0xa8;
    struct S14_sub1 field_0x128;
    struct S14_sub1 field_0x1a8;
    struct S14_sub1 field_0x228;
    undefined field_0x2a8[2000];
    int field_0xa78;
    int field_0xa7c;
};

typedef struct S15_script S15_script, *PS15_script;

typedef struct Script4k Script4k, *PScript4k;

struct Script4k {
    ushort numOfStrings;
    undefined field_0x2;
    undefined field_0x3;
    struct SCR_STRING_HEADER * strings[999];
};

struct S15_script { /* Map or something related to missions */
    short f0;
    undefined field_0x2;
    undefined field_0x3;
    int arr96i[96];
    short field_0x184;
    undefined field_0x186;
    undefined field_0x187;
    int arr60i[60];
    short field_0x278;
    undefined field_0x27a;
    undefined field_0x27b;
    int arr30i[30];
    undefined4 shouldBeEqTo1;
    undefined field_0x2f8;
    undefined field_0x2f9;
    undefined field_0x2fa;
    undefined field_0x2fb;
    undefined field_0x2fc;
    undefined field_0x2fd;
    undefined field_0x2fe;
    undefined field_0x2ff;
    undefined field_0x300;
    undefined field_0x301;
    undefined field_0x302;
    undefined field_0x303;
    undefined field_0x304;
    undefined field_0x305;
    undefined field_0x306;
    undefined field_0x307;
    undefined field_0x308;
    undefined field_0x309;
    undefined field_0x30a;
    undefined field_0x30b;
    undefined field_0x30c;
    undefined field_0x30d;
    undefined field_0x30e;
    undefined field_0x30f;
    undefined4 field_0x310;
    undefined4 field_0x314;
    undefined4 field_0x318;
    undefined4 field_0x31c;
    undefined4 field_0x320;
    undefined4 field_0x324;
    undefined4 field_0x328;
    undefined4 field_0x32c;
    undefined4 field_0x330;
    undefined4 field_0x334;
    undefined4 field_0x338;
    undefined4 field_0x33c;
    undefined4 field_0x340;
    undefined4 field_0x344;
    undefined4 field_0x348;
    undefined4 field_0x34c;
    undefined4 field_0x350;
    byte field_0x354;
    byte field_0x355;
    undefined2 field_0x356;
    undefined2 field_0x358;
    undefined2 field_0x35a;
    char pathToScriptFile[256];
    char name[4];
    undefined4 field_0x460;
    byte field_0x464;
    undefined field_0x465;
    undefined field_0x466;
    undefined field_0x467;
    undefined4 field_0x468;
    Uint16 base_pointers[6000];
    Uint8 script[65536];
    struct SCR_STRINGS * ptrToStrings; /* Created by retype action */
    struct Script4k * pScript4k;
    byte a20kArray[4][2000];
    undefined field_0x15294[612000];
    MissionCode missionScript[30]; /* Created by retype action */
    undefined field_0xc1134[3072];
    ushort unk[30];
    undefined field_0xc1d70;
    undefined field_0xc1d71;
    ushort base_script_max_pointers[30];
    short len2;
    uint mission_script_size[30];
    undefined field_0xc1e28;
    undefined field_0xc1e29;
    undefined field_0xc1e2a;
    undefined field_0xc1e2b;
    undefined field_0xc1e2c;
    byte field_0xc1e2d;
    byte field_0xc1e2e;
    short field_0xc1e2f;
    byte field_0xc1e31;
    int arr15i_3[15];
    short field_0xc1e6e;
    int field_0xc1e70;
    int arr12i[12];
    short field_0xc1ea4;
    undefined field_0xc1ea6;
    undefined field_0xc1ea7;
};

typedef struct S16 S16, *PS16;

typedef struct S16_sub1 S16_sub1, *PS16_sub1;

typedef struct Vec2i Vec2i, *PVec2i;

struct Vec2i {
    int x;
    int y;
};

struct S16_sub1 {
    undefined4 field_0x0;
    undefined2 field_0x4;
    byte field_0x6;
    undefined field_0x7;
    undefined4 field_0x8;
    byte field_0xc;
    undefined field_0xd;
    undefined2 field_0xe;
    byte field_0x10;
    undefined field_0x11;
    undefined field_0x12;
    undefined field_0x13;
    int arr64i[64];
    struct Vec2i * vec2i;
    byte field_0x118;
    undefined field_0x119;
    short field_0x11a;
};

struct S16 {
    undefined field_0x0;
    undefined field_0x1;
    undefined field_0x2;
    undefined field_0x3;
    int field_0x4;
    struct S16_sub1 arr_s16sub[8];
    undefined field_0x8e8;
    undefined field_0x8e9;
    undefined field_0x8ea;
    undefined field_0x8eb;
};

typedef struct S17_mission S17_mission, *PS17_mission;

typedef struct Vec3i Vec3i, *PVec3i;

struct Vec3i {
    int x;
    int y;
    int z;
};

struct S17_mission {
    int len;
    struct Vec3i vec3i50[50];
};

typedef struct S18 S18, *PS18;

typedef struct S18_sub S18_sub, *PS18_sub;

struct S18_sub {
    undefined4 b;
    undefined2 c;
    undefined field_0x6;
    undefined field_0x7;
    undefined4 a;
};

struct S18 {
    int len;
    struct S18_sub s18_sub_50[50];
};

typedef struct S19 S19, *PS19;

typedef ulong DWORD;

struct S19 {
    undefined4 field_0x0;
    DWORD time;
    undefined4 field_0x8;
    undefined4 field_0xc;
    DWORD time2;
    undefined4 field_0x14;
    int field_0x18[3];
    int field_0x24[3];
    int field_0x30[3];
    int field_0x3c[3];
    int field_0x48[3];
};

typedef struct S20 S20, *PS20;

struct S20 {
    undefined4 field_0x0;
    undefined2 inc;
    undefined field_0x6;
    undefined field_0x7;
};

typedef struct S22 S22, *PS22;

struct S22 {
    struct S22_1 * last;
    struct S22_1 arr[5031];
};

typedef struct S23 S23, *PS23;

struct S23 {
    int field_0x0;
    undefined field_0x4;
    undefined field_0x5;
    undefined field_0x6;
    undefined field_0x7;
    undefined field_0x8;
    undefined field_0x9;
    undefined field_0xa;
    undefined field_0xb;
    undefined field_0xc;
    undefined field_0xd;
    undefined field_0xe;
    undefined field_0xf;
    ushort field_0x10;
    undefined field_0x12;
    undefined field_0x13;
    int field_0x14;
    undefined field_0x18;
    undefined field_0x19;
    undefined field_0x1a;
    undefined field_0x1b;
    undefined field_0x1c;
    undefined field_0x1d;
    undefined field_0x1e;
    undefined field_0x1f;
    undefined field_0x20;
    undefined field_0x21;
    undefined field_0x22;
    undefined field_0x23;
    ushort field_0x24;
    undefined field_0x26;
    undefined field_0x27;
    int field_0x28;
    undefined field_0x2c;
    undefined field_0x2d;
    undefined field_0x2e;
    undefined field_0x2f;
    undefined field_0x30;
    undefined field_0x31;
    undefined field_0x32;
    undefined field_0x33;
    undefined field_0x34;
    undefined field_0x35;
    undefined field_0x36;
    undefined field_0x37;
    undefined field_0x38;
    undefined field_0x39;
    undefined field_0x3a;
    undefined field_0x3b;
    int field_0x3c;
    undefined field_0x40;
    undefined field_0x41;
    undefined field_0x42;
    undefined field_0x43;
    undefined field_0x44;
    undefined field_0x45;
    undefined field_0x46;
    undefined field_0x47;
    undefined field_0x48;
    undefined field_0x49;
    undefined field_0x4a;
    undefined field_0x4b;
    undefined field_0x4c;
    undefined field_0x4d;
    undefined field_0x4e;
    undefined field_0x4f;
    int field_0x50;
    undefined field_0x54[36];
    int field_0x78;
    undefined field_0x7c[536];
    int field_0x294;
    undefined field_0x298[296];
    undefined4 field_0x3c0;
    int field_0x3c4;
    undefined4 buf0x40000;
};

typedef struct S24 S24, *PS24;

struct S24 {
    short short0;
    byte field_0x2;
    byte field_0x3;
    byte field_0x4;
    byte field_0x5;
    byte field_0x6;
    byte field_0x7;
    struct Pos * position;
};

typedef struct S27 S27, *PS27;

struct S27 {
    undefined field_0x0[2040];
};

typedef struct S28 S28, *PS28;

struct S28 {
    undefined field_0x0[6288];
    byte arr12[12][240];
    undefined field_0x23d0[720];
    byte arr8[8][164];
};

typedef struct S29 S29, *PS29;

typedef struct S29_1 S29_1, *PS29_1;

struct S29_1 {
    int field_0x0;
    int field_0x4;
    int field_0x8;
    int field_0xc;
    int field_0x10;
};

struct S29 {
    short field_0x0;
    short field_0x2;
    struct S29_1 arr10[10];
};

typedef struct S30 S30, *PS30;

struct S30 {
    int field_0x0;
    int field_0x4;
    byte arr[99][8];
    int field_0x320;
};

typedef struct S31 S31, *PS31;

typedef struct S32 S32, *PS32;

struct S32 {
    int field_0x0;
    struct S22_1 * s22_1_ex;
    void * field_0x8;
    struct S22_1 * s22_1;
    struct Pos * pos;
    int field_0x14; /* 99 */
    int field_0x18;
    byte field_0x1c;
    undefined field_0x1d;
    undefined field_0x1e;
    undefined field_0x1f;
    int field_0x20;
    byte field_0x24;
    byte field_0x25;
    byte field_0x26; /* 99 */
    byte field_0x27;
    byte field_0x28;
    undefined field_0x29;
    undefined field_0x2a;
    undefined field_0x2b;
};

struct S31 {
    struct S32 * last;
    int field_0x4;
    struct S32 arrS32[3825];
    short field_0x29174;
    undefined field_0x29176;
    undefined field_0x29177;
};

typedef struct S33 S33, *PS33;

typedef struct S34 S34, *PS34;

struct S34 {
    struct S34 * ref1;
    short field_0x4;
    byte field_0x6;
    byte field_0x7;
};

struct S33 {
    struct S34 * last;
    struct S34 arr[1101];
};

typedef struct S35 S35, *PS35;

typedef struct S36 S36, *PS36;

struct S36 {
    undefined field_0x0;
    undefined field_0x1;
    undefined field_0x2;
    undefined field_0x3;
    struct Pos * pos;
    struct S36 * ref1;
    struct S36 * ref2;
    int field_0x10;
    undefined field_0x14;
    undefined field_0x15;
    undefined field_0x16;
    undefined field_0x17;
    struct S36 * ref3;
    int field_0x1c;
    int field_0x20;
    int field_0x24;
    short field_0x28;
    short field_0x2a;
    short field_0x2c;
    byte field_0x2e;
    byte field_0x2f;
    byte field_0x30;
    undefined field_0x31;
    undefined field_0x32;
    undefined field_0x33;
    int field_0x34;
    byte field_0x38;
    undefined field_0x39;
    undefined field_0x3a;
    undefined field_0x3b;
};

struct S35 {
    struct S36 * last;
    struct S36 arr[385]; /* Created by retype action */
};

typedef struct S37 S37, *PS37;

typedef struct S38 S38, *PS38;

struct S38 {
    int field_0x0;
    int field_0x4;
    int field_0x8;
    int field_0xc;
    int field_0x10;
    int field_0x14;
    int field_0x18;
    short field_0x1c;
    short field_0x1e;
    byte field_0x20;
    undefined field_0x21;
    undefined field_0x22;
    undefined field_0x23;
    int field_0x24;
    int field_0x28;
    int field_0x2c;
    int field_0x30;
    int field_0x34;
    int field_0x38;
    int field_0x3c;
    int field_0x40;
    int field_0x44;
    int field_0x48;
    int field_0x4c;
    int field_0x50;
    int field_0x54;
    int field_0x58;
    int field_0x5c;
    byte field_0x60;
    byte field_0x61;
    undefined field_0x62;
    undefined field_0x63;
    byte field_0x64;
    byte field_0x65;
    undefined field_0x66;
    undefined field_0x67;
    int field_0x68;
    byte field_0x6c;
    undefined field_0x6d;
    undefined field_0x6e;
    undefined field_0x6f;
    int field_0x70;
};

struct S37 {
    ushort index;
    undefined field_0x2;
    undefined field_0x3;
    struct S38 arr[300]; /* Created by retype action */
    undefined field_0x87f4[1200];
    short someShort;
    undefined field_0x8ca6;
    undefined field_0x8ca7;
};

typedef struct S4 S4, *PS4;

struct S4 {
    int iArr1024[1024];
    byte field_0x1000;
    byte field_0x1001;
    undefined field_0x1002;
    undefined field_0x1003;
    int iArr48[48];
    undefined field_0x10c4[1144];
    int field_0x153c;
    int field_0x1540;
    int field_0x1544;
    undefined field_0x1548[118];
    short field_0x15be;
    short field_0x15c0;
};

typedef struct S5 S5, *PS5;

struct S5 {
    char f1;
    undefined field_0x1;
    undefined field_0x2;
    undefined field_0x3;
    undefined field_0x4;
    undefined field_0x5;
    undefined field_0x6;
    undefined field_0x7;
    short field_0x8;
    byte field_0xa;
    undefined field_0xb;
};

typedef struct S7 S7, *PS7;

struct S7 {
    undefined field_0x0;
    undefined field_0x1;
    int field_0x2;
    undefined field_0x6;
    undefined field_0x7;
    undefined2 field_0x8;
    short field_0xa;
    undefined4 field_0xc;
    int field_0x10;
    undefined2 field_0x14;
    undefined2 field_0x16;
    undefined field_0x18;
    undefined field_0x19;
    undefined field_0x1a;
    undefined field_0x1b;
    undefined field_0x1c;
    undefined field_0x1d;
    undefined field_0x1e;
    undefined field_0x1f;
    undefined field_0x20;
    undefined field_0x21;
    undefined field_0x22;
    undefined field_0x23;
    undefined field_0x24;
    undefined field_0x25;
    undefined field_0x26;
    undefined field_0x27;
    byte field_0x28;
    byte field_0x29;
    undefined field_0x2a;
    undefined field_0x2b;
    undefined2 field_0x2c;
    undefined field_0x2e[58];
    undefined4 field_0x68;
    undefined field_0x6c[600];
    int field_0x2c4;
    undefined field_0x2c8[888];
    byte field_0x640;
    undefined field_0x641[63];
    undefined2 field_0x680;
    undefined2 field_0x682;
    undefined field_0x684[148];
    byte weapons[15];
    undefined field_0x727[97];
    undefined2 field_0x788;
};

typedef struct SNightArray SNightArray, *PSNightArray;

struct SNightArray {
    undefined4 field_0x0;
    struct SNightArray * ptr1;
    struct SNightArray * ptr2;
    struct SNightArray * field_0xc;
    undefined4 field_0x10;
    byte field_0x14;
    byte field_0x15;
    byte field_0x16;
    byte field_0x17;
    byte field_0x18;
    undefined field_0x19;
    undefined field_0x1a;
    undefined field_0x1b;
    undefined4 field_0x1c;
    undefined4 field_0x20;
    undefined4 field_0x24;
};

typedef struct SRelateToNight SRelateToNight, *PSRelateToNight;

struct SRelateToNight {
    undefined field_0x0;
    undefined field_0x1;
    undefined field_0x2;
    undefined field_0x3;
    int field_0x4;
    struct SNightArray nightArr3000[3000]; /* Created by retype action */
    short field_0x1d4c8;
    undefined field_0x1d4ca;
    undefined field_0x1d4cb;
};

typedef struct SRelToBonus2 SRelToBonus2, *PSRelToBonus2;

struct SRelToBonus2 {
    undefined field_0x0;
    undefined field_0x1;
    undefined field_0x2;
    undefined field_0x3;
    undefined field_0x4;
    undefined field_0x5;
    undefined field_0x6;
    undefined field_0x7;
    undefined field_0x8;
    undefined field_0x9;
    undefined field_0xa;
    undefined field_0xb;
    undefined field_0xc;
    undefined field_0xd;
    undefined field_0xe;
    undefined field_0xf;
    undefined field_0x10;
    undefined field_0x11;
    undefined field_0x12;
    undefined field_0x13;
    undefined field_0x14;
    undefined field_0x15;
    undefined field_0x16;
    undefined field_0x17;
    undefined field_0x18;
    undefined field_0x19;
    undefined field_0x1a;
    undefined field_0x1b;
    undefined field_0x1c;
    undefined field_0x1d;
    undefined field_0x1e;
    undefined field_0x1f;
    undefined field_0x20;
    undefined field_0x21;
    undefined field_0x22;
    undefined field_0x23;
    undefined field_0x24;
    undefined field_0x25;
    undefined field_0x26;
    undefined field_0x27;
    undefined field_0x28;
    undefined field_0x29;
    undefined field_0x2a;
    undefined field_0x2b;
    byte mask;
};

typedef struct SubScript SubScript, *PSubScript;

struct SubScript {
    undefined field_0x0;
    undefined field_0x1;
    short index; /* Created by retype action */
    byte eq21;
    undefined field_0x5;
    undefined field_0x6;
    undefined field_0x7;
    byte missionNameLength; /* Created by retype action */
    char missionName[13];
    undefined field_0x16;
    undefined field_0x17;
    undefined field_0x18;
    undefined field_0x19;
    undefined field_0x1a;
    undefined field_0x1b;
    undefined field_0x1c;
    undefined field_0x1d;
    undefined field_0x1e;
    undefined field_0x1f;
};

typedef struct SubScript20k SubScript20k, *PSubScript20k;

struct SubScript20k {
    undefined field_0x0[20000];
};

typedef struct SubSubScript SubSubScript, *PSubSubScript;

struct SubSubScript {
    undefined field_0x0[3072];
};

typedef struct TrafficLigthStruct TrafficLigthStruct, *PTrafficLigthStruct;

struct TrafficLigthStruct {
    undefined field_0x0[402];
    byte cycle;
};

