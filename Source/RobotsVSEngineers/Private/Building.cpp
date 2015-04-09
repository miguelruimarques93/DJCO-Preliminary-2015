// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotsVSEngineers.h"
#include "Building.h"

#include "RvEGameState.h"
#include "RobotsVSEngineersGameMode.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->TimeToGenerateResources = ARobotsVSEngineersGameMode::SecondsPerTurn;

}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuilding::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	TimeToGenerateResources -= DeltaTime;

	if (TimeToGenerateResources <= 0.0) {
		TimeToGenerateResources = ARobotsVSEngineersGameMode::SecondsPerTurn;

		GenerateResources();
	}

}

// Called to bind functionality to input
void ABuilding::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ABuilding::GenerateResources()
{
	auto GameState = GetWorld()->GetGameState<ARvEGameState>();

	if (GameState)
	{
		GameState->AddResources(this, ResourcesGeneratedPerTimeUnit);
	}
}

UFaction ABuilding::GetFaction() const
{
	return Faction;
}

