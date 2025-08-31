// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AMyActor.generated.h"

UCLASS()
class C_TEST_API AAMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AAMyActor();
	void StartMoveSequence();
	void MoveOneStep();
	
	TArray<FVector2D> PathArray;
	FVector2D CurPos;
	int32 CurrentStep = 0;
	FVector ActorLocation;
	FTimerHandle TimerHandle_Move;
	int32 MoveStepsTotal = 10;
	int32 step();

	UPROPERTY(EditAnywhere, Category = "Movement");
	AActor* TargetActor;

	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float GridSize = 100.0f;

	// 액터를 놓을 Z 높이 값
	

	int32 event_cnt = 0;
	float distanceTotal = 0.f;
	bool TriggerEventWithProbability(float Probability);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
