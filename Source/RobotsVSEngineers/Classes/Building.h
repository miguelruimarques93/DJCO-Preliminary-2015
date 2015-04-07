// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "FactionInterface.h"


#include "Building.generated.h"

UCLASS()
class ROBOTSVSENGINEERS_API ABuilding : public APawn, public IFactionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABuilding();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	UFaction Faction;

	UFUNCTION(BlueprintCallable, Category = Game)
	virtual UFaction GetFaction() const override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
	
};
