#pragma once

#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "WinApp.h"
#include "math.h"

namespace affine
{
	const float PI = 3.141592f;

	/// <summary>
	/// 度数法 -> ラジアン
	/// </summary>
	float radConvert(float value);

	/// <summary>
	/// ラジアン -> 度数法
	/// </summary>
	float degConvert(float value);

	// 単位行列生成
	Matrix4 identityMatrix();

	// ベクトルと行列の掛け算
	Vector3 vectorMul(Vector3 vec, Matrix4 mat);
	Vector3 vectorMul3D(Vector3 vec, Matrix4 mat);

	// 拡縮
	Matrix4 matScale(Vector3 scale);
	Matrix4 matScale(float scaleX, float scaleY, float scaleZ);

	// 回転
	Matrix4 matRotateX(float rotationX);
	Matrix4 matRotateY(float rotationY);
	Matrix4 matRotateZ(float rotationZ);
	Matrix4 matRotation(float rotateX, float rotateY, float rotateZ);
	Matrix4 vecRotation(Vector3 rotate);

	// 平行移動
	Matrix4 matTrans(Vector3 move);
	Matrix4 vecTrans(float moveX, float moveY, float moveZ);

	// 行列の合成
	Matrix4 matWorld(Vector3 move, Vector3 rotate, Vector3 scale);

	// ワールド座標取得
	Vector3 GetWorldTrans(Matrix4 matrix);

	// W除算
	Vector3 wDivision(Vector3 vector, Matrix4 matrix);

	//sin、cos両方を出力
	void SinCos(float& sin_, float& cos_, float angle);
};


