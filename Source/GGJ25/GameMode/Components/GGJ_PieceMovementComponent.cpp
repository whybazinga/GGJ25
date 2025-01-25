// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_PieceMovementComponent.h"

#include "GGJ25/Player/GGJ_PlayerController.h"

FMoveState FMoveState::Initial()
{
    FMoveState MoveState;
    MoveState.ElapsedTime = 0;
    MoveState.StepIdx = 0;

    return MoveState;
}

UGGJ_PieceMovementComponent::UGGJ_PieceMovementComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UGGJ_PieceMovementComponent::BeginPlay()
{
    Super::BeginPlay();

    CachedPlayerController = Cast<AGGJ_PlayerController>(GetWorld()->GetFirstPlayerController());
}

void UGGJ_PieceMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!CurrentMoveRequest.IsSet() || !CurrentMoveState.IsSet())
    {
        return;
    }

    const bool HasReachedFinalStep = CurrentMoveState->StepIdx >= CurrentMoveRequest->Path.Num() - 1;
    if (HasReachedFinalStep)
    {
        OnMoveFinished.Broadcast();
        Reset();
        return;
    }

    const bool HasDurationElapsed = CurrentMoveState->ElapsedTime >= CurrentMoveRequest->Duration;
    if (HasDurationElapsed)
    {
        CurrentMoveState->ElapsedTime = 0;
        CurrentMoveState->StepIdx++;
        return;
    }

    const float Progress = CurrentMoveState->ElapsedTime / CurrentMoveRequest->Duration;

    const FVector StepStartLocation = CurrentMoveRequest->Path[CurrentMoveState->StepIdx];
    const FVector StepFinishLocation = CurrentMoveRequest->Path[CurrentMoveState->StepIdx + 1];

    const FVector NewInterpolatedLocation = FMath::Lerp(StepStartLocation, StepFinishLocation, Progress);
    GetOwner()->SetActorLocation(NewInterpolatedLocation);

    CurrentMoveState->ElapsedTime += DeltaTime;
}

void UGGJ_PieceMovementComponent::RequestMove(const FMoveRequest& MoveRequest)
{
    if (CurrentMoveRequest.IsSet() || CurrentMoveState.IsSet())
    {
        ensureAlways(false);
        return;
    }

    if (MoveRequest.Path.IsEmpty())
    {
        ensureAlways(false);
        return;
    }

    CurrentMoveRequest = MoveRequest;
    CurrentMoveState = FMoveState::Initial();
    OnMoveStarted.Broadcast();
}

void UGGJ_PieceMovementComponent::Reset()
{
    CurrentMoveRequest.Reset();
    CurrentMoveState.Reset();
}

