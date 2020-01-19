#include "stdafx.h"
#include "MainGame.h"
//#include "MiniGame/IsoTile.h"
//#include "MiniGame/TileMap.h"
#include "MiniGame/MainMenu.h"

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
	//싱글톤 해제

	SCENEMANAGER->ReleaseAll();
	SCENEMANAGER->ReleaseSingleton();
	KEYMANAGER->ReleaseSingleton();
	TIMEMANAGER->ReleaseSingleton();
	SOUNDMANAGER->ReleaseSingleton();
	CAMMANAGER->ReleaseSingleton();
	IMGMANAGER->DeleteAll();
	IMGMANAGER->ReleaseSingleton();
	WRITEMANAGER->ReleaseSingleton();
}

HRESULT MainGame::init()
{
	//윈도우가 시작되서 지금까지 흐른 시간을 1/1000초 단위로
	//DWORD형을 리턴하는 함수다.
	srand(GetTickCount());
	////////////////////////////////////////////////////
	
	IMGMANAGER->AddImage("TILE", _T("tilemap.bmp"), 2, 2, "PS");
	IMGMANAGER->AddImage("egg", _T("알.bmp"), "PS2");
	IMGMANAGER->AddImage("Main", _T("Main.png"), "PS2");
	IMGMANAGER->AddImage("Logo", _T("Logo.png"), "PS2");
	IMGMANAGER->AddImage("Option", _T("SettingsButton.png"), 1, 2, "PS2");

	IMGMANAGER->AddImage("Cursor", _T("pointer.png"), "PS2");


	SOUNDMANAGER->addSound("BGM", "sound/Theme.wav", true);
	//GameNode* p;
	//
	//p = new IsoTile;
	//SCENEMANAGER->AddScene("Iso", p);
	//SCENEMANAGER->AddScene("Iso", new IsoTile);
	//SCENEMANAGER->AddScene("Tile", new TileMap);
	SCENEMANAGER->AddScene("MainMenu", new MainMenu);
	//
	//SCENEMANAGER->ChangeScene("Iso");
	SCENEMANAGER->ChangeScene("MainMenu");


	Cursor = IMGMANAGER->GetImage("Cursor");

	////////////////////////////////////////////////////
	ImGui::Create(g_hwnd, Device, DeviceContext);
	ImGui::StyleColorsDark();
	return S_OK;
}

void MainGame::release()
{
	////////////////////////////////////////////////////
	




	////////////////////////////////////////////////////
	ImGui::Delete();
}

void MainGame::update()
{
	////////////////////////////////////////////////////
	
	
	//if (KEYMANAGER->isKeyDown('1'))
	//{
	//	SCENEMANAGER->ChangeScene("Iso");
	//}
	//
	//
	//
	//if (KEYMANAGER->isKeyDown('2'))
	//{
	//	SCENEMANAGER->ChangeScene("Tile");
	//}
	
	SCENEMANAGER->ChangeScene("MainMenu");
	
	
	
	
	ShowCursor(false);
	
	SCENEMANAGER->CurrentSceneUpdate();

	////////////////////////////////////////////////////
	SOUNDMANAGER->Update();
	ImGui::Update();
}

void MainGame::render()
{
	D3DXCOLOR background = D3DXCOLOR(1, 1, 1, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float *)background);
	CAMMANAGER->SetBuffers();
	WRITEMANAGER->GetDc()->BeginDraw();
	TIMEMANAGER->render();
	////////////////////////////////////////////////////
	



	SCENEMANAGER->CurrentSceneRender();

	Cursor->Scale(110.0f, 60.0f);
	Cursor->Position(g_ptMouse.x + 46.0f, g_ptMouse.y - 23.0f);
	Cursor->Rotate(0, 0, 0);
	Cursor->Render();
	////////////////////////////////////////////////////
#ifdef _DEBUG
	ImGui::Render();
#endif
	
	WRITEMANAGER->GetDc()->EndDraw();
	SwapChain->Present(0, 0);

}
