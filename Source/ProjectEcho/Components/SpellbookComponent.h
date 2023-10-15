// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Systems/Spells/USpell.h"


#include "SpellbookComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) , BlueprintType, Blueprintable)
class PROJECTECHO_API USpellbookComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpellbookComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		USpellbookComponent* InitialiseSpells(
			UResourceComponent* resource, 
			TSubclassOf<ASpell> primaryFire, 
			TSubclassOf<ASpell> secondaryFire,
			TSubclassOf<ASpell> ultimate,
			TSubclassOf<ASpell> offensive,
			TSubclassOf<ASpell> defensive
		);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	UResourceComponent* r;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells")
		ASpell* PrimaryFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells")
		ASpell* SecondaryFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells")
		ASpell* Ultimate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells")
		ASpell* Offensive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spells")
		ASpell* Defensive;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		bool CastPrimaryFire();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		bool CastSecondaryFire();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        bool CastAbility1();
};
