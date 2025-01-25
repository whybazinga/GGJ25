#pragma once

#include "CoreMinimal.h"
#include "GeneralTypes.generated.h"

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

enum class EPlayer : bool
{
    One,
    Two
};