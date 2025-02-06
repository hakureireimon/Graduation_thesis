// Copyright Epic Games, Inc. All Rights Reserved.

#include "UGCItemFrameworkCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Item.h"
#include "DrawDebugHelpers.h"
#include "ItemManager.h"
#include "Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////////////////////////
// AUGCItemFrameworkCharacter

AUGCItemFrameworkCharacter::AUGCItemFrameworkCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void AUGCItemFrameworkCharacter::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<AItemManager>(AItemManager::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	AItemManager* ItemManager = Cast<AItemManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AItemManager::StaticClass()));
	if (ItemManager)
	{
		ItemManager->OnItemManagerCreated.AddDynamic(this, &AUGCItemFrameworkCharacter::OnItemManagerCreated);
	}
	ItemManager->OnItemManagerCreated.Broadcast();
}

void AUGCItemFrameworkCharacter::OnItemManagerCreated()
{
	AItemManager* ItemManager = Cast<AItemManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AItemManager::StaticClass()));
	if (ItemManager)
	{
		OnGenerateItem.AddDynamic(ItemManager, &AItemManager::OnGenerateItemTriggered);
	}
	UE_LOG(LogTemp, Warning, TEXT("ItemManager has been created and bound to Character."));
}


//////////////////////////////////////////////////////////////////////////
// Input

void AUGCItemFrameworkCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AUGCItemFrameworkCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUGCItemFrameworkCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AUGCItemFrameworkCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AUGCItemFrameworkCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AUGCItemFrameworkCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AUGCItemFrameworkCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AUGCItemFrameworkCharacter::OnResetVR);

	PlayerInputComponent->BindAction("FKey", IE_Pressed, this, &AUGCItemFrameworkCharacter::OnFPressed);

	PlayerInputComponent->BindAction("Bag", IE_Pressed, this, &AUGCItemFrameworkCharacter::ShowOrHideBag);
}


void AUGCItemFrameworkCharacter::OnResetVR()
{
	// If UGCItemFramework is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in UGCItemFramework.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AUGCItemFrameworkCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AUGCItemFrameworkCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AUGCItemFrameworkCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AUGCItemFrameworkCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AUGCItemFrameworkCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AUGCItemFrameworkCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AUGCItemFrameworkCharacter::OnFPressed()
{
	FVector LookAtLocation;
	if (GetLookAtLocation(LookAtLocation))
	{
		GenerateItemAtLocation(LookAtLocation);
	}
}

void AUGCItemFrameworkCharacter::GenerateItemAtLocation(FVector Location)
{
	OnGenerateItem.Broadcast(Location);
}

bool AUGCItemFrameworkCharacter::GetLookAtLocation(FVector& OutLookAtLocation)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

		FVector LookDirection = CameraRotation.Vector();
		FVector TraceStart = CameraLocation;
		FVector TraceEnd = TraceStart + (LookDirection * 10000.0f);

		FHitResult HitResult;
		FCollisionQueryParams TraceParams(FName(TEXT("")), false, this);
		if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams))
		{
			DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 1.0f, 0, 1.0f);
			OutLookAtLocation = HitResult.Location;
			return true;
		}
	}
	return false;
}

void AUGCItemFrameworkCharacter::AddItemToInventory(AItem* Item)
{
	Inventory.Add(Item);
}

void AUGCItemFrameworkCharacter::ShowOrHideBag()
{
	UE_LOG(LogTemp, Log, TEXT("Inventory:"));
	for (AItem* Item : Inventory)
	{
		if (Item)
		{
			const FUGCProperty& Property = Item->UGCProperty;
			UE_LOG(LogTemp, Log, TEXT("Item ID: %s"), *Property.Id);
			UE_LOG(LogTemp, Log, TEXT("Name: %s"), *Property.Name);
			UE_LOG(LogTemp, Log, TEXT("Type: %s"), *Property.Type);
			UE_LOG(LogTemp, Log, TEXT("Description: %s"), *Property.Description);
			UE_LOG(LogTemp, Log, TEXT("Icon: %s"), *Property.Icon);
			UE_LOG(LogTemp, Log, TEXT("Effect: %s"), *Property.Effect);
			UE_LOG(LogTemp, Log, TEXT("Charge: %s"), *Property.Charge);
			UE_LOG(LogTemp, Log, TEXT("Condition: %s"), *Property.Condition);
		}
	}
}
