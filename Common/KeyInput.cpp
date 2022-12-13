#include "KeyInput.h"
#include "App.h"
#include <iostream>
#include <string.h>
#include <cassert>

LPDIRECTINPUT8 KeyInput::mDinput = nullptr;
LPDIRECTINPUTDEVICE8 KeyInput::mKeyDevice = nullptr;
BYTE KeyInput::mCurrentKey[256];
BYTE KeyInput::mPrevKey[256];



KeyInput::KeyInput() {
	
}

KeyInput::~KeyInput() {

}

//-------------------------------------------
//  KeyStateの取得
//-------------------------------------------
KeyState KeyInput::GetKeyState(int keyCode) {
	// keyStateの更新

	// 前のフレームで押されていたら
	if (mPrevKey[keyCode] & 0x80) {
		// 今回も押されているなら
		if (mCurrentKey[keyCode] & 0x80) {
			return EHold; // Hold状態を返す
		}
		//今回は押されていないなら
		else {
			return ERelease; // Release状態を返す
		}
	}

	//前のフレームで押されていないなら
	else {
		//今回は押されているなら
		if (mCurrentKey[keyCode] & 0x80) {
			return EPush; // Push状態を返す
		}
		//今回も押されていないなら
		else {
			return ENone; // None状態を返す
		}
	}
}

//--------------------------------------------
//　　最新のkeyと最新のkeyStateの更新
//--------------------------------------------
void KeyInput::UpdateCurrentKey() {
	assert(mDinput != nullptr || !"InitDinputは二回呼び出しちゃダメ!!");

	memcpy(mPrevKey,mCurrentKey,sizeof(BYTE)*256);   // 1回前の押されたkeyの更新
	// 最新のkeyの更新
	HRESULT hr = mKeyDevice->Acquire();
	if ( hr == S_OK || hr == S_FALSE ) {
		mKeyDevice->GetDeviceState(sizeof(mCurrentKey),&mCurrentKey); // mCurretKeyに最新のkeyを入れる
	}
}


//-------------------------------------------
//  DirectInputの初期化
//-------------------------------------------
void KeyInput::InitDinput() {
	assert(mDinput == nullptr || !"InitDinputは二回呼び出しちゃダメ!!");
	HRESULT hr;
	//DirectInputオブジェクトの作成
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL),
			DIRECTINPUT_VERSION,IID_IDirectInput8,(VOID**)&mDinput,NULL))) 
	{
		assert(!"DirectInputオブジェクトの生成に失敗\n");
	}
	//DirectInputデバイスの生成
	if (FAILED( hr = mDinput->CreateDevice(GUID_SysKeyboard,&mKeyDevice,NULL))) {
		assert(!"DirectInputデバイスの生成に失敗\n");
	}
	//デバイスをキーボードに設定
	if ( hr = mKeyDevice->SetDataFormat(&c_dfDIKeyboard)) {
		assert(!"デバイスの設定に失敗\n");
	}
	//協調レベルの設定
	if (FAILED(hr = mKeyDevice->SetCooperativeLevel(
		g_hWnd,DISCL_NONEXCLUSIVE | DISCL_BACKGROUND))) 
	{
		assert(!"協調レベルの設定に失敗\n");
	}
	//デバイスを取得
	mKeyDevice->Acquire();
}


