// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceComponent.h"
#include "Engine/Engine.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"

// Sets default values for this component's properties
UResourceComponent::UResourceComponent(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	TestDefaultConstructorID = FString::Printf(TEXT("[%d]"), this->GetUniqueID());
}


UResourceComponent* UResourceComponent::InitialiseResources(float health, float maxHealth, float mana, float maxMana, float stun, float maxStun, ANameplateActor* nameplateActor = nullptr){
	Health = health;
	MaxHealth = maxHealth;
    Mana = mana;
    MaxMana = maxMana;
    Stun = stun;
    MaxStun = maxStun;
	NameplateActor = nameplateActor;
	
	if (NameplateActor != nullptr) { NameplateActor->AttachToActor(this->GetOwner(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, false)); }
	//TODO default nameplateActor
	
	UpdateMaxHealthDisplay(MaxHealth);
	UpdateHealthDisplay(Health);
    UpdateMaxHealthDisplay(MaxStun);
    UpdateHealthDisplay(Stun);
	return this;
}


// Called when the game starts
void UResourceComponent::BeginPlay(){
	Super::BeginPlay();

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(
			1, 15.0f, FColor::Yellow, FString::Printf(
				TEXT(
					"ResourceComponent().UID = %s\n    Set Health = %s\n    Set MaxHealth = %s\n"
				),
				*FString::Printf(TEXT("[%d]"), this->GetUniqueID()),
				*FString::SanitizeFloat(Health),
				*FString::SanitizeFloat(MaxHealth)
			)
		);
	}
	
}


// Called every frame
void UResourceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
        /*
	if (GEngine) {
                GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString::Printf(TEXT("TimeUntilStunRegen = %s"),*FString::SanitizeFloat(TimeUntilStunRegen));
        }

	if (TimeUntilStunRegen > 0.f) {
		TimeUntilStunRegen -= DeltaTime;
        } else if (TimeUntilStunRegen <= 0.f) {
                Stun -= NaturalStunRegenRate * DeltaTime;
                UpdateStunDisplay(Stun);
		}

		*/
	// ...
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
	case EDamageCategory::HEALTH :
		s.Append(" HP");
			break;
	case EDamageCategory::MANA :
		s.Append(" MP");
		break;
	case EDamageCategory::STUN :
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
			-1,
			15.f,
			FColor::Yellow,
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

	if (Health >= MaxHealth) { if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString("MAX HEALTH!")); } }

	Health = FMath::Clamp(Health, 0.f, MaxHealth);

	DamageEventCallout(EDamageCategory::HEALTH, h1, Health);

	return Health - h1; //return the actual damage healed
}

float UResourceComponent::DamageMana(float magnitude) {
	return 0.0f;
}

float UResourceComponent::HealMana(float magnitude) {
	return 0.0f;
}

float UResourceComponent::DamageStun(float magnitude) {
	        // Get State before
        float s1 = Stun;

        // increment health
        Stun -= FMath::Abs(magnitude);

        if (Stun <= 0.f) {
                //Death();
        }

        Stun = FMath::Clamp(Stun, 0.f, MaxStun);

        DamageEventCallout(EDamageCategory::STUN, s1, Stun);

        return s1 - Stun; // return the actual damage dealt
}

float UResourceComponent::HealStun(float magnitude) {
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
                    GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString("MAX Stun!"));
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

void UResourceComponent::UpdateHealthDisplay(float health) {
	//UTextBlock* text = (UTextBlock*)DisplayWidget->GetWidget()->GetWidgetFromName(TEXT("HealthText"));
	//text->SetText(FText::FromString(string));
	if (NameplateActor != nullptr) { NameplateActor->SetHealth(health); }
}

void UResourceComponent::UpdateMaxHealthDisplay(float maxHealth){
        if (NameplateActor != nullptr) {
                NameplateActor->SetMaxHealth(maxHealth);
                if (GEngine) {
                    GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString::Printf(TEXT("Tried to set the maxHealth of the actor to %s"), *FString::SanitizeFloat(maxHealth)), true);
                }
        }
}

void UResourceComponent::UpdateManaDisplay(float mana){
        if (NameplateActor != nullptr) {
                NameplateActor->SetMana(mana);
        }
}

void UResourceComponent::UpdateMaxManaDisplay(float maxMana){
        if (NameplateActor != nullptr) {
                NameplateActor->SetMaxMana(maxMana);
        }
}

void UResourceComponent::UpdateStunDisplay(float stun){
        if (NameplateActor != nullptr) {
                NameplateActor->SetStun(stun);
        }
}

void UResourceComponent::UpdateMaxStunDisplay(float maxStun){
        if (NameplateActor != nullptr) {
                NameplateActor->SetMaxStun(maxStun);
        }
}
