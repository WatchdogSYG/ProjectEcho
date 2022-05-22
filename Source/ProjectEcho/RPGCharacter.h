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
	float Health;
	UPROPERTY(BlueprintReadWrite, Category = "STATS");
	float MaxHealth{ 100.f };

	UPROPERTY(BlueprintReadWrite, Category = "STATS");
	float Mana;
	UPROPERTY(BlueprintReadWrite, Category = "STATS");
	float MaxMana{ 80.f };

	UPROPERTY(BlueprintReadWrite, Category = "STATS");
	float Shock;
	UPROPERTY(BlueprintReadWrite, Category = "STATS");
	float MaxShock{ 25.f };

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

	UFUNCTION(BlueprintCallable)
		float ReceiveDamage(float damage);

	UFUNCTION()
		float ReceiveHealing(float healing);

	UFUNCTION(BlueprintCallable)
		float TakeDamage(float DamageAmount, UDamageType* DamageType, class AController* EventInstigator, class AActor* DamageCauser);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
