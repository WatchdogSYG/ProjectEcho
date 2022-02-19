// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "UIHUD.h"
#include "UIStatBar.h"

#include "RPGCharacter.generated.h"


UCLASS()
class PROJECTECHO_API ARPGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UCameraComponent* camera;

	// Sets default values for this character's properties
	ARPGCharacter();

	UUIHUD* HealthBar;

	UPROPERTY(BlueprintReadWrite, Category = "STATS");
	float health{ 100.f };
	
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

	UFUNCTION()
		float GetHealth();

	UFUNCTION()
		void SetHealth(float h);

	UFUNCTION()
		float TakeDamage(float damage);

	UFUNCTION()
		float ReceiveHealing(float healing);

	UPROPERTY(EditAnywhere, Category = "User Interface")
		TSubclassOf<UUserWidget> StatBar;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
