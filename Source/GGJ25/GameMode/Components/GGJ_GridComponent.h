// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "GGJ_Grid.h"

#include "GGJ_GridComponent.generated.h"


struct FCoordinates;
enum class EPlayer : bool;


DECLARE_MULTICAST_DELEGATE(FOnGridReady);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGridPlayerLocationSet, EPlayer);


UCLASS(ClassGroup = (Custom), Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class GGJ25_API UGGJ_GridComponent : public UActorComponent
{
    GENERATED_BODY()

public:

    UGGJ_GridComponent();

    static UGGJ_GridComponent* Get(const UObject* WorldContext);

    TPair<FIntVector2, FIntVector2> GetPlayersSpawnCoordinates() const;

    TOptional<FIntVector2> GetPlayerLocation(EPlayer Player) const;
    TOptional<FVector> GetPlayerWorldLocation(EPlayer Player) const;

    void SetPlayerLocation(FIntVector2 NewLocation, EPlayer Player, bool ShouldNotify = true);

    TArray<FVector> GetAppliedMoveStepsWorldLocations(const FIntVector2 SourceLocation, TArray<FCoordinates> Steps) const;

    bool IsValidGridLocation(const FIntVector2& Location) const;

public:
    FOnGridReady OnGridReady;

    FOnGridPlayerLocationSet OnGridPlayerLocationSet;

protected:

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    void GenerateGrid();

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<AGGJ_Grid> GridClass = nullptr;

    UPROPERTY()
    TObjectPtr<AGGJ_Grid> Grid = nullptr;

    TOptional<FIntVector2> FirstPlayerLocation;
    TOptional<FIntVector2> SecondPlayerLocation;
};
