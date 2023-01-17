#include "Affine.h"

float affine::radConvert(float value)
{
	float radValue;

	radValue = value * (PI / 180);

	return radValue;
}

float affine::degConvert(float value)
{
	float degValue;

	degValue = value * (180 / PI);

	return degValue;
}

Matrix4 affine::identityMatrix()
{
	Matrix4 mat =
	{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	return mat;
}

Vector3 affine::vectorMul(Vector3 vec, Matrix4 mat)
{
	float x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + 0 * mat.m[3][0];
	float y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + 0 * mat.m[3][1];
	float z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + 0 * mat.m[3][2];

	Vector3 result = { x, y, z };

	return result;
}

Vector3 affine::vectorMul3D(Vector3 vec, Matrix4 mat)
{
	Vector3 Result = { 0, 0, 0 };

	Result.x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] * 1 * mat.m[3][0];
	Result.y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] * 1 * mat.m[3][1];
	Result.z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] * 1 * mat.m[3][2];

	return Result;
}

Matrix4 affine::matScale(Vector3 scale)
{
	Matrix4 matScale =
	{ 
		scale.x,	0.0f,    0.0f, 0.0f,
		   0.0f, scale.y,    0.0f, 0.0f,
		   0.0f,	0.0f, scale.z, 0.0f,
		   0.0f,	0.0f,    0.0f, 1.0f
	};

	return matScale;
}

Matrix4 affine::matScale(float scaleX, float scaleY, float scaleZ)
{
	Matrix4 matScale =
	{
		scaleX,   0.0f,   0.0f, 0.0f,
		  0.0f, scaleY,   0.0f, 0.0f,
		  0.0f,   0.0f, scaleZ, 0.0f,
		  0.0f,   0.0f,   0.0f, 1.0f
	};

	return matScale;
}

Matrix4 affine::matRotateX(float rotationX)
{
	float rotRad = radConvert(rotationX);
	float cosRad = cos(rotRad);
	float sinRad = sin(rotRad);

	Matrix4 matRotX =
	{
		1.0f,    0.0f,   0.0f, 0.0f,
		0.0f,  cosRad, sinRad, 0.0f,
		0.0f, -sinRad, cosRad, 0.0f,
		0.0f,    0.0f,   0.0f, 1.0f
	};

	return matRotX;
}

Matrix4 affine::matRotateY(float rotationY)
{
	float rotRad = radConvert(rotationY);
	float cosRad = cos(rotRad);
	float sinRad = sin(rotRad);
	Matrix4 matRotY = 
	{
		cosRad, 0.0f, -sinRad, 0.0f,
		  0.0f, 1.0f,    0.0f, 0.0f,
		sinRad, 0.0f,  cosRad, 0.0f,
		  0.0f, 0.0f,    0.0f, 1.0f
	};

	return matRotY;
}

Matrix4 affine::matRotateZ(float rotationZ)
{
	float rotRad = radConvert(rotationZ);
	float cosRad = cos(rotRad);
	float sinRad = sin(rotRad);
	Matrix4 matRotZ =
	{
		 cosRad, sinRad, 0.0f, 0.0f,
		-sinRad, cosRad, 0.0f, 0.0f,
		   0.0f,   0.0f, 1.0f, 0.0f,
		   0.0f,   0.0f, 0.0f, 1.0f
	};

	return matRotZ;
}

Matrix4 affine::matRotation(float rotateX, float rotateY, float rotateZ)
{
	Matrix4 x = matRotateX(rotateX);
	Matrix4 y = matRotateY(rotateY);
	Matrix4 z = matRotateZ(rotateZ);
	Matrix4 matRot;

	x *= z;
	y *= x;
	matRot = y;

	return matRot;
}

Matrix4 affine::vecRotation(Vector3 rotate)
{
	Matrix4 x = matRotateX(rotate.x);
	Matrix4 y = matRotateY(rotate.y);
	Matrix4 z = matRotateZ(rotate.z);
	Matrix4 matRot;

	x *= z;
	y *= x;
	matRot = y;

	return matRot;
}

Matrix4 affine::matTrans(Vector3 move)
{
	Matrix4 matTrans;

	matTrans =
	{
		  1.0f,   0.0f,   0.0f, 0.0f,
		  0.0f,   1.0f,   0.0f, 0.0f,
		  0.0f,   0.0f,   1.0f, 0.0f,
		move.x, move.y, move.z, 1.0f
	};

	return matTrans;
}

Matrix4 affine::vecTrans(float moveX, float moveY, float moveZ)
{
	Matrix4 matTrans;

	matTrans =
	{
		 1.0f,  0.0f,  0.0f, 0.0f,
		 0.0f,  1.0f,  0.0f, 0.0f,
		 0.0f,  0.0f,  1.0f, 0.0f,
		moveX, moveY, moveZ, 1.0f
	};

	return matTrans;
}

Matrix4 affine::matWorld(Vector3 move, Vector3 rotate, Vector3 scale)
{
	Matrix4 scaleM = matScale(scale);
	Matrix4 rotateM = vecRotation(rotate);
	Matrix4 moveM = matTrans(move);
	Matrix4 matWorld = identityMatrix();

	matWorld *= scaleM;
	matWorld *= rotateM;
	matWorld *= moveM;

	return matWorld;
}

Vector3 affine::GetWorldTrans(Matrix4 matrix)
{
	Vector3 mat;

	mat.x = matrix.m[3][0];
	mat.y = matrix.m[3][1];
	mat.z = matrix.m[3][2];

	return mat;
}

Vector3 affine::wDivision(Vector3 vector, Matrix4 matrix)
{
	Vector3 result;
	float w;

	w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];

	result = 
	{
	  (vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0]) / w,
	  (vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1]) / w,
	  (vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2]) / w 
	};

	return result;
}

void affine::SinCos(float& sin_, float& cos_, float angle)
{
	sin_ = sin(angle);
	cos_ = cos(angle);
}
