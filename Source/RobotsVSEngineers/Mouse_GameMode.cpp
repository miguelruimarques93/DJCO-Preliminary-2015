// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotsVSEngineers.h"
#include "Mouse_GameMode.h"
#include "Mouse_PlayerController.h"

AMouse_GameMode::AMouse_GameMode(const class FObjectInitializer& obj) : AGameMode(obj)
{
	this->PlayerControllerClass = AMouse_PlayerController::StaticClass();
}
