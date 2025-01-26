// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJ_GameState.h"

#include "Components/AudioComponent.h"
#include "Components/GGJ_GridComponent.h"

AGGJ_GameState::AGGJ_GameState() : Super()
{
    BackgroundMusic = CreateDefaultSubobject<UAudioComponent>("BackgroundMusic");
}

void AGGJ_GameState::BeginPlay()
{
    Super::BeginPlay();

    GridComponent = GetComponentByClass<UGGJ_GridComponent>();

    BackgroundMusic->Play();
}

void AGGJ_GameState::SetMovementAllowed(const bool InMovementAllowed)
{
    bIsMovementAllowed = InMovementAllowed;
}

bool AGGJ_GameState::IsMovementAllowed() const
{
    return bIsMovementAllowed;
}