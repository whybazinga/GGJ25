// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameState.h"

#include "GGJ_GameState.generated.h"

class UGGJ_GridComponent;

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class GGJ25_API AGGJ_GameState : public AGameState
{
    GENERATED_BODY()

public:

    AGGJ_GameState();

protected:

    TObjectPtr<UGGJ_GridComponent> GridComponent = nullptr;
};
