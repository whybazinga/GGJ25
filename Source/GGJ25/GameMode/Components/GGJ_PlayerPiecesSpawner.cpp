// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_PlayerPiecesSpawner.h"

#include "GGJ25/GameMode/GGJ_GameState.h"
#include "GGJ25/Player/GGJ_PlayerController.h"
#include "GGJ25/Player/PieceActor.h"

#include "GGJ_GridComponent.h"


UGGJ_PlayerPiecesSpawner::UGGJ_PlayerPiecesSpawner() : Super(FObjectInitializer::Get())
{
}


void UGGJ_PlayerPiecesSpawner::BeginPlay()
{
    Super::BeginPlay();

    CachedGridComponent = GetWorld()->GetGameState<AGGJ_GameState>()->FindComponentByClass<UGGJ_GridComponent>();
    check(CachedGridComponent.IsValid());
    CachedGridComponent->OnGridReady.AddUObject(this, &ThisClass::OnGridReady);
}

void UGGJ_PlayerPiecesSpawner::OnGridReady()
{
    CachedGridComponent->OnGridReady.RemoveAll(this);

    const auto PlayersSpawnLocations = GetPlayersSpawnLocations();

    // Player 1
    const FTransform FirstPlayerSpawnTransform = FTransform(PlayersSpawnLocations.Key);

    APieceActor* FirstPlayerPiece = GetWorld()->SpawnActorDeferred<APieceActor>(
        PlayerPieceActorClass,
        FTransform::Identity);
    FirstPlayerPiece->FinishSpawning(FirstPlayerSpawnTransform);

    // Player 2
    const FTransform SecondPlayerSpawnTransform = FTransform(PlayersSpawnLocations.Value);

    APieceActor* SecondPlayerPiece = GetWorld()->SpawnActorDeferred<APieceActor>(
        PlayerPieceActorClass,
        FTransform::Identity);
    SecondPlayerPiece->FinishSpawning(SecondPlayerSpawnTransform);

    // Set them to PC
    AGGJ_PlayerController* PlayerController = Cast<AGGJ_PlayerController>(GetWorld()->GetFirstPlayerController());
    check(PlayerController);

    PlayerController->PawnOne = FirstPlayerPiece;
    PlayerController->PawnTwo = SecondPlayerPiece;
    PlayerController->GetOnPiecesSet().Broadcast();
}

TPair<FVector, FVector> UGGJ_PlayerPiecesSpawner::GetPlayersSpawnLocations() const
{
    check(CachedGridComponent.IsValid());

    return CachedGridComponent->GetPlayersSpawnLocations();
}

