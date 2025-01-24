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

FTile FGrid::GetTile(int32 X, int32 Y) const
{
    check(Tiles.IsValidIndex(Y));
    check(Tiles[Y].IsValidIndex(X));

    return Tiles[Y][X];
}

FVector FGrid::GetTileWorldLocation(const int32 X, const int32 Y) const
{
    return FVector(X * TileSize.X + TileLocationOffset.X, Y * TileSize.Y + TileLocationOffset.Y, 0.0f);
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

void FGrid::DebugDraw(const UObject* WorldContext) const
{
    for (int32 Y = 0; Y < Tiles.Num(); Y++)
    {
        for (int32 X = 0; X < Tiles[Y].Num(); X++)
        {
            UE_LOG(LogTemp, Log, TEXT("%s"), *GetTileWorldLocation(X, Y).ToString());
            DrawDebugBox(
                GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull),
                GetTileWorldLocation(X, Y),
                GetTile(X, Y).GetExtent(),
                FColor::Red, false, 100);

            DrawDebugSphere(
                GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull),
                GetTileWorldLocation(X, Y),
                5,
                10,
                FColor::Black, false, 100);
        }
    }
}
