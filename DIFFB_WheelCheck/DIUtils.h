#pragma once

#include <stdio.h>
#include <dinput.h>
#include <string>
#include <vector>


#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


// デバイス指定
enum DIDEV {
	DID_KEYBOARD, // キーボード
	DID_MOUSE, // マウス
	DID_GAMEPAD1, // ゲームパッド１
	DID_GAMEPAD2, // ゲームパッド２

	DID_MAX // デバイス最大数
};

enum {
	DIAXIS_RANGE_MIN = -32767,
	DIAXIS_RANGE_MAX = 32767,
	DIAXIS_RANGE_CENTER = (DIAXIS_RANGE_MAX + DIAXIS_RANGE_MIN + 1) / 2
};

bool DIInit(const HINSTANCE hInstance, const HWND hWnd);
void DIRelease();
bool DIInitKeyboard(const HWND hWnd);
bool DIInitMouse(const HWND hWnd);
bool DIInitGamePad(const HWND hWnd);
BOOL CALLBACK DIEnumGamePadProc(LPDIDEVICEINSTANCE lpDIDInst, LPVOID lpRef);
BOOL CALLBACK DIEnumGamePadAxesProc(LPCDIDEVICEOBJECTINSTANCE lpDIDObjInst, LPVOID lpRef);
BOOL CALLBACK DIEnumGamePadEffectsProc(LPCDIEFFECTINFO lpDIEffectInfo, LPVOID lpRef);
void DIReleaseDevice(const DIDEV did);
bool DIGetKeyboardState(BYTE byKeyState[]);
bool DIGetMouseState(DIMOUSESTATE& diMouseState);
bool DIGetGamePadState(const DIDEV did, DIJOYSTATE& diGamePadState);
LONG DISetFFB_Spring(const DIDEV did, LONG centerOffset, LONG saturation, LONG coefficient, LONG centering=0);
void DISetFFB_Damper(const DIDEV did, LONG coefficient);
void DISetFFB_Friction(const DIDEV did, LONG coefficient);
void DISetFFB_Constant(const DIDEV did, LONG coefficient);
void DISetFFB_Inertia(const DIDEV did, LONG coefficient);
System::String^ DIGetGamePadProductName(const DIDEV did);
System::String^ DIGetGamePadInstanceName(const DIDEV did);
std::string DIGetGamePadProductName_std(const DIDEV did);
std::string DIGetGamePadInstanceName_std(const DIDEV did);
std::vector<std::string> GetlXEffects(const DIDEV did);