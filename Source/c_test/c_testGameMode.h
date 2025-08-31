// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AMyActor.h"
#include "c_testGameMode.generated.h"

UCLASS(minimalapi)
class Ac_testGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	Ac_testGameMode();
protected:
	virtual void BeginPlay()override;
};



