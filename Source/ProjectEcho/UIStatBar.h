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

public:
	float CurrentPct;
	float TargetPct;
	float InterpTime;

	void InterpProgress();

protected:

	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UImage* pb_back;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* pb_secondary;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* pb_primary;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* valueDisplay;
};
