// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "GGJ_Grid.h"

#include "GGJ_GridComponent.generated.h"


struct FCoordinates;
enum class EPlayer : bool;
DECLARE_MULTICAST_DELEGATE(FOnGridReady);


UCLASS(ClassGroup = (Custom), Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class GGJ25_API UGGJ_GridComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UGGJ_GridComponent();

    TPair<FVector,FVector> GetPlayersSpawnLocations() const;

    TOptional<FIntVector2> GetPlayerLocation(EPlayer Player) const;

    TArray<FVector> GetAppliedMoveStepsWorldLocations(const FIntVector2 SourceLocation, TArray<FCoordinates> Steps) const;


public:
    FOnGridReady OnGridReady;

protected:

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    void GenerateGrid();

    void SetPlayerLocation(FIntVector2 NewLocation, EPlayer Player);

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<AGGJ_Grid> GridClass = nullptr;

    UPROPERTY()
    TObjectPtr<AGGJ_Grid> Grid = nullptr;

    TOptional<FIntVector2> FirstPlayerLocation;
    TOptional<FIntVector2> SecondPlayerLocation;
};
