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

bool UGGJ_GridComponent::IsGridReady() const
{
    return bIsGridReady;
}

void UGGJ_GridComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}

void UGGJ_GridComponent::GenerateGrid()
{
    Grid = Cast<AGGJ_Grid>(UGameplayStatics::GetActorOfClass(this, AGGJ_Grid::StaticClass()));

    bIsGridReady = true;
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

TOptional<FVector> UGGJ_GridComponent::GetPlayerWorldLocation(const EPlayer Player) const
{
    if (GetPlayerLocation(Player).IsSet())
    {
        return Grid->GetTileWorldLocation(GetPlayerLocation(Player).GetValue());
    }

    return NullOpt;
}

void UGGJ_GridComponent::SetPlayerLocation(const EPlayer Player, const FIntVector2 NewLocation, const bool ShouldNotify /* = true */)
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

TArray<FIntVector2> UGGJ_GridComponent::GetAppliedMoveStepsLocations(const FIntVector2 SourceLocation, TArray<FCoordinates> Steps)
{
    TArray<FIntVector2> OutStepsLocations;

    FIntVector2 CurrentLocation = SourceLocation;
    for (const FCoordinates& Step : Steps)
    {
        CurrentLocation.X += Step.X;
        CurrentLocation.Y += Step.Y;
        OutStepsLocations.Add(CurrentLocation);
    }

    return OutStepsLocations;
}

FVector UGGJ_GridComponent::GetTileWorldLocation(const FIntVector2 Coordinates) const
{
    return Grid->GetTileWorldLocation(Coordinates);
}

bool UGGJ_GridComponent::IsValidGridLocation(const FIntVector2& Location) const
{
    return Grid->GetTileOptional(Location).IsSet();
}

TPair<FIntVector2, FIntVector2> UGGJ_GridComponent::GetPlayersSpawnCoordinates() const
{
    const bool ShouldSpawnOnOppositeY = FMath::RandBool();

    FIntVector2 FirstPlayerSpawnCoordinates;
    FIntVector2 SecondPlayerSpawnCoordinates;

    const bool IsFirstPlayerCloserToZero = FMath::RandBool();
    if (ShouldSpawnOnOppositeY)
    {
        FirstPlayerSpawnCoordinates.X = FMath::RandHelper(Grid->Size.X);
        FirstPlayerSpawnCoordinates.Y = IsFirstPlayerCloserToZero ? 0 : Grid->Size.Y - 1;

        SecondPlayerSpawnCoordinates.X = Grid->Size.X - 1 - FirstPlayerSpawnCoordinates.X;
        SecondPlayerSpawnCoordinates.Y = Grid->Size.Y - 1 - FirstPlayerSpawnCoordinates.Y;
    }
    else
    {
        FirstPlayerSpawnCoordinates.X = IsFirstPlayerCloserToZero ? 0 : Grid->Size.X - 1;
        FirstPlayerSpawnCoordinates.Y = FMath::RandHelper(Grid->Size.Y);

        SecondPlayerSpawnCoordinates.X = Grid->Size.X - 1 - FirstPlayerSpawnCoordinates.X;
        SecondPlayerSpawnCoordinates.Y = Grid->Size.Y - 1 - FirstPlayerSpawnCoordinates.Y;
    }

    check(Grid->Tiles.IsValidIndex(FirstPlayerSpawnCoordinates.Y));
    check(Grid->Tiles[FirstPlayerSpawnCoordinates.Y].IsValidIndex(FirstPlayerSpawnCoordinates.X));

    check(Grid->Tiles.IsValidIndex(SecondPlayerSpawnCoordinates.Y));
    check(Grid->Tiles[SecondPlayerSpawnCoordinates.Y].IsValidIndex(SecondPlayerSpawnCoordinates.X));

    return {
        FirstPlayerSpawnCoordinates,
        SecondPlayerSpawnCoordinates};
}
