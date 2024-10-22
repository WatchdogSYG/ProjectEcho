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

	//UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* HealthTextBlock;

protected:
	////////////////////////////////////////////////////////////////
	//  CONSTRUCTORS
	////////////////////////////////////////////////////////////////

	virtual void NativeOnInitialized() override;

public:

	////////////////////////////////////////////////////////////////
	//  GET/SET
	////////////////////////////////////////////////////////////////

	UFUNCTION(BlueprintCallable)
		void SetValue(float value, float duration);

	UFUNCTION(BlueprintCallable)
		void SetMaxValue(float value, BarTransformationMode method);

	UFUNCTION(BlueprintCallable)
		void SetPercent(float value, float duration);

	UFUNCTION(BlueprintCallable)
		float GetMaxValue();

	UFUNCTION(BlueprintCallable)
        void SetMainColor(FColor color);

    UFUNCTION(BlueprintCallable)
        void SetUpColor(FColor color);

    UFUNCTION(BlueprintCallable)
        void SetDownColor(FColor color);

	UFUNCTION(BlueprintCallable)
		void InitialRefresh(float health, float maxHealth);

private:
	////////////////////////////////////////////////////////////////
	//  MEMBER VARIABLES
	////////////////////////////////////////////////////////////////

	
	//Default Colours
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "Display")
    FColor MainColor;
        UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "Display")
	FColor DownColor;
        UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "Display")
	FColor UpColor;

	//Bar ptrs
	UProgressBar* FrontBar;
	UProgressBar* BackBar;

	bool ConfigurationChanged;
	bool DownConfiguration;

	//Resource Values
	float MinValue;		//value displayed by the bar when it is empty
	float MaxValue;		//float MaxValue;value displayed by the bar when it is full
	float TargetValue;	//The value that the bar animates towards (this is the "correct" instantaneous value)

	//Instantaneous values
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Display")
	float CurrentValue;			//The instantaneous interpolated value of the PrimaryBar

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Display")
	float SecondaryCurrentValue;//The instantaneous interpolated value of the SecondaryBar

	//Percentages (0 <= % <= 1.f)
	
	float OriginalPct;	//The pct that represents the beginning of the interpolated animation for the PrimaryBar
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Display")
	float CurrentPct;	//The pct that the bar animates towards (this is the "correct" instantaneous pct) for the PrimaryBar
	float TargetPct;	//The pct that represents the end of the interpolated animation for the PrimaryBar

	float SecondaryOriginalPct;//The pct that represents the beginning of the interpolated animation for the SecondaryBar
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Display")
	float SecondaryCurrentPct; //The pct that the bar animates towards (this is the "correct" instantaneous pct) for the SecondaryBar
	float SecondaryTargetPct;  //The pct that represents the end of the interpolated animation for the SecondaryBar

	UPROPERTY(EditAnywhere, Category = "Animation")
		float AnimationDuration;	//The animation duration.

	UPROPERTY(EditAnywhere, Category = "Animation")
        float MicroEventMagnitudeThreshold; // The threshold definitoin for microevents

	UPROPERTY(EditAnywhere, Category = "Animation")
        float MicroEventAnimationDuration; // The animation duration for microevents

	float RemainingAnimationTime;	//The remaining animation time. Resets upon setting a new CurrentValue;
	float RemainingSecondaryAnimationTime;

	UPROPERTY(EditAnywhere, Category = "Animation")
		float InterpolationExpConstant;	//The degree of the easing function, if an exponential ease is selected.

	UPROPERTY(EditAnywhere, Category = "Animation")
		float SecondaryBarLag;	//The delay between animating the PrimaryBar compared to the SecondaryBar.

		//a struct that records when the resource is +- and when it happens
	struct ResourceEvent {
		float	SetPct;			//the magnitude of the resource being taken
		float	EventTime;		//the time at which it happened. TODO: determine how I will keep track of relative time/absolute time.
		float	Duration = 0.f;		//Positive only. The time it takes to apply the effect. If Duration > 0, the damage is applied as Damage Over Time while processed in the DOTQueue.
	};

	TQueue< ResourceEvent, EQueueMode::Mpsc > HitQueue; //A queue which will store all events where a resource changed, and is deq'd as the progress bar animates.
	TQueue< ResourceEvent > PrimaryHistoryQueue;

	////////////////////////////////////////////////////////////////
	//  UI CONTROL FUNCTIONS
	////////////////////////////////////////////////////////////////

	float InterpolateProgress(UProgressBar* bar, float originalPct, float targetPct, float rem, float dur);
	float SetProgress(UProgressBar* bar, float targetPct);

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
