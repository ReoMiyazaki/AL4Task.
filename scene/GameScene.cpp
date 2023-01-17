#include "GameScene.h"
#include "Affine.h"
#include <cassert>
#include <random>

using namespace DirectX;

//乱数生成装置
std::random_device seed_gen;
std::mt19937_64 engine(seed_gen());
std::uniform_real_distribution<float>distX(-20.0f, 20.0f);
std::uniform_real_distribution<float>distZ(0.0f, 100.0f);

GameScene::GameScene() {}

GameScene::~GameScene() {
	//3Dオブジェクト解放
	delete player;
	delete key;
	delete skydome;

	//3Dモデル解放
	delete playerModel;
	delete keyModel;
	delete skydomeModel;

	//オーディオ解放
	audio->Finalize();
	delete audio;

}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	//スプライトの初期化
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
	//スプライトの画像指定
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
	// OBJからモデルデータを読み込み
	{
		playerModel = Model::LoadFromOBJ("player");
		keyModel = Model::LoadFromOBJ("enemy");
		skydomeModel = Model::LoadFromOBJ("skydome");
	}
	//3Dオブジェクト生成
	{
		player = Object3d::Create();
		key = Object3d::Create();
		skydome = Object3d::Create();
	}
	// オブジェクトにモデルを紐づける
	{
		player->SetModel(playerModel);
		key->SetModel(keyModel);
		skydome->SetModel(skydomeModel);
	}
	//3Dオブジェクトの位置を指定
	{
		key->SetPosition({ distX(engine),0,distZ(engine) });
		skydome->SetScale({ 10000, 10000, 10000 });
	}
	// 3Dオブジェクトの向きを変更
	{
		player->SetRotate({ 0,0,180 });
	}
	// 3Dオブジェクトの向きを変更
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
		limit = time / 60;	// 1が出力されん

		// オブジェクト移動
		if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
		{
			// 現在の座標を取得
			XMFLOAT3 position = player->GetPosition();

			// 移動後の座標を計算
			if (input->PushKey(DIK_UP)) { position.z += 1.0f; }
			else if (input->PushKey(DIK_DOWN)) { position.z -= 1.0f; }
			if (input->PushKey(DIK_RIGHT)) { position.x -= 1.0f; }
			else if (input->PushKey(DIK_LEFT)) { position.x += 1.0f; }

			if (position.x < -50) { position.x = -50; }
			if (position.x > 50) { position.x = 50; }
			if (position.z > 100) { position.z = 100; }
			if (position.z < -100) { position.z = -50; }

			// 座標の変更を反映
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

	//当たり判定
	XMFLOAT3 a = key->GetPosition();
	XMFLOAT3 b = player->GetPosition();
	float xyz = std::pow(a.x - b.x, 2.0f) + std::pow(a.y - b.y, 2.0f) + std::pow(a.z - b.z, 2.0f);
	float lenR = std::pow(1.0f + 1.0f, 2.0f);
	if (xyz <= lenR) {
		isHit = 1;
	}

}

void GameScene::Draw() {

	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// <summary>

	//3Dオブジェクトの描画
	player->Draw();
	key->Draw();
	skydome->Draw();

	//3Dオブジェクト描画後処理
	Object3d::PostDraw();

	// スプライトの描画
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