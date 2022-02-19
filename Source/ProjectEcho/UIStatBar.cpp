// Fill out your copyright notice in the Description page of Project Settings.

#include "UIStatBar.h"
#include "Components/ProgressBar.h"

#include "Components/TextBlock.h"

//UUIStatBar::UUIStatBar() {

//}

void UUIStatBar::InterpProgress(float newHealth) {
	pb_primary->Percent = 0.20;
	valueDisplay->SetText(FText::AsNumber(newHealth));
}

void UUIStatBar::NativeTick(const FGeometry& MyGeometry, float DeltaTime) {
	Super::NativeTick(MyGeometry, DeltaTime);
	 
}
