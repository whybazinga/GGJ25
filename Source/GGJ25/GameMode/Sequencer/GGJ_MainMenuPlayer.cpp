// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_MainMenuPlayer.h"
#include "GGJ25/Player/GGJ_PlayerController.h"
#include "Runtime/CinematicCamera/Public/CineCameraActor.h"
#include "LevelSequencePlayer.h"


// Sets default values
AGGJ_MainMenuPlayer::AGGJ_MainMenuPlayer()
{
}

void AGGJ_MainMenuPlayer::BeginPlay()
{
    Super::BeginPlay();

    if(!MenuCamera || !MainCamera)
    {
        return;
    }
    
    CachedPlayerController = Cast<AGGJ_PlayerController>(GetWorld()->GetFirstPlayerController());
    CachedPlayerController->SetViewTargetWithBlend(MenuCamera, 0.f);

    ALevelSequenceActor* LevelSequenceActor;
    CachedLevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), MenuLevelSequence, FMovieSceneSequencePlaybackSettings(), LevelSequenceActor);
    
    if (CachedLevelSequencePlayer)
    {
        CachedLevelSequencePlayer->OnFinished.AddDynamic(this, &ThisClass::OnSequenceFinished);
        CachedLevelSequencePlayer->Play();
        bPlayReverse = true;
    }

    CachedPlayerController->GetOnGameStart().AddDynamic(this, &ThisClass::OnGameStarted);
}

void AGGJ_MainMenuPlayer::OnSequenceFinished()
{
    if(bPlayReverse)
    {
        CachedLevelSequencePlayer->PlayReverse();
        bPlayReverse = false;
    }
    else
    {
        CachedLevelSequencePlayer->Play();
        bPlayReverse = true;
    }
}

void AGGJ_MainMenuPlayer::OnGameStarted()
{
    CachedLevelSequencePlayer->Stop();
    CachedPlayerController->SetViewTargetWithBlend(MainCamera, 0.f);
    OnGameStartedEvent();
}

