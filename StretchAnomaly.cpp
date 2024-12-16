// Fill out your copyright notice in the Description page of Project Settings.

#include "StretchAnomaly.h"

#include "Engine/StaticMesh.h"


AStretchAnomaly::AStretchAnomaly()
{
    PrimaryActorTick.bCanEverTick = true;


    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;
}

void AStretchAnomaly::BeginPlay()
{
    Super::BeginPlay();

    InitialSize = GetActorScale3D();

}



void AStretchAnomaly::TriggerAnomaly()
{
    ChangeMeshZScale(2.0f);

    UnfixedAnamolyCount++;
}

void AStretchAnomaly::FixAnomaly()
{
    ChangeMeshToOriginalSize();

    UnfixedAnamolyCount--;
}

void AStretchAnomaly::ChangeMeshZScale(float NewScale) // NewScale is Z scale   
{
    if (MeshComponent)
    {
        FVector CurrentScale = InitialSize;

        CurrentScale.Z = NewScale; // make currentscale.Z to an input value

        MeshComponent->SetWorldScale3D(CurrentScale);
    }
}

void AStretchAnomaly::ChangeMeshToOriginalSize()
{
    if (MeshComponent)
    {
        MeshComponent->SetWorldScale3D(InitialSize);
    }
}

