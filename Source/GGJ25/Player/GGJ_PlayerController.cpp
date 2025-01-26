// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJ_PlayerController.h"

#include "GGJ25/GameMode/Components/GGJ_GridComponent.h"
#include "GGJ25/GameMode/GGJ_GameMode.h"
#include "GGJ25/GameMode/GGJ_GameState.h"
#include "GGJ25/GeneralTypes.h"

#include "PieceActor.h"


void AGGJ_PlayerController::BeginPlay()
{
    Super::BeginPlay();
    CachedGridComponent = GetWorld()->GetGameState<AGGJ_GameState>()->FindComponentByClass<UGGJ_GridComponent>();
    check(CachedGridComponent.IsValid());

    if(!PawnTwo || !PawnOne)
    {
        OnPiecesSet.AddDynamic(this, &ThisClass::OnPiecesSeted);
    }
    else
    {
        OnPiecesSeted();
    }
    
}

void AGGJ_PlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if(UGGJ_PieceMovementComponent* FirstPieceMovementComponent = PawnOne->GetComponentByClass<UGGJ_PieceMovementComponent>())
    {
        FirstPieceMovementComponent->OnMoveFinished.RemoveAll(this);
    }

    if(UGGJ_PieceMovementComponent* SecondPieceMovementComponent = PawnOne->GetComponentByClass<UGGJ_PieceMovementComponent>())
    {
        SecondPieceMovementComponent->OnMoveFinished.RemoveAll(this);
    }
    Super::EndPlay(EndPlayReason);
}

void AGGJ_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAction("RestartGame", IE_Pressed, this, &ThisClass::RestartGame);

    InputComponent->BindAction("ForwardFirst", IE_Pressed, this, &ThisClass::ForwardFirst);
    InputComponent->BindAction("BackwardFirst", IE_Pressed, this, &ThisClass::BackwardFirst);
    InputComponent->BindAction("LeftFirst", IE_Pressed, this, &ThisClass::LeftFirst);
    InputComponent->BindAction("RightFirst", IE_Pressed, this, &ThisClass::RightFirst);

    InputComponent->BindAction("ForwardSecond", IE_Pressed, this, &ThisClass::ForwardSecond);
    InputComponent->BindAction("BackwardSecond", IE_Pressed, this, &ThisClass::BackwardSecond);
    InputComponent->BindAction("LeftSecond", IE_Pressed, this, &ThisClass::LeftSecond);
    InputComponent->BindAction("RightSecond", IE_Pressed, this, &ThisClass::RightSecond);
}

void AGGJ_PlayerController::RestartGame()
{
    Cast<AGGJ_GameMode>(GetWorld()->GetAuthGameMode())->Restart();
}

APieceActor* AGGJ_PlayerController::GetPlayerPawn(const EPlayer InPlayer) const
{
    if (InPlayer == EPlayer::One)
    {
        return PawnOne;
    }

    return PawnTwo;
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

void AGGJ_PlayerController::FirstPlayerFinished(FMoveRequest MoveRequest)
{
    FlushBuffer(BufferFirst);
}

void AGGJ_PlayerController::SecondPlayerFinished(FMoveRequest MoveRequest)
{
    FlushBuffer(BufferSecond);
}

void AGGJ_PlayerController::OnPiecesSeted()
{
    if(UGGJ_PieceMovementComponent* FirstPieceMovementComponent = PawnOne->GetComponentByClass<UGGJ_PieceMovementComponent>())
    {
        FirstPieceMovementComponent->OnMoveFinished.AddUObject(this, &ThisClass::FirstPlayerFinished);
    }

    if(UGGJ_PieceMovementComponent* SecondPieceMovementComponent = PawnTwo->GetComponentByClass<UGGJ_PieceMovementComponent>())
    {
        SecondPieceMovementComponent->OnMoveFinished.AddUObject(this, &ThisClass::SecondPlayerFinished);
    }
}

void AGGJ_PlayerController::ProcessMovement(EInputSide InputSide, EPlayer PlayerEnum)
{
    auto UpdateBufferInternal = [this](TInputBuffer& BufferToUpdate, EInputSide InputSide)
    {
        if(!BufferToUpdate.Key.IsSet() || IsOppositeInputSide(BufferToUpdate.Key.GetValue(), InputSide))
        {
            BufferToUpdate.Key = InputSide;
        }
        else if(!BufferToUpdate.Value.IsSet())
        {
            BufferToUpdate.Value = InputSide;
        }
        // else //TODO: delete this section, it is just for flush test
        // {
        //     FlushBuffer(BufferToUpdate);
        // }
    };
    
    if(PlayerEnum == EPlayer::One)
    {
        UpdateBufferInternal(BufferFirst, InputSide);
    }
    else
    {
        UpdateBufferInternal(BufferSecond, InputSide);
    }
    MovePawn(PlayerEnum);
    
    FString PlayerS = (PlayerEnum == EPlayer::One) ? "One" : "Two";
    TPair<FString, FString> BufferS = PlayerEnum == EPlayer::One ? ConvertBufferToString(BufferFirst) : ConvertBufferToString(BufferSecond);
    UE_LOG(LogTemp, Warning, TEXT("Player %s buffer: [%s, %s]"), *PlayerS, *BufferS.Key, *BufferS.Value);
}

void AGGJ_PlayerController::MovePawn(EPlayer PlayerEnum)
{
    TInputBuffer InputBuffer;
    APieceActor* Piece;
    if(PlayerEnum == EPlayer::One)
    {
        InputBuffer = BufferFirst;
        Piece = PawnOne;
    }
    else
    {
        InputBuffer = BufferSecond;
        Piece = PawnTwo;
    }

    if(!InputBuffer.Key.IsSet() || !InputBuffer.Value.IsSet())
    {
        return;
    }

    Piece->Move(InputBuffer);
}

void AGGJ_PlayerController::FlushBuffer(TInputBuffer& BufferToFlush)
{
    BufferToFlush.Key.Reset();
    BufferToFlush.Value.Reset();
}

bool AGGJ_PlayerController::IsOppositeInputSide(EInputSide BufferInputSide, EInputSide InputSide)
{
    if(BufferInputSide == InputSide)
    {
        return true;
    }
    
    if((BufferInputSide == EInputSide::Front) && (InputSide == EInputSide::Back))
    {
        return true;
    }

    if((BufferInputSide == EInputSide::Back) && (InputSide == EInputSide::Front))
    {
        return true;
    }

    if((BufferInputSide == EInputSide::Left) && (InputSide == EInputSide::Right))
    {
        return true;
    }

    if((BufferInputSide == EInputSide::Right) && (InputSide == EInputSide::Left))
    {
        return true;
    }
    return false;
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