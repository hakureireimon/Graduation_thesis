#include "ItemManager.h"

AItemManager::AItemManager()
{
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

void AItemManager::OnGenerateItemTriggered()
{
	return;
}
