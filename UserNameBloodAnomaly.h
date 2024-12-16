// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnomalyBase.h"
#include "UserNameBloodAnomaly.generated.h"

/**
 * 
 */
UCLASS()
class OBSERVATION2_API AUserNameBloodAnomaly : public AAnomalyBase
{
	GENERATED_BODY()
public:

	AUserNameBloodAnomaly();

	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	virtual void TriggerAnomaly() override;

	virtual void FixAnomaly() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;



protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Text")
	class UTextRenderComponent* TextComponent;

	UFUNCTION(BlueprintCallable, Category = "Text")
	void UpdateText(FString UserName);

	UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* PlaneComponent;
	
};
