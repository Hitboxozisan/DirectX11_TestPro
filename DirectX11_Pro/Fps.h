#pragma once

#include "Common.h"

class Text;

/// <summary>
/// �t���[�����[�g�v�Z�E�\��
/// </summary>
class Fps
{
public:
	
	void Init(Text* inText);
	void Render();

	Text* text;

private:
	// �萔
	const int X = 0;
	const int Y = 0;

	DWORD time;
	int frame;
	int av_frame;
	int fps[3600];		//�v����1���Ԉȓ��ɂ��邱��
	int avg;
	int first2;
	char str[50];

};

