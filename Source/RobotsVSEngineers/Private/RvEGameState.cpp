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
