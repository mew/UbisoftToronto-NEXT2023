#include "stdafx.h"
#include <windows.h> 

#include "GameScreen.h"
#include "Screen.h"
#include "TitleScreen.h"
#include "utils.h"
#include "app/app.h"

// 
// This file from provided api
// 

void Init() {
	ScreenHolder::ChangeScreen(new TitleScreen());
	ScreenHolder::GetScreen()->Init();
}

void Update(float deltaTime) {
	ScreenHolder::GetScreen()->Update();
}

void Render() {
	ScreenHolder::GetScreen()->Render();
}

void Shutdown() {
}