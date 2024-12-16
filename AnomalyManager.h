#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AnomalyBase.h"
#include "Containers/Queue.h"  // TQueue 사용을 위한 헤더 추가
#include "AnomalyManager.generated.h"

// 구조체 정의: 이상 현상 정보 저장
USTRUCT(BlueprintType)
struct FAnomalyManagerInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Place;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool IsActive;

    FAnomalyManagerInfo() : Place(""), Type(""), IsActive(false) {}
};

// 이상 현상 매니저 클래스
UCLASS()
class OBSERVATION2_API AAnomalyManager : public AActor
{
    GENERATED_BODY()
    
public:
    AAnomalyManager();

    UPROPERTY(BlueprintReadOnly)
    bool bIsAnomalyTriggered;

    UFUNCTION(BlueprintCallable, Category = "Anomaly")
    bool IsCurrentAnomaly(FString Place, FString Type);

    UFUNCTION(BlueprintCallable, Category = "Anomaly")
    FString GetCurrentAnomalyInfo() const;

    UFUNCTION(BlueprintCallable, Category = "Anomaly")
    void ResetCurrentAnomaly();

    UFUNCTION(BlueprintCallable, Category = "Anomaly")
    AAnomalyBase* GetCurrentAnomalyObject();

    UFUNCTION(BlueprintCallable, Category = "Anomaly")
    void AddAnomalyToQueue(FString Place, FString Type);  // 큐에 추가하는 함수

    UFUNCTION(BlueprintCallable, Category = "Anomaly")
    bool GetNextAnomalyFromQueue(FAnomalyManagerInfo& OutAnomaly);  // 큐에서 다음 이상 현상 가져오는 함수

    float CurrentElapsedTime;

    UPROPERTY(BlueprintReadOnly)
    int32 AnomalyCount;

protected:
    virtual void BeginPlay() override;

private:
    FTimerHandle AnomalyTimerHandle;

    UPROPERTY(EditAnywhere, Category="Anomalies")
    TArray<AAnomalyBase*> Anomalies;

    UPROPERTY()
    FAnomalyManagerInfo CurrentAnomaly;

    TQueue<FAnomalyManagerInfo> AnomalyQueue;  // 큐 선언

    void TriggerRandomAnomaly();
    void StartAnomalyTimer();

    int32 LastAnomalyIndex = -1;
};
