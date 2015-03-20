// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotsVSEngineers.h"
#include "RobotsVSEngineersGameMode.h"
#include "Mouse_PlayerController.h"

ARobotsVSEngineersGameMode::ARobotsVSEngineersGameMode(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	this->PlayerControllerClass = AMouse_PlayerController::StaticClass();
}
