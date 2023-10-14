// This is a prototype of a game, currently for non-commercial purposes. This may change at any time without notice in the future and may be licenced under different conditions. You may not copy or redistribute content for commercial purposes. TODO: Assign licence (CC or otherwise).


#include "EchoCharacter.h"

// Sets default values
AEchoCharacter::AEchoCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEchoCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEchoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEchoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


