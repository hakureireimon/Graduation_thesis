#pragma once

#include "Item.h"
#include "ItemManager.generated.h"
UCLASS()
class AItemManager : public AActor
{
	GENERATED_BODY()
private:
	static AItemManager* Instance;
	uint32 Seed;
	int32 ErrorItemCount;
	int32 RandActionCount;
public:
	AItemManager();
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
	UPROPERTY(BlueprintReadOnly, Category = "ItemManager")
	TArray<AItem*> ItemPool;
	UPROPERTY(BlueprintReadOnly, Category = "ItemManager")
	TArray<FString> Conditions;
	UPROPERTY(BlueprintReadOnly, Category = "ItemManager")
	TArray<FString> Effects;
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	void AddItemToPool(AItem* Item);
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	AItem* GenerateErrorItem(FVector Location);
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	void OnGenerateItemTriggered(FVector Location);
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	FUGCProperty GenerateRandomProperty();

	uint32 GenerateWithSeed();
	FString GetRandomCondition(uint32 RandomNumber);
	FString GetRandomEffect(uint32 RandomNumber);
	
	static AItemManager* GetInstance(UWorld* World);
};
