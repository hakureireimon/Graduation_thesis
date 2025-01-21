#include "ItemManager.h"
#include "Kismet/GameplayStatics.h"
#include "UGCItemFrameworkCharacter.h"

AItemManager* AItemManager::Instance = nullptr;

AItemManager::AItemManager()
{
	PrimaryActorTick.bCanEverTick = false;
	return;
}

void AItemManager::AddItemToPool(AItem* Item)
{
	return;
}

AItem* AItemManager::GenerateErrorItem(FVector Location)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return nullptr;
	}
	
	AItem* Item = World->SpawnActor<AItem>(AItem::StaticClass(), Location, FRotator::ZeroRotator);
	return Item;
}

void AItemManager::OnGenerateItemTriggered(FVector Location)
{
	AItem* NewItem = GenerateErrorItem(Location);
	if (NewItem)
	{
		AddItemToPool(NewItem);
	}
}

AItemManager* AItemManager::GetInstance(UWorld* World)
{
	if (!Instance)
	{
		Instance = World->SpawnActor<AItemManager>();
	}
	return Instance;
}