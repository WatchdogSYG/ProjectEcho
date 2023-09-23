// This is a prototype of a game, currently for non-commercial purposes. This may change at any time without notice in the future and may be licenced under different conditions. You may not copy or redistribute content for commercial purposes. TODO: Assign licence (CC or otherwise).

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EchoCharacter.generated.h"

UCLASS()
class PROJECTECHO_API AEchoCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEchoCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
