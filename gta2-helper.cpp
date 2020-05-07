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