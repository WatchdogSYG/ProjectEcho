// This is a prototype of a game, currently for non-commercial purposes. This may change at any time without notice in the future and may be licenced under different conditions. You may not copy or redistribute content for commercial purposes. TODO: Assign licence (CC or otherwise).

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WidgetAnchorComponent.generated.h"

/* Connect this component to an actor. This component serves as an anchor for other components and widgets in world space.
*/

UCLASS( Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTECHO_API UWidgetAnchorComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWidgetAnchorComponent();

private:

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
