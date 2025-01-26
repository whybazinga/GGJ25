// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GGJ25/GameMode/Components/GGJ_DeathEffectActor.h"
#include "GGJ25/Moves/MoveDataAsset.h"
#include "GameFramework/Actor.h"

#include "GGJ_PlayerPieceData.h"

#include "PieceActor.generated.h"


struct FMoveRequest;
class UGGJ_PlayerPiecesSpawner;
class UGGJ_DeathsTracker;
class UGGJ_MovePreviewComponent;
class UGGJ_GridComponent;
class UGGJ_PieceMovementComponent;


UCLASS(Blueprintable, BlueprintType)
class GGJ25_API APieceActor : public AActor
{
    GENERATED_BODY()

public:

    APieceActor();

    TOptional<FDirectedMove> GetDirectedMove(const TPair<TOptional<EInputSide>, TOptional<EInputSide>>& Buffer) const;

    void Move(const TPair<TOptional<EInputSide>, TOptional<EInputSide>>& InputBuffer);

    void HideHand();

public:

    //TODO: subject to change to the set of UMoveDataAssets
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMoveDataAsset* MoveDataAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MovementTime = 0.2f;

    EPlayer Player = EPlayer::One;

protected:

    virtual void BeginPlay() override;

    void OnPiecesPlacedOnBoard();
    void OnPlayerDeath(EPlayer InPlayer, EDeathReason DeathReason);

    void OnMoveStarted(FMoveRequest MoveRequest);
    void OnMoveFinished(FMoveRequest MoveRequest);

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UBillboardComponent> SpriteComponent = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UBillboardComponent> HandSpriteComponent = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UAudioComponent> MoveAudio = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UAudioComponent> MoveFinishedAudio = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FPerPlayerPieceData FirstPlayerData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FPerPlayerPieceData SecondPlayerData;

    UPROPERTY()
    TObjectPtr<UGGJ_MovePreviewComponent> MovePreviewComponent = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UGGJ_PieceMovementComponent> MovementComponent = nullptr;
    
    TWeakObjectPtr<UGGJ_DeathsTracker> CachedDeathsTracker = nullptr;
    
    TWeakObjectPtr<UGGJ_PlayerPiecesSpawner> CachedPlayerPiecesSpawner = nullptr;

    TWeakObjectPtr<UGGJ_GridComponent> CachedGridComponent = nullptr;
};