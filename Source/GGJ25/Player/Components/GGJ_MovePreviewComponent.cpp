// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_MovePreviewComponent.h"

#include "Components/DecalComponent.h"
#include "GGJ25/GameMode/Components/GGJ_GridComponent.h"
#include "GGJ25/GameMode/Components/GGJ_PieceMovementComponent.h"
#include "GGJ25/Moves/MoveDataAsset.h"
#include "Kismet/GameplayStatics.h"


UGGJ_MovePreviewComponent::UGGJ_MovePreviewComponent()
{
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

void UGGJ_MovePreviewComponent::OnMoveFinished(FMoveRequest MoveRequest)
{
    ShowPreview(MoveRequest.DestinationCoordinates.GetValue());
}

void UGGJ_MovePreviewComponent::OnMoveStarted()
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

    for (const FVector& PathTileWorldLocation : DirectedMovePreviewPath)
    {
        SpawnedDecalComponents.Add(
            UGameplayStatics::SpawnDecalAtLocation(this, DecalMaterial, DecalSize, PathTileWorldLocation, DecalRotation));
    }
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
    for (auto SpawnedDecal : SpawnedDecalComponents)
    {
        SpawnedDecal->DestroyComponent();
        SpawnedDecal = nullptr;
    }

    SpawnedDecalComponents.Empty();
}


