// Fill out your copyright notice in the Description page of Project Settings.

////////////////////////////////////////////////////////////////
//  NOTES
////////////////////////////////////////////////////////////////
// Tutorial used for initial Character skeleton code.
//https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/ProgrammingWithCPP/CPPTutorials/FirstPersonShooter/2/

#include "RPGCharacter.h"
#include "Math/Rotator.h"
#include "Blueprint/UserWidget.h"
#include "UIStatBar.h"
#include "UIHUD.h"

////////////////////////////////////////////////////////////////
//  CONSTRUCTORS
////////////////////////////////////////////////////////////////

ARPGCharacter::ARPGCharacter() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

////////////////////////////////////////////////////////////////
//  ACTOR FUNCTIONS
////////////////////////////////////////////////////////////////

// Called when the game starts or when spawned
void ARPGCharacter::BeginPlay() {

	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("ARPGCharacter BeginPlay"));

	//Initialise Camera
	UE_LOG(LogTemp, Log, TEXT("ARPGCharacter	Initialise CameraComponent3P"));
	camera = Cast<UCameraComponent>(GetDefaultSubobjectByName(TEXT("CameraComponent3P")));

	//Initialise User Interface (HUD)
	//why GetWorld() ???
	//https://forums.unrealengine.com/t/cannot-create-widget-using-c/451606

	//Create a type-safe HUD class and add it to the viewport
	UE_LOG(LogTemp, Log, TEXT("ARPGCharacter	Create Widget UIHealthBar"));
	HealthBar = Cast<UUIHUD>(CreateWidget(GetWorld(), StatBar, "UIHealthBar"));

	if (HealthBar == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("ARPGCharacter	HealthBar UUIHUD == nullptr"));
	} else {
		UE_LOG(LogTemp, Log, TEXT("ARPGCharacter	Add HealthBar to Viewport"));
		HealthBar->AddToViewport();

		HealthBar->SetMaxHealth(MaxHealth);
		HealthBar->SetHealth(Health);
	}
}

// Called every frame
void ARPGCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(
		"ForwardAxis",
		this,
		&ARPGCharacter::MoveForward);

	PlayerInputComponent->BindAxis(
		"RightAxis",
		this,
		&ARPGCharacter::MoveRight);

	PlayerInputComponent->BindAxis(
		"TurnX",
		this,
		&ARPGCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAxis(
		"TurnY",
		this,
		&ARPGCharacter::MouseUp);

	PlayerInputComponent->BindAction(
		"dev0",
		IE_Pressed,
		this,
		&ARPGCharacter::KeyLeft);

	PlayerInputComponent->BindAction(
		"dev1",
		IE_Pressed,
		this,
		&ARPGCharacter::KeyRight);
}

////////////////////////////////////////////////////////////////
//  OTHER MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////

void ARPGCharacter::MoveForward(float magnitude) {
	FVector dir = this->GetActorForwardVector();
	AddMovementInput(dir, magnitude);
}

void ARPGCharacter::MoveRight(float magnitude) {
	FVector dir = this->GetActorRightVector() * -1;
	AddMovementInput(dir, magnitude);
}

void ARPGCharacter::MouseUp(float magnitude) {
	//For now, this controls the pitch of the camera as a way of aiming the 3P camera about the lateral axis.
	camera->SetWorldRotation(camera->GetComponentRotation().Add(magnitude, 0, 0));
}

void ARPGCharacter::KeyLeft() {
	UE_LOG(LogTemp, Log, TEXT("ARPGCharacter pressed LEFTKEY"));
	HealthBar->GetBar()->SetValue(TakeDamage(7));
	UE_LOG(LogTemp, Log, TEXT("ARPGCharacter	Health = %4.0f"), Health);
}

void ARPGCharacter::KeyRight() {
	UE_LOG(LogTemp, Log, TEXT("ARPGCharacter pressed RIGHTKEY"));
	HealthBar->GetBar()->SetValue(ReceiveHealing(10));
	UE_LOG(LogTemp, Log, TEXT("ARPGCharacter	Health = %4.0f"), Health);
}

float ARPGCharacter::GetHealth() {
	UE_LOG(LogTemp, Log, TEXT("ARPGCharacter GetHealth() : %4.2f"), Health);
	return Health;
}

void ARPGCharacter::SetHealth(float h) {
	Health = h;
}

float ARPGCharacter::TakeDamage(float damage) {
	UE_LOG(LogTemp, Log, TEXT("ARPGCharacter takes %4.0f damage"), damage);
	float newHealth = Health - damage;
	SetHealth(newHealth);
	return newHealth;
}

float ARPGCharacter::ReceiveHealing(float healing) {
	UE_LOG(LogTemp, Log, TEXT("ARPGCharacter receives %4.0f healing"), healing);
	float newHealth = Health + healing;
	SetHealth(newHealth);
	return newHealth;
}