// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "Optional.h"
#include "FactionInterface.h"
#include "Building.h"


#include "RvEGameState.generated.h"

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_USTRUCT_BODY()

	/** current resources */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Data)
	int32 ResourcesAvailable;

	/** total resources gathered */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Data)
	int32 ResourcesGathered;

	/** total damage done */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Data)
	float DamageDone;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Data)
	int32 UnitsKilled;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Data)
	int32 UnitsLost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Data)
	int32 UnitsSpawned;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Data)
	ABuilding* Headquarter;

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
	void OnCharDied(const class AUnit* KilledChar, const class IFactionInterface* Killer);

	/**
	* Notification that a character has spawned.
	*
	* @param	InChar	The character that has died.
	*/
	void OnCharSpawned(const class AUnit* InChar);

	/**
	* Notification that an actor was damaged.
	*
	* @param	InChar	The character that has died.
	* @param	Damage	The amount of damage inflicted.
	* @param	InChar	The controller that inflicted the damage.
	*/
	void OnActorDamaged(const class IFactionInterface* DamagedActor, float Damage, const class IFactionInterface* DamageCauser);

	/**
	* Get a team's data.
	*
	* @param	TeamNum	The team to get the data for
	* @returns FPlayerData pointer to the data for requested team.
	*/
	UFUNCTION(BlueprintPure, Category = Player)
	FPlayerData GetPlayerData(UFaction faction) const;

	/**
	 * Set a faction's Headquarter
	 *
	 * @param Headquarter The Building that is going to be a headquarter.
	 */
	UFUNCTION(BlueprintCallable, Category = Game)
	void SetFactionHeadquarter(ABuilding* Headquarter);


	/**
	 * Add Resources to a Faction
	 * 
	 * @param Building The Building that generated the resources.
	 * @param Resources The amount of resources generated.
	 */
	UFUNCTION(BlueprintCallable, Category = Player)
	void AddResources(const ABuilding* Building, uint32 Resources);	

	AUnit* SpawnActor(UClass* UnitClassToSpawn, FVector Location);
};
