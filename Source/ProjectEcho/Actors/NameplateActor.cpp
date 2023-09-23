// Fill out your copyright notice in the Description page of Project Settings.


#include "NameplateActor.h"

// Sets default values
ANameplateActor::ANameplateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ANameplateActor::SetText_Implementation(const FString& string){
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString("ANameplateActor::SetText(FString string) called from base class!")); }
}

void ANameplateActor::SetVisibility_Implementation(const bool visibility){
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString("ANameplateActor::SetVisibility(bool vsibility) called from base class!")); }
}


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

