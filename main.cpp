
#include "FPS.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "GameScene.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

#pragma region WindowsApi初期化処理
	//ポインタ
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	FPS* fps = new FPS;
	Input* input = nullptr;
	GameScene* gameScene = nullptr;

	//windowsAPIの初期化
	winApp = new WinApp();
	winApp->Initialize();

	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	MSG msg = {};
	
	//入力の初期化　
	input = new Input();
	input->Initialize(winApp);
#pragma endregion

#pragma region DirectX初期化処理
	// 3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
#pragma endregion

#pragma region 描画初期化処理

	//
	// 音声読み込み
	//

	// ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize(dxCommon, input);

	// FPS変更
	fps->SetFrameRate(60);
#pragma endregion

	//ゲームループ
	while (true) {
#pragma region ウィンドウメッセージ処理
		//アプリケーションが終わる時にmessageがWM_QUITになる
		if (msg.message == WM_QUIT) {
			break;
		}
		if (input->PushKey(DIK_ESCAPE)) {
			break;
		}

		fps->FpsControlBegin();

#pragma endregion

#pragma region DirectX毎フレーム処理
		//
		// DireceX毎フレーム処理　ここから
		//

		//入力の更新
		input->Update();
		// ゲームシーンの毎フレーム処理
		gameScene->Update();

		//
		// DireceX毎フレーム処理　ここまで
		//

#pragma endregion

#pragma region グラフィックスコマンド

		//4.描画コマンドここから
		dxCommon->PreDraw(); 
		// ゲームシーンの描画
		gameScene->Draw();
		// 描画終了
		dxCommon->PostDraw();

		fps->FpsControlEnd();
		//4.描画コマンドここまで

#pragma endregion

#pragma region 画面入れ替え

#pragma endregion
	}
#pragma region  WindowsAPI終了処理

	// ゲームシーン解放
	delete gameScene;
	gameScene = nullptr;

	//WindowsAPIの終了処理
	winApp->Finalize();

	// 入力解放
	delete input;
	input = nullptr;
	// WindowsAPI開放
	delete winApp;
	winApp = nullptr;
	// DirectX解放
	delete dxCommon;
	dxCommon = nullptr;
	// fps固定設定解放
	delete fps;
	fps = nullptr;

#pragma endregion
	return 0;
}