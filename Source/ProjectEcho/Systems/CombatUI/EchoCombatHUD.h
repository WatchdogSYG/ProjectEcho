// This is a prototype of a game, currently for non-commercial purposes. This may change at any time without notice in the future and may be licenced under different conditions. You may not copy or redistribute content for commercial purposes. TODO: Assign licence (CC or otherwise).

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EchoCombatHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTECHO_API UEchoCombatHUD : public UUserWidget
{
	GENERATED_BODY()
	
    public:	

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources")
        void SetHealth(const float& value);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources")
        void SetMaxHealth(const float& value);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources")
        void SetMana(const float& value);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources")
        void SetMaxMana(const float& value);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources")
        void SetStun(const float& value);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources")
        void SetMaxStun(const float& value);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources")
        void SetName(const FString& name);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resources")
        void SetText(const FString& text);


};
