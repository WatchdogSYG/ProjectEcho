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

protected:
	////////////////////////////////////////////////////////////////
	//  CONSTRUCTORS
	////////////////////////////////////////////////////////////////

	virtual void NativeConstruct() override;

public:

	////////////////////////////////////////////////////////////////
	//  MEMBER VARIABLE & ENUMERATION
	////////////////////////////////////////////////////////////////

	enum BarTransformation {
		SCALE,
		EXTEND
	};

	enum TextUpdateMode {
		DISCRETE,
		CONTINUOUS
	};

	////////////////////////////////////////////////////////////////
	//  GET/SET
	////////////////////////////////////////////////////////////////
	float GetMaxValue();
	void SetMaxValue(float value, BarTransformation method);

	
	float GetPercent();
	void SetPercent(float value);

	float GetTargetValue();
	void SetTargetValue(float value);

private:

	void SetCurrentValue(float value);	//This is private as this fn controls the real time display which we don't want the user controlling. It also synchronises the internal UUIStatBar::CurrentValue with the text display.

private:
	////////////////////////////////////////////////////////////////
	//  MEMBER VARIABLES
	////////////////////////////////////////////////////////////////

	//Resource Values
	float MinValue;
	float MaxValue;

	float TargetValue;
	float CurrentValue;

	//Percentages
	float OriginalPct;
	float CurrentPct;
	float TargetPct;

	float SecondaryOriginalPct;
	float SecondaryCurrentPct;
	float SecondaryTargetPct;

	UPROPERTY(EditAnywhere, Category = "Animation")
		float AnimationDuration;	//The animation duration.

	float RemainingAnimationTime;	//The remaining animation time. Resets upon setting a new CurrentValue;
	float RemainingSecondaryAnimationTime;

	UPROPERTY(EditAnywhere, Category = "Animation")
		float InterpolationExpConstant;	//The degree of the easing function, if an exponential ease is selected.

	UPROPERTY(EditAnywhere, Category = "Animation")
		float SecondaryBarLag;	//The delay between animating the PrimaryBar compared to the SecondaryBar.

		//a struct that records when the resource is +- and when it happens
	struct ResourceEvent {
		float	SetPct;				//the magnitude of the resource being taken
		float	EventTime;		//the time at which it happened. TODO: determine how I will keep track of relative time/absolute time.
	};

	TQueue< ResourceEvent, EQueueMode::Mpsc > HitQueue; //A queue which will store all events where a resource changed, and is deq'd as the progress bar animates.

	////////////////////////////////////////////////////////////////
	//  UI CONTROL FUNCTIONS
	////////////////////////////////////////////////////////////////

	float InterpolateProgress(UProgressBar* bar, float originalPct, float targetPct, float rem, float dur);

	////////////////////////////////////////////////////////////////
	//  OPTIONS
	////////////////////////////////////////////////////////////////
	
	TextUpdateMode Mode;

	bool DisplayMaxValue;


	float EventTime;
	float SecondaryBarDelay;
	bool SecondaryBarAnimating;

};
