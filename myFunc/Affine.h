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
	/// �x���@ -> ���W�A��
	/// </summary>
	float radConvert(float value);

	/// <summary>
	/// ���W�A�� -> �x���@
	/// </summary>
	float degConvert(float value);

	// �P�ʍs�񐶐�
	Matrix4 identityMatrix();

	// �x�N�g���ƍs��̊|���Z
	Vector3 vectorMul(Vector3 vec, Matrix4 mat);
	Vector3 vectorMul3D(Vector3 vec, Matrix4 mat);

	// �g�k
	Matrix4 matScale(Vector3 scale);
	Matrix4 matScale(float scaleX, float scaleY, float scaleZ);

	// ��]
	Matrix4 matRotateX(float rotationX);
	Matrix4 matRotateY(float rotationY);
	Matrix4 matRotateZ(float rotationZ);
	Matrix4 matRotation(float rotateX, float rotateY, float rotateZ);
	Matrix4 vecRotation(Vector3 rotate);

	// ���s�ړ�
	Matrix4 matTrans(Vector3 move);
	Matrix4 vecTrans(float moveX, float moveY, float moveZ);

	// �s��̍���
	Matrix4 matWorld(Vector3 move, Vector3 rotate, Vector3 scale);

	// ���[���h���W�擾
	Vector3 GetWorldTrans(Matrix4 matrix);

	// W���Z
	Vector3 wDivision(Vector3 vector, Matrix4 matrix);

	//sin�Acos�������o��
	void SinCos(float& sin_, float& cos_, float angle);
};


