#pragma once

#include "Item.h"
#include "ItemManager.generated.h"
UCLASS()
class AItemManager : public AActor
{
	GENERATED_BODY()
public:
	AItemManager();
	UPROPERTY(BlueprintReadOnly, Category = "ItemManager")
	TArray<AItem*> ItemPool;
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	void AddItemToPool(AItem* Item);
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	AItem* GenerateErrorItem();
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	void OnGenerateItemTriggered();
};
