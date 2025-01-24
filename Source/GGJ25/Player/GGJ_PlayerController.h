// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"

#include "GGJ_PlayerController.generated.h"

UENUM()
enum class EInputSide : uint8
{
    Front,
    Back,
    Left,
    Right
};

enum class EPlayer : bool
{
    One,
    Two
};

/**
 *
 */
UCLASS()
class GGJ25_API AGGJ_PlayerController : public APlayerController
{
    GENERATED_BODY()

    using TInputBuffer = TPair<TOptional<EInputSide>, TOptional<EInputSide>>; 
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AActor* PawnOne;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AActor* PawnTwo;
    
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
};
