// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "GGJ_Grid.h"

#include "GGJ_GridComponent.generated.h"


UCLASS(ClassGroup = (Custom), Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class GGJ25_API UGGJ_GridComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UGGJ_GridComponent();

protected:

    virtual void BeginPlay() override;

    void GenerateGrid();

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<AGGJ_Grid> GridClass = nullptr;

    UPROPERTY()
    TObjectPtr<AGGJ_Grid> Grid = nullptr;
};
