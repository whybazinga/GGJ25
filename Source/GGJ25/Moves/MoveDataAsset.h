// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGJ25/Player/GGJ_PlayerController.h"
#include "UObject/Object.h"
#include "MoveDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FInputPair
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    EInputSide First;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    EInputSide Second;
};

USTRUCT(BlueprintType)
struct FCoordinates
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 X;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    int32 Y;
};

USTRUCT(BlueprintType)
struct FDirectedMove
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FInputPair InputBuffer;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TArray<FCoordinates> Steps;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class GGJ25_API UMoveDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FDirectedMove> DirectedMoves;
};
