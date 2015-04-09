#pragma once

#include "Types.generated.h"

UENUM()
enum class UType : uint8
{
	Physical,
	Poison
};

USTRUCT(BlueprintType)
struct FPawnStats
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Data)
	int32 BaseHealthPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Data)
	int32 Attack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Data)
	int32 AttackRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Data)
	int32 AttackSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Data)
	int32 SpawnTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Data)
	int32 Cost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Data)
	UType AttackType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Data)
	TArray<UType> DefenseTypes;

	FPawnStats()
	{
		BaseHealthPoints = 100;
		Attack = 20;
		AttackRange = 75;
		AttackSpeed = 2000;
		SpawnTime = 2;
		Cost = 2;

		AttackType = UType::Physical;
	}
};