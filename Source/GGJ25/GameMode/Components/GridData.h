#pragma once

#include <CoreMinimal.h>

#include "GridData.generated.h"


USTRUCT()
struct FTile
{
    GENERATED_BODY()
    
public:
    FIntVector2 Coordinates;

    FVector2d TileSize;

public:
    FVector GetExtent() const;
    
    FString ToString() const;
};


USTRUCT()
struct FGrid
{
    GENERATED_BODY()

public:
    FVector2d Size;

    FVector2d TileSize;
    FVector2d TileLocationOffset;

    TArray<TArray<FTile>> Tiles;

public:
    FGrid() = default;

    void Generate();

    FTile GetTile(int32 X, int32 Y) const;
    FVector GetTileWorldLocation(int32 X, int32 Y) const;

    void Print();

    void DebugDraw(const UObject* WorldContext) const;
};
