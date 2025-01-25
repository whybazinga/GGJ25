// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJ_GameMode.h"

#include "Components/GGJ_DeathsTracker.h"
#include "GGJ25/Player/GGJ_Pawn.h"
#include "GGJ25/Player/GGJ_PlayerController.h"

#include "GGJ_GameState.h"


AGGJ_GameMode::AGGJ_GameMode() : Super()
{
    GameStateClass = AGGJ_GameState::StaticClass();
    PlayerControllerClass = AGGJ_PlayerController::StaticClass();
    DefaultPawnClass = AGGJ_Pawn::StaticClass();

    DeathsChecker = CreateDefaultSubobject<UGGJ_DeathsTracker>("DeathsTracker");
}
