// Tested on UE 4.27.2

#pragma once

#include "LevelSequence.h"  // Visual studio may not recognize but works with clean build
#include "LevelSequencePlayer.h"  // Visual studio may not recognize but works with clean build

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class EXAMPLE_API AMyActor : public AActor
{
	GENERATED_BODY()

public:	
	AMyActor();

protected:
	virtual void BeginPlay() override;

private:
	ULevelSequence* MySequence = nullptr;
	ALevelSequenceActor* MySequenceActor = nullptr;  // Actor can be used to end sequence
};
