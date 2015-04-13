// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotsVSEngineers.h"
#include "RobotsVSEngineersFunctionLibrary.h"

#include "RobotsVSEngineersGameMode.h"
#include "Unit.h"


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

bool URobotsVSEngineersFunctionLibrary::SpawnUnit(const ABuilding* Instigator, UClass* UnitClassToSpawn, FVector Location, FUnitSpawned UnitSpawned)
{
	auto GameState = Instigator->GetWorld()->GetGameState<ARvEGameState>();

	if (GameState) 
		return GameState->SpawnUnit(Instigator, UnitClassToSpawn, Location, UnitSpawned);

	return false;
}

bool URobotsVSEngineersFunctionLibrary::ResearchUnit(const ABuilding* Instigator, UFaction Faction, int32 Cost, int32 Time, FUnitResearched UnitResearched)
{
	auto GameState = Instigator->GetWorld()->GetGameState<ARvEGameState>();

	if (GameState)
		return GameState->ResearchUnit(Faction, Cost, Time, UnitResearched);

	return false;
}

bool URobotsVSEngineersFunctionLibrary::SpawnBuilding(const ABuilding* Instigator, UClass* BuildingClassToSpawn, FVector Location, FBuildingSpawned BuildingSpawned)
{
	auto GameState = Instigator->GetWorld()->GetGameState<ARvEGameState>();

	if (GameState)
		return GameState->SpawnBuilding(Instigator, BuildingClassToSpawn, Location, BuildingSpawned);

	return false;
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

int32 URobotsVSEngineersFunctionLibrary::GetCost(UClass* ClassQuery)
{
	if (!ClassQuery)
	{
		return -1;
	}

	auto DefaultUnit = Cast<AUnit>(ClassQuery->GetDefaultObject());

	if (DefaultUnit) 
	{
		return DefaultUnit->Stats.Cost;
	}

	auto DefaultBuilding = Cast<ABuilding>(ClassQuery->GetDefaultObject());

	if (DefaultBuilding) 
	{
		return DefaultBuilding->Stats.Cost;
	}

	return -1;
}

int32 URobotsVSEngineersFunctionLibrary::GetSpawnTime(UClass* ClassQuery)
{
	if (!ClassQuery)
	{
		return -1;
	}

	auto DefaultUnit = Cast<AUnit>(ClassQuery->GetDefaultObject());

	if (DefaultUnit)
	{
		return DefaultUnit->Stats.SpawnTime;
	}

	auto DefaultBuilding = Cast<ABuilding>(ClassQuery->GetDefaultObject());

	if (DefaultBuilding)
	{
		return DefaultBuilding->Stats.SpawnTime;
	}

	return -1;
}
