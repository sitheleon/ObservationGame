// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnomalyBase.h"
#include "SmokeAnomaly.generated.h"

/**
 * 
 */
UCLASS()
class OBSERVATION2_API ASmokeAnomaly : public AAnomalyBase
{
	GENERATED_BODY()
public:
	ASmokeAnomaly();

protected:
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	virtual void TriggerAnomaly() override;

	virtual void FixAnomaly() override;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* ParticleSystem;

	UPROPERTY(BlueprintReadWrite)
	bool bIsSmokeActivated;

};
