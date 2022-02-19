// Fill out your copyright notice in the Description page of Project Settings.


#include "UIStatBar.h"


void UUIStatBar::InterpProgress() {
}

void UUIStatBar::NativeTick(const FGeometry& MyGeometry, float DeltaTime) {
	Super::NativeTick(MyGeometry, DeltaTime);
	 
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5, FColor::Red, TEXT("WidgetTick"));
}
