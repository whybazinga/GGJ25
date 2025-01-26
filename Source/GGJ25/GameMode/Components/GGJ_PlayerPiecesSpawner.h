// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "GGJ_GridComponent.h"

#include "GGJ_PlayerPiecesSpawner.generated.h"


class AGGJ_PlayerController;
class UGGJ_GridComponent;
class APieceActor;


DECLARE_MULTICAST_DELEGATE(FOnPiecesPlacedOnBoard);


/**
 * @brief GameMode component
 */
UCLASS(ClassGroup = (Custom), Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class GGJ25_API UGGJ_PlayerPiecesSpawner : public UActorComponent
{
    GENERATED_BODY()

public:

    UGGJ_PlayerPiecesSpawner();

    void PlacePiecesOnBoard();

public:
    FOnPiecesPlacedOnBoard OnPiecesPlacedOnBoard;

protected:

    virtual void BeginPlay() override;

    void OnGridReady();

protected:
    
    void PlacePlayerPieceOnBoard(EPlayer Player, const FIntVector2& Coordinates);

    APieceActor* SpawnPlayer(EPlayer Player) const;

    TPair<FIntVector2, FIntVector2> GetPlayersSpawnCoordinates() const;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<APieceActor> PlayerPieceActorClass = nullptr;

    TWeakObjectPtr<UGGJ_GridComponent> CachedGridComponent = nullptr;

    TWeakObjectPtr<AGGJ_PlayerController> CachedPlayerController = nullptr;
};
