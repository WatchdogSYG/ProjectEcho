// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"
#include "../Actors/NameplateActor.h"
#include "../Systems/CombatUI/EchoCombatHUD.h"

#include "ResourceComponent.generated.h"

UENUM(BlueprintType)
enum class EDamageCategory : uint8 {
	HEALTH UMETA(DisplayName = "Health Damage"),
	MANA UMETA(DisplayName = "Mana Damage"),
	STUN UMETA(DisplayName = "Stun Damage")
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTECHO_API UResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UResourceComponent();

	UFUNCTION(BlueprintCallable, Category = "Constructor")
        UResourceComponent* InitialiseResources(float health, float maxHealth, float mana, float maxMana, float stun, float maxStun, ANameplateActor* nameplateActor, UEchoCombatHUD* hud);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	//https ://www.oreilly.com/library/view/unreal-engine-4/9781785885549/ch02s10.html#:~:text=C%2B%2B%20enum%20are%20very%20useful,Blueprint%20that%20you%20are%20editing.

	FString TestDefaultConstructorID;

	void DamageEventCallout(EDamageCategory category, float x1, float x2);
	
	//HEALTH
	float Health = 0.0f;
	float MaxHealth = 200.0f;
	
	UFUNCTION(BlueprintCallable, Category = "Resources")
		float DamageHealth(float magnitude);

	UFUNCTION(BlueprintCallable, Category = "Resources")
		float HealHealth(float magnitude);

	//MANA
	float Mana = 0.0f;
	float MaxMana = 200.0f;

	UFUNCTION(BlueprintCallable, Category = "Resources")
		float DamageMana(float magnitude);

	UFUNCTION(BlueprintCallable, Category = "Resources")
		float HealMana(float magnitude);

	bool RegenMana = false;
	float TimeUntilManaRegen = 0.f;
    float NaturalManaRegenRate = 40.f;
    float NaturalManaRegenDelay = 1.0f;
    

	//STUN
	float Stun = 0.0f;
	float MaxStun = 300.0f;

	UFUNCTION(BlueprintCallable, Category = "Resources")
		float DamageStun(float magnitude);

	UFUNCTION(BlueprintCallable, Category = "Resources")
		float HealStun(float magnitude);

	bool RegenStun = false;
	float TimeUntilStunRegen= 0.f;
	float NaturalStunRegenRate = 40.f;
    float NaturalStunRegenDelay = 1.0f;
	

	void Death();

	//DISPLAY

	ANameplateActor* NameplateActor;

	UEchoCombatHUD* HUD;

	UFUNCTION(BlueprintCallable, Category = "Initialisation")
        UEchoCombatHUD* LinkHUD(UEchoCombatHUD* hud);

	UFUNCTION(BlueprintCallable, Category = "Resources")
		void UpdateHealthDisplay(float health);

	UFUNCTION(BlueprintCallable, Category = "Resources")
		void UpdateMaxHealthDisplay(float maxHealth);

	UFUNCTION(BlueprintCallable, Category = "Resources")
        void UpdateManaDisplay(float mana);

    UFUNCTION(BlueprintCallable, Category = "Resources")
        void UpdateMaxManaDisplay(float maxMana);

	UFUNCTION(BlueprintCallable, Category = "Resources")
        void UpdateStunDisplay(float stun);

    UFUNCTION(BlueprintCallable, Category = "Resources")
        void UpdateMaxStunDisplay(float maxStun);
};
