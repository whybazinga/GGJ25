// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJ_GameMode.h"

#include "GGJ25/Player/GGJ_PlayerController.h"

#include "GGJ_GameState.h"


AGGJ_GameMode::AGGJ_GameMode() : Super()
{
    GameStateClass = AGGJ_GameState::StaticClass();
    PlayerControllerClass = AGGJ_PlayerController::StaticClass();
}