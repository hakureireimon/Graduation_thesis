#include "EffectLibrary.h"

FString UEffectLibrary::GetModuleName_Implementation() const
{
	return TEXT("EffectLibrary_C");
}

void UEffectLibrary::Test()
{
	UE_LOG(LogTemp, Warning, TEXT("Test"));
}
