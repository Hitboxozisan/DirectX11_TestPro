#include <mutex>
#include <cassert>
#include "SingletonFainalizer.h"


namespace
{
	// 解放処理を行えるインスタンスの最大数
	constexpr int finalizersSizeMax = 256;
	std::mutex Mutex;
	// 解放処理に登録されているインスタンスの数
	int finalizerNum = 0;
	// 解放処理用の関数
	SingletonFainalizer::FinalizerFunc finalizerFunc[finalizersSizeMax];
}

void SingletonFainalizer::AddFinalizer(FinalizerFunc func)
{
	//  排他制御を行う
	std::lock_guard<std::mutex> lock(Mutex);
	//  登録できるインスタンス数を超えたらエラーを出す
	assert(finalizerNum < finalizersSizeMax);
	//  インスタンスを解放処理に登録
	finalizerFunc[finalizerNum++] = func;
}

void SingletonFainalizer::Fainalize()
{
	//  排他制御を行う
	std::lock_guard<std::mutex> lock(Mutex);
	//  登録されているインスタンスを全て解放する
	for (int i = finalizerNum - 1; i >= 0; --i) {
		(*finalizerFunc[i])();
	}
	finalizerNum = 0;
}
