#pragma once

#include "CoreMinimal.h"
#include "GeneralTypes.generated.h"

enum class EGameState : uint8
{
    None = 0,
    InProgress,
    Ended
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

enum class EPlayer : bool
{
    One,
    Two
};

namespace Utility
{
    inline EPlayer GetOppositePlayer(const EPlayer Player)
    {
        return Player == EPlayer::One ? EPlayer::Two : EPlayer::One;
    }
}