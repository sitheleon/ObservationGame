#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ComputerSittingCharacter.generated.h"

UCLASS()
class OBSERVATION2_API AComputerSittingCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AComputerSittingCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly)
	FRotator HeadRotation;

private:
	class APlayerController* PlayerController;

	void UpdateHeadRotation();

	UPROPERTY()
	class USkeletalMeshComponent* SkeletalMeshComponent;
};