// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_PlayerPiecesSpawner.h"

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

    CachedPlayerController = Cast<AGGJ_PlayerController>(GetWorld()->GetFirstPlayerController());
}

void UGGJ_PlayerPiecesSpawner::PlacePlayerPieceOnBoard(const EPlayer Player, const FIntVector2& Coordinates)
{
    const FVector PieceWorldLocation = CachedGridComponent->GetTileWorldLocation(Coordinates);
    APieceActor* PlayerPieceActor = CachedPlayerController->GetPlayerPawn(Player);

    PlayerPieceActor->SetActorLocation(PieceWorldLocation);
    PlayerPieceActor->SetActorHiddenInGame(false);
    PlayerPieceActor->HideHand(); // cause it reappears during PlayerPieceActor->SetActorHiddenInGame(false)

    CachedGridComponent->SetPlayerLocation(Player, Coordinates, false);
}

void UGGJ_PlayerPiecesSpawner::PlacePiecesOnBoard()
{
    const auto PlayersSpawnCoordinates = GetPlayersSpawnCoordinates();

    PlacePlayerPieceOnBoard(EPlayer::One, PlayersSpawnCoordinates.Key);
    PlacePlayerPieceOnBoard(EPlayer::Two, PlayersSpawnCoordinates.Value);
}

APieceActor* UGGJ_PlayerPiecesSpawner::SpawnPlayer(const EPlayer Player) const
{
    // good old hide under the carpet
    const FTransform PieceSpawnTransform = FTransform(FVector::DownVector * 1000.f);

    APieceActor* PlayerPiece = GetWorld()->SpawnActorDeferred<APieceActor>(
        PlayerPieceActorClass,
        FTransform::Identity);

    PlayerPiece->Player = Player;

    PlayerPiece->FinishSpawning(PieceSpawnTransform);


    return PlayerPiece;
}

void UGGJ_PlayerPiecesSpawner::OnGridReady()
{
    CachedGridComponent->OnGridReady.RemoveAll(this);

    const auto PlayersSpawnCoordinates = GetPlayersSpawnCoordinates();

    // =============== Player 1 ===============
    APieceActor* FirstPlayerPiece = SpawnPlayer(EPlayer::One);


    // =============== Player 2 ===============
    APieceActor* SecondPlayerPiece = SpawnPlayer(EPlayer::Two);


    // =============== Set them to PC ===============

    CachedPlayerController->PawnOne = FirstPlayerPiece;
    CachedPlayerController->PawnTwo = SecondPlayerPiece;
    CachedPlayerController->GetOnPiecesSet().Broadcast();

    PlacePiecesOnBoard();
}

TPair<FIntVector2, FIntVector2> UGGJ_PlayerPiecesSpawner::GetPlayersSpawnCoordinates() const
{
    check(CachedGridComponent.IsValid());

    return CachedGridComponent->GetPlayersSpawnCoordinates();
}
