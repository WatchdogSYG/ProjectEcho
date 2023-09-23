// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay() {
	Super::BeginPlay();

	// ...


	ItemArray.Add(Item(FString("Item Example 1")));
	ItemArray.Add(Item(FString("Item Example 2")));
	ItemArray.Add(Item(FString("Item Example 3")));

}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FString UInventoryComponent::PrintDebugInventory() {
	FString s = FString("----------------\nInventory\n----------------\n");
	for (int i = 0; i < ItemArray.Num(); i++) {
		s.Append(ItemArray[i].GetName()).Append("\n");
	};
	return s;
}
