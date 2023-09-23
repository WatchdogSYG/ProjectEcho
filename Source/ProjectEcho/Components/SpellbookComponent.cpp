// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellbookComponent.h"

// Sets default values for this component's properties
USpellbookComponent::USpellbookComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...


}


// Called when the game starts
void USpellbookComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USpellbookComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

USpellbookComponent* USpellbookComponent::InitialiseSpells(
	UResourceComponent* resource, 
	TSubclassOf<ASpell> primaryFire, 
	TSubclassOf<ASpell> secondaryFire, 
	TSubclassOf<ASpell> ultimate, 
	TSubclassOf<ASpell> offensive, 
	TSubclassOf<ASpell> defensive
){
	r = resource;
	
	//https://forums.unrealengine.com/t/newobject-using-a-blueprint-class/136956/2
	PrimaryFire = NewObject<ASpell>(this, NAME_None, RF_NoFlags, primaryFire->GetDefaultObject(), true);
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(
			1, 10.0f, FColor::Green,
			primaryFire->GetClass()->GetFName().ToString()

		);
	}
	return this;
}

bool USpellbookComponent::CastPrimaryFire_Implementation(){
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(
			1, 1.0f, FColor::Purple, FString::Printf(
				TEXT(
					"Shoot Primary Fire"
				)
			)
		);
	}
	PrimaryFire->Activate(r, true);
	return true;
}

bool USpellbookComponent::CastSecondaryFire_Implementation() {
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(
			1, 1.0f, FColor::Purple, FString::Printf(
				TEXT(
					"Shoot Secondary Fire"
				)
			)
		);
	}
	return true;
}