#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Item.generated.h"

UCLASS()
class AItem : public AActor
{
	GENERATED_BODY()
public:
	AItem();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TMap<FString, FString> Effects;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Charge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Condition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	USphereComponent* SphereComponent;
	
	UFUNCTION(BlueprintCallable, Category = "Item")
	void OnItemPickedUp();
	UFUNCTION(BlueprintCallable, Category = "Item")
	void OnItemDropped();
	UFUNCTION(BlueprintCallable, Category = "Item")
	void OnItemTriggered();
};
