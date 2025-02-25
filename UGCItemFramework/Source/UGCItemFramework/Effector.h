#pragma once
#include "UnLuaInterface.h"

#include "Effector.generated.h"

UCLASS()
class AEffector : public AActor, public IUnLuaInterface
{
	GENERATED_BODY()
public:
	virtual FString GetModuleName_Implementation() const override;
	
	UFUNCTION(blueprintCallable, Category = "Effector")
	void ApplyEffect(FString Effect);
};
