#include "GridData.h"


FVector FTile::GetExtent() const
{
    return FVector(TileSize.X / 2, TileSize.Y / 2, 0.0f);
}

FString FTile::ToString() const
{
    return FString::Printf(TEXT("(Loc: [%s]: Size: [%s])"), *Coordinates.ToString(), *TileSize.ToString());
}

void FGrid::Generate()
{
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
}

TOptional<FTile> FGrid::GetTileOptional(const int32 X, const int32 Y) const
{
    if (Tiles.IsValidIndex(Y) && Tiles[Y].IsValidIndex(X))
    {
        return Tiles[Y][X];
    }

    return NullOpt;
}

FTile FGrid::GetTileChecked(const int32 X, const int32 Y) const
{
    return GetTileOptional(X, Y).GetValue();
}

FVector FGrid::GetTileWorldLocation(const int32 X, const int32 Y) const
{
    return FVector(X * TileSize.X + TileCenterLocationOffset.X, Y * TileSize.Y + TileCenterLocationOffset.Y, 0.0f);
}

TOptional<FTile> FGrid::GetTileNeighbor(const FTile& Source, const ETileNeighbour NeighbourType) const
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

void FGrid::Print()
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

void FGrid::DebugDrawAxis(const UObject* WorldContext) const
{
    // X axis
    DrawDebugLine(
        GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull),
        FVector::ZeroVector,
        FVector::ForwardVector * (Size.X + 1) * TileSize.X,
        FColor::Red, false, 100);

    // Y axis
    DrawDebugLine(
        GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull),
        FVector::ZeroVector,
        FVector::RightVector * (Size.Y + 1) * TileSize.Y,
        FColor::Green, false, 100);
}

void FGrid::DebugDraw(const UObject* WorldContext) const
{
    for (int32 Y = 0; Y < Tiles.Num(); Y++)
    {
        for (int32 X = 0; X < Tiles[Y].Num(); X++)
        {
            DebugDrawTile(WorldContext, GetTileChecked(X, Y));
        }
    }
}

void FGrid::DebugDrawTile(const UObject* WorldContext, const FTile& InTile) const
{
    DrawDebugBox(
                GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull),
                GetTileWorldLocation(InTile.Coordinates.X, InTile.Coordinates.Y),
                GetTileChecked(InTile.Coordinates.X, InTile.Coordinates.Y).GetExtent(),
                FColor::Red, false, 100);

    DrawDebugSphere(
        GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull),
        GetTileWorldLocation(InTile.Coordinates.X, InTile.Coordinates.Y),
        5,
        10,
        FColor::Black, false, 100);
}
