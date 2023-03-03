#include "stdafx.h"
#include <windows.h> 

#include "Screen.h"
#include "TestScreen.h"
#include "app/app.h"

Screen* currentScreen;

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init() {
	currentScreen = new TestScreen;
	currentScreen->Init();
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	currentScreen->Update();
	// //------------------------------------------------------------------------
	// // Example Sprite Code....
	// testSprite->Update(deltaTime);
	// if (App::GetController().GetLeftThumbStickX() > 0.5f)
	// {
	// 	testSprite->SetAnimation(ANIM_RIGHT);
	// 	float x, y;
	// 	testSprite->GetPosition(x, y);
	// 	x += 1.0f;
	// 	testSprite->SetPosition(x, y);
	// }
	// if (App::GetController().GetLeftThumbStickX() < -0.5f)
	// {
	// 	testSprite->SetAnimation(ANIM_LEFT);
	// 	float x, y;
	// 	testSprite->GetPosition(x, y);
	// 	x -= 1.0f;
	// 	testSprite->SetPosition(x, y);
	// }
	// if (App::GetController().GetLeftThumbStickY() > 0.5f)
	// {
	// 	testSprite->SetAnimation(ANIM_FORWARDS);
	// 	float x, y;
	// 	testSprite->GetPosition(x, y);
	// 	y += 1.0f;
	// 	testSprite->SetPosition(x, y);
	// }
	// if (App::GetController().GetLeftThumbStickY() < -0.5f)
	// {
	// 	testSprite->SetAnimation(ANIM_BACKWARDS);
	// 	float x, y;
	// 	testSprite->GetPosition(x, y);
	// 	y -= 1.0f;
	// 	testSprite->SetPosition(x, y);
	// }
	// if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
	// {
	// 	testSprite->SetScale(testSprite->GetScale() + 0.1f);
	// }
	// if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
	// {
	// 	testSprite->SetScale(testSprite->GetScale() - 0.1f);
	// }
	// if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
	// {
	// 	testSprite->SetAngle(testSprite->GetAngle() + 0.1f);
	// }
	// if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
	// {
	// 	testSprite->SetAngle(testSprite->GetAngle() - 0.1f);
	// }
	// if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	// {
	// 	testSprite->SetAnimation(-1);
	// }
	//
	// //------------------------------------------------------------------------
	// // Sample Sound.
	// //------------------------------------------------------------------------
	// if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	// {
	// 	App::PlaySound(".\\TestData\\Test.wav");
	// }
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render() {
	currentScreen->Render();

	
	//App::Print(100, 100, "Sample Text");
//
	//float cw = (float) CENTRE_SCREEN_W;
	//Utils::DrawRect(cw - 50, 60, cw + 50, 90);
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown() {
}