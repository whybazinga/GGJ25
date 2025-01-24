#pragma once

#include <CoreMinimal.h>

#include "GridData.generated.h"


USTRUCT()
struct FTile
{
    GENERATED_BODY()
    
public:
    FIntVector2 Coordinates;

public:
    FString ToString() const;
};


USTRUCT()
struct FGrid
{
    GENERATED_BODY()

public:
    int32 SizeX = 0;
    int32 SizeY = 0;

    TArray<TArray<FTile>> Tiles;

public:
    FGrid() = default;

    void Generate(int32 InSizeX, int32 InSizeY);

    void Print();
};
