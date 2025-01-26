// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "GGJ25/Moves/MoveDataAsset.h"

#include "GGJ_MovePreviewComponent.generated.h"


class AGGJ_MovePreviewActor;
struct FMoveRequest;
class UGGJ_GridComponent;
class UMoveDataAsset;
class UGGJ_PieceMovementComponent;


USTRUCT(BlueprintType)
struct FPerPlayerMovePreviewData
{
    GENERATED_BODY()

public:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<AGGJ_MovePreviewActor> DestinationTileMovePreviewActorClass = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FVector SpawnLocationOffset = FVector::ZeroVector;
};


UCLASS(ClassGroup = (Custom), Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class GGJ25_API UGGJ_MovePreviewComponent : public UActorComponent
{
    GENERATED_BODY()

public:

    UGGJ_MovePreviewComponent();

    void SetPlayer(EPlayer InPlayer);

    void SetCurrentMove(UMoveDataAsset* MoveDataAsset);

    void ClearPreviews();

protected:

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    FPerPlayerMovePreviewData GetPlayerMovePreviewData() const;

    void OnMoveFinished(FMoveRequest MoveRequest);
    void OnMoveStarted(FMoveRequest MoveRequest);
    void SpawnMovePreviewActor(const TSubclassOf<AGGJ_MovePreviewActor>& MovePreviewActorClass, const FVector& TileWorldLocation);

    void ShowDirectedMovePreview(const FIntVector2& SourceCoordinates, const FDirectedMove& DirectedMove);

    void ShowPlanningPreview(const FIntVector2& SourceCoordinates);

    void ShowMovingPreview(const FMoveRequest& MoveRequest);

protected:

    EPlayer Player = EPlayer::One;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FPerPlayerMovePreviewData FirstPlayerMovePreviewData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FPerPlayerMovePreviewData SecondPlayerMovePreviewData;

    UPROPERTY()
    TArray<AGGJ_MovePreviewActor*> SpawnedPreviewActors;

    TWeakObjectPtr<UGGJ_PieceMovementComponent> CachedPieceMovementComponent = nullptr;

    TWeakObjectPtr<UGGJ_GridComponent> CachedGridComponent = nullptr;

    TWeakObjectPtr<UMoveDataAsset> CurrentMoveDataAsset = nullptr;
};
