// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_GridComponent.h"


UGGJ_GridComponent::UGGJ_GridComponent()
    : Super(FObjectInitializer::Get())
{
    Grid = FGrid();
    Grid.Size = FVector2d(3, 3);
    Grid.TileSize = FVector2D(50, 50);
    Grid.TileCenterLocationOffset = FVector2D(0, 0);
}


void UGGJ_GridComponent::BeginPlay()
{
    Super::BeginPlay();

    GenerateGrid();
}

void UGGJ_GridComponent::GenerateGrid()
{
    Grid.Generate();

    Grid.Print();
    Grid.DebugDrawAxis(this);
    Grid.DebugDraw(this);
}

