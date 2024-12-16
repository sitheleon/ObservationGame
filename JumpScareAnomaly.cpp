// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpScareAnomaly.h"


AJumpScareAnomaly::AJumpScareAnomaly()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AJumpScareAnomaly::TriggerAnomaly()
{
    bIsJumpScareAnomalyTriggered = true;
    UnfixedAnamolyCount--;
}

void AJumpScareAnomaly::FixAnomaly()
{
    bIsFixed = true;
    UnfixedAnamolyCount++;
}

void AJumpScareAnomaly::BeginPlay()
{
    Super::BeginPlay();

    bIsJumpScareAnomalyTriggered = false;
    
    bIsFixed = false;
    
}

void AJumpScareAnomaly::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


}
