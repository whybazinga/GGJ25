// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_DeathEffectActor.h"

#include "Components/AudioComponent.h"
#include "Components/BillboardComponent.h"

#include "GGJ_DeathsTracker.h"


AGGJ_DeathEffectActor::AGGJ_DeathEffectActor()
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SpriteComponent = CreateDefaultSubobject<UBillboardComponent>("SpriteComponent");
    SpriteComponent->SetupAttachment(RootComponent);
    SpriteComponent->bHiddenInGame = false;

    OutOfBoundsSpriteComponent = CreateDefaultSubobject<UBillboardComponent>("OutOfBoundsSpriteComponent");
    OutOfBoundsSpriteComponent->SetupAttachment(RootComponent);
    OutOfBoundsSpriteComponent->bHiddenInGame = false;

    KillAudio = CreateDefaultSubobject<UAudioComponent>("KillAudio");
    OutOfBoundsAudio = CreateDefaultSubobject<UAudioComponent>("OutOfBoundsAudio");
}

void AGGJ_DeathEffectActor::Show(const float Duration, const FVector& WorldLocation, const EDeathReason DeathReason)
{
    SetActorLocation(WorldLocation);

    SetActorHiddenInGame(false);
    if (DeathReason == EDeathReason::Kill)
    {
        SpriteComponent->SetHiddenInGame(false);
        OutOfBoundsSpriteComponent->SetHiddenInGame(true);
        KillAudio->Play();
    }
    else
    {
        OutOfBoundsSpriteComponent->SetHiddenInGame(false);
        SpriteComponent->SetHiddenInGame(true);
        OutOfBoundsAudio->Play();
    }

    GetWorld()->GetTimerManager().SetTimer(HideTimerHandle, [this] () {
        SetActorHiddenInGame(true);
    }, Duration, false);
}

void AGGJ_DeathEffectActor::BeginPlay()
{
    Super::BeginPlay();

    SetActorHiddenInGame(true);

    KillAudio->Stop();
    OutOfBoundsAudio->Stop();
}


