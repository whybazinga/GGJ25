// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGJ25/Moves/MoveDataAsset.h"

#include "PieceActor.generated.h"


class UGGJ_PieceMovementComponent;

UCLASS(Blueprintable, BlueprintType)
class GGJ25_API APieceActor : public AActor
{
    GENERATED_BODY()

public:

    APieceActor();

    TOptional<FDirectedMove> GetDirectedMove(const TPair<TOptional<EInputSide>, TOptional<EInputSide>>& Buffer) const;

public:

    //TODO: subject to change to the set of UMoveDataAssets
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMoveDataAsset* MoveDataAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MovementTime = 0.2f;

    EPlayer Player = EPlayer::One;

protected:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UBillboardComponent> SpriteComponent = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UGGJ_PieceMovementComponent> MovementComponent = nullptr;
};