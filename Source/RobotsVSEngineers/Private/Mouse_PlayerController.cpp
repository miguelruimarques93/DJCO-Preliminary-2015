// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotsVSEngineers.h"
#include "Mouse_PlayerController.h"
#include <system_error>

AMouse_PlayerController::AMouse_PlayerController(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	bBlockInput = false;
	
}

void AMouse_PlayerController::OnClick()
{
	auto Building = GetBuildingAtCursor();
	SetSelected(Building);
}

void AMouse_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &AMouse_PlayerController::OnClick);
}

ABuilding* AMouse_PlayerController::GetBuildingAtCursor()
{
	FHitResult Hit;
	
	if (GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, Hit))
	{
		auto Actor = Hit.GetActor();
		if (!Actor)
			return nullptr;

		auto Building = Cast<ABuilding>(Actor);

		if (!Building)
			return nullptr;

		return Building;
	}

	return nullptr;
}

void AMouse_PlayerController::SetSelected(ABuilding* NewBuilding)
{
	if (NewBuilding) 
	{
		UE_LOG(LogTemp, Display, TEXT("Selection Changed: %s"), *NewBuilding->GetHumanReadableName());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Selection Changed: nullptr"));
	}
		

	

	if (SelectedBuilding == NewBuilding)
		return;

	if (SelectedBuilding)
	{
		SelectedBuilding->OnSelectionLost();
		SelectedBuilding = nullptr;
	}

	if (NewBuilding && !SelectedBuilding)
	{
		SelectedBuilding = NewBuilding;
		SelectedBuilding->OnSelectionGained();
	}
}
