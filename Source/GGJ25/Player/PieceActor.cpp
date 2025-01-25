// Fill out your copyright notice in the Description page of Project Settings.


#include "PieceActor.h"

APieceActor::APieceActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

void APieceActor::BeginPlay()
{
    Super::BeginPlay();
    
}

void APieceActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

