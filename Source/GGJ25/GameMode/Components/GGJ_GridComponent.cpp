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

void UGGJ_GridComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}

void UGGJ_GridComponent::GenerateGrid()
{
    Grid = Cast<AGGJ_Grid>(UGameplayStatics::GetActorOfClass(this, AGGJ_Grid::StaticClass()));
    OnGridReady.Broadcast();
}

TPair<FVector, FVector> UGGJ_GridComponent::GetPlayersSpawnLocations() const
{
    const bool ShouldSpawnOnOppositeY = FMath::RandBool();

    FIntVector2 FirstPlayerSpawnLocation = FIntVector2(INDEX_NONE);
    FIntVector2 SecondPlayerSpawnLocation = FIntVector2(INDEX_NONE);

    const bool IsFirstPlayerCloserToZero = FMath::RandBool();
    if (ShouldSpawnOnOppositeY)
    {
        FirstPlayerSpawnLocation.X = FMath::RandHelper(Grid->Size.X);
        FirstPlayerSpawnLocation.Y = IsFirstPlayerCloserToZero ? 0 : Grid->Size.Y - 1;

        SecondPlayerSpawnLocation.X = Grid->Size.X - 1 - FirstPlayerSpawnLocation.X;
        SecondPlayerSpawnLocation.Y = Grid->Size.Y - 1 - FirstPlayerSpawnLocation.Y;
    }
    else
    {
        FirstPlayerSpawnLocation.X = IsFirstPlayerCloserToZero ? 0 : Grid->Size.X - 1;
        FirstPlayerSpawnLocation.Y = FMath::RandHelper(Grid->Size.Y);

        SecondPlayerSpawnLocation.X = Grid->Size.X - 1 - FirstPlayerSpawnLocation.X;
        SecondPlayerSpawnLocation.Y = Grid->Size.Y - 1 - FirstPlayerSpawnLocation.Y;
    }

    check(Grid->Tiles.IsValidIndex(FirstPlayerSpawnLocation.Y));
    check(Grid->Tiles[FirstPlayerSpawnLocation.Y].IsValidIndex(FirstPlayerSpawnLocation.X));

    check(Grid->Tiles.IsValidIndex(SecondPlayerSpawnLocation.Y));
    check(Grid->Tiles[SecondPlayerSpawnLocation.Y].IsValidIndex(SecondPlayerSpawnLocation.X));

    return {
        Grid->GetTileWorldLocation(FirstPlayerSpawnLocation.X, FirstPlayerSpawnLocation.Y),
        Grid->GetTileWorldLocation(SecondPlayerSpawnLocation.X, SecondPlayerSpawnLocation.Y)
    };
}

