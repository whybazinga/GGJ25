// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_DeathEffectsComponent.h"

#include "GGJ25/Player/GGJ_PlayerController.h"
#include "GGJ25/Player/PieceActor.h"
#include "Kismet/GameplayStatics.h"

#include "GGJ_DeathEffectActor.h"
#include "GGJ_GridComponent.h"


UGGJ_DeathEffectsComponent::UGGJ_DeathEffectsComponent()
{
}


void UGGJ_DeathEffectsComponent::BeginPlay()
{
    Super::BeginPlay();

    CachedGridComponent = UGGJ_GridComponent::Get(this);

    CachedDeathsTracker = GetOwner()->FindComponentByClass<UGGJ_DeathsTracker>();

    DeathEffectActor = Cast<AGGJ_DeathEffectActor>(UGameplayStatics::GetActorOfClass(this, AGGJ_DeathEffectActor::StaticClass()));

    CachedDeathsTracker->OnPlayerDeath.AddUObject(this, &ThisClass::OnPlayerDeath);
}

void UGGJ_DeathEffectsComponent::OnPlayerDeath(const EPlayer Player)
{
    DeathEffectActor->Show(0.6f, CachedGridComponent->GetPlayerWorldLocation(Player).GetValue());
    
    Cast<AGGJ_PlayerController>(GetWorld()->GetFirstPlayerController())->GetPlayerPawn(Player)->SetActorHiddenInGame(true);
}

