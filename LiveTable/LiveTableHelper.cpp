#include "../pch.h"
#include "../gta2dll.h"
#include "LiveTableHelper.h"
#include "LiveTableData.h"

bool LiveTableHelper::m_selectedDataInitialized = false;
std::vector<LiveTableData> LiveTableHelper::m_selectedData[LT_MODE_COUNT];

void LiveTableHelper::InitSelectedData()
{
	if(m_selectedDataInitialized) return;
	m_selectedDataInitialized = true;

	for(int i = 0; i < LT_MODE_COUNT; i++) {

		const LiveTableData* data = ltData[i];
		const int count = ltDataCount[i];

		for(int v = 0; v < count; v++) {
			if(!data[v].default) continue;

			m_selectedData[i].push_back(data[v]);
		}
	}
}

int LiveTableHelper::GetData(void* item, LiveTableData& data, bool* failed)
{

	int value = (int)item;

	for (int i = 0; i < data.offsetsCount; i++) {
		if (value < 0x400000) {
			*failed = true;
			return 0;
		}

		value = *(int*)(value + data.offsets[i]);
	}

	*failed = false;
	int copiedValue = 0;
	memcpy(&copiedValue, (byte*)&value, data.size);

	return copiedValue;
}

CString LiveTableHelper::GetDataString(void* item, LiveTableData& data)
{
	bool failed = false;
	int value = GetData(item, data, &failed);

	if (failed) {
		return L"";
	}

	CString valueStr;

	switch (data.type) {
	case LT_DATA_TYPE_INT:
		valueStr.Format(L"%d", value);
		break;
	case LT_DATA_TYPE_UINT:
		valueStr.Format(L"%u", value);
		break;
	case LT_DATA_TYPE_SCR_FLOAT:
		valueStr.Format(L"%.2f", value / 16384.0);
		break;
	case LT_DATA_TYPE_BOOLEAN:
		valueStr = (value == 0) ? L"F" : L"T";
		break;
	case LT_DATA_TYPE_ADDRESS:
		if (value == 0) {
			valueStr = L"";
			break;
		}
	case LT_DATA_TYPE_HEX:
		valueStr.Format(L"0x%X", value);
		break;
	}

	return valueStr;
}

std::vector<LiveTableData>* LiveTableHelper::GetSelectedData(LT_MODE mode)
{
	InitSelectedData();
	return &m_selectedData[mode];
}

void LiveTableHelper::GetItems(LT_MODE mode, void*& firstItem, int& itemsCount)
{
	itemsCount = -1;

	if(mode == LT_MODE_PEDS) {
		PedManager_S25* pedsManager = ByPtr(PedManager_S25, ptrToPedManager);
		if(pedsManager == nullptr) return;

		firstItem = (void*)(&pedsManager->peds[0]);
		itemsCount = 200;

		return;
	}

	if(mode == LT_MODE_CARS) {
		CarsPrefab* carsManager = ByPtr(CarsPrefab, ptrToCarsPrefabs);
		if (carsManager == nullptr) return;

		firstItem = (void*)(&carsManager->arr306Cars[0]);
		itemsCount = 306;

		return;
	}
}
