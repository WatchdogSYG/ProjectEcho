// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceComponent.h"
#include "Engine/Engine.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"

// Sets default values for this component's properties
UResourceComponent::UResourceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	TestDefaultConstructorID = FString::Printf(TEXT("[%d]"), this->GetUniqueID());
}


UResourceComponent* UResourceComponent::InitialiseResources(float health, float maxHealth, ANameplateActor* nameplateActor=nullptr) {
	Health = health;
	MaxHealth = maxHealth;
	NameplateActor = nameplateActor;
	
	if (NameplateActor != nullptr) { NameplateActor->AttachToActor(this->GetOwner(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, false)); }
	//TODO default nameplateActor
	UpdateDisplay(FString::SanitizeFloat(Health,0));

	return this;
}


// Called when the game starts
void UResourceComponent::BeginPlay()
{
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
void UResourceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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

	UpdateDisplay(FString::Printf(TEXT("%s"), *FString::SanitizeFloat(Health, 0)));
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
	return 0.0f;
}

float UResourceComponent::HealStun(float magnitude) {
	return 0.0f;
}

void UResourceComponent::Death() {
	//probably need a death flag to stop this being run multiple times per tick
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString::Printf(TEXT("YOU DIED")), true); }
}

void UResourceComponent::UpdateDisplay(FString string) {
	//UTextBlock* text = (UTextBlock*)DisplayWidget->GetWidget()->GetWidgetFromName(TEXT("HealthText"));
	//text->SetText(FText::FromString(string));
	if (NameplateActor != nullptr) { NameplateActor->SetText(string); }
}