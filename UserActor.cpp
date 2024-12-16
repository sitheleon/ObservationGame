// Fill out your copyright notice in the Description page of Project Settings.


#include "UserActor.h"

// Sets default values
AUserActor::AUserActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);

	
}

// Called when the game starts or when spawned
void AUserActor::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
}

// Called every frame
void AUserActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateHeadRotation();
}

void AUserActor::UpdateHeadRotation()
{
	if (!PlayerController) return;

	// 마우스 위치 및 화면 크기 가져오기
	FVector2D MousePosition;
	PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);

	int32 ScreenWidth, ScreenHeight;
	PlayerController->GetViewportSize(ScreenWidth, ScreenHeight);
	FVector2D ScreenSize(ScreenWidth, ScreenHeight);

	// 마우스 위치를 기준으로 캐릭터가 머리를 부드럽게 움직이게 함
	float NormalizedX = FMath::Clamp(MousePosition.X / ScreenSize.X - 0.5f, -0.3f, 0.3f); // -0.3 ~ 0.3 범위로 제한
	float NormalizedY = FMath::Clamp(MousePosition.Y / ScreenSize.Y - 0.5f, -0.3f, 0.3f); // -0.3 ~ 0.3 범위로 제한

	// HeadRotation 설정
	HeadRotation = FRotator(NormalizedY * -30.f, NormalizedX * 30.f, 0.f);
}

