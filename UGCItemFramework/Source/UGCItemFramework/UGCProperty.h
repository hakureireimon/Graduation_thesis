#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UGCProperty.generated.h"

USTRUCT(BlueprintType)
struct FUGCProperty 
{
	GENERATED_USTRUCT_BODY()
	
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
	FString Effect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Charge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Condition;
};
