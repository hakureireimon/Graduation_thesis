#include "Item.h"

#include "UGCItemFrameworkCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EffectManager.h"
#include "Kismet/GameplayStatics.h"

DECLARE_MULTICAST_DELEGATE_OneParam(ItemEventDelegate, FString)

ItemEventDelegate EventOnItemPickedUp;
ItemEventDelegate EventOnItemDropped;
ItemEventDelegate EventOnItemTriggered;

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SphereComponent->InitSphereRadius(100.0f);
	RootComponent = SphereComponent;
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComponent->SetCollisionProfileName(TEXT("Trigger"));
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnItemPickedUp);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
	}
}

FString AItem::GetModuleName_Implementation() const
{
	return TEXT("Item_C");
}

void AItem::SetUGCProperty(FUGCProperty Property)
{
	UGCProperty = Property;
}

FUGCProperty AItem::GetUGCProperty()
{
	return UGCProperty;
}

void AItem::OnItemPickedUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AUGCItemFrameworkCharacter* Character = Cast<AUGCItemFrameworkCharacter>(OtherActor);
	if (Character)
	{
		Character->AddItemToInventory(this);

		AEffectManager* EffectManager = Cast<AEffectManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AEffectManager::StaticClass()));
		if (EffectManager)
		{
			EffectManager->RegisterItem(this);
		}
		Destroy();
		
		EventOnItemPickedUp.Broadcast(GetUGCProperty().Id);
	}
}

void AItem::OnItemDropped()
{
	EventOnItemDropped.Broadcast(GetUGCProperty().Id);
}

void AItem::OnItemTriggered()
{
	EventOnItemTriggered.Broadcast(GetUGCProperty().Id);
}