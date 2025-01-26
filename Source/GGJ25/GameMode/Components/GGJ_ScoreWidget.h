// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"

#include "GGJ_DeathEffectsComponent.h"
#include "GGJ_ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class GGJ25_API UGGJ_ScoreWidget : public UUserWidget
{
    GENERATED_BODY()
    
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ScoreFirst;
    
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ScoreSecond;
    
private:
    void ScoreUpdated(EPlayer Player) const;

    TWeakObjectPtr<UGGJ_DeathsTracker> DeathsTracker;
};
