#include "AnomalyManager.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "TimerManager.h"
#include "CameraPlayerController.h"

AAnomalyManager::AAnomalyManager()
{
    PrimaryActorTick.bCanEverTick = true;
    UE_LOG(LogTemp, Warning, TEXT("AAnomalyManager 생성자 호출"));
}

void AAnomalyManager::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("AAnomalyManager BeginPlay 시작"));

    CurrentElapsedTime = 0.0f;

    if (UWorld* World = GetWorld())
    {
        for (TActorIterator<AAnomalyBase> It(World); It; ++It)
        {
            Anomalies.Add(*It);
        }
        UE_LOG(LogTemp, Warning, TEXT("총 %d개의 AAnomalyBase 액터를 찾았습니다."), Anomalies.Num());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("World를 가져오는데 실패했습니다."));
    }

    StartAnomalyTimer();
    UE_LOG(LogTemp, Warning, TEXT("AAnomalyManager BeginPlay 종료"));
}

void AAnomalyManager::StartAnomalyTimer()
{
    // 기본 시간 텀을 45~60초로 설정
    float RandomTime = FMath::RandRange(45.0f, 60.0f);

    ACameraPlayerController* PlayerController = Cast<ACameraPlayerController>(GetWorld()->GetFirstPlayerController());

    if (PlayerController)
    {
        CurrentElapsedTime = PlayerController->GetElapsedTime();
    }

    // 경과 시간이 180초에 도달했을 때
    if (FMath::IsNearlyEqual(CurrentElapsedTime, 180.0f, 0.1f))
    {   
        RandomTime = FMath::RandRange(40.0f, 55.0f);  // 40~55초로 범위 확장
        UE_LOG(LogTemp, Warning, TEXT("ElapsedTime이 180초에 도달하여 더 자주 발생: %.2f초 후"), RandomTime);
    }
    // 경과 시간이 300초에 도달했을 때
    else if (FMath::IsNearlyEqual(CurrentElapsedTime, 300.0f, 0.1f))
    {   
        RandomTime = FMath::RandRange(38.0f, 50.0f);  // 38~50초로 범위 확장
        UE_LOG(LogTemp, Warning, TEXT("ElapsedTime이 300초에 도달하여 더 자주 발생: %.2f초 후"), RandomTime);
    }

    GetWorldTimerManager().SetTimer(AnomalyTimerHandle, this, &AAnomalyManager::TriggerRandomAnomaly, RandomTime, false);
    UE_LOG(LogTemp, Warning, TEXT("다음 이상 현상 타이머 설정: %.2f초 후"), RandomTime);
}


void AAnomalyManager::TriggerRandomAnomaly()
{
    UE_LOG(LogTemp, Warning, TEXT("TriggerRandomAnomaly 함수 호출"));
    
    if (Anomalies.Num() > 0)
    {
        int32 RandomIndex;
        AAnomalyBase* SelectedAnomaly;

        do
        {
            RandomIndex = FMath::RandRange(0, Anomalies.Num() - 1);
            SelectedAnomaly = Anomalies[RandomIndex];
        } while (RandomIndex == LastAnomalyIndex && Anomalies.Num() > 1);

        if (SelectedAnomaly)
        {
            UE_LOG(LogTemp, Warning, TEXT("이상 현상 발생: %s"), *SelectedAnomaly->GetName());
            SelectedAnomaly->TriggerAnomaly();

            // 이상 현상을 큐에 추가
            AddAnomalyToQueue(SelectedAnomaly->GetAnomalyLocation(), SelectedAnomaly->GetAnomalyType());

            CurrentAnomaly.Place = SelectedAnomaly->GetAnomalyLocation();
            CurrentAnomaly.Type = SelectedAnomaly->GetAnomalyType();
            CurrentAnomaly.IsActive = true;

            bIsAnomalyTriggered = true;
            LastAnomalyIndex = RandomIndex;
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("선택된 이상 현상이 유효하지 않습니다."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("활성화할 이상 현상이 없습니다."));
    }
    
    StartAnomalyTimer();
}

void AAnomalyManager::AddAnomalyToQueue(FString Place, FString Type)
{
    FAnomalyManagerInfo NewAnomaly;
    NewAnomaly.Place = Place;
    NewAnomaly.Type = Type;
    NewAnomaly.IsActive = true;
    AnomalyQueue.Enqueue(NewAnomaly);

    AnomalyCount++;
    UE_LOG(LogTemp, Warning, TEXT("이상 현상 큐에 추가: 위치=%s, 종류=%s"), *Place, *Type);
}

bool AAnomalyManager::GetNextAnomalyFromQueue(FAnomalyManagerInfo& OutAnomaly)
{
    if (AnomalyQueue.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("이상 현상 큐가 비어 있습니다."));
        return false;
    }

    AnomalyQueue.Dequeue(OutAnomaly);
    UE_LOG(LogTemp, Warning, TEXT("큐에서 이상 현상 추출: 위치=%s, 종류=%s"), *OutAnomaly.Place, *OutAnomaly.Type);
    return true;
}

bool AAnomalyManager::IsCurrentAnomaly(FString Place, FString Type)
{
    // 큐가 비어 있는지 확인하여 비어 있으면 바로 반환
    if (AnomalyQueue.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("이상 현상 큐가 비어 있습니다."));
        return false;
    }

    // 임시 큐를 생성해 데이터를 이동하면서 검색
    TQueue<FAnomalyManagerInfo> TempQueue;
    FAnomalyManagerInfo Anomaly;

    while (AnomalyQueue.Dequeue(Anomaly)) // 큐에서 하나씩 꺼냅니다.
    {
        // 조건에 맞는 이상 현상을 찾으면 즉시 true를 반환
        if (Anomaly.Place == Place && Anomaly.Type == Type && Anomaly.IsActive)
        {
            // 기존 큐에 데이터를 복원
            while (TempQueue.Dequeue(Anomaly))
            {
                AnomalyQueue.Enqueue(Anomaly);
            }
            return true;
        }

        // 임시 큐에 다시 저장하여 기존 큐를 유지합니다.
        TempQueue.Enqueue(Anomaly);
    }

    // 기존 큐에 데이터를 복원
    while (TempQueue.Dequeue(Anomaly))
    {
        AnomalyQueue.Enqueue(Anomaly);
    }

    return false;
}

FString AAnomalyManager::GetCurrentAnomalyInfo() const
{
    if (CurrentAnomaly.IsActive)
    {
        return FString::Printf(TEXT("Location: %s, Type: %s"), *CurrentAnomaly.Place, *CurrentAnomaly.Type);
    }
    return TEXT("No active anomaly");
}





void AAnomalyManager::ResetCurrentAnomaly()
{
    CurrentAnomaly = FAnomalyManagerInfo();
    bIsAnomalyTriggered = false;
}

AAnomalyBase* AAnomalyManager::GetCurrentAnomalyObject()
{
    if (CurrentAnomaly.IsActive)
    {
        AAnomalyBase** FoundAnomaly = Anomalies.FindByPredicate([this](AAnomalyBase* Anomaly) {
            return Anomaly->GetAnomalyLocation() == CurrentAnomaly.Place &&
                   Anomaly->GetAnomalyType() == CurrentAnomaly.Type;
        });

        return FoundAnomaly ? *FoundAnomaly : nullptr;
    }
    return nullptr;
}