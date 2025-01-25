// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GGJ_PieceMovementComponent.generated.h"

class AGGJ_PlayerController;


USTRUCT()
struct FMoveState
{
    GENERATED_BODY()

public:

    static FMoveState Initial();

    float ElapsedTime = -1;
    int32 StepIdx = INDEX_NONE;
};


USTRUCT()
struct FMoveRequest
{
    GENERATED_BODY()

public:
    TOptional<FIntVector2> SourceCoordinates;
    TOptional<FIntVector2> DestinationCoordinates;

    float Duration = 0.0f;

    TArray<FVector> Path;
};


DECLARE_MULTICAST_DELEGATE(FPieceMovementComponent_OnMoveStarted);
DECLARE_MULTICAST_DELEGATE_OneParam(FPieceMovementComponent_OnMoveFinished, FMoveRequest);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GGJ25_API UGGJ_PieceMovementComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UGGJ_PieceMovementComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void RequestMove(const FMoveRequest& MoveRequest);

    void Reset();

public:
    FPieceMovementComponent_OnMoveStarted OnMoveStarted;
    FPieceMovementComponent_OnMoveFinished OnMoveFinished;

private:
    TWeakObjectPtr<AGGJ_PlayerController> CachedPlayerController;

    TOptional<FMoveRequest> CurrentMoveRequest;
    TOptional<FMoveState> CurrentMoveState;
};