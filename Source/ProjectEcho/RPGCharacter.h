// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "UIHUD.h"
#include "UIStatBar.h"

#include "RPGCharacter.generated.h"

/*
 * A class that is a parent to all playable Characters in this game. It should implement movement, 
 * stats, stat behaviours (damage, effects, healing, death), and be a baseis for mounting other 
 * components.
*/
UCLASS()
class PROJECTECHO_API ARPGCharacter : public ACharacter {

	GENERATED_BODY()

public:
	////////////////////////////////////////////////////////////////
	//  CONSTRUCTORS
	////////////////////////////////////////////////////////////////

	ARPGCharacter();

	////////////////////////////////////////////////////////////////
	//  COMPONENTS
	////////////////////////////////////////////////////////////////

	//The main camera for this character. TODO: ThirdPerson gimbal implementation.
	UCameraComponent* camera;

	////////////////////////////////////////////////////////////////
	//  USER INTERFACE & WIDGETS
	////////////////////////////////////////////////////////////////

	UPROPERTY(EditAnywhere, Category = "User Interface")
		TSubclassOf<UUserWidget> StatBar;

	UUIHUD* HealthBar;

	////////////////////////////////////////////////////////////////
	//  CHARACTER STATS
	////////////////////////////////////////////////////////////////

	UPROPERTY(BlueprintReadWrite, Category = "STATS");
	float Health{ 100.f };
	float MaxHealth{ 100.f };

	////////////////////////////////////////////////////////////////
	//  BOUND FUNCTIONS
	////////////////////////////////////////////////////////////////

	UFUNCTION()
		void MoveForward(float magnitude);

	UFUNCTION()
		void MoveRight(float magnitude);

	UFUNCTION()
		void MouseUp(float magnitude);

	UFUNCTION(BlueprintCallable)
		void KeyLeft();

	UFUNCTION(BlueprintCallable)
		void KeyRight();

	////////////////////////////////////////////////////////////////
	//  OTHER FUNCTIONS
	////////////////////////////////////////////////////////////////

	UFUNCTION()
		float GetHealth();

	UFUNCTION()
		void SetHealth(float h);

	UFUNCTION()
		float TakeDamage(float damage);

	UFUNCTION()
		float ReceiveHealing(float healing);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
