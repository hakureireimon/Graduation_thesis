#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UnLuaInterface.h"
#include "EffectLibrary.generated.h"

UCLASS()
class UEffectLibrary : public UBlueprintFunctionLibrary, public IUnLuaInterface
{
	GENERATED_BODY()
public:
	virtual FString GetModuleName_Implementation() const override;
	
	UFUNCTION(BlueprintCallable, Category = "EffectLibrary")
	static void Test();
};
