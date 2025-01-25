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

void APieceActor::BeginPlay()
{
    Super::BeginPlay();
    
}

