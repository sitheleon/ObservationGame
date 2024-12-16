// Fill out your copyright notice in the Description page of Project Settings.


#include "SmokeAnomaly.h"
#include "Particles/ParticleSystemComponent.h"



ASmokeAnomaly::ASmokeAnomaly()
{
    PrimaryActorTick.bCanEverTick = true;

    ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
    ParticleSystem->SetupAttachment(RootComponent);
}

void ASmokeAnomaly::BeginPlay()
{
    Super::BeginPlay();

    ParticleSystem->SetVisibility(false);
    ParticleSystem->bAutoActivate = false;

    bIsSmokeActivated = false;

}

void ASmokeAnomaly::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ASmokeAnomaly::TriggerAnomaly()
{
    ParticleSystem->SetVisibility(true);
    ParticleSystem->Activate();

    bIsSmokeActivated = true;

    UnfixedAnamolyCount++;
}

void ASmokeAnomaly::FixAnomaly()
{
    ParticleSystem->SetVisibility(false);
    ParticleSystem->Deactivate();

    bIsSmokeActivated = false;
    
        UnfixedAnamolyCount--;
}   
