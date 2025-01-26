// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "GGJ_MovePreviewActor.generated.h"

UCLASS(Blueprintable, BlueprintType)
class GGJ25_API AGGJ_MovePreviewActor : public AActor
{
    GENERATED_BODY()

public:

    AGGJ_MovePreviewActor();

protected:

    virtual void BeginPlay() override;

};
