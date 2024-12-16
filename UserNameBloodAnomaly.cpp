// Fill out your copyright notice in the Description page of Project Settings.


#include "UserNameBloodAnomaly.h"
#include "Components/TextRenderComponent.h"


AUserNameBloodAnomaly::AUserNameBloodAnomaly()
{
    PrimaryActorTick.bCanEverTick = true;

    TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextComponent"));
    TextComponent->SetupAttachment(RootComponent);

    PlaneComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneComponent"));
    PlaneComponent->SetupAttachment(TextComponent);
}

void AUserNameBloodAnomaly::TriggerAnomaly()
{
    TextComponent->SetVisibility(true);
    PlaneComponent->SetVisibility(true);

    UnfixedAnamolyCount++;
}

void AUserNameBloodAnomaly::FixAnomaly()
{
    TextComponent->SetVisibility(false);
    PlaneComponent->SetVisibility(false);
    UnfixedAnamolyCount--;
}



void AUserNameBloodAnomaly::BeginPlay()
{
    Super::BeginPlay();

    TextComponent->SetVisibility(false);
    PlaneComponent->SetVisibility(false);
}

void AUserNameBloodAnomaly::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
/*
        if (TextComponent->IsVisible())
    {
        UE_LOG(LogTemp, Warning, TEXT("TextComponent is visible"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("TextComponent is hidden"));
    }

*/

}

void AUserNameBloodAnomaly::UpdateText(FString UserName)
{
    TextComponent->SetText(FText::FromString(UserName));
}
