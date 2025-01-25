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
}

APieceActor* UGGJ_PlayerPiecesSpawner::SpawnPlayer(const EPlayer Player, const FIntVector2& PieceSpawnCoordinates) const
{
    CachedGridComponent->SetPlayerLocation(Player, PieceSpawnCoordinates, false);

    const FVector PieceWorldLocation = CachedGridComponent->GetPlayerWorldLocation(Player).GetValue();
    const FTransform PieceSpawnTransform = FTransform(PieceWorldLocation);

    APieceActor* PlayerPiece = GetWorld()->SpawnActorDeferred<APieceActor>(
        PlayerPieceActorClass,
        FTransform::Identity);
    PlayerPiece->FinishSpawning(PieceSpawnTransform);

    PlayerPiece->Player = Player;

    return PlayerPiece;
}

void UGGJ_PlayerPiecesSpawner::OnGridReady()
{
    CachedGridComponent->OnGridReady.RemoveAll(this);

    const auto PlayersSpawnCoordinates = GetPlayersSpawnCoordinates();

    // =============== Player 1 ===============
    APieceActor* FirstPlayerPiece = SpawnPlayer(EPlayer::One, PlayersSpawnCoordinates.Key);


    // =============== Player 2 ===============
    APieceActor* SecondPlayerPiece = SpawnPlayer(EPlayer::Two, PlayersSpawnCoordinates.Value);


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
