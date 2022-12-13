#pragma once
#include <dinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

//===============================================
//  keyの状態列挙型
//===============================================
enum KeyState {
	EPush,
	EHold,
	ERelease,
	ENone
};

class KeyInput {
public:
	//----------------------------------------------------
	/// [機能] ダイレクトinputの初期化します
	/// [戻り値] 初期化に成功したか否かを返します
	/// [使用方法/注意点] プログラム中で一度だけ呼び出します
	//----------------------------------------------------
	static void InitDinput();

	//-------------------------------------------------------------------
	/// [機能] 最新のkeyのStateの取得します
	/// [引数] DirecInputに定義されたkeyの名前です(実態がint型であるだけ)
	/// [戻り値] 最新のkeyのstateです
	//-------------------------------------------------------------------
	static KeyState GetKeyState(int keyCode);


	//-------------------------------------------------------------------------------
	/// [機能] 最新の押されたkeyのkeyStateと最新の押されたkyeを更新します
	/// [使用方法/注意点] インスタンスの数関係なく一回のループにつき一度だけ呼び出します
	//-------------------------------------------------------------------------------
	static void UpdateCurrentKey();

private:
	KeyInput();    // シングルトンなのでコンストラクター封印
	~KeyInput();   // シングルトンなのでデストラクター封印
	KeyInput(const KeyInput&);  // シングルトンなのでコピーコンストラクター封印
	static LPDIRECTINPUT8 mDinput;
	static LPDIRECTINPUTDEVICE8 mKeyDevice;
	static BYTE mPrevKey[256];
	static BYTE mCurrentKey[256];
};
