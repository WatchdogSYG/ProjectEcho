// Fill out your copyright notice in the Description page of Project Settings.

#include "UIStatBar.h"
#include "Components/ProgressBar.h"
#include "Containers/Queue.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"
#include <string>


////////////////////////////////////////////////////////////////
//  CONSTRUCTORS
////////////////////////////////////////////////////////////////

//this is how to construct a derived class from UUserWidget which has no default constructor (initialisation lists did not work)
//https://www.reddit.com/r/unrealengine/comments/ibtr4m/lkn2019_error_when_compiling_a_uuserwidget/
void UUIStatBar::NativeConstruct() {
	Super::NativeConstruct();

	MinValue = 0.f;
	MaxValue = 1.f;

	Mode = UUIStatBar::DISCRETE;
	AnimationDuration = 0.25f;
	DisplayMaxValue = true;
	SecondaryBarDelay = 1.5f;

	CurrentPct = MaxValue;
	OriginalPct = CurrentPct;
	TargetPct = CurrentPct;
	SecondaryCurrentPct = CurrentPct;
	SecondaryTargetPct = CurrentPct;
	SecondaryBarAnimating = false;
}

////////////////////////////////////////////////////////////////
//  ENGINE FUNCTIONS
////////////////////////////////////////////////////////////////

void UUIStatBar::NativeTick(const FGeometry& MyGeometry, float DeltaTime) {
	Super::NativeTick(MyGeometry, DeltaTime);

	RemainingAnimationTime -= DeltaTime;
	//the value of the current resource is always set by the character we are bound to

	////Check wether an animation is needed ie. determine if we are under or over the target to determine the primary and secondary bar colours and behaviours
	if (TargetPct < CurrentPct) { //we have less resource than what is displayed
		//change bar configuration to downwards interpolation

		//PrimaryBar becomes primary colour and represents real-time health
		//PrimaryBar.set
		PrimaryBar->SetFillColorAndOpacity(FColor::Red);
		//SecondaryBar becomes DAMAGE secondary colour and represents lagging health
		SecondaryBar->SetFillColorAndOpacity(FColor::Green);

		//Interpolate values for health for this frame
		CurrentPct = InterpolateProgress(PrimaryBar, OriginalPct, TargetPct);



		//Change progress

	} else if (TargetPct > CurrentPct) { //we have more resource than what is displayed
		//change bar configuration to upwards interpolation

		//PrimaryBar becomes primary colour and represents lagging resource
		PrimaryBar->SetFillColorAndOpacity(FColor::Green);
		//SecondaryBar becomes HEALING secondary colour and represents real-time resource
		SecondaryBar->SetFillColorAndOpacity(FColor::Red);
		//Interpolate values for resource for this frame

		//Change progress


	}//otherwise we are already displaying the correct value

	//---------------------------------------------------------


	if (GetWorld()->GetTimeSeconds() - LastActionTime >= SecondaryBarDelay) {
		SecondaryTargetPct = TargetPct;
		SecondaryBarAnimating = true;
		RemainingSecondaryAnimationTime = AnimationDuration;
	}


	if (SecondaryCurrentPct == TargetPct) {
		SecondaryBarAnimating = false;
	}


	if (TargetPct < CurrentPct) { //we have less resource than what is displayed

		PrimaryBar->SetFillColorAndOpacity(FColor::Red);
		SecondaryBar->SetFillColorAndOpacity(FColor::Green);
		CurrentPct = InterpolateProgress(PrimaryBar, OriginalPct, TargetPct);

	} else if (TargetPct > CurrentPct) { //we have more resource than what is displayed

		PrimaryBar->SetFillColorAndOpacity(FColor::Green);
		SecondaryBar->SetFillColorAndOpacity(FColor::Green);

	} else { //otherwise we are already displaying the correct value/we have reached the correct value

		OriginalPct = TargetPct;

	}


	if (SecondaryTargetPct != SecondaryCurrentPct) {

		if (SecondaryBarAnimating) {
			//SecondaryCurrentPct = InterpolateProgress(SecondaryBar, OriginalPct, SecondaryTargetPct);
		}

	}


	if (SecondaryBarAnimating) {
		//SecondaryCurrentPct = InterpolateProgress(SecondaryBar, OriginalPct, SecondaryTargetPct);
	}

	UE_LOG(LogTemp, Log, TEXT("UIStatBar	CurrentPct = %3.4f, TargetPct = %3.4f, SecondaryCurrentPct = %3.4f, SecondaryTargetPct = %3.4f"), CurrentPct, TargetPct, SecondaryCurrentPct, SecondaryTargetPct);
}

////////////////////////////////////////////////////////////////
//  UI CONTROL FUNCTIONS
////////////////////////////////////////////////////////////////

void UUIStatBar::SetMaxValue(float newMaxValue, UUIStatBar::BarTransformation method) {

	switch (method) {

	case BarTransformation::SCALE: //The pct stays the same, but the val changes
		SetCurrentValue(CurrentPct / MaxValue);

	case BarTransformation::EXTEND: //The val stays the same, but the pct changes
		CurrentPct = CurrentValue / newMaxValue;

	}

	MaxValue = newMaxValue;

	ValueDisplay->SetText(FText::AsNumber(MaxValue));
}

void UUIStatBar::SetPercent(float value) {
	UE_LOG(LogTemp, Log, TEXT("Setting Target percent"));
	//resets the animation timer
	RemainingAnimationTime = AnimationDuration;

	OriginalPct = CurrentPct;

	//set the target percentage do instantaneously update the interpolation rate
	TargetPct = value / MaxValue;

	UWorld* const world = GetWorld();

	if (world) {
		UE_LOG(LogTemp, Log, TEXT("There is a world"));
		LastActionTime = GetWorld()->GetTimeSeconds();
	}

	if (Mode == UUIStatBar::DISCRETE) {
		UE_LOG(LogTemp, Log, TEXT("DISCRETE %4.1f"),TargetPct);
		ValueDisplay->SetText(FText::FromString(FString::SanitizeFloat(TargetPct)+FString(" | ")+ FString::SanitizeFloat(SecondaryTargetPct)));
	}
	//insert the change request in the queue for dynamics and lag
	//HitQueue.Enqueue(ResourceEvent{ TargetPct, LastActionTime });
}

void UUIStatBar::SetTargetValue(float value) {
	UE_LOG(LogTemp, Log, TEXT("Setting target value"));
	SetPercent(value / MaxValue);
}

float UUIStatBar::InterpolateProgress(UProgressBar* bar, float originalPct, float targetPct) {

	float NewPercent = UKismetMathLibrary::Ease(
		originalPct,
		targetPct,
		FMath::Clamp(1 - (RemainingAnimationTime / AnimationDuration), 0.f, 1.f),
		EEasingFunc::SinusoidalOut);


	bar->SetPercent(NewPercent*100);

	ValueDisplay->SetText(FText::FromString(FString::SanitizeFloat(NewPercent * 100) + FString(" | ") + FString::SanitizeFloat(bar->Percent)));
	//ValueDisplay->SetText(FText::AsNumber(NewPercent * MaxValue));

	return NewPercent;
}

void UUIStatBar::SetCurrentValue(float value) {
	CurrentValue = value;
	if (Mode == UUIStatBar::CONTINUOUS) {
		ValueDisplay->SetText(FText::AsNumber(CurrentValue));
	}
}