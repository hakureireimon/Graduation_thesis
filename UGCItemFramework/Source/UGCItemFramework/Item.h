#pragma once

#include "Item.generated.h"
UCLASS()
class AItem : public AActor
{
	GENERATED_BODY()
public:
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
};
