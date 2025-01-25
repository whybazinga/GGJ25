// Fill out your copyright notice in the Description page of Project Settings.


#include "PieceActor.h"

#include "Components/BillboardComponent.h"

APieceActor::APieceActor() : Super()
{
    PrimaryActorTick.bCanEverTick = false;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SpriteComponent = CreateDefaultSubobject<UBillboardComponent>("SpriteComponent");
    SpriteComponent->SetupAttachment(RootComponent);
    SpriteComponent->bHiddenInGame = false;
}

TOptional<FDirectedMove> APieceActor::GetDirectedMove(const TPair<TOptional<EInputSide>, TOptional<EInputSide>>& Buffer) const
{
    if(!Buffer.Key.IsSet() || !Buffer.Value.IsSet())
    {
        return {};
    }
    
    if(!MoveDataAsset)
    {
        return {};
    }

    for(auto& Move : MoveDataAsset->DirectedMoves)
    {
        if(Move.InputBuffer.First == Buffer.Key.GetValue()
            && Move.InputBuffer.Second == Buffer.Value.GetValue())
        {
            return Move;
        }
    }
    return {};
}

void APieceActor::BeginPlay()
{
    Super::BeginPlay();
    
}

