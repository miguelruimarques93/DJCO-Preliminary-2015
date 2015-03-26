#pragma once

#include "Types.generated.h"

UENUM()
enum class UType : uint8
{
	Physical,
	Poison
};

USTRUCT()
struct FPawnStats
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Data)
	int32 BaseHealthPoints;

	UPROPERTY(EditDefaultsOnly, Category = Data)
	int32 Attack;

	UPROPERTY(EditDefaultsOnly, Category = Data)
	int32 AttackRange;

	UPROPERTY(EditDefaultsOnly, Category = Data)
	int32 AttackSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Data)
	int32 SpawnTime;

	UPROPERTY(EditDefaultsOnly, Category = Data)
	UType AttackType;

	UPROPERTY(EditDefaultsOnly, Category = Data)
	TArray<UType> DefenseTypes;

	FPawnStats()
	{
		BaseHealthPoints = 100;
		Attack = 20;
		AttackRange = 75;
		AttackSpeed = 2000;
		SpawnTime = 2;

		AttackType = UType::Physical;
	}
};