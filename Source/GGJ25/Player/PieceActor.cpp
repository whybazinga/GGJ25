// Fill out your copyright notice in the Description page of Project Settings.


#include "PieceActor.h"

#include "Components/AudioComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/GGJ_MovePreviewComponent.h"
#include "GGJ25/GameMode/Components/GGJ_GridComponent.h"
#include "GGJ25/GameMode/Components/GGJ_PieceMovementComponent.h"
#include "GGJ25/GameMode/GGJ_GameState.h"

APieceActor::APieceActor() : Super()
{
    PrimaryActorTick.bCanEverTick = false;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SpriteComponent = CreateDefaultSubobject<UBillboardComponent>("SpriteComponent");
    SpriteComponent->SetupAttachment(RootComponent);
    SpriteComponent->bHiddenInGame = false;

    HandSpriteComponent = CreateDefaultSubobject<UBillboardComponent>("HandSpriteComponent");
    HandSpriteComponent->SetupAttachment(RootComponent);
    HandSpriteComponent->bHiddenInGame = true;

    MoveAudio = CreateDefaultSubobject<UAudioComponent>("MoveAudio");
    MoveFinishedAudio = CreateDefaultSubobject<UAudioComponent>("MoveFinishedAudio");

    MovementComponent = CreateDefaultSubobject<UGGJ_PieceMovementComponent>("PieceMovementComponent");
}

void APieceActor::BeginPlay()
{
    Super::BeginPlay();

    MovePreviewComponent = GetComponentByClass<UGGJ_MovePreviewComponent>();
    MovePreviewComponent->SetPlayer(Player);
    MovePreviewComponent->SetCurrentMove(MoveDataAsset);

    CachedGridComponent = UGGJ_GridComponent::Get(this);
    check(CachedGridComponent.IsValid());

    if (Player == EPlayer::One)
    {
        SpriteComponent->SetSprite(FirstPlayerData.SpriteTexture);
        HandSpriteComponent->SetSprite(FirstPlayerData.HandSpriteTexture);
        HandSpriteComponent->SetRelativeLocation(FirstPlayerData.HandSpriteOffset);
    }
    else
    {
        SpriteComponent->SetSprite(SecondPlayerData.SpriteTexture);
        HandSpriteComponent->SetSprite(SecondPlayerData.HandSpriteTexture);
        HandSpriteComponent->SetRelativeLocation(SecondPlayerData.HandSpriteOffset);
    }
}

TOptional<FDirectedMove> APieceActor::GetDirectedMove(const TPair<TOptional<EInputSide>, TOptional<EInputSide>>& Buffer) const
{
    if (!Buffer.Key.IsSet() || !Buffer.Value.IsSet())
    {
        return {};
    }

    if (!MoveDataAsset)
    {
        return {};
    }

    for (auto& Move : MoveDataAsset->DirectedMoves)
    {
        if (Move.InputBuffer.First == Buffer.Key.GetValue()
            && Move.InputBuffer.Second == Buffer.Value.GetValue())
        {
            return Move;
        }
    }
    return {};
}

void APieceActor::Move(const TPair<TOptional<EInputSide>, TOptional<EInputSide>>& InputBuffer)
{
    if (!GetWorld()->GetGameState<AGGJ_GameState>()->IsMovementAllowed())
    {
        return;
    }

    TOptional<FDirectedMove> Move = GetDirectedMove(InputBuffer);
    if (!Move.IsSet())
    {
        UE_LOG(LogTemp, Warning, TEXT("Move is not found: [%s]"), *GetName());
        return;
    }

    TOptional<FIntVector2> PlayerCurrentLocation = CachedGridComponent->GetPlayerLocation(Player);
    if (!PlayerCurrentLocation.IsSet())
    {
        UE_LOG(LogTemp, Warning, TEXT("Piece %s location not found"), *GetName());
    }

    TArray<FIntVector2> PathCoordinatesLocations = CachedGridComponent->GetAppliedMoveStepsLocations(PlayerCurrentLocation.GetValue(), Move.GetValue().Steps);


    TArray<FVector> Path;
    Path.Add(CachedGridComponent->GetPlayerWorldLocation(Player).GetValue());

    for (auto PathCoordinatesLocation : PathCoordinatesLocations)
    {
        Path.Add(CachedGridComponent->GetTileWorldLocation(PathCoordinatesLocation));
    }

    MovementComponent->OnMoveStarted.AddUObject(this, &ThisClass::OnMoveStarted);
    MovementComponent->OnMoveFinished.AddUObject(this, &ThisClass::OnMoveFinished);

    FMoveRequest MoveRequest;
    MoveRequest.SourceCoordinates = PlayerCurrentLocation;
    MoveRequest.DestinationCoordinates = PathCoordinatesLocations.Last();
    MoveRequest.Duration = MovementTime;
    MoveRequest.Path = Path;
    MovementComponent->RequestMove(MoveRequest);
}

void APieceActor::HideHand()
{
    HandSpriteComponent->SetHiddenInGame(true);
}

void APieceActor::OnMoveStarted(FMoveRequest MoveRequest)
{
    MovementComponent->OnMoveStarted.RemoveAll(this);

    HandSpriteComponent->SetHiddenInGame(false);
    MoveAudio->Play();
}

void APieceActor::OnMoveFinished(FMoveRequest MoveRequest)
{
    MovementComponent->OnMoveFinished.RemoveAll(this);

    HandSpriteComponent->SetHiddenInGame(true);
    CachedGridComponent->SetPlayerLocation(Player, MoveRequest.DestinationCoordinates.GetValue());

    MoveFinishedAudio->Play();
}


