// Fill out your copyright notice in the Description page of Project Settings.


#include "PieceActor.h"

#include "Components/BillboardComponent.h"

APieceActor::APieceActor() : Super()
{
    PrimaryActorTick.bCanEverTick = false;

    SpriteComponent = CreateDefaultSubobject<UBillboardComponent>("SpriteComponent");
}

void APieceActor::BeginPlay()
{
    Super::BeginPlay();
    
}

