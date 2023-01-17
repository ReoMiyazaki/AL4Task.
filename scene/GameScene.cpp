#include "GameScene.h"
#include "Affine.h"
#include <cassert>
#include <random>

using namespace DirectX;

//�����������u
std::random_device seed_gen;
std::mt19937_64 engine(seed_gen());
std::uniform_real_distribution<float>distX(-20.0f, 20.0f);
std::uniform_real_distribution<float>distZ(0.0f, 100.0f);

GameScene::GameScene() {}

GameScene::~GameScene() {
	//3D�I�u�W�F�N�g���
	delete player;
	delete key;
	delete skydome;

	//3D���f�����
	delete playerModel;
	delete keyModel;
	delete skydomeModel;

	//�I�[�f�B�I���
	audio->Finalize();
	delete audio;

}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	//�X�v���C�g���ʕ����̏�����
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	//�X�v���C�g�̏�����
	{
		title->Initialize(spriteCommon);
		titlePos.x = 0.0f;
		titlePos.y = 0.0f;
		title->SetPozition(titlePos);
		title->SetSize(XMFLOAT2{ 1280.0f, 720.0f });

		rule->Initialize(spriteCommon);
		rulePos.x = 0.0f;
		rulePos.y = 0.0f;
		rule->SetPozition(rulePos);
		rule->SetSize(XMFLOAT2{ 1280.0f, 720.0f });

		cle->Initialize(spriteCommon);
		clePos.x = 0.0f;
		clePos.y = 0.0f;
		cle->SetPozition(clePos);
		cle->SetSize(XMFLOAT2{ 1280.0f, 720.0f });

		over->Initialize(spriteCommon);
		overPos.x = 0.0f;
		overPos.y = 0.0f;
		over->SetPozition(overPos);
		over->SetSize(XMFLOAT2{ 1280.f, 720.0f });

		font1->Initialize(spriteCommon);
		font1Pos.x = 576.0f;
		font1Pos.y = 296.0f;
		font1->SetPozition(font1Pos);
		font1->SetSize(XMFLOAT2{ 128.0f, 128.0f });

		font2->Initialize(spriteCommon);
		font2Pos.x = 576.0f;
		font2Pos.y = 296.0f;
		font2->SetPozition(font2Pos);
		font2->SetSize(XMFLOAT2{ 128.0f, 128.0f });

		font3->Initialize(spriteCommon);
		font3Pos.x = 576.0f;
		font3Pos.y = 296.0f;
		font3->SetPozition(font3Pos);
		font3->SetSize(XMFLOAT2{ 128.0f, 128.0f });
	}
	//�X�v���C�g�̉摜�w��
	{
		spriteCommon->LoadTexture(0, "title.png");
		title->SetTextureIndex(0);
		spriteCommon->LoadTexture(1, "rule.png");
		rule->SetTextureIndex(1);
		spriteCommon->LoadTexture(2, "cle.png");
		cle->SetTextureIndex(2);
		spriteCommon->LoadTexture(3, "over.png");
		over->SetTextureIndex(3);
		spriteCommon->LoadTexture(4, "1.png");
		font1->SetTextureIndex(4);
		spriteCommon->LoadTexture(5, "2.png");
		font2->SetTextureIndex(5);
		spriteCommon->LoadTexture(6, "3.png");
		font3->SetTextureIndex(6);
	}
	// OBJ���烂�f���f�[�^��ǂݍ���
	{
		playerModel = Model::LoadFromOBJ("player");
		keyModel = Model::LoadFromOBJ("enemy");
		skydomeModel = Model::LoadFromOBJ("skydome");
	}
	//3D�I�u�W�F�N�g����
	{
		player = Object3d::Create();
		key = Object3d::Create();
		skydome = Object3d::Create();
	}
	// �I�u�W�F�N�g�Ƀ��f����R�Â���
	{
		player->SetModel(playerModel);
		key->SetModel(keyModel);
		skydome->SetModel(skydomeModel);
	}
	//3D�I�u�W�F�N�g�̈ʒu���w��
	{
		key->SetPosition({ distX(engine),0,distZ(engine) });
		skydome->SetScale({ 10000, 10000, 10000 });
	}
	// 3D�I�u�W�F�N�g�̌�����ύX
	{
		player->SetRotate({ 0,0,180 });
	}
	// 3D�I�u�W�F�N�g�̌�����ύX
	{
		player->SetScale({ 0.5f, 0.5f, 0.5f });
	}

	audio = new Audio();
	audio->Initialize();
}


void GameScene::Update() {
	player->Update();
	skydome->Update();
	switch (scene)
	{

	case 0:
		if (input->TriggerKey(DIK_SPACE))
		{
			scene = 1;
			player->SetPosition(XMFLOAT3{ 0,0,-10 });
			isHit = 0;
			limit = 3;
			time = 180;
		}
		break;

	case 1:
		if (input->TriggerKey(DIK_SPACE))
		{
			scene = 2;
			key->SetPosition({ distX(engine), 0, distZ(engine) });
		}
		break;

	case 2:
		time--;
		limit = time / 60;	// 1���o�͂����

		// �I�u�W�F�N�g�ړ�
		if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
		{
			// ���݂̍��W���擾
			XMFLOAT3 position = player->GetPosition();

			// �ړ���̍��W���v�Z
			if (input->PushKey(DIK_UP)) { position.z += 1.0f; }
			else if (input->PushKey(DIK_DOWN)) { position.z -= 1.0f; }
			if (input->PushKey(DIK_RIGHT)) { position.x -= 1.0f; }
			else if (input->PushKey(DIK_LEFT)) { position.x += 1.0f; }

			if (position.x < -50) { position.x = -50; }
			if (position.x > 50) { position.x = 50; }
			if (position.z > 100) { position.z = 100; }
			if (position.z < -100) { position.z = -50; }

			// ���W�̕ύX�𔽉f
			player->SetPosition(position);
		}

		if (0 < time && isHit == 1)
		{
			scene = 3;
		}
		if (time <= 0)
		{
			scene = 4;
		}
		break;
	case 3:
		if (input->TriggerKey(DIK_SPACE))
		{
			scene = 0;
		}
		break;
	case 4:
		if (input->TriggerKey(DIK_SPACE))
		{
			scene = 0;
		}
		break;
	}


	key->Update();

	//�����蔻��
	XMFLOAT3 a = key->GetPosition();
	XMFLOAT3 b = player->GetPosition();
	float xyz = std::pow(a.x - b.x, 2.0f) + std::pow(a.y - b.y, 2.0f) + std::pow(a.z - b.z, 2.0f);
	float lenR = std::pow(1.0f + 1.0f, 2.0f);
	if (xyz <= lenR) {
		isHit = 1;
	}

}

void GameScene::Draw() {

	//3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCommandList());
	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// <summary>

	//3D�I�u�W�F�N�g�̕`��
	player->Draw();
	key->Draw();
	skydome->Draw();

	//3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

	// �X�v���C�g�̕`��
	switch (scene)
	{
	case 0:
		title->Draw();
		break;
	case 1:
		rule->Draw();
		break;
	case 2:
		if (limit == 2) { font3->Draw(); }
		if (limit == 1) { font2->Draw(); }
		if (limit == 0) { font1->Draw(); }
		break;
	case 3:
		cle->Draw();
		break;
	case 4:
		over->Draw();
		break;
	}



}