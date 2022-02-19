// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGCharacter.h"
#include "Math/Rotator.h"
#include "Blueprint/UserWidget.h"
#include "UIStatBar.h"
#include "UIHUD.h"

//https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/ProgrammingWithCPP/CPPTutorials/FirstPersonShooter/2/

// Sets default values
ARPGCharacter::ARPGCharacter() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//CameraComponent1P->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void ARPGCharacter::BeginPlay() {
	Super::BeginPlay();

	camera = Cast<UCameraComponent>(GetDefaultSubobjectByName(TEXT("CameraComponent3P")));

	//why GetWorld() ???
	//https://forums.unrealengine.com/t/cannot-create-widget-using-c/451606

	UUIHUD* HealthBar = Cast<UUIHUD>(CreateWidget(GetWorld(), StatBar, "UIHealthBar"));

	if (HealthBar == nullptr) {
		check(GEngine != nullptr);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::Red, TEXT("HealthBar is null*"));
	} else {
		check(GEngine != nullptr);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::Red, TEXT("Added to viewport"));
		HealthBar->AddToViewport();
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

void ARPGCharacter::MoveForward(float magnitude) {
	FVector dir = this->GetActorForwardVector();
	AddMovementInput(dir, magnitude);
}

void ARPGCharacter::MoveRight(float magnitude) {
	FVector dir = this->GetActorRightVector() * -1;
	AddMovementInput(dir, magnitude);
}

void ARPGCharacter::MouseUp(float magnitude) {


	camera->SetWorldRotation(camera->GetComponentRotation().Add(magnitude, 0, 0));

	//check(GEngine != nullptr);
	//GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::Red, FString::SanitizeFloat(magnitude) + camera->GetComponentRotation().ToCompactString());
}

void ARPGCharacter::KeyLeft() {
	SetHealth(GetHealth() - 5);
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::Red, TEXT("LEFT"));
}

void ARPGCharacter::KeyRight() {
	SetHealth(GetHealth() + 5);
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::Red, TEXT("RIGHT"));
}

float ARPGCharacter::GetHealth() {
	return health;
}

void ARPGCharacter::SetHealth(float h) {
	health = h;
}