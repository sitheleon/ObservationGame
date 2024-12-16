// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnomalyBase.h"
#include "ScissorAnomaly.generated.h"

/**
 * 
 */
UCLASS()
class OBSERVATION2_API AScissorAnomaly : public AAnomalyBase
{
	GENERATED_BODY()

public:
	AScissorAnomaly();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	virtual void TriggerAnomaly() override;

	virtual void FixAnomaly() override;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* MeshComponent;


	UPROPERTY(BlueprintReadOnly, Category = "Anomaly")
	bool bIsScissorAnomalyTriggered;

	
	void ScissorLocationToDeath();

	void SetScissorDeathTrue();

	UPROPERTY(BlueprintReadOnly, Category = "Anomaly")
	bool bIsScissorDeath;

private:
	FVector InitialLocation;

	FRotator InitialRotation;

	FTimerHandle TimerHandle;

};
