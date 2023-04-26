#include "Common.h"
#include "Fps.h"
#include "Text.h"

/// <summary>
/// ����������
/// </summary>
void Fps::Init(Text* inText)
{

	time = 0;
	frame = 0;
	av_frame = 0;
	fps[3600] = { 0 };//�v����1���Ԉȓ��ɂ��邱��
	avg = 0;
	first2 = 0;

	text = inText;
}

/// <summary>
/// �`�揈��
/// </summary>
void Fps::Render()
{
	frame++;
	if (timeGetTime() - time > 1000)
	{
		first2++;
		fps[av_frame] = frame;
		if (first2 > 2)
		{
			av_frame++;
			avg = 0;
			for (int i = 0; i < av_frame; i++)
			{
				avg += fps[i];
			}
			avg = (float)avg / (float)av_frame;
		}
		sprintf(str, "fps=%d avg_fps=%d", frame, avg);
		time = timeGetTime();
		frame = 0;
	}
	text->Render(str, X, Y);
}
