// Fill out your copyright notice in the Description page of Project Settings.

#include "NameplateActor.h"

// Sets default values
ANameplateActor::ANameplateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ANameplateActor::SetHealth_Implementation(const float& value){ if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString("ANameplateActor::SetHealth(const float& value) called from base class!")); } }

void ANameplateActor::SetMaxHealth_Implementation(const float& value) { if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString("ANameplateActor::SetMaxHealth(const float& value) called from base class!")); } }

void ANameplateActor::SetMana_Implementation(const float& value) { if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString("ANameplateActor::SetMana(const float& value) called from base class!")); } }

void ANameplateActor::SetMaxMana_Implementation(const float& value){ if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString("ANameplateActor::SetMaxMana(const float& value) called from base class!")); } }

void ANameplateActor::SetStun_Implementation(const float& value){ if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString("ANameplateActor::SetStun(const float& value) called from base class!")); } }

void ANameplateActor::SetMaxStun_Implementation(const float& value){ if (GEngine) {GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString("ANameplateActor::SetMaxStun(const float& value) called from base class!")); } }

void ANameplateActor::SetVisibility_Implementation(const bool visibility){ if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString("ANameplateActor::SetVisibility(const bool vsibility) called from base class!")); } }

// Called when the game starts or when spawned
void ANameplateActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ANameplateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

