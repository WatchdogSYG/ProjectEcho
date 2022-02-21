// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Containers/Queue.h"

#include "UIStatBar.generated.h"

/**
 *
 */
UCLASS()
class PROJECTECHO_API UUIStatBar : public UUserWidget {

	GENERATED_BODY()

	////////////////////////////////////////////////////////////////
	//  UMG WIDGET BINDING
	////////////////////////////////////////////////////////////////
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UImage* BackgroundImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* SecondaryBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* PrimaryBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* ValueDisplay;

public:
	////////////////////////////////////////////////////////////////
	//  CONSTRUCTORS
	////////////////////////////////////////////////////////////////

	//UUIStatBar();

	////////////////////////////////////////////////////////////////
	//  GET/SET
	////////////////////////////////////////////////////////////////

	void SetMaxValue(float value);

	void SetPercent(float value);

	void SetCurrentValue(float value);

	float GetMaxValue();

	float GetPercent();

	float GetCurrentValue();

private:
	////////////////////////////////////////////////////////////////
	//  MEMBER VARIABLES
	////////////////////////////////////////////////////////////////

	float MaxValue;
	float CurrentValue;

	float CurrentPct;
	float TargetPct;
	float InterpTime;

	float InterpolationConstant;

	//a struct that records when the resource is +- and when it happens
	struct ResourceEvent {
		float	magnitude;	//the magnitude of the resource being taken
		long	time;		//the time at which it happened. TODO: determine how I will keep track of relative time/absolute time.
		bool	readOnce;	//TODO: doc and rename this
	};

	TQueue< ResourceEvent, EQueueMode::Mpsc > HitQueue; //A queue which will store all events where a resource changed, and is deq'd as the progress bar animates.

	////////////////////////////////////////////////////////////////
	//  UI CONTROL FUNCTIONS
	////////////////////////////////////////////////////////////////

	void InterpProgress(float newHealth);
};
