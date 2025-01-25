// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PieceActor.generated.h"

UCLASS()
class GGJ25_API APieceActor : public AActor
{
    GENERATED_BODY()

public:
    APieceActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
};