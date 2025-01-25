// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJ_PlayerController.h"

#include "GGJ25/GeneralTypes.h"

#include "PieceActor.h"

void AGGJ_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    
    InputComponent->BindAction("ForwardFirst", IE_Pressed, this, &ThisClass::ForwardFirst);
    InputComponent->BindAction("BackwardFirst", IE_Pressed, this, &ThisClass::BackwardFirst);
    InputComponent->BindAction("LeftFirst", IE_Pressed, this, &ThisClass::LeftFirst);
    InputComponent->BindAction("RightFirst", IE_Pressed, this, &ThisClass::RightFirst);
    
    InputComponent->BindAction("ForwardSecond", IE_Pressed, this, &ThisClass::ForwardSecond);
    InputComponent->BindAction("BackwardSecond", IE_Pressed, this, &ThisClass::BackwardSecond);
    InputComponent->BindAction("LeftSecond", IE_Pressed, this, &ThisClass::LeftSecond);
    InputComponent->BindAction("RightSecond", IE_Pressed, this, &ThisClass::RightSecond);
}

void AGGJ_PlayerController::ForwardFirst()
{
    ProcessMovement(EInputSide::Front, EPlayer::One);
}

void AGGJ_PlayerController::BackwardFirst()
{
    ProcessMovement(EInputSide::Back, EPlayer::One);
}

void AGGJ_PlayerController::LeftFirst()
{
    ProcessMovement(EInputSide::Left, EPlayer::One);
}

void AGGJ_PlayerController::RightFirst()
{
    ProcessMovement(EInputSide::Right, EPlayer::One);
}

void AGGJ_PlayerController::ForwardSecond()
{
    ProcessMovement(EInputSide::Front, EPlayer::Two);
}

void AGGJ_PlayerController::BackwardSecond()
{
    ProcessMovement(EInputSide::Back, EPlayer::Two);
}

void AGGJ_PlayerController::LeftSecond()
{
    ProcessMovement(EInputSide::Left, EPlayer::Two);
}

void AGGJ_PlayerController::RightSecond()
{
    ProcessMovement(EInputSide::Right, EPlayer::Two);
}

void AGGJ_PlayerController::ProcessMovement(EInputSide InputSide, EPlayer PlayerEnum)
{
    auto UpdateBufferInternal = [this](TInputBuffer& BufferToUpdate, EInputSide InputSide)
    {
        if(!BufferToUpdate.Key.IsSet())
        {
            BufferToUpdate.Key = InputSide;
        }
        else if(!BufferToUpdate.Value.IsSet())
        {
            BufferToUpdate.Value = InputSide;
        }
        else //TODO: delete this section, it is just for flush test
        {
            FlushBuffer(BufferToUpdate);
        }
    };
    
    if(PlayerEnum == EPlayer::One)
    {
        UpdateBufferInternal(BufferFirst, InputSide);
        MovePawn(PawnOne, BufferFirst);
    }
    else
    {
        UpdateBufferInternal(BufferSecond, InputSide);
        MovePawn(PawnTwo, BufferSecond);
    }
    
    FString PlayerS = (PlayerEnum == EPlayer::One) ? "One" : "Two";
    TPair<FString, FString> BufferS = PlayerEnum == EPlayer::One ? ConvertBufferToString(BufferFirst) : ConvertBufferToString(BufferSecond);
    UE_LOG(LogTemp, Warning, TEXT("Player %s buffer: [%s, %s]"), *PlayerS, *BufferS.Key, *BufferS.Value);
}

void AGGJ_PlayerController::MovePawn(APieceActor* Piece, const TInputBuffer& Buffer)
{
    if(!Buffer.Key.IsSet() || !Buffer.Value.IsSet())
    {
        return;
    }

    TOptional<FDirectedMove> Move = Piece->GetDirectedMove(Buffer);
    if(!Move.IsSet())
    {
        UE_LOG(LogTemp, Warning, TEXT("Move is not found: [%s]"), *Piece->GetName());
        return;
    }

    
}

void AGGJ_PlayerController::FlushBuffer(TInputBuffer& BufferToFlush)
{
    BufferToFlush.Key.Reset();
    BufferToFlush.Value.Reset();
}

FString AGGJ_PlayerController::ConvertInputSideToString(EInputSide InputSide)
{
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EInputSide"), true);
    if (!EnumPtr)
    {
        return FString("Invalid");
    }

    return EnumPtr->GetNameStringByIndex(static_cast<int32>(InputSide));
}

TPair<FString, FString> AGGJ_PlayerController::ConvertBufferToString(const TInputBuffer& Buffer)
{
    FString FirstValue = Buffer.Key.IsSet() ? ConvertInputSideToString(Buffer.Key.GetValue()) : "Invalid";
    FString SecondValue = Buffer.Value.IsSet() ? ConvertInputSideToString(Buffer.Value.GetValue()) : "Invalid";
    return {FirstValue,SecondValue };
}