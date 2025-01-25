// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_GridComponent.h"

#include "GGJ25/GeneralTypes.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"


UGGJ_GridComponent::UGGJ_GridComponent()
    : Super(FObjectInitializer::Get())
{
}

UGGJ_GridComponent* UGGJ_GridComponent::Get(const UObject* WorldContext)
{
    return GEngine
            ->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull)
            ->GetGameState()
            ->FindComponentByClass<UGGJ_GridComponent>();
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

TOptional<FIntVector2> UGGJ_GridComponent::GetPlayerLocation(const EPlayer Player) const
{
    switch (Player)
    {
        case EPlayer::One:
            return FirstPlayerLocation;
        case EPlayer::Two:
            return SecondPlayerLocation;

        default:
            checkNoEntry();
            return NullOpt;
    }
}

void UGGJ_GridComponent::SetPlayerLocation(const FIntVector2 NewLocation, const EPlayer Player, const bool ShouldNotify /* = true */)
{
    switch (Player)
    {
        case EPlayer::One:
            FirstPlayerLocation = NewLocation;
            break;
        case EPlayer::Two:
            SecondPlayerLocation = NewLocation;
            break;

        default:
            checkNoEntry();
            return;
    }

    if (ShouldNotify)
    {
        OnGridPlayerLocationSet.Broadcast(Player);
    }
}

TArray<FVector> UGGJ_GridComponent::GetAppliedMoveStepsWorldLocations(const FIntVector2 SourceLocation, TArray<FCoordinates> Steps) const
{
    TArray<FVector> OutStepsLocations;

    FIntVector2 CurrentLocation = SourceLocation;
    for (const FCoordinates& Step : Steps)
    {
        CurrentLocation.X += Step.X;
        CurrentLocation.Y += Step.Y;
        OutStepsLocations.Add(Grid->GetTileWorldLocation(CurrentLocation));
    }

    return OutStepsLocations;
}

bool UGGJ_GridComponent::IsValidGridLocation(const FIntVector2& Location) const
{
    return Grid->GetTileOptional(Location).IsSet();
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
        Grid->GetTileWorldLocation(FirstPlayerSpawnLocation),
        Grid->GetTileWorldLocation(SecondPlayerSpawnLocation)
    };
}

