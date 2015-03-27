// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "RobotsVSEngineersGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ROBOTSVSENGINEERS_API ARobotsVSEngineersGameMode : public AGameMode
{
	GENERATED_BODY()

	ARobotsVSEngineersGameMode(const class FObjectInitializer&);

public:
	static bool OnAllyFaction(const AActor* ActorA, const AActor* ActorB);

	static bool OnEnemyFaction(const AActor* ActorA, const AActor* ActorB);
	
	static bool IsUnitAlive(AActor* Actor);
	
	static bool IsUnitDead(AActor* Actor);
};
