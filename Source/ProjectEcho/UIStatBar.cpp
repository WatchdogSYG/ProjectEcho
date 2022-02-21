// Fill out your copyright notice in the Description page of Project Settings.

#include "UIStatBar.h"
#include "Components/ProgressBar.h"
#include "Containers/Queue.h"
#include "Components/TextBlock.h"


////////////////////////////////////////////////////////////////
//  CONSTRUCTORS
////////////////////////////////////////////////////////////////

//UUIStatBar::UUIStatBar() {

//}

////////////////////////////////////////////////////////////////
//  ENGINE FUNCTIONS
////////////////////////////////////////////////////////////////

void UUIStatBar::NativeTick(const FGeometry& MyGeometry, float DeltaTime) {
	Super::NativeTick(MyGeometry, DeltaTime);

	//the value of the current resource is always set by the character we are bound to

	//Check wether an animation is needed ie. determine if we are under or over the target to determine the primary and secondary bar colours and behaviours
	if (TargetPct < CurrentPct) { //we have less resource than what is displayed
		//change bar configuration to downwards interpolation

		//PrimaryBar becomes primary colour and represents real-time health
		//PrimaryBar.set
		//SecondaryBar becomes DAMAGE secondary colour and represents lagging health

		//Interpolate values for health for this frame

		//Change progress

	} else if (TargetPct > CurrentPct) { //we have more resource than what is displayed
		//change bar configuration to upwards interpolation

		//PrimaryBar becomes primary colour and represents lagging resource

		//SecondaryBar becomes HEALING secondary colour and represents real-time resource

		//Interpolate values for resource for this frame

		//Change progress


	}//otherwise we are already displaying the correct value


	//Text always displays the real-time value
	//ValueDisplay->SetText(TEXT(CurrentValue));



}

////////////////////////////////////////////////////////////////
//  UI CONTROL FUNCTIONS
////////////////////////////////////////////////////////////////

void UUIStatBar::SetMaxValue(float value) {
	MaxValue = value;
}

void UUIStatBar::SetPercent(float value) {
	HitQueue.Enqueue(ResourceEvent{ value, 0, false });
}

void UUIStatBar::InterpProgress(float newHealth) {
	PrimaryBar->Percent = 0.20;
	ValueDisplay->SetText(FText::AsNumber(newHealth));
}