// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "GGJ_DeathEffectActor.generated.h"


enum class EDeathReason : uint8;


UCLASS(Blueprintable)
class GGJ25_API AGGJ_DeathEffectActor : public AActor
{
    GENERATED_BODY()

public:

    AGGJ_DeathEffectActor();

    void Show(const float Duration, const FVector& WorldLocation, const EDeathReason DeathReason);

protected:

    virtual void BeginPlay() override;

protected:

    FTimerHandle HideTimerHandle;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UBillboardComponent> SpriteComponent = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UBillboardComponent> OutOfBoundsSpriteComponent = nullptr;
};
