// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotsVSEngineers.h"
#include "Unit.h"
#include "RvEGameState.h"
#include "RobotsVSEngineersGameMode.h"

// Sets default values
AUnit::AUnit()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bAllowTickOnDedicatedServer = true;

	bIsDead = false;
	bIsAttacking = false;

	DistanceToTarget = INT32_MAX;
}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	Health = Stats.BaseHealthPoints;
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AUnit::OnHit);
}

// Called every frame
void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUnit::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

UFaction AUnit::GetFaction() const
{
	return Faction;
}

void AUnit::Die(AActor* DamageCauser)
{
	bIsDead = true;

	// turn off collision
	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Ignore);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
	}

	// turn off movement
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
	}

	// detach the controller
	if (Controller != nullptr)
	{
		Controller->UnPossess();
	}

	auto Killer = Cast<const IFactionInterface>(DamageCauser);
	auto GameState = GetWorld()->GetGameState<ARvEGameState>();
	if (Killer && GameState)
	{
		GameState->OnCharDied(this, Killer);
	}
	else if (!Killer)
	{
		UE_LOG(LogTemp, Warning, TEXT("Unit killed but killer is no longer available."));
	}

}

void AUnit::OnHit(AActor* OtherActor, UPrimitiveComponent*, FVector, const FHitResult&)
{
	if (ARobotsVSEngineersGameMode::OnAllyFaction(OtherActor, this))
		this->MoveIgnoreActorAdd(OtherActor);

}

float AUnit::TakeDamage(float Damage, struct FDamageEvent const&, AController*, AActor* DamageCauser)
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

void AUnit::AttackFinished()
{
	StopAttacking.Broadcast();
	bIsAttacking = false;
}