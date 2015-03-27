// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
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
};
