#pragma once

class Hooks {
public:
	static void gameTick(void);
	static void drawChat(void);
	static void afterDebugFlags(LPCSTR stringVal);
};
