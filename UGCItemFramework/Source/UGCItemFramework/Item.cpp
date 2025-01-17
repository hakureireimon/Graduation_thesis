#include "Item.h"
#include "Components/SphereComponent.h"

DECLARE_MULTICAST_DELEGATE(ItemEventDelegate)

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
}

void AItem::OnItemPickedUp()
{
	EventOnItemPickedUp.Broadcast();
}

void AItem::OnItemDropped()
{
	EventOnItemDropped.Broadcast();
}

void AItem::OnItemTriggered()
{
	EventOnItemTriggered.Broadcast();
}