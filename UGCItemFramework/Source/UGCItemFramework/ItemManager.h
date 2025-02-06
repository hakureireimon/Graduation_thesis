#pragma once

#include "Item.h"
#include "ItemManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemManagerCreated);

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
	static FOnItemManagerCreated OnItemManagerCreated;
	
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
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	void AddEffect(FString Effect);
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	void AddCondition(FString Condition);

	uint32 GenerateWithSeed();
	uint32 GenerateRandomNumber();
	FString GetRandomCondition(uint32 RandomNumber);
	FString GetRandomEffect(uint32 RandomNumber);
	
	static AItemManager* GetInstance(UWorld* World);
};
