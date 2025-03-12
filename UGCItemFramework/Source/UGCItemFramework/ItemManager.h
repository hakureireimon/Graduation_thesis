#pragma once

#include "Item.h"
#include "ItemManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemManagerCreated);

UCLASS()
class AItemManager : public AActor, public IUnLuaInterface
{
	GENERATED_BODY()
private:
	uint32 Seed;
	int32 ErrorItemCount;
	int32 RandActionCount;
public:
	UPROPERTY(BlueprintAssignable, Category = "ItemManager")
	FOnItemManagerCreated OnItemManagerCreated;
	
	AItemManager();
	~AItemManager();

	virtual FString GetModuleName_Implementation() const override;
	
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, Category = "ItemManager")
	TArray<FUGCProperty> ItemPool;
	UPROPERTY(BlueprintReadOnly, Category = "ItemManager")
	TArray<FString> Conditions;
	UPROPERTY(BlueprintReadOnly, Category = "ItemManager")
	TArray<FString> Effects;
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	void AddItemToPool(FString Id, FString Name, FString Description, FString Icon, TArray<FString> Effect, FString Condition);
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	AItem* GenerateErrorItem(FVector Location);
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	AItem* GenerateNormalItem(FVector Location);
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	void OnGenerateErrorItemTriggered(FVector Location);
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	void OnGenerateNormalItemTriggered(FVector Location);
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	FUGCProperty GenerateRandomProperty();
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	FUGCProperty GenerateNormalProperty();
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	void AddEffect(FString Effect);
	UFUNCTION(BlueprintCallable, Category = "ItemManager")
	void AddCondition(FString Condition);

	uint32 GenerateWithSeed();
	uint32 GenerateRandomNumber();
	FString GetRandomCondition(uint32 RandomNumber);
	FString GetRandomEffect(uint32 RandomNumber);
};
