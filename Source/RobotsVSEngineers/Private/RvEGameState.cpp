// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotsVSEngineers.h"
#include "RvEGameState.h"
#include "RobotsVSEngineersGameMode.h"

#include "Unit.h"

#include <type_traits>



ARvEGameState::ARvEGameState(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayersData.AddZeroed(Factions::NumberOfFactions);
}

void ARvEGameState::OnCharDied(const class AUnit* KilledChar, const class IFactionInterface* Killer)
{
	auto killedFactionIndex = static_cast<std::underlying_type_t<UFaction>>(KilledChar->GetFaction());
	auto killerFactionIndex = static_cast<std::underlying_type_t<UFaction>>(Killer->GetFaction());

	PlayersData[killedFactionIndex].UnitsLost++;
	PlayersData[killerFactionIndex].UnitsKilled++;
}

void ARvEGameState::OnCharSpawned(const class AUnit* InChar)
{
	auto factionIndex = static_cast<std::underlying_type_t<UFaction>>(InChar->GetFaction());
	PlayersData[factionIndex].UnitsSpawned++;
}

void ARvEGameState::OnActorDamaged(const class IFactionInterface* DamagedActor, float Damage, const class IFactionInterface* DamageCauser)
{
	auto DamageCauserFaction = DamageCauser->GetFaction();
	auto DamageCauserFactionIndex = static_cast<std::underlying_type_t<UFaction>>(DamageCauserFaction);

	PlayersData[DamageCauserFactionIndex].DamageDone += Damage;

}

FPlayerData ARvEGameState::GetPlayerData(UFaction faction) const
{
	auto factionIndex = static_cast<std::underlying_type_t<UFaction>>(faction);

	return PlayersData[factionIndex];
}

void ARvEGameState::SetFactionHeadquarter(ABuilding* Headquarter)
{
	auto Faction = Headquarter->GetFaction();
	auto FactionIndex = static_cast<std::underlying_type_t<UFaction>>(Faction);
	PlayersData[FactionIndex].Headquarter = Headquarter;
}

void ARvEGameState::AddResources(const ABuilding* Building, uint32 Resources)
{
	auto Faction = Building->GetFaction();
	auto FactionIndex = static_cast<std::underlying_type_t<UFaction>>(Faction);
	PlayersData[FactionIndex].ResourcesAvailable += Resources;
	PlayersData[FactionIndex].ResourcesGathered += Resources;
}

bool ARvEGameState::SpawnUnit(const AActor* Instigator, UClass* UnitClassToSpawn, FVector Location, FUnitSpawned UnitSpawned)
{
	if (!UnitClassToSpawn)
	{
		UE_LOG(RveDevelopmentError, Error, TEXT("Invalid Unit class in '%s'."), *Instigator->GetName());
		return false;
	}

	auto DefaultUnit = Cast<AUnit>(UnitClassToSpawn->GetDefaultObject());

	if (!DefaultUnit)
	{
		UE_LOG(RveDevelopmentError, Error, TEXT("Invalid Unit class in '%s'."), *Instigator->GetName());
		return false;
	}

	auto UnitCost = DefaultUnit->Stats.Cost;
	auto Faction = DefaultUnit->GetFaction();
	auto FactionIndex = static_cast<std::underlying_type_t<UFaction>>(Faction);

	if (PlayersData[FactionIndex].ResourcesAvailable >= UnitCost)
	{
		PlayersData[FactionIndex].ResourcesAvailable -= UnitCost;

		FTimerHandle TimerHandle;

		FTimerDelegate TimerDelegate;
		TimerDelegate.BindLambda([this, UnitClassToSpawn, Location, Instigator, UnitSpawned](){
			auto SpawnedUnit = GetWorld()->SpawnActor<AUnit>(UnitClassToSpawn, Location, Instigator->GetActorRotation());

			if (SpawnedUnit) {
				OnCharSpawned(SpawnedUnit);
				UnitSpawned.ExecuteIfBound(SpawnedUnit);
			}
		});

		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, DefaultUnit->Stats.SpawnTime / 1000.0f, false);

		return true;
	}

	return false;
}

bool ARvEGameState::SpawnBuilding(const AActor* Instigator, UClass* BuildingClassToSpawn, FVector Location, FBuildingSpawned BuildingSpawned)
{
	if (!BuildingClassToSpawn)
	{
		UE_LOG(RveDevelopmentError, Error, TEXT("Invalid Building class in '%s'."), *Instigator->GetName());
		return false;
	}

	auto DefaultBuilding = Cast<ABuilding>(BuildingClassToSpawn->GetDefaultObject());

	if (!DefaultBuilding)
	{
		UE_LOG(RveDevelopmentError, Error, TEXT("Invalid Building class in '%s'."), *Instigator->GetName());
		return false;
	}

	auto BuildingCost = DefaultBuilding->Stats.Cost;
	auto Faction = DefaultBuilding->GetFaction();
	auto FactionIndex = static_cast<std::underlying_type_t<UFaction>>(Faction);

	if (PlayersData[FactionIndex].ResourcesAvailable >= BuildingCost)
	{
		PlayersData[FactionIndex].ResourcesAvailable -= BuildingCost;

		FTimerHandle TimerHandle;

		FTimerDelegate TimerDelegate;
		TimerDelegate.BindLambda([this, BuildingClassToSpawn, Location, Instigator, BuildingSpawned](){
			auto SpawnedBuilding = GetWorld()->SpawnActor<ABuilding>(BuildingClassToSpawn, Location, Instigator->GetActorRotation());

			if (SpawnedBuilding)
			{
				// OnBuildingSpawned(SpawnedBuilding);

				BuildingSpawned.ExecuteIfBound(SpawnedBuilding);
			}

			
		});

		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, DefaultBuilding->Stats.SpawnTime / 1000.0f, false);

		return true;
	}

	return false;
}

void ARvEGameState::BeginPlay()
{
	UE_LOG(LogTemp, Display, TEXT("PlayersData.Num() = %d"), PlayersData.Num());

	for (auto& PlayerData : PlayersData)
	{
		PlayerData.ResourcesAvailable += ARobotsVSEngineersGameMode::InitialResources;
		PlayerData.ResourcesGathered += ARobotsVSEngineersGameMode::InitialResources;
	}
}
