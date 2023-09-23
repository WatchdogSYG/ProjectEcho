// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PROJECTECHO_API Item
{
public:
	Item(FString name);
	~Item();

	FString GetName();
private:
	FString name;

};
