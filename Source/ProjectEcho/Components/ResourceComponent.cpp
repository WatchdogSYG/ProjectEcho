// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceComponent.h"
#include "Engine/Engine.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"

// Sets default values for this component's properties
UResourceComponent::UResourceComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	TestDefaultConstructorID = FString::Printf(TEXT("[%d]"), this->GetUniqueID());
}


UResourceComponent* UResourceComponent::InitialiseResources(float health, float maxHealth, float mana, float maxMana, float stun, float maxStun, ANameplateActor* nameplateActor = nullptr, UEchoCombatHUD* hud = nullptr) {
	Health = health;
	MaxHealth = maxHealth;
	Mana = mana;
	MaxMana = maxMana;
	Stun = stun;
	MaxStun = maxStun;
	NameplateActor = nameplateActor;
	HUD = hud;

	if (NameplateActor != nullptr) { NameplateActor->AttachToActor(this->GetOwner(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, false)); }
	//TODO default nameplateActor and HUD

	UpdateMaxHealthDisplay(MaxHealth);
	UpdateHealthDisplay(Health);
	UpdateMaxManaDisplay(MaxMana);
	UpdateManaDisplay(Mana);
	UpdateMaxStunDisplay(MaxStun);
	UpdateStunDisplay(Stun);
	return this;
}


// Called when the game starts
void UResourceComponent::BeginPlay() {
	Super::BeginPlay();
	/*
if (GEngine) {
	GEngine->AddOnScreenDebugMessage(
		INDEX_NONE, 10.0f, FColor::White, FString::Printf(
			TEXT(
				"ResourceComponent().UID = %s     Set Health = %s     Set MaxHealth = %s"
			),
			*FString::Printf(TEXT("[%d]"), this->GetUniqueID()),
			*FString::SanitizeFloat(Health),
			*FString::SanitizeFloat(MaxHealth)
		),true
	);
}
*/
}

// Called every frame
void UResourceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if (GEngine) { GEngine->AddOnScreenDebugMessage(INDEX_NONE, 10.f, FColor::Green, FString::Printf(TEXT("TimeUntilStunRegen = %s"),*FString::SanitizeFloat(TimeUntilStunRegen)),true); }

	// 1. Check if we are waiting to regen stun
	// 2. Check if Stun needs to be regend
	RegenStun = true;

	if (TimeUntilStunRegen > 0.f) {
		TimeUntilStunRegen -= DeltaTime;
		RegenStun = false;
	}

	if (Stun == 0) { RegenStun = false; }

	if (RegenStun) {
		HealStun(NaturalStunRegenRate * DeltaTime);
		UpdateStunDisplay(Stun);
	}


	RegenMana = true;

	if (TimeUntilManaRegen > 0.f) {
		TimeUntilManaRegen -= DeltaTime;
		RegenMana = false;
	}

	//if (GEngine) {GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString::Printf(TEXT("TimeUntilManaRegen = %s"), *FString::SanitizeFloat(TimeUntilManaRegen)));}

	if (Mana == MaxMana) { RegenMana = false; }

	if (RegenMana) {
		HealMana(NaturalManaRegenRate * DeltaTime);
		UpdateManaDisplay(Mana);
	}
}

//todo check for min/max health, optimise and change fstring instantiators to be in the message function

void UResourceComponent::DamageEventCallout(EDamageCategory category, float x1, float x2) {

	FString s;

	if (x2 > x1) {
		s = FString("Healed ");
	} else {
		s = FString("Damaged ");
	}

	s.Append(FString::SanitizeFloat(FMath::Abs(x2 - x1)));

	switch (category) {
	case EDamageCategory::HEALTH:
		s.Append(" HP");
		break;
	case EDamageCategory::MANA:
		s.Append(" MP");
		break;
	case EDamageCategory::STUN:
		s.Append(" SP");
		break;
	default:
		break;
	}

	s.Append(
		FString::Printf(
			TEXT(" | %s -> %s"),
			*FString::SanitizeFloat(x1, 0),
			*FString::SanitizeFloat(x2, 0)
		)
	);

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(
			INDEX_NONE,
			5.f,
			FColor::Blue,
			s,
			true);
	}

	switch (category) {
	case EDamageCategory::HEALTH:
		UpdateHealthDisplay(Health);
		break;
	case EDamageCategory::MANA:
		UpdateManaDisplay(Mana);
		break;
	case EDamageCategory::STUN:
		UpdateStunDisplay(Stun);
		break;
	default:
		break;
	}
}

float UResourceComponent::DamageHealth(float magnitude) {

	//Get State before
	float h1 = Health;

	//increment health
	Health -= FMath::Abs(magnitude);

	if (Health <= 0.f) { Death(); }

	Health = FMath::Clamp(Health, 0.f, MaxHealth);

	DamageEventCallout(EDamageCategory::HEALTH, h1, Health);

	return h1 - Health; //return the actual damage dealt
}
float UResourceComponent::HealHealth(float magnitude) {
	//Get State before
	float h1 = Health;

	//increment health
	Health += FMath::Abs(magnitude);

	if (Health <= 0.f) { Death(); }//keep this here in case there is a heal after a damage in a tick

	//if (Health >= MaxHealth) { if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString("MAX HEALTH!")); } }

	Health = FMath::Clamp(Health, 0.f, MaxHealth);

	DamageEventCallout(EDamageCategory::HEALTH, h1, Health);

	return Health - h1; //return the actual damage healed
}
float UResourceComponent::DamageMana(float magnitude) {
	// Set time for Natural Stun Regen
	TimeUntilManaRegen = NaturalManaRegenDelay;

	// Get State before
	float m1 = Mana;

	// increment health
	Mana -= FMath::Abs(magnitude);

	if (Mana <= 0.f) {
		//Death();
	}

	Mana = FMath::Clamp(Mana, 0.f, MaxMana);

	DamageEventCallout(EDamageCategory::MANA, m1, Mana);

	return m1 - Mana; // return the actual damage dealt
}
float UResourceComponent::HealMana(float magnitude) {
	// Get State before
	float m1 = Mana;

	// increment Mana
	Mana += FMath::Abs(magnitude);

	if (Mana <= 0.f) {
		//Death();
	} // keep this here in case there is a heal after a damage in a tick

	if (Mana >= MaxMana) {
		if (GEngine) {
			//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString("MAX HEALTH!"));
		}
	}

	Mana = FMath::Clamp(Mana, 0.f, MaxMana);

	DamageEventCallout(EDamageCategory::MANA, m1, Mana);

	return Mana - m1; // return the actual damage healed
}
float UResourceComponent::HealStun(float magnitude) {
	// Get State before
	float s1 = Stun;

	// increment health
	Stun -= FMath::Abs(magnitude);

	if (Stun <= 0.f) {
		//Death();
	}

	Stun = FMath::Clamp(Stun, 0.f, MaxStun);

	if (!RegenStun) { DamageEventCallout(EDamageCategory::STUN, s1, Stun); }

	return s1 - Stun; // return the actual damage dealt
}
float UResourceComponent::DamageStun(float magnitude) {
	//Set time for Natural Stun Regen
	TimeUntilStunRegen = NaturalStunRegenDelay;
	// Get State before
	float s1 = Stun;

	// increment health
	Stun += FMath::Abs(magnitude);

	if (Stun <= 0.f) {
		//  Death();
	} // keep this here in case there is a heal after a damage in a tick

	if (Stun >= MaxStun) {
		if (GEngine) {
			//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString("MAX Stun!"));
		}
	}

	Stun = FMath::Clamp(Stun, 0.f, MaxStun);

	DamageEventCallout(EDamageCategory::STUN, s1, Stun);

	return Stun - s1; // return the actual damage healed
}

void UResourceComponent::Death() {
	//probably need a death flag to stop this being run multiple times per tick
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString::Printf(TEXT("YOU DIED")), true); }
}

UEchoCombatHUD* UResourceComponent::LinkHUD(UEchoCombatHUD* hud) {
	HUD = hud;
	return hud;
}

void UResourceComponent::UpdateHealthDisplay(float health) {
	if (NameplateActor != nullptr) {
		NameplateActor->SetHealth(health);
		//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, FString::Printf(TEXT("tried to set the health display of [%s] to %s"), *GetOwner()->GetName(), *FString::SanitizeFloat(health)), true); }
	}

	if (HUD != nullptr) {
		HUD->SetHealth(health);
	}

}
void UResourceComponent::UpdateMaxHealthDisplay(float maxHealth) {
	if (NameplateActor != nullptr) {
		NameplateActor->SetMaxHealth(maxHealth);
		//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, FString::Printf(TEXT("Tried to set the maxHealth display of [%s] to %s"), *GetOwner()->GetName(), *FString::SanitizeFloat(maxHealth)), true); }
	}

	if (HUD != nullptr) {
		HUD->SetMaxHealth(maxHealth);
	}
}
void UResourceComponent::UpdateManaDisplay(float mana) {
	if (NameplateActor != nullptr) {
		NameplateActor->SetMana(mana);
		//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, FString::Printf(TEXT("Tried to set the mana display of [%s] to %s"), *GetOwner()->GetName(), *FString::SanitizeFloat(mana)), true); }
	}

	if (HUD != nullptr) {
		HUD->SetMana(mana);
	}
}
void UResourceComponent::UpdateMaxManaDisplay(float maxMana) {
	if (NameplateActor != nullptr) {
		NameplateActor->SetMaxMana(maxMana);
		//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, FString::Printf(TEXT("Tried to set the maxMana display of [%s] to %s"), *GetOwner()->GetName(), *FString::SanitizeFloat(maxMana)), true); }
	}

	if (HUD != nullptr) {
		HUD->SetMaxMana(maxMana);
	}
}
void UResourceComponent::UpdateStunDisplay(float stun) {
	if (NameplateActor != nullptr) {
		NameplateActor->SetStun(stun);
		//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, FString::Printf(TEXT("Tried to set the stun display of [%s] to %s"), *GetOwner()->GetName(), *FString::SanitizeFloat(stun)), true); }
	}

	if (HUD != nullptr) {
		HUD->SetStun(stun);
	}
}
void UResourceComponent::UpdateMaxStunDisplay(float maxStun) {
	if (NameplateActor != nullptr) {
		NameplateActor->SetMaxStun(maxStun);
		//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::White, FString::Printf(TEXT("Tried to set the maxStun display of [%s] to %s"), *GetOwner()->GetName(), *FString::SanitizeFloat(maxStun)), true); }
	}
	if (HUD != nullptr) {
		HUD->SetMaxStun(maxStun);
	}
}
