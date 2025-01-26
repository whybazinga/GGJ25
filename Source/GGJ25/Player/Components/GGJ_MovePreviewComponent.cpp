// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_MovePreviewComponent.h"

#include "Components/DecalComponent.h"
#include "GGJ25/GameMode/Components/GGJ_GridComponent.h"
#include "GGJ25/GameMode/Components/GGJ_PieceMovementComponent.h"
#include "GGJ25/Moves/MoveDataAsset.h"
#include "Kismet/GameplayStatics.h"

#include "GGJ_MovePreviewActor.h"


UGGJ_MovePreviewComponent::UGGJ_MovePreviewComponent()
    : Super(FObjectInitializer::Get())
{
}

void UGGJ_MovePreviewComponent::SetPlayer(const EPlayer InPlayer)
{
    Player = InPlayer;
}

void UGGJ_MovePreviewComponent::SetCurrentMove(UMoveDataAsset* MoveDataAsset)
{
    CurrentMoveDataAsset = MoveDataAsset;
}


void UGGJ_MovePreviewComponent::BeginPlay()
{
    Super::BeginPlay();

    CachedPieceMovementComponent = GetOwner()->FindComponentByClass<UGGJ_PieceMovementComponent>();
    CachedPieceMovementComponent->OnMoveFinished.AddUObject(this, &ThisClass::OnMoveFinished);
    CachedPieceMovementComponent->OnMoveStarted.AddUObject(this, &ThisClass::OnMoveStarted);

    CachedGridComponent = UGGJ_GridComponent::Get(this);
    check(CachedGridComponent.IsValid());
}

void UGGJ_MovePreviewComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}

FPerPlayerMovePreviewData UGGJ_MovePreviewComponent::GetPlayerMovePreviewData() const
{
    if (Player == EPlayer::One)
    {
        return FirstPlayerMovePreviewData;
    }
    return SecondPlayerMovePreviewData;
}

void UGGJ_MovePreviewComponent::OnMoveFinished(FMoveRequest MoveRequest)
{
    ShowPreview(MoveRequest.DestinationCoordinates.GetValue());
}

void UGGJ_MovePreviewComponent::OnMoveStarted(FMoveRequest MoveRequest)
{
    HidePreview();
}

void UGGJ_MovePreviewComponent::ShowDirectedMovePreview(const FIntVector2& SourceCoordinates, const FDirectedMove& DirectedMove)
{
    TArray<FIntVector2> PathCoordinatesLocations = CachedGridComponent->GetAppliedMoveStepsLocations(SourceCoordinates, DirectedMove.Steps);

    TArray<FVector> DirectedMovePreviewPath;
    for (const auto PathCoordinatesLocation : PathCoordinatesLocations)
    {
        DirectedMovePreviewPath.Add(CachedGridComponent->GetTileWorldLocation(PathCoordinatesLocation));
    }

    // for (int i = 0; i < DirectedMovePreviewPath.Num() - 1; ++i)
    // {
    //     const FVector& PathTileWorldLocation = DirectedMovePreviewPath[i];
    //
    //
    //
    //     SpawnedPreviewActors.Add(
    //         UGameplayStatics::SpawnDecalAtLocation(
    //             this,
    //             PathLocationDecalMaterial,
    //             PathLocationDecalSize,
    //             PathTileWorldLocation, DecalRotation));
    // }

    const FVector& DestinationTileWorldLocation = DirectedMovePreviewPath.Last();

    const FTransform DestinationTileMovePreviewActorSpawnTransform = FTransform(
        DestinationTileWorldLocation + GetPlayerMovePreviewData().SpawnLocationOffset);

    AGGJ_MovePreviewActor* DestinationTileMovePreviewActor = GetWorld()->SpawnActorDeferred<AGGJ_MovePreviewActor>(
        GetPlayerMovePreviewData().DestinationTileMovePreviewActorClass,
        FTransform::Identity);

    DestinationTileMovePreviewActor->FinishSpawning(DestinationTileMovePreviewActorSpawnTransform);

    SpawnedPreviewActors.Add(DestinationTileMovePreviewActor);
}

void UGGJ_MovePreviewComponent::ShowPreview(const FIntVector2& SourceCoordinates)
{
    for (const auto DirectedMove : CurrentMoveDataAsset->DirectedMoves)
    {
        ShowDirectedMovePreview(SourceCoordinates, DirectedMove);
    }
}

void UGGJ_MovePreviewComponent::HidePreview()
{
    for (auto SpawnedPreviewActor : SpawnedPreviewActors)
    {
        if (SpawnedPreviewActor)
        {
            SpawnedPreviewActor->Destroy();
            SpawnedPreviewActor = nullptr;
        }
    }

    SpawnedPreviewActors.Empty();
}
