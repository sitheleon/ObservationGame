// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnomalyBase.h"
#include "StretchAnomaly.generated.h"

/**
 * 
 */
UCLASS()
class OBSERVATION2_API AStretchAnomaly : public AAnomalyBase
{
	GENERATED_BODY()
public:
	AStretchAnomaly();

	virtual void TriggerAnomaly() override;	

	
	virtual void FixAnomaly() override;

	void ChangeMeshZScale(float NewScale);

	void ChangeMeshToOriginalSize();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FVector InitialSize;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* MeshComponent;
};
