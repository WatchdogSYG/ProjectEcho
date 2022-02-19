// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIHUD.generated.h"

/**
 *
 */
UCLASS()
class PROJECTECHO_API UUIHUD : public UUserWidget {
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UUIStatBar* bar;
};
