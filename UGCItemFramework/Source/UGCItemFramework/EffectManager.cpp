#include "EffectManager.h"

#include "EffectLibrary.h"
#include "Effector.h"

void AEffectManager::BeginPlay()
{
	Super::BeginPlay();
}

void AEffectManager::RegisterItem(AItem* Item)
{
	if (Item)
	{
		for(auto& Effect : Item->GetUGCProperty().Effects)
		{
			ConditionAndEffectMap.Add(Item->GetUGCProperty().Condition, Effect);	
		}
	}
}

void AEffectManager::SendSignal(FString Signal)
{
	for(TMultiMap<FString, FString>::TIterator It(ConditionAndEffectMap); It; ++It)
	{
		if (It.Key() == Signal)
		{
			this->ApplyEffect(It.Value());
		}
	}
}

void AEffectManager::ApplyEffect(FString Effect)
{
	AEffector* Effector = GetWorld()->SpawnActor<AEffector>(AEffector::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
	Effector->ApplyEffect(Effect);
}