#pragma once


/// <summary>
/// シングルトンクラス終了処理
/// </summary>
class SingletonFainalizer
{
public:
	/// <summary>
	/// このクラスの関数を利用するための宣言
	/// </summary>
	using FinalizerFunc = void(*)();

	// シングルトンクラスの終了処理時に解放されるインスタンスの登録
	static void AddFinalizer(FinalizerFunc func);
	// シングルトンクラスの終了処理
	static void Fainalize();
};

