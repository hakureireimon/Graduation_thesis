#pragma once

#include "Item.h"
#include "EffectManager.generated.h"

UCLASS()
class AEffectManager : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EffectManager")
	TMap<FString, FString> ConditionAndEffectMap;
	UFUNCTION(BlueprintCallable, Category = "EffectManager")
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "EffectManager")
	void RegisterItem(AItem* Item);
	UFUNCTION(BlueprintCallable, Category = "EffectManager")
	void SendSignal(FString Signal);
	UFUNCTION(BlueprintCallable, Category = "EffectManager")
	void ApplyEffect(FString Effect);
};
