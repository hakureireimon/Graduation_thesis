#include "EffectManager.h"

#include "EffectLibrary.h"
#include "Effector.h"

void AEffectManager::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->SpawnActor<AEffectManager>(AEffectManager::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
}

void AEffectManager::RegisterItem(AItem* Item)
{
	if (Item)
	{
		ConditionAndEffectMap.Add(Item->GetUGCProperty().Condition, Item->GetUGCProperty().Effect);
	}
}

void AEffectManager::SendSignal(FString Signal)
{
	for(auto& Pair : ConditionAndEffectMap)
	{
		if (Pair.Key == Signal)
		{
			this->ApplyEffect(Pair.Value);
		}
	}
}

void AEffectManager::ApplyEffect(FString Effect)
{
	AEffector* Effector = GetWorld()->SpawnActor<AEffector>(AEffector::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
	Effector->ApplyEffect(Effect);
}