// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIStatBar.generated.h"

/**
 *
 */
UCLASS()
class PROJECTECHO_API UUIStatBar : public UUserWidget {
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* pb_back;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* pb_secondary;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* pb_primary;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* valueDisplay;
};
