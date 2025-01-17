#pragma once

#include "Item.h"
#include "ItemManager.generated.h"
UCLASS()
class AItemManager : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "ItemManager")
	TArray<AItem*> ItemPool;
};
