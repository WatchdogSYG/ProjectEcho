// Fill out your copyright notice in the Description page of Project Settings.


#include "USpell.h"

ASpell::ASpell()
{
}

ASpell::~ASpell()
{
}

void ASpell::Activate(UResourceComponent* CasterResource, bool start)
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(
			1, 1.0f, FColor::Red, FString::Printf(
				TEXT(
					"USpell.Activate() is not defined"
				)
			)
		);
	}
}

