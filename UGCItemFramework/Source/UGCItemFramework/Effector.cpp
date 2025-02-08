#include "Effector.h"

#include "EffectLibrary.h"

void AEffector::ApplyEffect(FString Effect)
{
	UClass* Class = UEffectLibrary::StaticClass();
	UFunction* Function = Class->FindFunctionByName(FName(Effect));
	if (Function)
	{
		this->ProcessEvent(Function, nullptr);
	}
	this->Destroy();
}
