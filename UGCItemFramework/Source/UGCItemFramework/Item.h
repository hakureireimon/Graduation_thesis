#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "UGCProperty.h"
#include "UnLuaInterface.h"
#include "Item.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemEventDelegate, FString, Id);

UCLASS()
class AItem : public AActor, public IUnLuaInterface
{
	GENERATED_BODY()
public:
	AItem();

	virtual FString GetModuleName_Implementation() const override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Item")
	FUGCProperty UGCProperty;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FItemEventDelegate EventOnItemPickedUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FItemEventDelegate EventOnItemDropped;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FItemEventDelegate EventOnItemTriggered;

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
