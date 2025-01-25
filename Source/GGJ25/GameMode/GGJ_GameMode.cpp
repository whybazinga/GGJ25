// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJ_GameMode.h"

#include "Components/GGJ_DeathEffectsComponent.h"
#include "Components/GGJ_DeathsTracker.h"
#include "GGJ25/Player/GGJ_Pawn.h"
#include "GGJ25/Player/GGJ_PlayerController.h"

#include "GGJ_GameState.h"


AGGJ_GameMode::AGGJ_GameMode()
    : Super()
{
    GameStateClass = AGGJ_GameState::StaticClass();
    PlayerControllerClass = AGGJ_PlayerController::StaticClass();
    DefaultPawnClass = AGGJ_Pawn::StaticClass();

    DeathsTracker = CreateDefaultSubobject<UGGJ_DeathsTracker>("DeathsTracker");
    DeathEffectsComponent = CreateDefaultSubobject<UGGJ_DeathEffectsComponent>("DeathEffectsComponent");
}

void AGGJ_GameMode::BeginPlay()
{
    Super::BeginPlay();

    DeathsTracker->OnPlayerDeath.AddUObject(this, &ThisClass::OnPlayerDeath);

    Start();
}

void AGGJ_GameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    DeathsTracker->OnPlayerDeath.RemoveAll(this);

    Super::EndPlay(EndPlayReason);
}

void AGGJ_GameMode::Start()
{
    GetGameState<AGGJ_GameState>()->SetMovementAllowed(true);
}

void AGGJ_GameMode::Restart()
{
    GetGameState<AGGJ_GameState>()->SetMovementAllowed(true);
}

void AGGJ_GameMode::OnPlayerDeath(EPlayer Player)
{
    GetGameState<AGGJ_GameState>()->SetMovementAllowed(false);
}
