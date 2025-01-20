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

AItem* AItemManager::GenerateErrorItem()
{
	AItem* Item = NewObject<AItem>();
	return Item;
}

void AItemManager::OnGenerateItemTriggered(FVector Location)
{
	AItem* NewItem = GenerateErrorItem();
	AddItemToPool(NewItem);
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	World->SpawnActor<AItem>(NewItem->StaticClass(), Location, FRotator::ZeroRotator);
	return;
}

AItemManager* AItemManager::GetInstance(UWorld* World)
{
	if (!Instance)
	{
		Instance = World->SpawnActor<AItemManager>();
	}
	return Instance;
}