// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGJ25/GeneralTypes.h"
#include "UObject/Object.h"
#include "MoveDataAsset.generated.h"

UENUM()
enum class EInputSide : uint8
{
    Front,
    Back,
    Left,
    Right
};

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
