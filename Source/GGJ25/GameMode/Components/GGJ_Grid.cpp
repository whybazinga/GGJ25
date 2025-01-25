#include "GGJ_Grid.h"


FVector FTile::GetExtent() const
{
    return FVector(TileSize.X / 2, TileSize.Y / 2, 0.0f);
}

FString FTile::ToString() const
{
    return FString::Printf(TEXT("(Loc: [%s]: Size: [%s])"), *Coordinates.ToString(), *TileSize.ToString());
}

AGGJ_Grid::AGGJ_Grid()
    : Super()
{
    constexpr int32 GridSize = 6;

    constexpr int32 GridTileSize = 50;
    constexpr int32 GridTileCenterLocationOffset = 0;

    Size = FVector2d(GridSize, GridSize);

    TileSize = FVector2D(GridTileSize, GridTileSize);
    TileCenterLocationOffset = FVector2D(GridTileCenterLocationOffset, GridTileCenterLocationOffset);

    GridLocationOffset = FVector(
        -Size.X * TileSize.X / 2 + (TileSize.X / 2),
        -Size.Y * TileSize.Y / 2 + (TileSize.Y / 2),
        25);

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(RootComponent);
}

void AGGJ_Grid::BeginPlay()
{
    Super::BeginPlay();

    for (int32 Y = 0; Y < Size.Y; Y++)
    {
        TArray<FTile>& NewRow = Tiles.Emplace_GetRef();
        for (int32 X = 0; X < Size.X; X++)
        {
            FTile& NewTile = NewRow.Emplace_GetRef();
            NewTile.Coordinates.X = X;
            NewTile.Coordinates.Y = Y;
            NewTile.TileSize = TileSize;
        }
    }

    DebugDrawAxis(this);
    DebugDraw(this);
}

FVector AGGJ_Grid::GetGridLocation() const
{
    return GetActorLocation() + GridLocationOffset;
}

TOptional<FTile> AGGJ_Grid::GetTileOptional(const FIntVector2& Coordinates) const
{
    return GetTileOptional(Coordinates.X, Coordinates.Y);
}

TOptional<FTile> AGGJ_Grid::GetTileOptional(const int32 X, const int32 Y) const
{
    if (Tiles.IsValidIndex(Y) && Tiles[Y].IsValidIndex(X))
    {
        return Tiles[Y][X];
    }

    return NullOpt;
}

FTile AGGJ_Grid::GetTileChecked(const FIntVector2& Coordinates) const
{
    return GetTileChecked(Coordinates.X, Coordinates.Y);
}

FTile AGGJ_Grid::GetTileChecked(const int32 X, const int32 Y) const
{
    return GetTileOptional(X, Y).GetValue();
}

FVector AGGJ_Grid::GetTileWorldLocation(const FIntVector2& Coordinates) const
{
    return GetTileWorldLocation(Coordinates.X, Coordinates.Y);
}

FVector AGGJ_Grid::GetTileWorldLocation(const int32 X, const int32 Y) const
{
    return GetGridLocation() + FVector(
        X * TileSize.X + TileCenterLocationOffset.X,
        Y * TileSize.Y + TileCenterLocationOffset.Y,
        0.0f);
}

TOptional<FTile> AGGJ_Grid::GetTileNeighbor(const FTile& Source, const ETileNeighbour NeighbourType) const
{
    switch (NeighbourType)
    {
        case ETileNeighbour::TopLeft:
            return GetTileOptional(
                Source.Coordinates.X - 1,
                Source.Coordinates.Y - 1);

        case ETileNeighbour::Top:
            return GetTileOptional(
                Source.Coordinates.X,
                Source.Coordinates.Y - 1);

        case ETileNeighbour::TopRight:
            return GetTileOptional(
                Source.Coordinates.X + 1,
                Source.Coordinates.Y - 1);

        case ETileNeighbour::Left:
            return GetTileOptional(
                Source.Coordinates.X - 1,
                Source.Coordinates.Y);

        case ETileNeighbour::Right:
            return GetTileOptional(
                Source.Coordinates.X + 1,
                Source.Coordinates.Y);

        case ETileNeighbour::BottomLeft:
            return GetTileOptional(
                Source.Coordinates.X - 1,
                Source.Coordinates.Y + 1);

        case ETileNeighbour::Bottom:
            return GetTileOptional(
                Source.Coordinates.X,
                Source.Coordinates.Y + 1);

        case ETileNeighbour::BottomRight:
            return GetTileOptional(
                Source.Coordinates.X + 1,
                Source.Coordinates.Y + 1);


        default:
            // you deserve it
            checkNoEntry();
            return NullOpt;
    }
}

void AGGJ_Grid::Print()
{
    UE_LOG(LogTemp, Log, TEXT("Grid:"));
    for (int32 Y = 0; Y < Tiles.Num(); Y++)
    {
        for (int32 X = 0; X < Tiles[Y].Num(); X++)
        {
            UE_LOG(LogTemp, Log, TEXT("%s"), *Tiles[Y][X].ToString());
        }
    }
}

void AGGJ_Grid::DebugDrawAxis(const UObject* WorldContext) const
{
    // X axis
    DrawDebugLine(
        GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull),
        GetGridLocation(),
        GetGridLocation() + FVector::ForwardVector * (Size.X + 1) * TileSize.X,
        FColor::Red, false, 100);

    // Y axis
    DrawDebugLine(
        GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull),
        GetGridLocation(),
        GetGridLocation() + FVector::RightVector * (Size.Y + 1) * TileSize.Y,
        FColor::Green, false, 100);
}

void AGGJ_Grid::DebugDraw(const UObject* WorldContext) const
{
    for (int32 Y = 0; Y < Tiles.Num(); Y++)
    {
        for (int32 X = 0; X < Tiles[Y].Num(); X++)
        {
            DebugDrawTile(WorldContext, GetTileChecked(X, Y));
        }
    }
}

void AGGJ_Grid::DebugDrawTile(const UObject* WorldContext, const FTile& InTile) const
{
    DrawDebugBox(
                GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull),
                GetTileWorldLocation(InTile.Coordinates),
                GetTileChecked(InTile.Coordinates).GetExtent(),
                FColor::Red, false, 100);

    DrawDebugSphere(
        GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull),
        GetTileWorldLocation(InTile.Coordinates),
        5,
        10,
        FColor::Black, false, 100);
}
