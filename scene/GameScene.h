#pragma once

#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Object3d.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Model.h"
#include "Audio.h"
#include <string>


/// <summary>
/// �Q�[���V�[��
/// </summary>
class GameScene
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // �ÓI�����o�ϐ�
	static const int debugTextTexNumber = 0;

public: // �����o�֐�

	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	GameScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private: // �����o�ϐ�
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	Audio* audio = nullptr;
	
	/// <summary>
	/// �Q�[���V�[���p
	/// </summary>
	Sprite* title = new Sprite();
	XMFLOAT2 titlePos = title->GetPosition();

	Sprite* rule = new Sprite();
	XMFLOAT2 rulePos = rule->GetPosition();

	Sprite* cle = new Sprite();
	XMFLOAT2 clePos = cle->GetPosition();

	Sprite* over = new Sprite();
	XMFLOAT2 overPos = over->GetPosition();

	Sprite* font1 = new Sprite();
	XMFLOAT2 font1Pos = font1->GetPosition();

	Sprite* font2 = new Sprite();
	XMFLOAT2 font2Pos = font2->GetPosition();

	Sprite* font3 = new Sprite();
	XMFLOAT2 font3Pos = font3->GetPosition();

	// �����������ǂ���
	int isHit = 0;

	Object3d* player = nullptr;
	Object3d* key = nullptr;
	Object3d* skydome = nullptr;

	Model* playerModel = nullptr;
	Model* keyModel = nullptr;
	Model* skydomeModel = nullptr;

	int scene = 0;
	int time = 180;

	int limit = 0;
};

