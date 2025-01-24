#include "GridData.h"


FString FTile::ToString() const
{
    return FString::Printf(TEXT("[%s]"), *Coordinates.ToString());
}

void FGrid::Generate(const int32 InSizeX, const int32 InSizeY)
{
    SizeX = InSizeX;
    SizeY = InSizeY;

    for (int32 Y = 0; Y < SizeY; Y++)
    {
        TArray<FTile>& NewRow = Tiles.Emplace_GetRef();
        for (int32 X = 0; X < SizeX; X++)
        {
            FTile& NewTile = NewRow.Emplace_GetRef();
            NewTile.Coordinates.X = X;
            NewTile.Coordinates.Y = Y;
        }
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
