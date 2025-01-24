// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_GridComponent.h"

#include "Kismet/GameplayStatics.h"


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
    Grid = Cast<AGGJ_Grid>(UGameplayStatics::GetActorOfClass(this, AGGJ_Grid::StaticClass()));
}

