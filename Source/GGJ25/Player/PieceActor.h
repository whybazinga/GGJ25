// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGJ25/Moves/MoveDataAsset.h"

#include "PieceActor.generated.h"


UCLASS(Blueprintable, BlueprintType)
class GGJ25_API APieceActor : public AActor
{
    GENERATED_BODY()

public:
    APieceActor();

    //TODO: subject to change to the set of UMoveDataAssets
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMoveDataAsset* MoveDataAsset;

    TOptional<FDirectedMove> GetDirectedMove(const TPair<TOptional<EInputSide>, TOptional<EInputSide>>& Buffer) const;
protected:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UBillboardComponent> SpriteComponent = nullptr;

};