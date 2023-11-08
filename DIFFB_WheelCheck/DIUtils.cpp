#include "DIUtils.h"
#include <math.h>
#define M_PI        3.14159265358979323846264338327950288

static LPDIRECTINPUT8 g_lpDInput8 = NULL;
static LPDIRECTINPUTDEVICE8 g_lpDIDevice8[DID_MAX] = { NULL }; // DirectInputDevice8オブジェクト
static LPDIRECTINPUTEFFECT lpDIEffect_spring = NULL;//FFB用エフェクトオブジェクト
static LPDIRECTINPUTEFFECT lpDIEffect_damper = NULL;//FFB用エフェクトオブジェクト
static LPDIRECTINPUTEFFECT lpDIEffect_friction = NULL;//FFB用エフェクトオブジェクト
static LPDIRECTINPUTEFFECT lpDIEffect_constant = NULL;//FFB用エフェクトオブジェクト
static LPDIRECTINPUTEFFECT lpDIEffect_inertia = NULL;//FFB用エフェクトオブジェクト
static std::vector<std::string> lXEffects[DID_MAX];


bool DIInit(const HINSTANCE hInstance, const HWND hWnd)
{
	DIRelease();

	if (DI_OK != DirectInput8Create(hInstance, 0x0800, IID_IDirectInput8, (LPVOID*)&g_lpDInput8, NULL)) {
		// 生成失敗
		printf_s("DirectInput8オブジェクト生成失敗(DIInit)\n");
		return false;
	}

	bool init = false;

	// キーボード初期化
	if (DIInitKeyboard(hWnd)) {
		init = true;
	}

	// マウス初期化
	if (DIInitMouse(hWnd)) {
		init = true;
	}

	// ゲームパッド初期化
	if (DIInitGamePad(hWnd)) {
		init = true;
	}

	if (!init) {
		DIRelease();
	}
	

	return true;
}

void DIRelease()
{
	// エフェクトオブジェクトの解放
	if (lpDIEffect_spring) {
		lpDIEffect_spring->Unload(); // アンロード
		lpDIEffect_spring->Release(); // 解放
		lpDIEffect_spring = NULL;
	}
	if (lpDIEffect_damper) {
		lpDIEffect_damper->Unload(); // アンロード
		lpDIEffect_damper->Release(); // 解放
		lpDIEffect_damper = NULL;
	}
	if (lpDIEffect_constant) {
		lpDIEffect_constant->Unload(); // アンロード
		lpDIEffect_constant->Release(); // 解放
		lpDIEffect_constant = NULL;
	}
	if (lpDIEffect_inertia) {
		lpDIEffect_inertia->Unload(); // アンロード
		lpDIEffect_inertia->Release(); // 解放
		lpDIEffect_inertia = NULL;
	}
	

	// デバイスオブジェクト解放
	for (int did = 0; did < DID_MAX; did++)
		DIReleaseDevice((DIDEV)did);


	// DirectInput8オブジェクト解放
	if (NULL != g_lpDInput8) { // ポインタチェック。NULLの場合は解放しない(する必要がない)
		g_lpDInput8->Release(); // DirectInput8オブジェクト解放
		g_lpDInput8 = NULL; // NULLを代入し、無効なオブジェクトであることを示す
	}
}

bool DIInitKeyboard(const HWND hWnd)
{
#ifdef _DEBUG
	if (NULL == g_lpDInput8) {
		printf_s("*** Error - DirectInput未初期化(DIInitKeyboard)\n");
		return false;
	}
#endif
	DIReleaseDevice(DID_KEYBOARD);
	// デバイスオブジェクト生成
	if (DI_OK != g_lpDInput8->CreateDevice(GUID_SysKeyboard, &g_lpDIDevice8[DID_KEYBOARD], NULL))
		return false;
	// データフォーマット設定
	if (DI_OK != g_lpDIDevice8[DID_KEYBOARD]->SetDataFormat(&c_dfDIKeyboard)) {
		printf_s("*** Error - データフォーマット設定失敗(DIInitKeyboard)\n");
		DIReleaseDevice(DID_KEYBOARD);
		return false;
	}
	// 協調レベル設定
	if (DI_OK != g_lpDIDevice8[DID_KEYBOARD]->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)) {
		printf_s("*** Error - 協調レベル設定失敗(DIInitKeyboard)\n");
		DIReleaseDevice(DID_KEYBOARD);
		return false;
	}
	// アクセス権取得
	g_lpDIDevice8[DID_KEYBOARD]->Acquire();

	return true;
}

bool DIInitMouse(const HWND hWnd)
{
#ifdef _DEBUG
	if (NULL == g_lpDInput8) {
		printf_s("*** Error - DirectInput未初期化(DIInitMouse)\n");
		return false;
	}
#endif
	DIReleaseDevice(DID_MOUSE);
	// デバイスオブジェクト生成
	if (DI_OK != g_lpDInput8->CreateDevice(GUID_SysMouse, &g_lpDIDevice8[DID_MOUSE], NULL))
		return false;
	// データフォーマット設定
	if (DI_OK != g_lpDIDevice8[DID_MOUSE]->SetDataFormat(&c_dfDIMouse)) {
		printf_s("*** Error - データフォーマット設定失敗(DIInitMouse)\n");
		DIReleaseDevice(DID_MOUSE);
		return false;
	}
	// 協調レベル設定
	if (DI_OK != g_lpDIDevice8[DID_MOUSE]->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)) {
		printf_s("*** Error - 協調レベル設定失敗(DIInitMouse)\n");
		DIReleaseDevice(DID_MOUSE);
		return false;
	}
	// アクセス権取得
	g_lpDIDevice8[DID_MOUSE]->Acquire();
	return true;
}

bool DIInitGamePad(const HWND hWnd)
{
#ifdef _DEBUG
	if (NULL == g_lpDInput8) {
		printf_s("*** Error - DirectInput未初期化(DIInitGamePad)\n");
		return false;
	}
#endif
	for (int i = DID_GAMEPAD1; i < DID_MAX; i++)
		DIReleaseDevice((DIDEV)i);
	// ゲームパッド列挙
	//g_lpDInput8->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)DIEnumGamePadProc, hWnd, DIEDFL_FORCEFEEDBACK | DIEDFL_ATTACHEDONLY);//FFB対応コントローラーのみ取得
	g_lpDInput8->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)DIEnumGamePadProc, hWnd, DIEDFL_ATTACHEDONLY);//通常コントローラーも取得できる
	if (NULL == g_lpDIDevice8[DID_GAMEPAD1]) {
		printf_s("*** Error - ゲームパッドオブジェクト生成失敗(DICreateGamePad)\n");
		return false;
	}
	for (int i = DID_GAMEPAD1; i < DID_MAX; i++) {
		if (g_lpDIDevice8[i]) {
			// アクセス権取得
			g_lpDIDevice8[i]->Acquire();
		}
	}
	return true;
}

BOOL CALLBACK DIEnumGamePadProc(LPDIDEVICEINSTANCE lpDIDInst, LPVOID lpRef)
{
	int did = DID_GAMEPAD1;
	while (NULL != g_lpDIDevice8[did]) {
		did++;
		if (did <= DID_MAX) {
			return DIENUM_STOP;
		}
	}
	wprintf_s(lpDIDInst->tszProductName);
	printf_s("\n");
	
	//エフェクト列挙の初期化
	lXEffects[did].clear();

	// ゲームパッドオブジェクト生成
	if (DI_OK != g_lpDInput8->CreateDevice(lpDIDInst->guidInstance, &g_lpDIDevice8[did], NULL)) {
		printf_s("*** Error - ゲームパッドオブジェクト生成失敗(DIEnumGamePadProc)\n");
		return DIENUM_CONTINUE; // 次のゲームパッドへ
	}
	// データフォーマット設定
	if (DI_OK != g_lpDIDevice8[did]->SetDataFormat(&c_dfDIJoystick)) {
		printf_s("*** Error - データフォーマット設定失敗(DIEnumGamePadProc)\n");
		DIReleaseDevice((DIDEV)did);
		return DIENUM_CONTINUE;
	}
	// 協調レベル設定
	if (DI_OK != g_lpDIDevice8[did]->SetCooperativeLevel((HWND)lpRef, DISCL_BACKGROUND | DISCL_EXCLUSIVE)) {
		printf_s("*** Error - 協調レベル設定失敗(DIEnumGamePadProc)\n");
		DIReleaseDevice((DIDEV)did);
		return DIENUM_CONTINUE;
	}
	// バッファサイズ設定
	DIPROPDWORD dipd;
	ZeroMemory(&dipd, sizeof(dipd));
	dipd.diph.dwSize = sizeof(dipd);
	dipd.diph.dwHeaderSize = sizeof(dipd.diph);
	dipd.diph.dwObj = 0;
	dipd.diph.dwHow = DIPH_DEVICE;
	dipd.dwData = 0; // バッファの数
	
	if (FAILED(g_lpDIDevice8[did]->SetProperty(DIPROP_BUFFERSIZE, &dipd.diph))) {
		printf_s("*** Error - バッファサイズ設定失敗(DIEnumGamePadProc)\n");
		DIReleaseDevice((DIDEV)did);
		return DIENUM_CONTINUE;
	}
	// 軸の列挙
	if (FAILED(g_lpDIDevice8[did]->EnumObjects((LPDIENUMDEVICEOBJECTSCALLBACK)DIEnumGamePadAxesProc, (LPVOID)did, DIDFT_AXIS))) {
		DIReleaseDevice((DIDEV)did);
		return DIENUM_CONTINUE;
	}
	return DIENUM_CONTINUE;
}

BOOL CALLBACK DIEnumGamePadAxesProc(LPCDIDEVICEOBJECTINSTANCE lpDIDObjInst, LPVOID lpRef)
{
	//printf_s("軸: ");
	//wprintf_s(lpDIDObjInst->tszName);
	//wprintf_s(L"\n");
	//lX軸の場合、対応エフェクトを列挙
	if (lpDIDObjInst->guidType == GUID_XAxis) {
		g_lpDIDevice8[(int)lpRef]->EnumEffects((LPDIENUMEFFECTSCALLBACK)DIEnumGamePadEffectsProc, lpRef, NULL);
	}

	// 絶対軸の場合、軸の範囲を設定
	if (0 != (lpDIDObjInst->dwType & DIDFT_ABSAXIS)) {
		DIPROPRANGE dipr;
		dipr.diph.dwSize = sizeof(dipr);
		dipr.diph.dwHeaderSize = sizeof(dipr.diph);
		dipr.diph.dwHow = DIPH_BYID;
		dipr.diph.dwObj = lpDIDObjInst->dwType;
		dipr.lMin = DIAXIS_RANGE_MIN;
		dipr.lMax = DIAXIS_RANGE_MAX;
		if (FAILED(g_lpDIDevice8[(int)lpRef]->SetProperty(DIPROP_RANGE, &dipr.diph)))
			printf_s("*** Error - 軸範囲設定失敗(DISetAxesProp)\n");
	}
	// デッドゾーン設定
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(dipdw);
	dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);;
	dipdw.diph.dwHow = DIPH_BYID;
	dipdw.diph.dwObj = lpDIDObjInst->dwType;
	dipdw.dwData = 0;
	if (FAILED(g_lpDIDevice8[(int)lpRef]->SetProperty(DIPROP_DEADZONE, &dipdw.diph)))
		printf_s("*** Error - デッドゾーン設定失敗(DISetAxesProp)\n");

	return DIENUM_CONTINUE;
}

BOOL CALLBACK DIEnumGamePadEffectsProc(LPCDIEFFECTINFO lpDIEffectInfo, LPVOID lpRef) {
	wprintf_s(lpDIEffectInfo->tszName);
	wprintf_s(L"\n");

	//WCHARからstd::stringへ変換
	std::string s = "";
	int i = 0;
	while (lpDIEffectInfo->tszName[i]) {
		s += lpDIEffectInfo->tszName[i];
		i++;
	}

	lXEffects[(int)lpRef].push_back(s);

	return DIENUM_CONTINUE;
}

void DIReleaseDevice(const DIDEV did)
{
	if (NULL == g_lpDIDevice8[did])
		return;
	g_lpDIDevice8[did]->Unacquire();
	g_lpDIDevice8[did]->Release();
	g_lpDIDevice8[did] = NULL;
}

bool DIGetKeyboardState(BYTE byKeyState[])
{
	ZeroMemory(byKeyState, 256); // 配列をゼロクリア
	if (NULL == g_lpDIDevice8[DID_KEYBOARD]) {
		//printf_s("*** Error - キーボード未初期化(DIGetKeyboardState)\n");
		return false;
	}
	HRESULT hr = g_lpDIDevice8[DID_KEYBOARD]->GetDeviceState(256, byKeyState);
	if (DI_OK != hr) {
		if (DIERR_INPUTLOST == hr || DIERR_NOTACQUIRED == hr)
		{
			hr = g_lpDIDevice8[DID_KEYBOARD]->Acquire(); // アクセス権の再取得
		}
		//printf_s("*** Error - キーボード状態取得失敗(DIGetKeyboardState)\n");
		return false;
	}
	return true;
}

bool DIGetMouseState(DIMOUSESTATE& diMouseState)
{
	ZeroMemory(&diMouseState, sizeof(diMouseState)); // 構造体をゼロクリア
	if (NULL == g_lpDIDevice8[DID_MOUSE]) {
		//printf_s("*** Error - マウス未初期化(DIGetMouseState)\n");
		return false;
	}
	const HRESULT hr = g_lpDIDevice8[DID_MOUSE]->GetDeviceState(sizeof(diMouseState), &diMouseState);
	if (DI_OK != hr) {
		if (DIERR_INPUTLOST == hr || DIERR_NOTACQUIRED == hr)
			g_lpDIDevice8[DID_MOUSE]->Acquire(); // アクセス権の再取得
		//printf_s("*** Error - マウス状態取得(DIGetMouseState)\n");
		return false;
	}
	return true;
}

bool DIGetGamePadState(const DIDEV did, DIJOYSTATE& diGamePadState)
{
	ZeroMemory(&diGamePadState, sizeof(diGamePadState));
	diGamePadState.lX = diGamePadState.lY = diGamePadState.lZ = DIAXIS_RANGE_CENTER;
	diGamePadState.lRx = diGamePadState.lRy = diGamePadState.lRz = DIAXIS_RANGE_CENTER;
#ifdef _DEBUG
	if (DID_GAMEPAD1 > did) {
		printf_s("*** Error - デバイス指定エラー(DIGetGamePadState)\n");
		return false;
	}
#endif
	if (NULL == g_lpDIDevice8[did]) {
		//printf_s("*** Error - ゲームパッド未初期化(DIGetGamePadState)\n");
		return false;
	}
	g_lpDIDevice8[did]->Poll();
	const HRESULT hr = g_lpDIDevice8[did]->GetDeviceState(sizeof(diGamePadState), &diGamePadState);
	if (DI_OK != hr) {
		if (DIERR_INPUTLOST == hr || DIERR_NOTACQUIRED == hr)
			g_lpDIDevice8[did]->Acquire();
		//printf_s("*** Error - ゲームパッド状態取得(DIGetGamePadState)\n");
		return false;
	}
	return true;
}

LONG DISetFFB_Spring(const DIDEV did, LONG centerOffset, LONG saturation, LONG coefficient, LONG centering) {
	if (NULL == g_lpDIDevice8[did]) {
		//printf_s("*** Error - ゲームパッド未初期化(DISetFFB_Spring)\n");
		return 0;
	}

	centerOffset = min(max(centerOffset, -10000), 10000);
	saturation = min(max(saturation, 0), 10000);
	coefficient = min(max(coefficient, 0), 10000);
	centering = min(max(centering, 0), 10000);

	DIJOYSTATE diJoyState;
	if (!DIGetGamePadState(DID_GAMEPAD1, diJoyState)) {
		return 0;
	}
	LONG handle = diJoyState.lX * 10000 / DIAXIS_RANGE_MAX;
	LONG diffHandle = handle - centerOffset;
	LONG centeringCorrection = diffHandle * centering / 10000;

	////コンスタントフォースでスプリングを再現
	//LONG coef = diffHandle * coefficient / 10000.f;
	////LONG coef = (0 < diffHandle) ? coefficient : -coefficient;
	//if (0 < saturation) {
	//	coef = min(max(coef, -saturation), saturation);
	//}
	//coef = min(max(coef, -10000),10000);
	//DISetFFB_Constant(did, coef);
	//return coef;

	// エフェクト周期設定
	DICONDITION dicondition;
	ZeroMemory(&dicondition, sizeof(dicondition));
	dicondition.lDeadBand = 0;
	dicondition.dwNegativeSaturation = saturation;
	dicondition.dwPositiveSaturation = saturation;
	dicondition.lNegativeCoefficient = coefficient;
	dicondition.lPositiveCoefficient = coefficient;
	dicondition.lOffset = centerOffset-centeringCorrection;

	// 振動エフェクト設定
	DWORD dwAxes[] = { DIJOFS_X }; // エフェクト軸
	LONG lDirection[] = { 0 }; // エフェクト方向
	DIEFFECT diEffect;
	ZeroMemory(&diEffect, sizeof(diEffect));
	diEffect.dwSize = sizeof(diEffect);
	diEffect.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
	diEffect.dwDuration = INFINITE; // エフェクト継続時間
	diEffect.dwGain = DI_FFNOMINALMAX;
	diEffect.dwTriggerButton = DIEB_NOTRIGGER;
	diEffect.dwTriggerRepeatInterval = 0;
	diEffect.cAxes = sizeof(dwAxes) / sizeof(dwAxes[0]);
	diEffect.rgdwAxes = dwAxes;
	diEffect.rglDirection = lDirection;
	diEffect.lpEnvelope = NULL; // エンベロープ構造体
	diEffect.cbTypeSpecificParams = sizeof(dicondition); // エフェクト周期構造体のサイズ
	diEffect.lpvTypeSpecificParams = &dicondition; // エフェクト周期構造体
	// エフェクト生成
	if (!lpDIEffect_spring) {
		HRESULT hr = g_lpDIDevice8[did]->CreateEffect(GUID_Spring, &diEffect, &lpDIEffect_spring, NULL);
	}

	if (lpDIEffect_spring) {
		lpDIEffect_spring->SetParameters(&diEffect, DIEP_TYPESPECIFICPARAMS | DIEP_START);
	}
}

void DISetFFB_Damper(const DIDEV did, LONG coefficient) {
	if (NULL == g_lpDIDevice8[did]) {
		//printf_s("*** Error - ゲームパッド未初期化(DISetFFB_Damper)\n");
		return;
	}

	coefficient = min(max(coefficient, 0), 10000);

	// エフェクト周期設定
	DICONDITION dicondition;
	ZeroMemory(&dicondition, sizeof(dicondition));
	dicondition.lDeadBand = 0;
	dicondition.dwNegativeSaturation = 0;
	dicondition.dwPositiveSaturation = 0;
	dicondition.lNegativeCoefficient = coefficient;
	dicondition.lPositiveCoefficient = coefficient;
	dicondition.lOffset = 0;

	// 振動エフェクト設定
	DWORD dwAxes[] = { DIJOFS_X }; // エフェクト軸
	LONG lDirection[] = { 0 }; // エフェクト方向
	DIEFFECT diEffect;
	ZeroMemory(&diEffect, sizeof(diEffect));
	diEffect.dwSize = sizeof(diEffect);
	diEffect.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
	diEffect.dwDuration = INFINITE; // エフェクト継続時間
	diEffect.dwGain = DI_FFNOMINALMAX;
	diEffect.dwTriggerButton = DIEB_NOTRIGGER;
	diEffect.dwTriggerRepeatInterval = 0;
	diEffect.cAxes = sizeof(dwAxes) / sizeof(dwAxes[0]);
	diEffect.rgdwAxes = dwAxes;
	diEffect.rglDirection = lDirection;
	diEffect.lpEnvelope = NULL; // エンベロープ構造体
	diEffect.cbTypeSpecificParams = sizeof(dicondition); // エフェクト周期構造体のサイズ
	diEffect.lpvTypeSpecificParams = &dicondition; // エフェクト周期構造体
	// エフェクト生成
	if (!lpDIEffect_damper) {
		HRESULT hr = g_lpDIDevice8[did]->CreateEffect(GUID_Damper, &diEffect, &lpDIEffect_damper, NULL);
	}

	if (lpDIEffect_damper) {
		lpDIEffect_damper->SetParameters(&diEffect, DIEP_TYPESPECIFICPARAMS | DIEP_START);
	}
}

void DISetFFB_Friction(const DIDEV did, LONG coefficient) {
	if (NULL == g_lpDIDevice8[did]) {
		//printf_s("*** Error - ゲームパッド未初期化(DISetFFB_Damper)\n");
		return;
	}

	coefficient = min(max(coefficient, 0), 10000);

	// エフェクト周期設定
	DICONDITION dicondition;
	ZeroMemory(&dicondition, sizeof(dicondition));
	dicondition.lDeadBand = 0;
	dicondition.dwNegativeSaturation = 0;
	dicondition.dwPositiveSaturation = 0;
	dicondition.lNegativeCoefficient = coefficient;
	dicondition.lPositiveCoefficient = coefficient;
	dicondition.lOffset = 0;

	// 振動エフェクト設定
	DWORD dwAxes[] = { DIJOFS_X }; // エフェクト軸
	LONG lDirection[] = { 0 }; // エフェクト方向
	DIEFFECT diEffect;
	ZeroMemory(&diEffect, sizeof(diEffect));
	diEffect.dwSize = sizeof(diEffect);
	diEffect.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
	diEffect.dwDuration = INFINITE; // エフェクト継続時間
	diEffect.dwGain = DI_FFNOMINALMAX;
	diEffect.dwTriggerButton = DIEB_NOTRIGGER;
	diEffect.dwTriggerRepeatInterval = 0;
	diEffect.cAxes = sizeof(dwAxes) / sizeof(dwAxes[0]);
	diEffect.rgdwAxes = dwAxes;
	diEffect.rglDirection = lDirection;
	diEffect.lpEnvelope = NULL; // エンベロープ構造体
	diEffect.cbTypeSpecificParams = sizeof(dicondition); // エフェクト周期構造体のサイズ
	diEffect.lpvTypeSpecificParams = &dicondition; // エフェクト周期構造体
	// エフェクト生成
	if (!lpDIEffect_friction) {
		HRESULT hr = g_lpDIDevice8[did]->CreateEffect(GUID_Friction, &diEffect, &lpDIEffect_friction, NULL);
	}

	if (lpDIEffect_friction) {
		lpDIEffect_friction->SetParameters(&diEffect, DIEP_TYPESPECIFICPARAMS | DIEP_START);
	}
}

void DISetFFB_Constant(const DIDEV did, LONG coefficient) {
	if (NULL == g_lpDIDevice8[did]) {
		//printf_s("*** Error - ゲームパッド未初期化(DISetFFB_Constant)\n");
		return;
	}

	coefficient = min(max(-coefficient, -10000), 10000);

	// エフェクト周期設定
	DICONSTANTFORCE diconstant;
	ZeroMemory(&diconstant, sizeof(diconstant));
	diconstant.lMagnitude = coefficient;

	// 振動エフェクト設定
	DWORD dwAxes[] = { DIJOFS_X }; // エフェクト軸
	LONG lDirection[] = { 0 }; // エフェクト方向
	DIEFFECT diEffect;
	ZeroMemory(&diEffect, sizeof(diEffect));
	diEffect.dwSize = sizeof(diEffect);
	diEffect.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
	diEffect.dwDuration = INFINITE; // エフェクト継続時間
	diEffect.dwGain = DI_FFNOMINALMAX;
	diEffect.dwTriggerButton = DIEB_NOTRIGGER;
	diEffect.dwTriggerRepeatInterval = 0;
	diEffect.cAxes = sizeof(dwAxes) / sizeof(dwAxes[0]);
	diEffect.rgdwAxes = dwAxes;
	diEffect.rglDirection = lDirection;
	diEffect.lpEnvelope = NULL; // エンベロープ構造体
	diEffect.cbTypeSpecificParams = sizeof(diconstant); // エフェクト周期構造体のサイズ
	diEffect.lpvTypeSpecificParams = &diconstant; // エフェクト周期構造体
	// エフェクト生成
	if (!lpDIEffect_constant) {
		HRESULT hr = g_lpDIDevice8[did]->CreateEffect(GUID_ConstantForce, &diEffect, &lpDIEffect_constant, NULL);
	}

	if (lpDIEffect_constant) {
		lpDIEffect_constant->SetParameters(&diEffect, DIEP_TYPESPECIFICPARAMS | DIEP_START);
	}
}

void DISetFFB_Inertia(const DIDEV did, LONG coefficient) {
	if (NULL == g_lpDIDevice8[did]) {
		//printf_s("*** Error - ゲームパッド未初期化(DISetFFB_Inertia)\n");
		return;
	}

	coefficient = min(max(coefficient, -10000), 10000);

	// エフェクト周期設定
	DICONDITION dicondition;
	ZeroMemory(&dicondition, sizeof(dicondition));
	dicondition.lDeadBand = 0;
	dicondition.dwNegativeSaturation = 0;
	dicondition.dwPositiveSaturation = 0;
	dicondition.lNegativeCoefficient = coefficient;
	dicondition.lPositiveCoefficient = coefficient;
	dicondition.lOffset = 0;

	// 振動エフェクト設定
	DWORD dwAxes[] = { DIJOFS_X }; // エフェクト軸
	LONG lDirection[] = { 0 }; // エフェクト方向
	DIEFFECT diEffect;
	ZeroMemory(&diEffect, sizeof(diEffect));
	diEffect.dwSize = sizeof(diEffect);
	diEffect.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
	diEffect.dwDuration = INFINITE; // エフェクト継続時間
	diEffect.dwGain = DI_FFNOMINALMAX;
	diEffect.dwTriggerButton = DIEB_NOTRIGGER;
	diEffect.dwTriggerRepeatInterval = 0;
	diEffect.cAxes = sizeof(dwAxes) / sizeof(dwAxes[0]);
	diEffect.rgdwAxes = dwAxes;
	diEffect.rglDirection = lDirection;
	diEffect.lpEnvelope = NULL; // エンベロープ構造体
	diEffect.cbTypeSpecificParams = sizeof(dicondition); // エフェクト周期構造体のサイズ
	diEffect.lpvTypeSpecificParams = &dicondition; // エフェクト周期構造体
	// エフェクト生成
	if (!lpDIEffect_inertia) {
		HRESULT hr = g_lpDIDevice8[did]->CreateEffect(GUID_Inertia, &diEffect, &lpDIEffect_inertia, NULL);
	}

	if (lpDIEffect_inertia) {
		lpDIEffect_inertia->SetParameters(&diEffect, DIEP_TYPESPECIFICPARAMS | DIEP_START);
	}
}

System::String^ DIGetGamePadProductName(const DIDEV did) {
	DIDEVICEINSTANCE lpDeviceInst;
	lpDeviceInst.dwSize = sizeof(DIDEVICEINSTANCE);
	if (g_lpDIDevice8[did]) {
		g_lpDIDevice8[did]->GetDeviceInfo(&lpDeviceInst);
		if (&lpDeviceInst) {
			System::String^ s = gcnew System::String("");
			int i = 0;
			while (lpDeviceInst.tszProductName[i]) {
				s += lpDeviceInst.tszProductName[i];
				i++;
			}
			return s;
		}
	}
	return "No Device";
}
System::String^ DIGetGamePadInstanceName(const DIDEV did) {
	DIDEVICEINSTANCE lpDeviceInst;
	lpDeviceInst.dwSize = sizeof(DIDEVICEINSTANCE);
	if (g_lpDIDevice8[did]) {
		g_lpDIDevice8[did]->GetDeviceInfo(&lpDeviceInst);
		if (&lpDeviceInst) {
			System::String^ s = gcnew System::String("");
			int i = 0;
			while (lpDeviceInst.tszInstanceName[i]) {
				s += lpDeviceInst.tszInstanceName[i];
				i++;
			}
			return s;
		}
	}
	return "No Device";
}

std::string DIGetGamePadProductName_std(const DIDEV did) {
	DIDEVICEINSTANCE lpDeviceInst;
	lpDeviceInst.dwSize = sizeof(DIDEVICEINSTANCE);
	if (g_lpDIDevice8[did]) {
		g_lpDIDevice8[did]->GetDeviceInfo(&lpDeviceInst);
		if (&lpDeviceInst) {
			std::string s = "";
			int i = 0;
			while (lpDeviceInst.tszProductName[i]) {
				s += lpDeviceInst.tszProductName[i];
				i++;
			}
			return s;
		}
	}
	return "No Device";
}
std::string DIGetGamePadInstanceName_std(const DIDEV did) {
	DIDEVICEINSTANCE lpDeviceInst;
	lpDeviceInst.dwSize = sizeof(DIDEVICEINSTANCE);
	if (g_lpDIDevice8[did]) {
		g_lpDIDevice8[did]->GetDeviceInfo(&lpDeviceInst);
		if (&lpDeviceInst) {
			std::string s = "";
			int i = 0;
			while (lpDeviceInst.tszInstanceName[i]) {
				s += lpDeviceInst.tszInstanceName[i];
				i++;
			}
			return s;
		}
	}
	return "No Device";
}

std::vector<std::string> GetlXEffects(const DIDEV did) {
	return lXEffects[did];
}

void All_DIERR(HRESULT hr) {
	int t = 0;
	switch (hr)
	{
	case DIERR_ACQUIRED: t = 0; break;
	case DIERR_ALREADYINITIALIZED: t = 0; break;
	case DIERR_BADDRIVERVER: t = 0; break;
	case DIERR_BETADIRECTINPUTVERSION: t = 0; break;
	case DIERR_DEVICEFULL: t = 0; break;
	case DIERR_DEVICENOTREG: t = 0; break;
	case DIERR_EFFECTPLAYING: t = 0; break;
	case DIERR_GENERIC: t = 0; break;
	case DIERR_HANDLEEXISTS: t = 0; break;
	case DIERR_HASEFFECTS: t = 0; break;
	case DIERR_INCOMPLETEEFFECT: t = 0; break;
	case DIERR_INPUTLOST: t = 0; break;
	case DIERR_INSUFFICIENTPRIVS: t = 0; break;
	case DIERR_INVALIDPARAM: t = 0; break;
	case DIERR_MAPFILEFAIL: t = 0; break;
	case DIERR_MOREDATA: t = 0; break;
	case DIERR_NOAGGREGATION: t = 0; break;
	case DIERR_NOINTERFACE: t = 0; break;
	case DIERR_NOTACQUIRED: t = 0; break;
	case DIERR_NOTBUFFERED: t = 0; break;
	case DIERR_NOTDOWNLOADED: t = 0; break;
	case DIERR_NOTEXCLUSIVEACQUIRED: t = 0; break;
	case DIERR_NOTFOUND: t = 0; break;
	case DIERR_NOTINITIALIZED: t = 0; break;
		//case DIERR_OBJECTNOTFOUND: t = 0; break;
	case DIERR_OLDDIRECTINPUTVERSION: t = 0; break;
		//case DIERR_OTHERAPPHASPRIO: t = 0; break;
	case DIERR_OUTOFMEMORY: t = 0; break;
		//case DIERR_READONLY: t = 0; break;
	case DIERR_REPORTFULL: t = 0; break;
	case DIERR_UNPLUGGED: t = 0; break;
	case DIERR_UNSUPPORTED: t = 0; break;
	default:
		break;
	}
}