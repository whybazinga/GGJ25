// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameMode.h"

#include "GGJ_GameMode.generated.h"


class UGGJ_DeathEffectsComponent;
class UGGJ_DeathsTracker;

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class GGJ25_API AGGJ_GameMode : public AGameMode
{
    GENERATED_BODY()

public:
    AGGJ_GameMode();

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UGGJ_DeathsTracker> DeathsTracker = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UGGJ_DeathEffectsComponent> DeathEffectsComponent = nullptr;

protected:

    virtual void BeginPlay() override;
};
