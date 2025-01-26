// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_MovePreviewComponent.h"

#include "GGJ25/GameMode/Components/GGJ_GridComponent.h"
#include "GGJ25/GameMode/Components/GGJ_PieceMovementComponent.h"
#include "GGJ25/Moves/MoveDataAsset.h"

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
    CachedPieceMovementComponent->OnMoveFinished.RemoveAll(this);
    CachedPieceMovementComponent->OnMoveStarted.RemoveAll(this);

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
    ClearPreviews();
    ShowPlanningPreview(MoveRequest.DestinationCoordinates.GetValue());
}

// ReSharper disable once CppPassValueParameterByConstReference
void UGGJ_MovePreviewComponent::OnMoveStarted(FMoveRequest MoveRequest)
{
    ClearPreviews();
    ShowMovingPreview(MoveRequest);
}

void UGGJ_MovePreviewComponent::SpawnMovePreviewActor(const TSubclassOf<AGGJ_MovePreviewActor>& MovePreviewActorClass, const FVector& TileWorldLocation)
{
    const FTransform MovePreviewActorSpawnTransform = FTransform(
        TileWorldLocation + GetPlayerMovePreviewData().SpawnLocationOffset);

    AGGJ_MovePreviewActor* MovePreviewActor = GetWorld()->SpawnActorDeferred<AGGJ_MovePreviewActor>(
        MovePreviewActorClass,
        FTransform::Identity);

    MovePreviewActor->FinishSpawning(MovePreviewActorSpawnTransform);

    SpawnedPreviewActors.Add(MovePreviewActor);
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

    SpawnMovePreviewActor(GetPlayerMovePreviewData().DestinationTileMovePreviewActorClass, DestinationTileWorldLocation);
}

void UGGJ_MovePreviewComponent::ShowPlanningPreview(const FIntVector2& SourceCoordinates)
{
    for (const auto DirectedMove : CurrentMoveDataAsset->DirectedMoves)
    {
        ShowDirectedMovePreview(SourceCoordinates, DirectedMove);
    }
}

void UGGJ_MovePreviewComponent::ClearPreviews()
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

void UGGJ_MovePreviewComponent::ShowMovingPreview(const FMoveRequest& MoveRequest)
{
    const FVector& DestinationTileWorldLocation = CachedGridComponent->GetTileWorldLocation(MoveRequest.DestinationCoordinates.GetValue());

    SpawnMovePreviewActor(GetPlayerMovePreviewData().DestinationTileMovePreviewActorClass, DestinationTileWorldLocation);
}