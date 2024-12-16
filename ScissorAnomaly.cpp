// Fill out your copyright notice in the Description page of Project Settings.
#include "ScissorAnomaly.h"
#include "TimerManager.h"




AScissorAnomaly::AScissorAnomaly()
{
    PrimaryActorTick.bCanEverTick = true;


    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;
}

void AScissorAnomaly::BeginPlay()
{
    Super::BeginPlay();

    InitialLocation = GetActorLocation();

    InitialRotation = GetActorRotation();

    bIsScissorAnomalyTriggered = false;

    bIsScissorDeath = false;
}

void AScissorAnomaly::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}

void AScissorAnomaly::TriggerAnomaly()
{
    FVector NewLocation(-6583.0f, 13966.0f, 135.0f);

    SetActorLocation(NewLocation);

    FRotator NewRotation(0.0f, 0.0f, 180.0f);

    SetActorRotation(NewRotation);

    bIsScissorAnomalyTriggered = true;

    //(X=-6583.000000,Y=13966.000000,Z=135.000000) -> Location left to the player character.

    UnfixedAnamolyCount++;
}

void AScissorAnomaly::FixAnomaly()
{
    SetActorLocation(InitialLocation);

    SetActorRotation(InitialRotation);  

    bIsScissorAnomalyTriggered = false;

    UnfixedAnamolyCount--;
}

void AScissorAnomaly::ScissorLocationToDeath()
{
    FVector KillLocation(-6583.0f, 13994.0f, 135.0f);
    // (X=-6583.000000,Y=13994.000000,Z=135.000000)
    SetActorLocation(KillLocation);
}

void AScissorAnomaly::SetScissorDeathTrue()
{
    bIsScissorDeath = true;
}
