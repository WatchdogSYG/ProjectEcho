// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIStatBar.h"

#include "UIHUD.generated.h"

/**
 * A container class for all Main Player UMG UI. The Character that this is bound to
 * should control all UI functionality related to that Character through this class.
 */
UCLASS()
class PROJECTECHO_API UUIHUD : public UUserWidget {

	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void ChangePct(int a);

	UUIStatBar* GetBar();

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UUIStatBar* bar;
};