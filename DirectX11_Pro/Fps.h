#pragma once

#include "Common.h"

class Text;

/// <summary>
/// フレームレート計算・表示
/// </summary>
class Fps
{
public:
	
	void Init(Text* inText);
	void Render();

	Text* text;

private:
	// 定数
	const int X = 0;
	const int Y = 0;

	DWORD time;
	int frame;
	int av_frame;
	int fps[3600];		//計測は1時間以内にすること
	int avg;
	int first2;
	char str[50];

};

