// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GGJ_PieceMovementComponent.generated.h"


class AGGJ_PlayerController;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GGJ25_API UGGJ_PieceMovementComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UGGJ_PieceMovementComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void SetMovementStart(const TArray<FVector>& Steps);

private:
    TArray<FVector> Path;
    float ElapsedTime;
    int32 CurrenStepIdx;
    TObjectPtr<AGGJ_PlayerController> PieceController;
};