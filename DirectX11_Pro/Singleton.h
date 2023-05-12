#pragma once

#include <mutex>

/// <summary>
/// �N���X���V���O���g��������
/// </summary>
template <typename T>
class Singleton final
{
public:

	static T& GetInstance()
	{
		std::call_once(initFlag, Create);
	}

private:

	// �C���X�^���X�̐���
	static void Create()
	{
		instance = new T;
		// ��������ɃC���X�^���X��o�^
		
	}

	// �C���X�^���X�̉��
	static void Delete()
	{
		delete instance;
		instance = nullptr;
	}

	static std::once_flag initFlag;
	// �N���X�̃C���X�^���X
	static T* instance;
};

// �ÓI�����o�ϐ��̎��Ԃ��`
template <typename T>std::once_flag Singleton<T>::initFlag;
template <typename T> T* Singleton<T>::instance = nullptr;