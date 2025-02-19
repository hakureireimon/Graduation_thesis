#pragma once

#include "Item.h"
#include "UnLuaInterface.h"
#include "EffectManager.generated.h"

UCLASS()
class AEffectManager : public AActor, public IUnLuaInterface
{
	GENERATED_BODY()
public:
	virtual FString GetModuleName_Implementation() const override;
	
	UFUNCTION(BlueprintCallable, Category = "EffectManager")
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "EffectManager")
	void RegisterItem(AItem* Item);
	UFUNCTION(BlueprintCallable, Category = "EffectManager")
	void SendSignal(FString Signal);
	UFUNCTION(BlueprintCallable, Category = "EffectManager")
	void ApplyEffect(FString Effect);
};
