// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_ScoreWidget.h"
#include "Components/TextBlock.h"
#include "GGJ25/GameMode/GGJ_GameMode.h"

void UGGJ_ScoreWidget::NativeConstruct()
{
    Super::NativeConstruct();

    AGGJ_GameMode* GameMode = Cast<AGGJ_GameMode>(GetWorld()->GetAuthGameMode());
    if(!GameMode)
    {
        return;
    }

    DeathsTracker = GameMode->DeathsTracker;
    DeathsTracker->OnPlayerDeath.AddUObject(this, &ThisClass::ScoreUpdated);
}

void UGGJ_ScoreWidget::ScoreUpdated(EPlayer Player) const
{
    FScore Score = DeathsTracker->GetScore();
    ScoreFirst->SetText(FText::AsNumber(Score.First));
    ScoreSecond->SetText(FText::AsNumber(Score.Second));
}