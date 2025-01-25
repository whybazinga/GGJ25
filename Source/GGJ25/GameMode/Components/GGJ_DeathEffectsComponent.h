// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "GGJ_DeathsTracker.h"

#include "GGJ_DeathEffectsComponent.generated.h"


class AGGJ_DeathEffectActor;
class UGGJ_GridComponent;
enum class EPlayer : bool;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GGJ25_API UGGJ_DeathEffectsComponent : public UActorComponent
{
    GENERATED_BODY()

public:

    UGGJ_DeathEffectsComponent();

protected:

    virtual void BeginPlay() override;

    void OnPlayerDeath(EPlayer Player);

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<AGGJ_DeathEffectActor> DeathEffectActor = nullptr;

    TWeakObjectPtr<UGGJ_GridComponent> CachedGridComponent = nullptr;

    TWeakObjectPtr<UGGJ_DeathsTracker> CachedDeathsTracker = nullptr;

    
    
};
