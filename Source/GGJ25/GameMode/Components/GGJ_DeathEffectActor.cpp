// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_DeathEffectActor.h"

#include "Components/BillboardComponent.h"


AGGJ_DeathEffectActor::AGGJ_DeathEffectActor()
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SpriteComponent = CreateDefaultSubobject<UBillboardComponent>("SpriteComponent");
    SpriteComponent->SetupAttachment(RootComponent);
    SpriteComponent->bHiddenInGame = false;
}

void AGGJ_DeathEffectActor::Show(const float Duration, const FVector& WorldLocation)
{
    SetActorLocation(WorldLocation);

    SetActorHiddenInGame(false);

    GetWorld()->GetTimerManager().SetTimer(HideTimerHandle, [this] () {
        SetActorHiddenInGame(true);
    }, Duration, false);
}

void AGGJ_DeathEffectActor::BeginPlay()
{
    Super::BeginPlay();

    SetActorHiddenInGame(true);
}


