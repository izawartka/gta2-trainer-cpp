#pragma once
#include "LiveTableData.h"
#include <vector>

// Live table helper class

class LiveTableHelper
{
	static bool m_selectedDataInitialized;
	static std::vector<LiveTableData> m_selectedData[];

public:
	static void InitSelectedData();
	static int GetData(void* item, LiveTableData& data, bool* failed);
	static CString GetDataString(void* item, LiveTableData& data);
	static std::vector<LiveTableData>* GetSelectedData(LT_MODE mode);
	static void GetItems(LT_MODE mode, void*& firstItem, int& itemsCount);

};