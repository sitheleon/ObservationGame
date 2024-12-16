// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnomalyBase.h"
#include "JumpScareAnomaly.generated.h"

/**
 * 
 */
UCLASS()
class OBSERVATION2_API AJumpScareAnomaly : public AAnomalyBase
{
	GENERATED_BODY()

public:
	
	AJumpScareAnomaly();

	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	virtual void TriggerAnomaly() override;

	
	virtual void FixAnomaly() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "Anomaly")
	bool bIsJumpScareAnomalyTriggered;

	UPROPERTY(BlueprintReadWrite, Category = "Anomaly")
	bool bIsFixed;

};
