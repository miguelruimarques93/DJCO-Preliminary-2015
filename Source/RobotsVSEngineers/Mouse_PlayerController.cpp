// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotsVSEngineers.h"
#include "Mouse_PlayerController.h"

AMouse_PlayerController::AMouse_PlayerController(const class FObjectInitializer& obj) :
	APlayerController(obj)
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}
