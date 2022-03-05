// Fill out your copyright notice in the Description page of Project Settings.

#include "UIStatBar.h"
#include "Components/ProgressBar.h"
#include "Containers/Queue.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"
#include <string>

////////////////////////////////////////////////////////////////
//  TODO
////////////////////////////////////////////////////////////////

// - threshold for linear/reduced animation time for trickle damage
// - set appropriate UPROPERTY assignments

////////////////////////////////////////////////////////////////
//  CONSTRUCTORS
////////////////////////////////////////////////////////////////

//this is how to construct a derived class from UUserWidget which has no default constructor (initialisation lists did not work)
//https://www.reddit.com/r/unrealengine/comments/ibtr4m/lkn2019_error_when_compiling_a_uuserwidget/
void UUIStatBar::NativeConstruct() {
	Super::NativeConstruct();

	MinValue = 0.f;
	MaxValue = 1.f;

	Mode = UUIStatBar::CONTINUOUS;
	AnimationDuration = 0.25f;
	DisplayMaxValue = true;
	SecondaryBarDelay = 1.5f;

	CurrentPct = MaxValue;
	OriginalPct = CurrentPct;
	TargetPct = CurrentPct;

	SecondaryOriginalPct = CurrentPct;
	SecondaryCurrentPct = CurrentPct;
	SecondaryTargetPct = CurrentPct;

	SecondaryBarAnimating = false;
}

////////////////////////////////////////////////////////////////
//  ENGINE FUNCTIONS
////////////////////////////////////////////////////////////////

void UUIStatBar::NativeTick(const FGeometry& MyGeometry, float DeltaTime) {
	Super::NativeTick(MyGeometry, DeltaTime);

	//Firstly, see if enough time has passed to input a ResourceEvent into the secondary Bar

	if (HitQueue.Peek() != nullptr) {
		if (GetWorld()->GetTimeSeconds() - HitQueue.Peek()->EventTime > SecondaryBarDelay) {
			ResourceEvent event;
			if (HitQueue.Dequeue(event)) {
				SecondaryTargetPct = event.SetPct;
				SecondaryOriginalPct = SecondaryCurrentPct;
				//do we need to adjust for the inter-tick delta between (GetWorld()->GetTimeSeconds() - HitQueue.Peek()->EventTime) and (SecondaryBarDelay)? Not for now.
			} else {
				//we deqd nothing! This should never happen due to the peek() check
			}
		}
	} else {
		//nothing in the queue to peek();
	}


	RemainingAnimationTime -= DeltaTime;
	RemainingSecondaryAnimationTime -= DeltaTime;//do we do this every tick?



	//what configuration are we in (damage or healing?) ie. Do we need to animate either of the bars?

	if (TargetPct < CurrentPct) { //we have less resource than what is displayed

		PrimaryBar->SetFillColorAndOpacity(FColor::Red);
		SecondaryBar->SetFillColorAndOpacity(FColor::Green);

		CurrentPct = InterpolateProgress(PrimaryBar, OriginalPct, TargetPct, RemainingAnimationTime, AnimationDuration);

	} else if (TargetPct > CurrentPct) { //we have more resource than what is displayed

		PrimaryBar->SetFillColorAndOpacity(FColor::Green);
		SecondaryBar->SetFillColorAndOpacity(FColor::Green);

		CurrentPct = InterpolateProgress(PrimaryBar, OriginalPct, TargetPct, RemainingAnimationTime, AnimationDuration);
	} else {
		OriginalPct = TargetPct;
	}


	//----------------------------------------

	if (SecondaryTargetPct < SecondaryCurrentPct) { //we have less resource than what is displayed


		SecondaryCurrentPct = InterpolateProgress(SecondaryBar, SecondaryOriginalPct, SecondaryTargetPct, RemainingSecondaryAnimationTime, AnimationDuration);

	} else if (TargetPct > CurrentPct) { //we have more resource than what is displayed


		SecondaryCurrentPct = InterpolateProgress(SecondaryBar, SecondaryOriginalPct, SecondaryTargetPct, RemainingSecondaryAnimationTime, AnimationDuration);

	} else {
		SecondaryOriginalPct = SecondaryTargetPct;
	}



	//the value of the current resource is always set by the character we are bound to

	//---------------------------------------------------------


	if (GetWorld()->GetTimeSeconds() - EventTime >= SecondaryBarDelay) {
		//SecondaryTargetPct = TargetPct;
		//SecondaryBarAnimating = true;
		//RemainingSecondaryAnimationTime = AnimationDuration;
	}


	if (SecondaryCurrentPct == TargetPct) {
		//SecondaryBarAnimating = false;
	}

	if (SecondaryBarAnimating) {
		//SecondaryCurrentPct = InterpolateProgress(SecondaryBar, OriginalPct, SecondaryTargetPct);
	}

	//UE_LOG(LogTemp, Log, TEXT("UIStatBar	CurrentPct = %3.4f, TargetPct = %3.4f, SecondaryCurrentPct = %3.4f, SecondaryTargetPct = %3.4f"), CurrentPct, TargetPct, SecondaryCurrentPct, SecondaryTargetPct);

	if (Mode == UUIStatBar::CONTINUOUS) {
		ValueDisplay->SetText(FText::FromString(
			FString::SanitizeFloat(CurrentValue, 0)			+ FString("/") +	FString::SanitizeFloat(MaxValue,0) + FString("\n") + 
			FString::SanitizeFloat(SecondaryCurrentPct, 0 ) + FString("/") +	FString::SanitizeFloat(MaxValue,0)));
	}
}

////////////////////////////////////////////////////////////////
//  PUBLIC INTERFACE
////////////////////////////////////////////////////////////////

void UUIStatBar::SetMaxValue(float newMaxValue, UUIStatBar::BarTransformation method) {

	switch (method) {

	case BarTransformation::SCALE: //The pct stays the same, but the val changes
		SetCurrentValue(CurrentPct / MaxValue);

	case BarTransformation::EXTEND: //The val stays the same, but the pct changes
		CurrentPct = CurrentValue / newMaxValue;

	}

	if (newMaxValue <= MinValue) {
		UE_LOG(LogTemp, Warning, TEXT("newMaxValue is not greater than MinValue! MaxValue was not changed."))
	} else {
		MaxValue = newMaxValue;
	}
}

void UUIStatBar::SetTargetValue(float value) {
	UE_LOG(LogTemp, Log, TEXT("Setting target value: value/MaxValue: %4.4f / %4.4f = %4.4f"), value, MaxValue,value / MaxValue);
	SetPercent(value / MaxValue);
}

void UUIStatBar::SetCurrentValue(float value) {
	CurrentValue = value;
}

void UUIStatBar::SetPercent(float percent) {
	UE_LOG(LogTemp, Log, TEXT("Setting Target percent"));

	//resets the animation timer
	RemainingAnimationTime = AnimationDuration;

	OriginalPct = CurrentPct;

	//set the target percentage do instantaneously update the interpolation rate

	TargetPct = FMath::Clamp(percent, 0.f, 1.f);
	UE_LOG(LogTemp, Warning, TEXT("value: % 4.4f, MinValue: % 4.4f, MaxValue: % 4.4f, TargetPct: % 4.4f"), percent, MinValue, MaxValue, TargetPct);

	EventTime = GetWorld()->GetTimeSeconds();

	if (Mode == UUIStatBar::DISCRETE) {
		UE_LOG(LogTemp, Log, TEXT("DISCRETE %4.1f"), TargetPct);
		ValueDisplay->SetText(FText::FromString(FString::SanitizeFloat(TargetPct) + FString(" | ") + FString::SanitizeFloat(SecondaryTargetPct)));
	}
	//insert the change request in the queue for dynamics and lag
	HitQueue.Enqueue(ResourceEvent{ TargetPct, EventTime });
}

////////////////////////////////////////////////////////////////
//  PRIVATE INTERFACE
////////////////////////////////////////////////////////////////

float UUIStatBar::InterpolateProgress(UProgressBar* bar, float originalPct, float targetPct, float rem, float dur) {

	float NewPercent = UKismetMathLibrary::Ease(
		originalPct,
		targetPct,
		FMath::Clamp(1 - (rem / dur), 0.f, 1.f),
		EEasingFunc::SinusoidalOut);

	UE_LOG(LogTemp, Warning, TEXT("rem: %4.4f, dur: %4.4f, val: %4.4f, og: %4.4f, target: %4.4f, NewPercent: %4.4f"), rem, dur, FMath::Clamp(1 - (rem / dur), 0.f, 1.f), originalPct, targetPct, NewPercent);

	bar->SetPercent(NewPercent);

	return NewPercent;
}

