#include "EffectManager.h"

#include "EffectLibrary.h"
#include "Effector.h"

TMultiMap<FString, FString> ConditionAndEffectMap;

FString AEffectManager::GetModuleName_Implementation() const
{
	return TEXT("EffectManager_C");
}

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
	TSet<FString> Keys;
	if (ConditionAndEffectMap.GetKeys(Keys) > 0)
	{
		for(auto& Key : Keys)
		{
			if (Key == Signal)
			{
				TArray<FString> Effects;
				ConditionAndEffectMap.MultiFind(Key, Effects);
				for(auto& Effect : Effects)
				{
					this->ApplyEffect(Effect);
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SendSignal: ConditionAndEffectMap is empty"));
	}
}

void AEffectManager::ApplyEffect(FString Effect)
{
	AEffector* Effector = GetWorld()->SpawnActor<AEffector>(AEffector::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
	Effector->ApplyEffect(Effect);
}