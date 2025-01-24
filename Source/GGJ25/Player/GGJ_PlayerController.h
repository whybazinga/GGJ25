// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"

#include "GGJ_PlayerController.generated.h"

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class GGJ25_API AGGJ_PlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AActor* PawnOne;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AActor* PawnTwo;
    
protected:
    virtual void SetupInputComponent() override;

    void ForwardFirst();
    void BackwardFirst();
    void LeftFirst();
    void RightFirst();

    void ForwardSecond();
    void BackwardSecond();
    void LeftSecond();
    void RightSecond();
};
