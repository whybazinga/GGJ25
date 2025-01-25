// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_PieceMovementComponent.h"

#include "GGJ25/Player/GGJ_PlayerController.h"
#include "GGJ25/Player/PieceActor.h"

UGGJ_PieceMovementComponent::UGGJ_PieceMovementComponent(): ElapsedTime(0)
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UGGJ_PieceMovementComponent::BeginPlay()
{
    Super::BeginPlay();

    APieceActor* PieceActor = Cast<APieceActor>(GetOwner());
    check(PieceActor)

    AController* Controller = PieceActor->GetInstigatorController();
    if(!Controller)
    {
        return;
    }

    PieceController = Cast<AGGJ_PlayerController>(Controller);
}

void UGGJ_PieceMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    APieceActor* PieceActor = Cast<APieceActor>(GetOwner());
    check(PieceActor)
    
    if(ElapsedTime < PieceActor->MovementTime && !Path.IsEmpty() && Path.IsValidIndex(CurrenStepIdx + 1))
    {
        float Progress = ElapsedTime / PieceActor->MovementTime;
        FVector StartingLocation = Path[CurrenStepIdx];
        FVector NewLocation = FMath::Lerp(StartingLocation, Path[CurrenStepIdx + 1], Progress);
        PieceActor->SetActorLocation(NewLocation);
        ElapsedTime += DeltaTime;
    }
    else
    {
        CurrenStepIdx++;
        ElapsedTime = 0.f;

        if(!Path.IsValidIndex(CurrenStepIdx + 1))
        {
            //PieceController->GetOnMoveFinished().Broadcast(PieceActor, )
        }
    }
}

void UGGJ_PieceMovementComponent::SetMovementStart(const TArray<FVector>& Steps)
{
    CurrenStepIdx = 0;
    Path = Steps;
}

