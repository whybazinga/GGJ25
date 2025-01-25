// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GGJ25/Moves/MoveDataAsset.h"
#include "GGJ_PlayerController.generated.h"

class APieceActor;


enum class EPlayer : bool
{
    One,
    Two
};

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class GGJ25_API AGGJ_PlayerController : public APlayerController
{
    GENERATED_BODY()

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMoveStarted, AActor*, Actor, FCoordinates, Coordinates);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMoveFinished, AActor*, Actor, FCoordinates, Coordinates);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCooldownFinished);
    
    using TInputBuffer = TPair<TOptional<EInputSide>, TOptional<EInputSide>>; 
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    APieceActor* PawnOne;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    APieceActor* PawnTwo;

    FOnMoveStarted& GetOnMoveStarted() { return OnMoveStarted; }
    FOnMoveFinished& GetOnMoveFinished() { return OnMoveFinished; }
    FOnCooldownFinished& GetOnCooldownFinished(){ return OnCooldownFinished; }
    
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

private:
    TInputBuffer BufferFirst;
    TInputBuffer BufferSecond;
    
    void UpdateBuffer(EInputSide InputSide, EPlayer PlayerEnum);
    void FlushBuffer(TInputBuffer& BufferToFlush);

    FString ConvertInputSideToString(EInputSide InputSide);
    TPair<FString, FString> ConvertBufferToString(const TInputBuffer& Buffer);

    FOnMoveStarted OnMoveStarted;
    FOnMoveFinished OnMoveFinished;
    FOnCooldownFinished OnCooldownFinished;
};
