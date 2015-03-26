// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"

#include "FactionInterface.h"
#include "Types.h"

#include "Unit.generated.h"

UCLASS()
class ROBOTSVSENGINEERS_API AUnit : public ACharacter, public IFactionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnit();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintCallable, Category=Game)
	virtual UFaction GetFaction() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Unit)
	UFaction Faction;

	UPROPERTY(EditDefaultsOnly, Category = Unit)
	FPawnStats Stats;
	
	
};
