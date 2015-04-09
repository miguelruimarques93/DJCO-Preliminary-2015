#pragma once

#include "FactionInterface.generated.h"

UENUM()
enum class UFaction : uint8
{
	Engineers,
	Robots
};

namespace Factions
{
	CONSTEXPR const auto NumberOfFactions = 2;
	UFaction GetEnemyFaction(UFaction Faction);
}

UINTERFACE()
class UFactionInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()

};

class IFactionInterface
{
	GENERATED_IINTERFACE_BODY()

	virtual UFaction GetFaction() const = 0;
};