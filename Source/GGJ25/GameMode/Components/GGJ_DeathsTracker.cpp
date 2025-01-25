// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_DeathsTracker.h"

#include "GGJ25/GeneralTypes.h"

#include "GGJ_GridComponent.h"


UGGJ_DeathsTracker::UGGJ_DeathsTracker()
{
    PrimaryComponentTick.bCanEverTick = false;
}


void UGGJ_DeathsTracker::BeginPlay()
{
    Super::BeginPlay();

    CachedGridComponent = UGGJ_GridComponent::Get(this);
    check(CachedGridComponent.IsValid());

    StartTracking();
}

void UGGJ_DeathsTracker::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    StopTracking();

    Super::EndPlay(EndPlayReason);
}

void UGGJ_DeathsTracker::StartTracking()
{
    check(CachedGridComponent.IsValid());
    CachedGridComponent->OnGridPlayerLocationSet.AddUObject(this, &ThisClass::OnGridPlayerLocationSet);
}
void UGGJ_DeathsTracker::StopTracking()
{
    check(CachedGridComponent.IsValid());
    CachedGridComponent->OnGridPlayerLocationSet.RemoveAll(this);
}

void UGGJ_DeathsTracker::OnGridPlayerLocationSet(const EPlayer MovedPlayer)
{
    const TOptional<FIntVector2> MovedPlayerLocation = CachedGridComponent->GetPlayerLocation(MovedPlayer);
    check(MovedPlayerLocation.IsSet());

    if (!CachedGridComponent->IsValidGridLocation(MovedPlayerLocation.GetValue()))
    {
        OnPlayerDeath.Broadcast(MovedPlayer);
    }
    else
    {
        const EPlayer StandingPlayer = Utility::GetOppositePlayer(MovedPlayer);
        const TOptional<FIntVector2> StandingPlayerLocation = CachedGridComponent->GetPlayerLocation(StandingPlayer);

        if (MovedPlayerLocation == StandingPlayerLocation)
        {
            OnPlayerDeath.Broadcast(StandingPlayer);
        }
    }
}
