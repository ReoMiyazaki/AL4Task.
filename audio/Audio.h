#pragma once

#include <xaudio2.h>
#include <cstdint>
#include <wrl.h>
#include <map>
#include <string>
#include <fstream>

/// <summary>
/// オーディオ
/// </summary>
class Audio
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	//チャンクヘッダ
	struct ChunkHeader {
		char id[4];		//チャンク毎のID
		int32_t size;	//チャンクサイズ
	};
	//RIFFヘッダチャンク
	struct RiffHeader {
		ChunkHeader chunk;	//"RIFF"
		char type[4];		//"WAVE"
	};
	//FMTチャンク
	struct FormatChunk {
		ChunkHeader chunk;	//"fmt"
		WAVEFORMATEX fmt;	//波形フォーマット
	};
	//音声データ
	struct SoundData {
		//波形フォーマット
		WAVEFORMATEX wfex;
		//バッファの先頭アドレス
		BYTE* pBuffer;
		//バッファサイズ
		unsigned int bufferSize;
	};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const std::string& directoryPath = "Resources/");

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// //音声データの読み込み
	/// </summary>
	void LoadWave(const std::string& filename);

	/// <summary>
	/// //音声の解放
	/// </summary>
	void Unload(SoundData* soundData);

	/// <summary>
	/// //音声再生
	/// </summary>
	void PlayWave(const std::string& filename);

private:
	//サウンド再生
	ComPtr<IXAudio2> xAudio2_;
	//サウンドデータの連想配列
	std::map<std::string, SoundData> soundDates_;
	//サウンド格納ディレクトリ
	std::string directoryPath_;
};

