// Fill out your copyright notice in the Description page of Project Settings.

#include "GGJ_PlayerController.h"

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
    UE_LOG(LogTemp, Warning, TEXT("FIRST: FORWARD"))
}

void AGGJ_PlayerController::BackwardFirst()
{
    UE_LOG(LogTemp, Warning, TEXT("FIRST: BACKWARD"))
}

void AGGJ_PlayerController::LeftFirst()
{
    UE_LOG(LogTemp, Warning, TEXT("FIRST: LEFT"))
}

void AGGJ_PlayerController::RightFirst()
{
    UE_LOG(LogTemp, Warning, TEXT("FIRST: RIGHT"))
}

void AGGJ_PlayerController::ForwardSecond()
{
    UE_LOG(LogTemp, Warning, TEXT("SECOND: FORWARD"))
}

void AGGJ_PlayerController::BackwardSecond()
{
    UE_LOG(LogTemp, Warning, TEXT("SECOND: BACKWARD"))
}

void AGGJ_PlayerController::LeftSecond()
{
    UE_LOG(LogTemp, Warning, TEXT("SECOND: LEFT"))
}

void AGGJ_PlayerController::RightSecond()
{
    UE_LOG(LogTemp, Warning, TEXT("SECOND: RIGHT"))
}