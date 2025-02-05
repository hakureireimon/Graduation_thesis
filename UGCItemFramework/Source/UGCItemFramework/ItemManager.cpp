#include "ItemManager.h"
#include "Kismet/GameplayStatics.h"
#include "UGCItemFrameworkCharacter.h"

AItemManager* AItemManager::Instance = nullptr;

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

void AItemManager::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (Instance)
	{
		Instance->Destroy();
		Instance = nullptr;
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
	uint32 RandNumber = 0;
	while((RandNumber & 0x80000000) != 0x80000000)
	{
		RandNumber = RandNumber * 2 + Seed * RandActionCount;
	}
	return RandNumber;
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
		Charge = LexToString(RandomNumber & 0x7 + 1);
	}
	else
	{
		Type = "Passive";
		Condition = GetRandomCondition(RandomNumber & 0x7 + 1);
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
	return "Null";
}

FString AItemManager::GetRandomEffect(uint32 RandNumber)
{
	RandActionCount++;
	return "Null";
}

AItemManager* AItemManager::GetInstance(UWorld* World)
{
	if (!Instance)
	{
		Instance = World->SpawnActor<AItemManager>();
	}
	return Instance;
}