// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CastableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCastableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTECHO_API ICastableInterface
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Initialisation")
		void Activate();

	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Initialisation")
		//void SetSpellName(FString name);
};
