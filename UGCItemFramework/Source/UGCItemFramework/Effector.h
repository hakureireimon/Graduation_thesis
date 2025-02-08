#pragma once

#include "Effector.generated.h"

UCLASS()
class AEffector : public AActor
{
	GENERATED_BODY()
public:
	UFUNCTION(blueprintCallable, Category = "Effector")
	void ApplyEffect(FString Effect);
};
