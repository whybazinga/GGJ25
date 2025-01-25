// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GGJ25/Moves/MoveDataAsset.h"

#include "GGJ_PlayerController.generated.h"


class UGGJ_GridComponent;
enum class EPlayer : bool;
class APieceActor;


/**
* Ту-ту-ту, ты тупа, убью тебя с улыбкой на устах
* Я уеду в Будапешт и прыгну с самого красивого моста
* Бэйби, ты в итоге так и ничего не поняла
* А я просто сердце развлекал
* Модели, модели
* Модели, модели
* Further lyrics you can find at https://genius.com/Feduk-acoustic-version-models-lyrics
 */
UCLASS(Blueprintable, BlueprintType)
class GGJ25_API AGGJ_PlayerController : public APlayerController
{
    GENERATED_BODY()

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMoveStarted, AActor*, Actor, FCoordinates, Coordinates);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMoveFinished, AActor*, Actor, FCoordinates, Coordinates);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCooldownFinished);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPiecesSet);
    
    using TInputBuffer = TPair<TOptional<EInputSide>, TOptional<EInputSide>>; 
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    APieceActor* PawnOne;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    APieceActor* PawnTwo;

    FOnMoveStarted& GetOnMoveStarted() { return OnMoveStarted; }
    FOnMoveFinished& GetOnMoveFinished() { return OnMoveFinished; }
    FOnCooldownFinished& GetOnCooldownFinished(){ return OnCooldownFinished; }
    FOnPiecesSet& GetOnPiecesSet() { return OnPiecesSet; }

    APieceActor* GetPlayerPawn(const EPlayer InPlayer) const;
    
protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

    void ForwardFirst();
    void BackwardFirst();
    void LeftFirst();
    void RightFirst();

    void ForwardSecond();
    void BackwardSecond();
    void LeftSecond();
    void RightSecond();

private:
    TInputBuffer BufferFirst;
    TInputBuffer BufferSecond;
    
    void ProcessMovement(EInputSide InputSide, EPlayer PlayerEnum);
    void MovePawn(EPlayer PlayerEnum);
    void FlushBuffer(TInputBuffer& BufferToFlush);

    FString ConvertInputSideToString(EInputSide InputSide);
    TPair<FString, FString> ConvertBufferToString(const TInputBuffer& Buffer);

    FOnMoveStarted OnMoveStarted;
    FOnMoveFinished OnMoveFinished;
    FOnCooldownFinished OnCooldownFinished;
    FOnPiecesSet OnPiecesSet;

    TWeakObjectPtr<UGGJ_GridComponent> CachedGridComponent = nullptr;
};
