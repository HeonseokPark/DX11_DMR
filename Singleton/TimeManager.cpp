#include "stdafx.h"
#include "TimeManager.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
//timeGetTime �Լ��� ����ϱ� ���� ���̺귯�� �߰�
//�����찡 ���۵ǰ� �� ���� �ð��� ����

TimeManager::TimeManager()
{
	// ���� http://www.tipssoft.com/bulletin/board.php?bo_table=FAQ&wr_id=735

		//Ŭ���� ������ ������ ������ �ݺ��Ǵ� ���ļ��� Ŭ�� ���ļ��� �ϴµ� �ٿ��� Ŭ�� �̶� ��

		/*��ǻ���� ���κ��忡�� �ϳ��� ���ػ� Ÿ�̸Ӱ� �����Ѵ�. �� Ÿ�̸Ӵ� ��Ȯ�ϰ� ������ ���ļ�
		(��, 1�ʿ� �� Ÿ�̸��� ���ɿ� �´� ������)�� ���� ������ �����ϰ��� �ϴ� �ڵ���� ���۰� ������
			CPU Ŭ������ ��� �� ���� ����ð��� ���� �� �ִ�.*/

	//QueryPerformanceFrequency : ���ػ� Ÿ�̸��� ���ļ�(1�ʴ� ������)�� �Ű������� ��� �Լ�
	//���� ���� ������ 0�� ��ȯ��
	//QueryPerformanceCounter : ���ػ� Ÿ�̸��� ���� CPU�� Ŭ�� ���� �Ű������� ��� �Լ�
	//���� ���� ������ 0�� ��ȯ��


	//���� Ÿ�̸� �������θ� üũ�Ѵ�.
	//���� Ÿ�̸Ӹ� �����ϸ� �ʴ� ����ũ�μ��ϵ���� ���� ����.
	//(1/1000000)
	//�ð� ����
	__int64 _periodFrequency;
	//									����������ȯ,����ü
	if (QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_periodFrequency)))
	{
		//64��Ʈ ������ ����� �� �ֵ��� ������ ������
		//����ũ�μ����带 (1/1000000)�� ���� �����Ͽ� ���� ��Ȯ�� �ð����� �����ϱ� ����
		_isHardware = true;
		//�ʱ�ȭ �ɶ� �������ð���(Ŭ������) ���� �ʱ�ȭ ����
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_lastTime));

		//���� ������ ��� �Ǵ��� �ʴ� �������� ������ �ʱ�ȭ
		_timeScale = 1.0f / _periodFrequency;
	}

	else
	{
		_isHardware = false;

		//timeGetTime:������(�ü��)�� ���۵Ǿ ���ݱ��� �帥 �ð��� 
		//1 / 1000 ��(milliseconds) ������ DWORD���� �����ϴ� �Լ���.

		//�ʱ�ȭ �� �� �������ð���(�и� ������ ����) ���� �ʱ�ȭ ����
		_lastTime = timeGetTime();
		//�и������� ũ��� ����̶�� �� �ʱ�ȭ
		_timeScale = 0.001f;
	}

	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPStimeElapsed = 0.0f;
	_worldTime = 0;
}


TimeManager::~TimeManager()
{
}

void TimeManager::SetFrame(UINT lock)
{
	//���� Ÿ�̸Ӹ� �����Ѵٸ�
	if (_isHardware)
	{
		//����ð���(Ŭ������) ���� �ʱ�ȭ ����
		QueryPerformanceCounter((reinterpret_cast<LARGE_INTEGER*>(&_curTime)));
	}
	else
	{
		//�������� ������ time �Լ��� �̿� �и�������(1/1000)
		_curTime = timeGetTime();
	}

	//������ �ð��� ���� �ð��� �� �����Ӵ� �����
	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	//�̰��� �ݺ��� ������ ����ð��� ������.
	//�̰����� �ݺ����� ���ٰ� ������ ���߸� ������Ʈ�� ������ ���Ե�
	if (lock > 0.0f)
	{
		//���� �������� �ð��� �����Ҷ����� ����
		while (_timeElapsed < (1.0f / lock))
		{
			if (_isHardware) QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_curTime));
			else _curTime = timeGetTime();

			//������ �ð��� ���� �ð��� �����
			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime;				//������ �ð��� ���
	_FPSFrameCount++;					//�ڵ����� ������ ī��Ʈ ����
	_FPStimeElapsed += _timeElapsed;	//�ʴ� ������ �ð� ����� ����
	_worldTime += _timeElapsed;			//��ü �ð� ����� ����

	//������ �ʱ�ȭ�� 1�ʸ��� ����
	if (_FPStimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPStimeElapsed = 0.0f;
	}
}

void TimeManager::render()
{
	wchar_t str[256];
	RECT rect = { 0, 0, 800, 20 };
#ifdef _DEBUG
	//FPS
	swprintf_s(str, L"FPS: %d", TIMEMANAGER->GetFrameRate());
	WRITEMANAGER->RenderText(str, rect, 20, L"����ü", D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f));

	//��ü����ð�
	swprintf_s(str, L"WorldTime: %f", TIMEMANAGER->GetWorldTime());
	rect = { 0, 20, 800, 40 };
	WRITEMANAGER->RenderText(str, rect, 20, L"����ü", D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f));

	//�������Ӵ� ����ð�
	swprintf_s(str, L"SecondPerFrameTime: %f", TIMEMANAGER->GetElapsedTime());
	rect = { 0, 40, 800, 60 };
	WRITEMANAGER->RenderText(str, rect, 20, L"����ü", D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f));
	
#else
	//FPS
	swprintf_s(str, L"FPS: %d", TIMEMANAGER->GetFrameRate());
	WRITEMANAGER->RenderText(str, rect, 20, L"����ü", D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f));
#endif  
}
