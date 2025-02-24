#include "Effector.h"
#include "EffectManager.h"
#include "EffectLibrary.h"
#include "Kismet/GameplayStatics.h"

void AEffector::ApplyEffect(FString Effect)
{
	UClass* Class = UEffectLibrary::StaticClass();
	UFunction* Function = Class->FindFunctionByName(FName(Effect));
	if (Function)
	{
		this->ProcessEvent(Function, nullptr);
	}
	AEffectManager* EffectManager = Cast<AEffectManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AEffectManager::StaticClass()));
	EffectManager->SendSignal("EffectApplied");
	this->Destroy();
}
