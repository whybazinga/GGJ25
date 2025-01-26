// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "GGJ_GridComponent.h"

#include "GGJ_DeathsTracker.generated.h"


class UGGJ_GridComponent;


UENUM()
enum class EDeathReason : uint8
{
    None = 0,
    OutOfBounds,
    Kill,
};


DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerDeath, EPlayer, EDeathReason);


USTRUCT(BlueprintType, Blueprintable)
struct FScore
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    int32 First;

    UPROPERTY(BlueprintReadWrite)
    int32 Second;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GGJ25_API UGGJ_DeathsTracker : public UActorComponent
{
    GENERATED_BODY()

public:

    UGGJ_DeathsTracker();

public:
    FOnPlayerDeath OnPlayerDeath;

    UFUNCTION(BlueprintCallable)
    FScore GetScore(){ return Score; }
    
protected:

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    void StartTracking();
    void StopTracking();

    void OnGridPlayerLocationSet(EPlayer MovedPlayer);
    
private:
    void UpdateScore(EPlayer LostPlayer);
    
protected:
    FScore Score;
    TWeakObjectPtr<UGGJ_GridComponent> CachedGridComponent = nullptr;
};
