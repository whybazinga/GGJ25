// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJ_GameState.h"

#include "Components/GGJ_GridComponent.h"

AGGJ_GameState::AGGJ_GameState() : Super()
{
}

void AGGJ_GameState::BeginPlay()
{
    Super::BeginPlay();

    GridComponent = GetComponentByClass<UGGJ_GridComponent>();
}

void AGGJ_GameState::SetMovementAllowed(const bool InMovementAllowed)
{
    bIsMovementAllowed = InMovementAllowed;
}

bool AGGJ_GameState::IsMovementAllowed() const
{
    return bIsMovementAllowed;
}