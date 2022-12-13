#include "MyMath.h"

//------------------------------
//   ベクトルの加算
//------------------------------
const XMFLOAT3 Math::Add(const XMFLOAT3& vector1,const XMFLOAT3& vector2) {
	XMFLOAT3 returnVec;
	returnVec.x = vector1.x + vector2.x;
	returnVec.y = vector1.y + vector2.y;
	returnVec.z = vector1.z + vector2.z;
	return returnVec;
}

//-------------------------------
//  ベクトルの減算
//-------------------------------
const XMFLOAT3 Math::Sub(const XMFLOAT3& vector1,const XMFLOAT3& vector2) {
	XMFLOAT3 returnVec;
	returnVec.x = vector1.x - vector2.x;
	returnVec.y = vector1.y - vector2.y;
	returnVec.z = vector1.z - vector2.z;
	return returnVec;
}

//--------------------------------
//   ベクトルとスカラーの乗算
//--------------------------------
const XMFLOAT3 Math::MulScaler(const XMFLOAT3& vector,float scaler) {
	XMFLOAT3 returnVec;
	returnVec.x = vector.x * scaler;
	returnVec.y = vector.y * scaler;
	returnVec.z = vector.z * scaler;
	return returnVec;
}

//---------------------------------
//   ベクトルとスカラーの除算
//---------------------------------
const XMFLOAT3 Math::DivScaler(const XMFLOAT3& vector, float scaler) {
	assert(scaler == 0 || !("0除算ダメ。Math::DivScaler"));
	XMFLOAT3 returnVec;
	returnVec.x = vector.x / scaler;
	returnVec.y = vector.y / scaler;
	returnVec.z = vector.z / scaler;
	return returnVec;
}


//----------------------------------------
//  ベクトルの長さの取得
//----------------------------------------
float Math::GetLenght(const XMFLOAT3& vector) {
	return sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

//--------------------------------------
//   ベクトルの正規化
//--------------------------------------
const XMFLOAT3 Math::GetNormalize(const XMFLOAT3& vector) {
	float lenght = Math::GetLenght(vector);
	XMFLOAT3 returnVec;
	returnVec.x = vector.x / lenght;
	returnVec.y = vector.y / lenght;
	returnVec.z = vector.z / lenght;
	return returnVec;
}

//-----------------------------------
//  ベクトルの内積の取得
//-----------------------------------
float Math::GetDot(const XMFLOAT3& vector1,const XMFLOAT3& vector2) {
	float dot;
	dot = (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);
	return dot;
}



//-------------------------------------
//   前方ベクトルの取得
//-------------------------------------
const XMFLOAT3 Math::GetFront(float rot) {
	float radian = XMConvertToRadians(rot);
	XMFLOAT3 front(
		cosf(radian),
		0.0f,
		sinf(radian)
	);
	return front;
}

//-------------------------------------
//   後方ベクトルの取得
//-------------------------------------
const XMFLOAT3 Math::GetBack(float rot) {
	float radian = XMConvertToRadians(rot);
	XMFLOAT3 back(
		cosf(radian + XM_PI),
		0.0f,
		sinf(radian + XM_PI)
	);
	return back;
}

//-------------------------------------
//   右ベクトルの取得
//-------------------------------------
const XMFLOAT3 Math::GetRight(float rot) {
	float radian = XMConvertToRadians(rot);
	XMFLOAT3 right(
		cosf(radian + (XM_PI/2)),
		0.0f,
		sinf(radian + (XM_PI/2))
	);
	return right;
}

//-------------------------------------
//   左ベクトルの取得
//-------------------------------------
const XMFLOAT3 Math::GetLeft(float rot) {
	float radian = XMConvertToRadians(rot);
	XMFLOAT3 left(
		cosf(radian - (XM_PI/2)),
		0.0f,
		sinf(radian - (XM_PI/2))
	);
	return left;
}


//----------------------------------------
//   二つの数値がほぼ同じか調べる
//----------------------------------------
bool Math::NearEqualF(float num1,float num2) {
	float error = num1 - num2;  // 誤差の取得
	if (error < 0.01f && error > -0.01f) {  // 誤差0.01未満なら
		return true;  // trueを返す
	}
	return false; // 誤差が0.01より大きいならfalseを返す
}

//---------------------------------------------
//  絶対値を取得する
//---------------------------------------------
float Math::AbsoluteValue(float num) {
	if (num < 0.0f) {
		num *= -1;
	}
	return num;
}