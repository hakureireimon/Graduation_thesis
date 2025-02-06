// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UGCItemFrameworkGameMode.generated.h"

UCLASS(minimalapi)
class AUGCItemFrameworkGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUGCItemFrameworkGameMode();
	virtual void BeginPlay() override;
};



