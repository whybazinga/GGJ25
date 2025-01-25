// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "GGJ_GridComponent.h"

#include "GGJ_DeathsTracker.generated.h"


class UGGJ_GridComponent;


DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerDeath, EPlayer);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GGJ25_API UGGJ_DeathsTracker : public UActorComponent
{
    GENERATED_BODY()

public:

    UGGJ_DeathsTracker();

public:
    FOnPlayerDeath OnPlayerDeath;

protected:

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    void StartTracking();
    void StopTracking();

    void OnGridPlayerLocationSet(EPlayer MovedPlayer);

protected:
    
    TWeakObjectPtr<UGGJ_GridComponent> CachedGridComponent = nullptr;
};
