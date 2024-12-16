#include "ComputerSittingCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PlayerController.h" 
#include "Components/SkeletalMeshComponent.h" 

// Sets default values
AComputerSittingCharacter::AComputerSittingCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AComputerSittingCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
}

// Called every frame
void AComputerSittingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateHeadRotation();
}

// Called to bind functionality to input
void AComputerSittingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AComputerSittingCharacter::UpdateHeadRotation()
{
	if (!PlayerController) return;

	// 마우스 위치 및 화면 크기 가져오기
	FVector2D MousePosition;
	PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);

	int32 ScreenWidth, ScreenHeight;
	PlayerController->GetViewportSize(ScreenWidth, ScreenHeight);
	FVector2D ScreenSize(ScreenWidth, ScreenHeight);

	// 마우스 위치를 기준으로 캐릭터가 머리를 움직이게 함
	float NormalizedX = MousePosition.X / ScreenSize.X - 0.5f;
	float NormalizedY = MousePosition.Y / ScreenSize.Y - 0.5f;

	// HeadRotation 설정
	HeadRotation = FRotator(NormalizedY * -30.f, NormalizedX * 30.f, 0.f);

}


