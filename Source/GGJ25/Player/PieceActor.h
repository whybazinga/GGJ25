﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GGJ25/GameMode/Components/GGJ_PieceMovementComponent.h"
#include "GGJ25/Moves/MoveDataAsset.h"
#include "GameFramework/Actor.h"

#include "PieceActor.generated.h"


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

    void OnMoveStarted();
    void OnMoveFinished(FMoveRequest MoveRequest);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UBillboardComponent> SpriteComponent = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UBillboardComponent> HandSpriteComponent = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FVector FirstPlayerHandSpriteOffset = FVector::ZeroVector;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UTexture2D> FirstPlayerHandTexture = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FVector SecondPlayerHandSpriteOffset = FVector::ZeroVector;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UTexture2D> SecondPlayerHandTexture = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UGGJ_PieceMovementComponent> MovementComponent = nullptr;

    TWeakObjectPtr<UGGJ_GridComponent> CachedGridComponent = nullptr;
};