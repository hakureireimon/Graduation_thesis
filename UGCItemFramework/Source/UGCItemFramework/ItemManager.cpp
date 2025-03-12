#include "ItemManager.h"
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
	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("SetSeed"),
		TEXT("Reroll Your Destiny"),
		FConsoleCommandWithArgsDelegate::CreateLambda([this](const TArray<FString>& Args)
		{
			if (Args.Num() > 0)
			{
				Seed = FCString::Atoi(*Args[0]) & 0x7FFFFFFF;
			}
		}),
		ECVF_Default
		);
	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("Seed"),
		TEXT("Get Seed"),
		FConsoleCommandWithArgsDelegate::CreateLambda([this](const TArray<FString>& Args)
		{
			UE_LOG(LogTemp, Warning, TEXT("Seed: %d"), Seed);
		}),
		ECVF_Default
		);
	return;
}

AItemManager::~AItemManager()
{
	IConsoleManager::Get().UnregisterConsoleObject(TEXT("Seed"));
	IConsoleManager::Get().UnregisterConsoleObject(TEXT("SetSeed"));
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

void AItemManager::AddItemToPool(FString Id, FString Name, FString Description, FString Icon, TArray<FString> Effect, FString Condition)
{
	FUGCProperty Property;
	Property.Id = Id;
	Property.Name = Name;
	Property.Description = Description;
	Property.Icon = Icon;
	Property.Effects = Effect;
	Property.Condition = Condition;
	ItemPool.Add(Property);
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

AItem* AItemManager::GenerateNormalItem(FVector Location)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return nullptr;
	}
	AItem* Item = World->SpawnActor<AItem>(AItem::StaticClass(), Location, FRotator::ZeroRotator);
	Item->SetUGCProperty(GenerateNormalProperty());
	AEffectManager* EffectManager = Cast<AEffectManager>(UGameplayStatics::GetActorOfClass(World, AEffectManager::StaticClass()));
	EffectManager->SendSignal("ItemGenerated");
	return Item;
}

void AItemManager::OnGenerateErrorItemTriggered(FVector Location)
{
	AItem* NewItem = GenerateErrorItem(Location);
}

void AItemManager::OnGenerateNormalItemTriggered(FVector Location)
{
	GenerateNormalItem(Location);
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
	Effect = GetRandomEffect((RandomNumber & 0xf) + 1);
	FUGCProperty RandomProperty = FUGCProperty();
	RandomProperty.Id = "-" + LexToString(++ErrorItemCount);
	RandomProperty.Name = "Error Item";
	RandomProperty.Description = "Error Item";
	RandomProperty.Icon = "Error Item";
	RandomProperty.Condition = Condition;
	RandomProperty.Effects.Add(Effect);
	float Probability = 0.25f;
	while (FMath::FRand() < Probability)
	{
		Effect = GetRandomEffect((GenerateWithSeed() & 0xf) + 1);
		RandomProperty.Effects.Add(Effect);
		Probability *= 0.5f;
	}
	return RandomProperty;
}

FUGCProperty AItemManager::GenerateNormalProperty()
{
	return ItemPool[GenerateWithSeed() % ItemPool.Num()];
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