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
/// ゲームシーン
/// </summary>
class GameScene
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // 静的メンバ変数
	static const int debugTextTexNumber = 0;

public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	Audio* audio = nullptr;
	
	/// <summary>
	/// ゲームシーン用
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

	// 当たったかどうか
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

