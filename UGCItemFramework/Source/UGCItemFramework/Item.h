#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "UGCProperty.h"
#include "Item.generated.h"

UCLASS()
class AItem : public AActor
{
	GENERATED_BODY()
public:
	AItem();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Item")
	FUGCProperty UGCProperty;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	UStaticMeshComponent* MeshComponent;

	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetUGCProperty(FUGCProperty Property);
	UFUNCTION(BlueprintCallable, Category = "Item")
	FUGCProperty GetUGCProperty();
	
	UFUNCTION(BlueprintCallable, Category = "Item")
	void OnItemPickedUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable, Category = "Item")
	void OnItemDropped();
	UFUNCTION(BlueprintCallable, Category = "Item")
	void OnItemTriggered();
};
