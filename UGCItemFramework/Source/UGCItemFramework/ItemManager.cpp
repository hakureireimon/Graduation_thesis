﻿#include "ItemManager.h"
#include "Kismet/GameplayStatics.h"
#include "UGCItemFrameworkCharacter.h"
#include "UGCItemFrameworkCharacter.h"
#include "EffectManager.h"

AItemManager::AItemManager()
{
	PrimaryActorTick.bCanEverTick = false;
	ErrorItemCount = 0;
	Seed = 0;
	RandActionCount = 0;
	return;
}

FString AItemManager::GetModuleName_Implementation() const
{
	return TEXT("ItemManager_C");
}

void AItemManager::BeginPlay()
{
	Super::BeginPlay();

	Seed = FMath::Rand();
	while(Seed == 0)
	{
		Seed = FMath::Rand();
	}
}

void AItemManager::AddItemToPool(AItem* Item)
{
	ItemPool.Add(Item);
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
	Item->SetUGCProperty(GenerateRandomProperty());
	AEffectManager* EffectManager = Cast<AEffectManager>(UGameplayStatics::GetActorOfClass(World, AEffectManager::StaticClass()));
	EffectManager->SendSignal("ItemGenerated");
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

uint32 AItemManager::GenerateWithSeed()
{
	RandActionCount++;
	return GenerateRandomNumber();
}

uint32 AItemManager::GenerateRandomNumber()
{
	// Xorshift 算法
	uint32 x = Seed;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	Seed = x;
	return x;
}

FUGCProperty AItemManager::GenerateRandomProperty()
{
	FString Condition = "";
	FString Effect = "";

	uint32 RandomNumber = GenerateWithSeed();
	Condition = GetRandomCondition((RandomNumber & 0x7) + 1);
	Effect = GetRandomEffect(RandomNumber & 0xf + 1);
	FUGCProperty RandomProperty = FUGCProperty();
	RandomProperty.Id = "-" + LexToString(++ErrorItemCount);
	RandomProperty.Name = "Error Item";
	RandomProperty.Description = "Error Item";
	RandomProperty.Icon = "Error Item";
	RandomProperty.Condition = Condition;
	RandomProperty.Effects.Add(Effect);
	return RandomProperty;
}

FString AItemManager::GetRandomCondition(uint32 RandNumber)
{
	RandActionCount++;
	uint32 Index = (RandNumber ^ 2 + RandActionCount * RandNumber) % Conditions.Num();
	return Conditions[Index];
}

FString AItemManager::GetRandomEffect(uint32 RandNumber)
{
	RandActionCount++;
	uint32 Index = (RandNumber ^ 2 + RandActionCount * RandNumber) % Effects.Num();
	return Effects[Index];
}

void AItemManager::AddEffect(FString Effect)
{
	Effects.Add(Effect);
}

void AItemManager::AddCondition(FString Condition)
{
	Conditions.Add(Condition);
}