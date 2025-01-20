#pragma once

#include "Item.h"
#include "ItemManager.generated.h"
UCLASS()
class AItemManager : public AActor
{
	GENERATED_BODY()
private:
	static AItemManager* Instance;
public:
	AItemManager();
	UPROPERTY(BlueprintReadOnly, Category = "ItemManager")
	TArray<AItem*> ItemPool;
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	void AddItemToPool(AItem* Item);
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	AItem* GenerateErrorItem();
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	void OnGenerateItemTriggered(FVector Location);

	static AItemManager* GetInstance(UWorld* World);
};
