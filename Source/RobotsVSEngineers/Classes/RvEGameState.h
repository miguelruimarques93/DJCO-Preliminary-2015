// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "Optional.h"
#include "FactionInterface.h"
#include "RvEGameState.generated.h"

struct FPlayerData
{
	/** current resources */
	uint32 ResourcesAvailable;

	/** total resources gathered */
	uint32 ResourcesGathered;

	/** total damage done */
	uint32 DamageDone;

	uint32 UnitsKilled;

	uint32 UnitsLost;

	uint32 UnitsSpawned;

};

/**
 * 
 */
UCLASS()
class ROBOTSVSENGINEERS_API ARvEGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	
	ARvEGameState(const class FObjectInitializer&);

	/** Gameplay information about each player. */
	mutable TArray<FPlayerData> PlayersData;

	/** Winning Team information */
	TOptional<UFaction> WinningTeam;

	/**
	* Notification that a character has died.
	*
	* @param	InChar	The character that has died.
	*/
	void OnCharDied(class AUnit* KilledChar, class AUnit* KillerChar);

	/**
	* Notification that a character has spawned.
	*
	* @param	InChar	The character that has died.
	*/
	void OnCharSpawned(class AUnit* InChar);

	/**
	* Notification that an actor was damaged.
	*
	* @param	InChar	The character that has died.
	* @param	Damage	The amount of damage inflicted.
	* @param	InChar	The controller that inflicted the damage.
	*/
	void OnActorDamaged(class AActor* InActor, float Damage, class AController* EventInstigator);

	/**
	* Get a team's data.
	*
	* @param	TeamNum	The team to get the data for
	* @returns FPlayerData pointer to the data for requested team.
	*/
	FPlayerData* GetPlayerData(UFaction faction) const;


	
};
