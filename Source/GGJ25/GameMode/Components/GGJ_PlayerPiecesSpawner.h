// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "GGJ_GridComponent.h"

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
    APieceActor* SpawnPlayer(EPlayer Player, const FIntVector2& PieceSpawnCoordinates) const;

    void OnGridReady();

protected:

    TPair<FIntVector2, FIntVector2> GetPlayersSpawnCoordinates() const;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<APieceActor> PlayerPieceActorClass = nullptr;

    TWeakObjectPtr<UGGJ_GridComponent> CachedGridComponent = nullptr;
};
