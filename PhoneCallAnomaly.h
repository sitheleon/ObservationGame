// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnomalyBase.h"
#include "PhoneCallAnomaly.generated.h"

/**
 * 
 */
UCLASS()
class OBSERVATION2_API APhoneCallAnomaly : public AAnomalyBase
{
	GENERATED_BODY()

public:
	APhoneCallAnomaly();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	virtual void TriggerAnomaly() override;

	virtual void FixAnomaly() override;

	UPROPERTY(BlueprintReadOnly)
	bool IsPhoneCallAnomlayTriggered;

	UPROPERTY(BlueprintReadOnly)
	bool bIsPhoneCallAnomalyFixed;
};
