// This is a prototype of a game, currently for non-commercial purposes. This may change at any time without notice in the future and may be licenced under different conditions. You may not copy or redistribute content for commercial purposes. TODO: Assign licence (CC or otherwise).


#include "EchoCombatHUD.h"

void UEchoCombatHUD::SetHealth_Implementation(const float& value){ if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString("UEchoCombatHUD::SetHealth(const float& value) called from base class!")); } }

void UEchoCombatHUD::SetMaxHealth_Implementation(const float& value) { if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString("UEchoCombatHUD::SetMaxHealth(const float& value) called from base class!")); } }

void UEchoCombatHUD::SetMana_Implementation(const float& value) { if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString("UEchoCombatHUD::SetMana(const float& value) called from base class!")); } }

void UEchoCombatHUD::SetMaxMana_Implementation(const float& value){ if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString("UEchoCombatHUD::SetMaxMana(const float& value) called from base class!")); } }

void UEchoCombatHUD::SetStun_Implementation(const float& value){ if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString("UEchoCombatHUD::SetStun(const float& value) called from base class!")); } }

void UEchoCombatHUD::SetMaxStun_Implementation(const float& value){ if (GEngine) {GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString("UEchoCombatHUD::SetMaxStun(const float& value) called from base class!")); } }

void UEchoCombatHUD::SetName_Implementation(const FString& name){ if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString("UEchoCombatHUD::SetName(const FString& name) called from base class!")); } }

void UEchoCombatHUD::SetText_Implementation(const FString& text){ if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString("UEchoCombatHUD::SetText(const FString& text) called from base class!")); } }
