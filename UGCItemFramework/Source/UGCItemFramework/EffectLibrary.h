﻿#pragma once

#include "EffectLibrary.generated.h"

UCLASS()
class UEffectLibrary : public UBlueprintFunctionLibrary 
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "EffectLibrary")
	static void Test();
};
