// Fill out your copyright notice in the Description page of Project Settings.


#include "PhoneCallAnomaly.h"


APhoneCallAnomaly::APhoneCallAnomaly()
{
    IsPhoneCallAnomlayTriggered = false;

    bIsPhoneCallAnomalyFixed = false;

    PrimaryActorTick.bCanEverTick = true;
}

void APhoneCallAnomaly::BeginPlay()
{
    Super::BeginPlay();
}

void APhoneCallAnomaly::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void APhoneCallAnomaly::TriggerAnomaly()
{
    IsPhoneCallAnomlayTriggered = true;

    bIsPhoneCallAnomalyFixed = false;

    UnfixedAnamolyCount++;
}

void APhoneCallAnomaly::FixAnomaly()
{
    IsPhoneCallAnomlayTriggered = false;

    bIsPhoneCallAnomalyFixed = true;

    UnfixedAnamolyCount--;
}

// Implemented mostly on blueprint