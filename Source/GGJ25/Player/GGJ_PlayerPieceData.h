#pragma once

#include "CoreMinimal.h"

#include "GGJ_PlayerPieceData.generated.h"


USTRUCT(BlueprintType)
struct FPerPlayerPieceData
{
    GENERATED_BODY()

public:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UTexture2D> SpriteTexture = nullptr;

    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FVector HandSpriteOffset = FVector::ZeroVector;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UTexture2D> HandSpriteTexture = nullptr;
};