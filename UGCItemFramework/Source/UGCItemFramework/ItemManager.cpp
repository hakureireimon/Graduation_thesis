#include "ItemManager.h"
#include "Kismet/GameplayStatics.h"
#include "UGCItemFrameworkCharacter.h"
#include "UGCItemFrameworkCharacter.h"

AItemManager::AItemManager()
{
	PrimaryActorTick.bCanEverTick = false;
	ErrorItemCount = 0;
	Seed = 0;
	RandActionCount = 0;
	return;
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
	// undone Generate Random Property OneByOne and return
	FString Type = "";
	FString Charge = "";
	FString Condition = "";
	FString Effect = "";

	uint32 RandomNumber = GenerateWithSeed();
	if ((RandomNumber & 0x1) == 1)
	{
		Type = "Active";
		Charge = LexToString((RandomNumber & 0x7) + 1);
	}
	else
	{
		Type = "Passive";
		Condition = GetRandomCondition((RandomNumber & 0x7) + 1);
	}
	Effect = GetRandomEffect(RandomNumber & 0xf + 1);
	FUGCProperty RandomProperty = FUGCProperty();
	RandomProperty.Id = "-" + LexToString(++ErrorItemCount);
	RandomProperty.Name = "Error Item";
	RandomProperty.Type = Type;
	RandomProperty.Description = "Error Item";
	RandomProperty.Icon = "Error Item";
	RandomProperty.Charge = Charge;
	RandomProperty.Condition = Condition;
	RandomProperty.Effect = Effect;
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