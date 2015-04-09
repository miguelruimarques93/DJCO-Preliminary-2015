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

void ARvEGameState::OnCharDied(class AUnit* KilledChar, class AUnit* KillerChar)
{
	auto killedFactionIndex = static_cast<std::underlying_type_t<UFaction>>(KilledChar->GetFaction());
	auto killerFactionIndex = static_cast<std::underlying_type_t<UFaction>>(KillerChar->GetFaction());

	PlayersData[killedFactionIndex].UnitsLost++;
	PlayersData[killerFactionIndex].UnitsKilled++;
}

void ARvEGameState::OnCharSpawned(class AUnit* InChar)
{
	auto factionIndex = static_cast<std::underlying_type_t<UFaction>>(InChar->GetFaction());

	PlayersData[factionIndex].UnitsSpawned++;
}

void ARvEGameState::OnActorDamaged(class AActor* InActor, float Damage, class AController* EventInstigator)
{
	//TODO
}

FPlayerData* ARvEGameState::GetPlayerData(UFaction faction) const
{
	auto factionIndex = static_cast<std::underlying_type_t<UFaction>>(faction);

	return &PlayersData[factionIndex];
}
