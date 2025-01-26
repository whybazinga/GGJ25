// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "GGJ25/Moves/MoveDataAsset.h"

#include "GGJ_MovePreviewComponent.generated.h"


struct FMoveRequest;
class UGGJ_GridComponent;
class UMoveDataAsset;
class UGGJ_PieceMovementComponent;


UCLASS(ClassGroup = (Custom), Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class GGJ25_API UGGJ_MovePreviewComponent : public UActorComponent
{
    GENERATED_BODY()

public:

    UGGJ_MovePreviewComponent();

    void SetCurrentMove(UMoveDataAsset* MoveDataAsset);

protected:

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    void OnMoveFinished(FMoveRequest MoveRequest);

    void OnMoveStarted();
    void ShowDirectedMovePreview(const FIntVector2& SourceCoordinates, const FDirectedMove& DirectedMove);

    void ShowPreview(const FIntVector2& SourceCoordinates);
    void HidePreview();

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UMaterialInterface> DecalMaterial;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FVector DecalSize = FVector::ZeroVector;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FRotator DecalRotation = FRotator::ZeroRotator;

    TArray<UDecalComponent*> SpawnedDecalComponents;

    TWeakObjectPtr<UGGJ_PieceMovementComponent> CachedPieceMovementComponent = nullptr;

    TWeakObjectPtr<UGGJ_GridComponent> CachedGridComponent = nullptr;

    TObjectPtr<UMoveDataAsset> CurrentMoveDataAsset = nullptr;
};
