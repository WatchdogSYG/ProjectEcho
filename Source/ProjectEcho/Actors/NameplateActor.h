// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NameplateActor.generated.h"

UCLASS()
class PROJECTECHO_API ANameplateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANameplateActor();

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
		void SetVisibility(const bool visibility);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
