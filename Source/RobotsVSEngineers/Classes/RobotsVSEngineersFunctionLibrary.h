// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "Building.h"
#include "Unit.h"

#include "RobotsVSEngineersFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ROBOTSVSENGINEERS_API URobotsVSEngineersFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = Game)
	static bool AreAllies(AActor* Actor1, AActor* Actor2);

	UFUNCTION(BlueprintPure, Category = Game)
	static bool AreEnemies(AActor* Actor1, AActor* Actor2);
	
	UFUNCTION(BlueprintPure, Category = Game)
	static bool IsUnitAlive(AActor* Actor);
	
	UFUNCTION(BlueprintPure, Category = Game)
	static bool IsUnitDead(AActor* Actor);

	UFUNCTION(BlueprintPure, Category = Game)
	static AActor* GetUnitDestination(const AUnit* InUnit);

	UFUNCTION(BlueprintPure, Category = Animation)
	static float GetAnimSequenceLength(UAnimSequence* anim);

	UFUNCTION(BlueprintCallable, Category = Game)
	static AUnit* SpawnUnit(const ABuilding* Instigator, UClass* UnitClassToSpawn, FVector Location);

	UFUNCTION(BlueprintCallable, Category = Game)
	static ABuilding* SpawnBuilding(const ABuilding* Instigator, UClass* BuildingClassToSpawn, FVector Location);

	UFUNCTION(BlueprintCallable, Category = Helpers)
	static TArray<AUnit*> PushUnit(TArray<AUnit*> InArray, AUnit* unitToPush);

	UFUNCTION(BlueprintCallable, Category = Helpers)
	static AUnit* TopUnit(TArray<AUnit*> array);
};
