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