// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotsVSEngineers.h"
#include "RobotsVSEngineersGameMode.h"
#include "Mouse_PlayerController.h"
#include "Unit.h"

#include "FactionInterface.h"

ARobotsVSEngineersGameMode::ARobotsVSEngineersGameMode(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	this->PlayerControllerClass = AMouse_PlayerController::StaticClass();
}

bool ARobotsVSEngineersGameMode::OnAllyFaction(const AActor* ActorA, const AActor* ActorB)
{
	auto TeamA = Cast<const IFactionInterface>(ActorA);
	auto TeamB = Cast<const IFactionInterface>(ActorB);

	return (TeamA != nullptr) && (TeamB != nullptr) && (TeamA->GetFaction() == TeamB->GetFaction());
}

bool ARobotsVSEngineersGameMode::OnEnemyFaction(const AActor* ActorA, const AActor* ActorB)
{
	auto TeamA = Cast<const IFactionInterface>(ActorA);
	auto TeamB = Cast<const IFactionInterface>(ActorB);

	return (TeamA != nullptr) && (TeamB != nullptr) && (TeamA->GetFaction() != TeamB->GetFaction());
}

bool ARobotsVSEngineersGameMode::IsUnitAlive(AActor* Actor)
{
	auto Unit = Cast<const AUnit>(Actor);

    return (Unit != nullptr) && (!Unit->IsPendingKill() || !Unit->bIsDead);
}

bool ARobotsVSEngineersGameMode::IsUnitDead(AActor* Actor)
{
	auto Unit = Cast<const AUnit>(Actor);

	return (Unit != nullptr) && (Unit->IsPendingKill() || Unit->bIsDead);
}
