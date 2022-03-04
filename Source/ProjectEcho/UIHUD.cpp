// Fill out your copyright notice in the Description page of Project Settings.

#include "UIHUD.h"
#include "UIStatBar.h"


UUIStatBar* UUIHUD::GetBar() {
	return bar;
}

void UUIHUD::SetMaxHealth(float max) {
	bar->SetMaxValue(max, UUIStatBar::SCALE);
}

void UUIHUD::SetHealth(float health) {
	bar->SetTargetValue(health);
}