// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotsVSEngineers.h"
#include "RobotsVSEngineersGameMode.h"
#include "Mouse_PlayerController.h"
#include "Unit.h"

#include "RvEGameState.h"

#include "FactionInterface.h"

CONSTEXPR const float ARobotsVSEngineersGameMode::SecondsPerTurn = 10.0;

CONSTEXPR const int32 ARobotsVSEngineersGameMode::InitialResources = 100;

ARobotsVSEngineersGameMode::ARobotsVSEngineersGameMode(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerControllerClass = AMouse_PlayerController::StaticClass();
	GameStateClass = ARvEGameState::StaticClass();
	DefaultPawnClass = ASpectatorPawn::StaticClass();
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
