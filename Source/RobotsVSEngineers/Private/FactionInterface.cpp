#include "RobotsVSEngineers.h"

#include "FactionInterface.h"

#include <type_traits>

UFactionInterface::UFactionInterface(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UFaction Factions::GetEnemyFaction(UFaction Faction)
{
	auto FactionIndex = static_cast<std::underlying_type_t<UFaction>>(Faction);
	auto EnemyFactionIndex = (FactionIndex + 1) % Factions::NumberOfFactions;
	return static_cast<UFaction>(EnemyFactionIndex);
}
