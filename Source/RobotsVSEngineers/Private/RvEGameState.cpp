// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotsVSEngineers.h"
#include "RvEGameState.h"

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

AUnit* ARvEGameState::SpawnActor(UClass* UnitClassToSpawn, FVector Location)
{
	auto DefaultUnit = Cast<AUnit>(UnitClassToSpawn->GetDefaultObject());
	auto UnitCost = DefaultUnit->Stats.Cost;
	auto Faction = DefaultUnit->GetFaction();
	auto FactionIndex = static_cast<std::underlying_type_t<UFaction>>(Faction);

	if (PlayersData[FactionIndex].ResourcesAvailable >= UnitCost) 
	{
		PlayersData[FactionIndex].ResourcesAvailable -= UnitCost;

		auto SpawnedUnit = GetWorld()->SpawnActor<AUnit>(UnitClassToSpawn, Location, Instigator->GetActorRotation());

		if (!SpawnedUnit)
			return nullptr;

		OnCharSpawned(SpawnedUnit);

		return SpawnedUnit;
	}
	
	return nullptr;
	
}