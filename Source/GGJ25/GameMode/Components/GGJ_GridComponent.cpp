// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_GridComponent.h"


UGGJ_GridComponent::UGGJ_GridComponent()
    : Super(FObjectInitializer::Get())
{
}


void UGGJ_GridComponent::BeginPlay()
{
    Super::BeginPlay();

    GenerateGrid();
}

void UGGJ_GridComponent::GenerateGrid()
{
    Grid = GetWorld()->SpawnActor<AGGJ_Grid>();

    Grid->Print();
    Grid->DebugDrawAxis(this);
    Grid->DebugDraw(this);
}

