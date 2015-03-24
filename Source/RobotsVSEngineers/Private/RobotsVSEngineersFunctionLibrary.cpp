// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotsVSEngineers.h"
#include "RobotsVSEngineersFunctionLibrary.h"

#include "RobotsVSEngineersGameMode.h"

bool URobotsVSEngineersFunctionLibrary::AreAllies(AActor* Actor1, AActor* Actor2)
{
	return ARobotsVSEngineersGameMode::OnAllyFaction(Actor1, Actor2);
}

bool URobotsVSEngineersFunctionLibrary::AreEnemies(AActor* Actor1, AActor* Actor2)
{
	return ARobotsVSEngineersGameMode::OnEnemyFaction(Actor1, Actor2);
}
