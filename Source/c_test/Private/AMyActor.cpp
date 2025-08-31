// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"
#include <iostream>
#include "AMyActor.h"
#include "Engine/StaticMeshActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAMyActor::AAMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}



// Called when the game starts or when spawned
void AAMyActor::BeginPlay()
{
	Super::BeginPlay();
    
    
}

// Called every frame
void AAMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 이동 시퀀스를 시작시키는 함수 (예: BeginPlay나 버튼 호출에서 사용)
void AAMyActor::StartMoveSequence()
{
    PathArray.Empty(); // 이전 경로 초기화   
    CurPos=FVector2D(0, 0); // 시작 위치 초기화
    PathArray.Add(CurPos); // 시작 위치 저장
    CurrentStep = 0; // 스텝 인덱스 초기화
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("mycube"), FoundActors);

    if (FoundActors.Num() > 0)
    {
        TargetActor = FoundActors[0];
        UE_LOG(LogTemp, Warning, TEXT("Cube found by tag!"));
    }
    
    
    GetWorld()->GetTimerManager().SetTimer(TimerHandle_Move, this, &AAMyActor::MoveOneStep, 1.5f, true);
}

// 타이머에 의해 주기적으로 호출되는 함수 — 한 스텝씩 이동하고 목표 액터를 갱신
void AAMyActor::MoveOneStep()
{   
    float ZOffset = 50.0f;
    if (CurrentStep >= MoveStepsTotal) { // 더 이동할 스텝이 없으면 타이머 정지
        GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Move);
        UE_LOG(LogTemp, Warning, TEXT("event count: %d total distance: %.2f"), event_cnt, distanceTotal);
        return;
    }
    if (!TargetActor) {
        UE_LOG(LogTemp, Warning, TEXT("test : cube null"));
        return;
    }
    ActorLocation = TargetActor->GetActorLocation();
    
    // 실제 위치 계산: X, Y 각각 0 또는 1을 더함w
    CurPos.X = step(); // X 증가
    CurPos.Y = step(); // Y 증가

    // 이전 위치와 거리 계산
    float len = FVector2D::Distance(CurPos,PathArray[CurrentStep])*GridSize;

    // 확률 이벤트 처리
    if (TriggerEventWithProbability(50)) {
        ZOffset = 200;
        event_cnt++;
    }
    distanceTotal += len;

    // 월드 좌표로 변환 후 액터 위치 갱신
    if (TargetActor) {
        FVector NewLoc = FVector(ActorLocation.X+CurPos.X * GridSize,ActorLocation.Y+CurPos.Y * GridSize, ZOffset);      
        TargetActor->SetActorLocation(NewLoc);
    }

    // 로그 출력
    UE_LOG(LogTemp, Warning, TEXT("Step %d -> x:%d y:%d dist:%.2f"), CurrentStep + 1, (int32)CurPos.X, (int32)CurPos.Y, len);

    // 현재 위치 저장 및 인덱스 증가
    PathArray.Add(CurPos);
    ++CurrentStep;
}

int32 AAMyActor::step() {
    int32 RandomValue = FMath::RandRange(0, 1);//0혹은 1생성;
    return RandomValue;
}



bool AAMyActor::TriggerEventWithProbability(float Probability)
{
    int32 RandomValue = FMath::RandRange(1, 100); // 1 ~ 100의 난수 생성
    if (RandomValue <= Probability)
    {
        UE_LOG(LogTemp, Error, TEXT("Event Triggered!"));
        return true;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Event Not Triggered"));
        return false;
    }
}


