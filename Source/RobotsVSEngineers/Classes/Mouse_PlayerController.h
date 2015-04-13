// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Building.h"

#include "Mouse_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ROBOTSVSENGINEERS_API AMouse_PlayerController : public APlayerController
{
	GENERATED_BODY()

	AMouse_PlayerController(const class FObjectInitializer&);

	ABuilding* GetBuildingAtCursor();

	void SetSelected(ABuilding* NewBuilding);

	UFUNCTION()
	void OnClick();

	virtual void SetupInputComponent();

public:

	UFUNCTION(BlueprintPure, Category = Transform)
	FRotator GetCameraRotation() const;




	ABuilding* SelectedBuilding;
};
