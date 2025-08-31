// Copyright Epic Games, Inc. All Rights Reserved.

#include "c_testGameMode.h"
#include "c_testCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"


Ac_testGameMode::Ac_testGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
}

void Ac_testGameMode::BeginPlay(){
	Super::BeginPlay();

	if (GetWorld()) {
		FVector SpawnLocation(1000.0f, 1000.0f, 50.0f);
		FRotator SpawnRotation(0.0f, 0.0f, 0.0f);

		AAMyActor* newActor = GetWorld()->SpawnActor<AAMyActor>(
			AAMyActor::StaticClass(),
			SpawnLocation,
			SpawnRotation
		);

		if (newActor) {
			UE_LOG(LogTemp, Warning, TEXT("Success spawn"));
			newActor->StartMoveSequence();
		}
	}
}


