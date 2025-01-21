#include "Item.h"
#include "Components/StaticMeshComponent.h"
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

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
	}
}

void AItem::SetUGCProperty(FUGCProperty Property)
{
	UGCProperty = Property;
}

FUGCProperty AItem::GetUGCProperty()
{
	return UGCProperty;
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