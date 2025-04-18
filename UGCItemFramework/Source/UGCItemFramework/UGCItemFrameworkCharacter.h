// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Item.h"
#include "Blueprint/UserWidget.h"
#include "UGCItemFrameworkCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGenerateItemDelegate, FVector, Location);

UCLASS(config=Game)
class AUGCItemFrameworkCharacter : public ACharacter, public IUnLuaInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AUGCItemFrameworkCharacter();

	virtual FString GetModuleName_Implementation() const override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FGenerateItemDelegate OnGenerateErrorItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FGenerateItemDelegate OnGenerateNormalItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> ItemInfoDisplayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> Cross;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UUserWidget* ItemInfoWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UUserWidget* CrossInstance;

	UFUNCTION(BlueprintCallable, Category = "Item")
	void GenerateErrorItemAtLocation(FVector Location);

	UFUNCTION(BlueprintCallable, Category = "Item")
	void GenerateNormalItemAtLocation(FVector Location);

	UFUNCTION(BlueprintCallable, Category = "Item")
	void OnFPressed();

	UFUNCTION(BlueprintCallable, Category = "Item")
	void OnQPressed();

	UFUNCTION(BlueprintCallable, Category = "Item")
	bool GetLookAtLocation(FVector& LookAtLocation);

	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	TArray<AItem*> Inventory;

	UFUNCTION(BlueprintCallable, Category = "Item")
	void AddItemToInventory(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Item")
	void ShowOrHideBag();

	UFUNCTION(BlueprintCallable, Category = "Item")
	void OnItemManagerCreated();
protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

