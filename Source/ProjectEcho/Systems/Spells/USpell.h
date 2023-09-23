// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "USpell.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTECHO_API ASpell: public AActor
{
	GENERATED_BODY()

public:
	ASpell();
	~ASpell();


	UFUNCTION(BlueprintCallable)
		virtual void Activate(UResourceComponent* CasterResource, bool start) ;



private:
	FString SpellName;

	
};
