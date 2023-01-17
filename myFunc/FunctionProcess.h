#pragma once

#include "Affine.h"
#include "math.h"
#include "MathUtility.h"
#include "Matrix4.h"
#include "WorldTransform.h"

//�~����
const float PI = 3.141592654f;

namespace FuncProcess
{
	/// <summary>
	/// affine�ϊ��̌v�Z����
	/// </summary>
	/// <param name="worldTransform">����object�̏�Ԃ��擾</param>
	/// <param name="i">�e�q�֌W������ꍇfor���Ŋ֌W��������, �Ȃ��ꍇ��0</param>
	void Matrix4(WorldTransform& worldTransform, int i);

	/// <summary>
	/// �x���@ -> ���W�A��
	/// </summary>
	float radConvert(float value);

	/// <summary>
	/// ���W�A�� -> �x���@
	/// </summary>
	float degConvert(float value);
};

