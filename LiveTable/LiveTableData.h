#pragma once
#ifndef LT_DATA
#define LT_DATA

#include <atlstr.h>  // Include for CString, make sure this is correct for your environment

#define LT_REFRESH_INTERVAL 500

typedef enum LT_MODE {
    LT_MODE_PEDS = 0,
    LT_MODE_CARS = 1
} LT_MODE;

extern constexpr int LT_MODE_COUNT = 2;

extern const CString LT_MODE_STR[];

typedef enum LT_DATA_TYPE {
    LT_DATA_TYPE_INT = 0,
    LT_DATA_TYPE_UINT = 1,
    LT_DATA_TYPE_SCR_FLOAT = 2,
    LT_DATA_TYPE_BOOLEAN = 3,
    LT_DATA_TYPE_ADDRESS = 4,
    LT_DATA_TYPE_HEX = 5
} LT_DATA_TYPE;

extern const CString LT_DATA_TYPE_STR[];

struct LiveTableData {
    CString name;
    int width;
    unsigned char size;
    LT_DATA_TYPE type;
    unsigned char offsetsCount;
    int* offsets;
    bool default = false;
};

extern const LiveTableData ltPedData[];
extern const int ltPedDataCount;

extern const LiveTableData ltCarData[];
extern const int ltCarDataCount;

extern const LiveTableData* ltData[];
extern const int ltDataCount[];
extern const int ltItemSize[];

#endif // !LT_DATA
