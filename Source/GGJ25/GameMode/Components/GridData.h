#pragma once

#include <CoreMinimal.h>

#include "GridData.generated.h"

UENUM()
enum class ETileNeighbour : uint8
{
    Invalid = 0,

    TopLeft, Top, TopRight,
    Left, /*Self, */ Right,
    BottomLeft, Bottom, BottomRight,
};


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
    FVector2d TileCenterLocationOffset;

    TArray<TArray<FTile>> Tiles;

public:
    FGrid() = default;

    void Generate();

    TOptional<FTile> GetTileOptional(int32 X, int32 Y) const;
    FTile GetTileChecked(int32 X, int32 Y) const;
    FVector GetTileWorldLocation(int32 X, int32 Y) const;

    TOptional<FTile> GetTileNeighbor(const FTile& Source, ETileNeighbour NeighbourType) const;

    void Print();

    void DebugDrawAxis(const UObject* WorldContext) const;
    void DebugDraw(const UObject* WorldContext) const;
    void DebugDrawTile(const UObject* WorldContext, const FTile& InTile) const;
};
