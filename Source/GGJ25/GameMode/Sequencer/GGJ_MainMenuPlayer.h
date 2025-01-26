// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGJ_MainMenuPlayer.generated.h"

class ULevelSequencePlayer;
class ULevelSequence;class AGGJ_PlayerController;
class ACineCameraActor;

UCLASS()
class GGJ25_API AGGJ_MainMenuPlayer : public AActor
{
    GENERATED_BODY()

public:
    AGGJ_MainMenuPlayer();

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    ACineCameraActor* MainCamera;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    ACineCameraActor* MenuCamera;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    ULevelSequence* MenuLevelSequence;
    
protected:

    UFUNCTION(BlueprintImplementableEvent)
    void OnGameStartedEvent();
    
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnSequenceFinished();

    UFUNCTION()
    void OnGameStarted();
    
private:
    TWeakObjectPtr<AGGJ_PlayerController> CachedPlayerController;
    TObjectPtr<ULevelSequencePlayer> CachedLevelSequencePlayer; 
    bool bPlayReverse;
};