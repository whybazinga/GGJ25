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
    Grid.Size = FVector2d(3, 3);
    Grid.TileSize = FVector2D(50, 50);
    Grid.TileLocationOffset = FVector2D(-25, -25);
    Grid.Generate();

    Grid.Print();
    Grid.DebugDraw(this);
}

