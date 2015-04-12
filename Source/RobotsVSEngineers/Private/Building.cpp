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
	bIsDead = false;
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	Health = Stats.BaseHealthPoints;
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

float ABuilding::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Health <= 0) {
		return 0.f;
	}

	/* TODO modify damage */

	if (Damage > 0.f) {
		Health -= Damage;

		auto Causer = Cast<const IFactionInterface>(DamageCauser);
		auto GameState = GetWorld()->GetGameState<ARvEGameState>();
		if (Causer && GameState)
		{
			GameState->OnActorDamaged(this, Damage, Causer);
		}

		if (Health <= 0.f) {
			/* TODO die*/
			Die(DamageCauser);
		}


	}

	return Damage;
}

void ABuilding::Die(AActor* DamageCauser)
{
	bIsDead = true;

	// detach the controller
	if (Controller != nullptr)
	{
		Controller->UnPossess();
	}

	auto Killer = Cast<const IFactionInterface>(DamageCauser);
	auto GameState = GetWorld()->GetGameState<ARvEGameState>();
	if (Killer && GameState)
	{
		// GameState->OnBuildingDestroyed(this, Killer);
	}
	else if (!Killer)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unit killed but killer is no longer available."));
	}

	SetActorHiddenInGame(true);
	SetLifeSpan(0.01f);
}

UFaction ABuilding::GetFaction() const
{
	return Faction;
}

void ABuilding::OnSelectionGained_Implementation()
{
	
}

void ABuilding::OnSelectionLost_Implementation()
{

}