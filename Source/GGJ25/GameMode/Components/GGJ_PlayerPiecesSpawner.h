// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "GGJ_PlayerPiecesSpawner.generated.h"


class UGGJ_GridComponent;
class APieceActor;


UCLASS(ClassGroup = (Custom), Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class GGJ25_API UGGJ_PlayerPiecesSpawner : public UActorComponent
{
    GENERATED_BODY()

public:

    UGGJ_PlayerPiecesSpawner();

protected:

    virtual void BeginPlay() override;

    void OnGridReady();

    TPair<FVector, FVector> GetPlayersSpawnLocations() const;

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<APieceActor> PlayerPieceActorClass = nullptr;

    TWeakObjectPtr<UGGJ_GridComponent> CachedGridComponent = nullptr;

};
