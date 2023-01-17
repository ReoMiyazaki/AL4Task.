#pragma once

#include "Affine.h"
#include "math.h"
#include "MathUtility.h"
#include "Matrix4.h"
#include "WorldTransform.h"

//円周率
const float PI = 3.141592654f;

namespace FuncProcess
{
	/// <summary>
	/// affine変換の計算処理
	/// </summary>
	/// <param name="worldTransform">そのobjectの状態を取得</param>
	/// <param name="i">親子関係がある場合for文で関係数分処理, ない場合は0</param>
	void Matrix4(WorldTransform& worldTransform, int i);

	/// <summary>
	/// 度数法 -> ラジアン
	/// </summary>
	float radConvert(float value);

	/// <summary>
	/// ラジアン -> 度数法
	/// </summary>
	float degConvert(float value);
};

