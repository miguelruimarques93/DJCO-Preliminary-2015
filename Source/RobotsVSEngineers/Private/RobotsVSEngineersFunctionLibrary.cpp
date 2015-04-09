// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotsVSEngineers.h"
#include "RobotsVSEngineersFunctionLibrary.h"

#include "RobotsVSEngineersGameMode.h"
#include "Unit.h"
#include "RvEGameState.h"


bool URobotsVSEngineersFunctionLibrary::AreAllies(AActor* Actor1, AActor* Actor2)
{
	return ARobotsVSEngineersGameMode::OnAllyFaction(Actor1, Actor2);
}

bool URobotsVSEngineersFunctionLibrary::AreEnemies(AActor* Actor1, AActor* Actor2)
{
	return ARobotsVSEngineersGameMode::OnEnemyFaction(Actor1, Actor2);
}

bool URobotsVSEngineersFunctionLibrary::IsUnitAlive(AActor* Actor)
{
	return ARobotsVSEngineersGameMode::IsUnitAlive(Actor);
}

bool URobotsVSEngineersFunctionLibrary::IsUnitDead(AActor* Actor)
{
	return ARobotsVSEngineersGameMode::IsUnitDead(Actor);
}

AActor* URobotsVSEngineersFunctionLibrary::GetUnitDestination(const AUnit* InUnit)
{
	auto GameState = InUnit->GetWorld()->GetGameState<ARvEGameState>();
	if (GameState)
	{
		return GameState->GetPlayerData(Factions::GetEnemyFaction(InUnit->GetFaction())).Headquarter;
	}

	return nullptr;
}

float URobotsVSEngineersFunctionLibrary::GetAnimSequenceLength(UAnimSequence* AnimSequence)
{
	return AnimSequence->SequenceLength;
}

AUnit* URobotsVSEngineersFunctionLibrary::SpawnUnit(const ABuilding* Instigator, UClass* UnitClassToSpawn, FVector Location)
{
	auto GameState = Instigator->GetWorld()->GetGameState<ARvEGameState>();
	if (GameState)
	{
		return GameState->SpawnActor(Instigator, UnitClassToSpawn, Location);
	}

	return nullptr;
}

TArray<AUnit*> URobotsVSEngineersFunctionLibrary::PushUnit(TArray<AUnit*> InArray, AUnit* unitToPush)
{
	InArray.HeapPush(unitToPush, [](AUnit& u1, AUnit& u2) { return u1.DistanceToTarget < u2.DistanceToTarget;  });
	return InArray;
}

AUnit* URobotsVSEngineersFunctionLibrary::TopUnit(TArray<AUnit*> array)
{
	return array.Num() > 0 ? array.HeapTop() : nullptr;
}
