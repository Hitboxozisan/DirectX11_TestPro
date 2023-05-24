#pragma once

#include <mutex>
#include <cassert>
#include "SingletonFainalizer.h"

/// <summary>
/// クラスをシングルトン化する
/// </summary>
template <typename T>
class Singleton final
{
public:
	//static T& GetInstanceComPtr()
	//{
	//	call_once(initFlag, CreateComPtr);
	//}


	static T& GetInstance()
	{
		call_once(initFlag, Create);
		assert(instance);
		return *instance;
	}

private:
	//static void CreatePtr()
	//{
	//	
	//}

	// インスタンスの生成
	static void Create()
	{
		instance = new T;
		// 解放処理にインスタンスを登録
		SingletonFainalizer::AddFinalizer(&Singleton<T>::Delete);
	}

	// インスタンスの解放
	static void Delete()
	{
		delete instance;
		instance = nullptr;
	}

	static std::once_flag initFlag;
	// クラスのインスタンス
	static T* instance;
};

// 静的メンバ変数の実態を定義
template <typename T> std::once_flag Singleton<T>::initFlag;
template <typename T> T* Singleton<T>::instance = nullptr;