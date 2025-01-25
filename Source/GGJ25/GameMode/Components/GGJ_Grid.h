#pragma once

#include <CoreMinimal.h>

#include "GGJ_Grid.generated.h"

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


UCLASS(Blueprintable, BlueprintType)
class GGJ25_API AGGJ_Grid : public AActor
{
    GENERATED_BODY()

public:
    FVector2d Size;

    FVector GridLocationOffset;

    FVector2d TileSize;
    FVector2d TileCenterLocationOffset;

    TArray<TArray<FTile>> Tiles;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TObjectPtr<UStaticMeshComponent> StaticMesh = nullptr;

public:
    AGGJ_Grid();

    virtual void BeginPlay() override;

    FVector GetGridLocation() const;

    TOptional<FTile> GetTileOptional(int32 X, int32 Y) const;
    FTile GetTileChecked(int32 X, int32 Y) const;
    
    FVector GetTileWorldLocation(const FIntVector2& Coordinates) const;
    FVector GetTileWorldLocation(int32 X, int32 Y) const;

    TOptional<FTile> GetTileNeighbor(const FTile& Source, ETileNeighbour NeighbourType) const;

    void Print();

    void DebugDrawAxis(const UObject* WorldContext) const;
    void DebugDraw(const UObject* WorldContext) const;
    void DebugDrawTile(const UObject* WorldContext, const FTile& InTile) const;
};
