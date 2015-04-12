// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "FactionInterface.h"
#include "Types.h"

#include "Building.generated.h"

UCLASS()
class ROBOTSVSENGINEERS_API ABuilding : public APawn, public IFactionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABuilding();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 Health;


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

	virtual void GenerateResources();
	
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void Die(AActor* DamageCauser);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	uint8 bIsDead : 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Building)
	FPawnStats Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	int32 ResourcesGeneratedPerTimeUnit;

	UFUNCTION(BlueprintNativeEvent, Category = UI)
	void OnSelectionGained();

	virtual void OnSelectionGained_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = UI)
	void OnSelectionLost();

	virtual void OnSelectionLost_Implementation();

private:

	float TimeToGenerateResources;
};
