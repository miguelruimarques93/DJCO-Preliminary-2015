// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotsVSEngineers.h"
#include "Unit.h"


// Sets default values
AUnit::AUnit()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bAllowTickOnDedicatedServer = true;

	bIsDead = false;
	bIsAttacking = false;
}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();
	Health = Stats.BaseHealthPoints;
	
}

// Called every frame
void AUnit::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

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
	if (Controller != NULL)
	{
		Controller->UnPossess();
	}

	float animLen = 0.f;
	auto mesh = GetMesh();
	if (mesh && DeathAnimation) {
		mesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
		mesh->PlayAnimation(DeathAnimation, false);
		animLen = DeathAnimation->GetMaxCurrentTime();
	}

	/* TODO give points to killer faction */

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AUnit::PostMortem, animLen, false);
}

void AUnit::PostMortem()
{
	SetActorHiddenInGame(true); SetLifeSpan(0.01f);
}

float AUnit::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Health <= 0) {
		return 0.f;
	}

	/* TODO modify damage */

	if (Damage > 0.f) {
		Health -= Damage;

		if (Health <= 0.f) {
			/* TODO die*/
			Die(DamageCauser);
		}


	}

	return Damage;
}
