// Fill out your copyright notice in the Description page of Project Settings.


#include "HeadTurnAnomaly.h"


AHeadTurnAnomaly::AHeadTurnAnomaly()
{
    PrimaryActorTick.bCanEverTick = true;
    AnomalyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AnomalyMesh"));
    RootComponent = AnomalyMesh;        
}

void AHeadTurnAnomaly::BeginPlay()
{
    Super::BeginPlay();

    AnomalyMesh->SetVisibility(false);
}

void AHeadTurnAnomaly::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FRotator NewRotation = FRotator(PitchValue, YawValue, RollValue);

    FQuat QuatRotation = FQuat(NewRotation);

    AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

void AHeadTurnAnomaly::TriggerAnomaly()
{
    

    AnomalyMesh->SetVisibility(true);
    UnfixedAnamolyCount++;
    UE_LOG(LogTemp, Warning, TEXT("Anomaly mesh visibility set to: %s"), bNewVisibility ? TEXT("true") : TEXT("false"));

}

void AHeadTurnAnomaly::FixAnomaly()
{
    

    AnomalyMesh->SetVisibility(false);
    UnfixedAnamolyCount--;
    UE_LOG(LogTemp, Warning, TEXT("Anomaly mesh visibility set to: %s"), bNewVisibility ? TEXT("true") : TEXT("false"));

}
