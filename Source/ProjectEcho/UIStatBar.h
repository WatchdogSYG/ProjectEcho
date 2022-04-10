// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Containers/Queue.h"
#include "UObject/ObjectMacros.h"

#include "UIStatBar.generated.h"

////////////////////////////////////////////////////////////////
////  ENUMERATION
////////////////////////////////////////////////////////////////

UENUM(BlueprintType)
enum class BarTransformationMode : uint8 {
	SCALE,
	EXTEND
};

UENUM(BlueprintType)
enum class TextUpdateMode : uint8 {
	DISCRETE,
	CONTINUOUS
};

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
	//  GET/SET
	////////////////////////////////////////////////////////////////

	UFUNCTION(BlueprintCallable)
		void SetValue(float value);

	UFUNCTION(BlueprintCallable)
		void SetMaxValue(float value, BarTransformationMode method);

	UFUNCTION(BlueprintCallable)
		void SetPercent(float value);

private:
	////////////////////////////////////////////////////////////////
	//  MEMBER VARIABLES
	////////////////////////////////////////////////////////////////

	
	//Default Colours

	FColor MainColor;
	FColor DownColor;
	FColor UpColor;

	//Bar ptrs
	UProgressBar* FrontBar;
	UProgressBar* BackBar;

	bool ConfigurationChanged;
	bool DownConfiguration;

	//Resource Values
	float MinValue;		//value displayed by the bar when it is empty
	float MaxValue;		//value displayed by the bar when it is full
	float TargetValue;	//The value that the bar animates towards (this is the "correct" instantaneous value)

	//Instantaneous values
	float CurrentValue;			//The instantaneous interpolated value of the PrimaryBar
	float SecondaryCurrentValue;//The instantaneous interpolated value of the SecondaryBar

	//Percentages (0 <= % <= 1.f)
	float OriginalPct;	//The pct that represents the beginning of the interpolated animation for the PrimaryBar
	float CurrentPct;	//The pct that the bar animates towards (this is the "correct" instantaneous pct) for the PrimaryBar
	float TargetPct;	//The pct that represents the end of the interpolated animation for the PrimaryBar

	float SecondaryOriginalPct;//The pct that represents the beginning of the interpolated animation for the SecondaryBar
	float SecondaryCurrentPct; //The pct that the bar animates towards (this is the "correct" instantaneous pct) for the SecondaryBar
	float SecondaryTargetPct;  //The pct that represents the end of the interpolated animation for the SecondaryBar

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


	void UpdateText();

};
