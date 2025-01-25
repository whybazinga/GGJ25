// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_PlayerPiecesSpawner.h"

#include "GGJ25/GameMode/GGJ_GameState.h"
#include "GGJ25/Player/GGJ_PlayerController.h"
#include "GGJ25/Player/PieceActor.h"

#include "GGJ_GridComponent.h"


UGGJ_PlayerPiecesSpawner::UGGJ_PlayerPiecesSpawner()
    : Super(FObjectInitializer::Get())
{
}


void UGGJ_PlayerPiecesSpawner::BeginPlay()
{
    Super::BeginPlay();

    CachedGridComponent = UGGJ_GridComponent::Get(this);
    check(CachedGridComponent.IsValid());
    CachedGridComponent->OnGridReady.AddUObject(this, &ThisClass::OnGridReady);
}

void UGGJ_PlayerPiecesSpawner::OnGridReady()
{
    CachedGridComponent->OnGridReady.RemoveAll(this);

    const auto PlayersSpawnCoordinates = GetPlayersSpawnCoordinates();

    // =============== Player 1 ===============
    CachedGridComponent->SetPlayerLocation(PlayersSpawnCoordinates.Key, EPlayer::One, false);

    const FVector FirstPlayerWorldLocation = CachedGridComponent->GetPlayerWorldLocation(EPlayer::One).GetValue();

    const FTransform FirstPlayerSpawnTransform = FTransform(FirstPlayerWorldLocation);

    APieceActor* FirstPlayerPiece = GetWorld()->SpawnActorDeferred<APieceActor>(
        PlayerPieceActorClass,
        FTransform::Identity);
    FirstPlayerPiece->FinishSpawning(FirstPlayerSpawnTransform);


    // =============== Player 2 ===============
    CachedGridComponent->SetPlayerLocation(PlayersSpawnCoordinates.Value, EPlayer::Two, false);

    const FVector SecondPlayerWorldLocation = CachedGridComponent->GetPlayerWorldLocation(EPlayer::Two).GetValue();

    const FTransform SecondPlayerSpawnTransform = FTransform(SecondPlayerWorldLocation);

    APieceActor* SecondPlayerPiece = GetWorld()->SpawnActorDeferred<APieceActor>(
        PlayerPieceActorClass,
        FTransform::Identity);
    SecondPlayerPiece->FinishSpawning(SecondPlayerSpawnTransform);


    // =============== Set them to PC ===============
    AGGJ_PlayerController* PlayerController = Cast<AGGJ_PlayerController>(GetWorld()->GetFirstPlayerController());
    check(PlayerController);

    PlayerController->PawnOne = FirstPlayerPiece;
    PlayerController->PawnTwo = SecondPlayerPiece;
    PlayerController->GetOnPiecesSet().Broadcast();
}

TPair<FIntVector2, FIntVector2> UGGJ_PlayerPiecesSpawner::GetPlayersSpawnCoordinates() const
{
    check(CachedGridComponent.IsValid());

    return CachedGridComponent->GetPlayersSpawnCoordinates();
}
