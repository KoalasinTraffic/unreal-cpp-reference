// Tested on UE 4.27.2

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExampleUsage.generated.h"

UCLASS()
class EXAMPLE_API AExampleUsage : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};