#include "Random.h"
#include <stdlib.h>
#include <time.h>
#include <cassert>

unsigned int Random::mSeed = -1;

//-----------------------------------------
//    初期化
//-----------------------------------------
void Random::Init() {
	mSeed = (unsigned int)time(NULL);   // ランダムのシード値設定
	srand(mSeed);
}

//-------------------------------------------
//   min～maxの間のランダムな整数値を返す
//-------------------------------------------
int Random::RandomInt(int min,int max) {
	assert((mSeed != -1) || !("Random::Init()を必ず呼び出してから使用してください"));  // 初期化してないならassert
	assert((min <= max) || !("RandomInt: minがmaxより大きいです"));   // minがmax以下が偽ならasset

	return (rand() % (max - min + 1) + min);  // min～maxの範囲から返す
}


//-------------------------------------------------
//    min～maxでランダムな浮動小数点数を返す
//-------------------------------------------------
float Random::RandomFloat(int min,int max) {
	assert((mSeed != -1) || !("Random::Init()を必ず呼び出してから使用してください"));  // 初期化してないならassert
	assert(min <= max || !("RandomFloat: minがmaxより大きいです"));   // minがmax以下が偽ならassret

	int floatRange = 0x7fff;                                              // ある程度正確な精度の小数点以下数値の最大値
	float decimalPart = (rand() % (floatRange + 1) / (float)floatRange);  // 小数部の数値設定
	int integerPart = (rand() % (max - min ) + min);                      // 整数部の数値設定
	return decimalPart + static_cast<float>(integerPart);                 // 整数部に小数部を足して返す
}
