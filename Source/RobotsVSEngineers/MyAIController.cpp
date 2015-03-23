// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotsVSEngineers.h"
#include "MyAIController.h"
#include "Navigation/CrowdFollowingComponent.h"

AMyAIController::AMyAIController(const FObjectInitializer& Object)
	: Super(Object.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
}

