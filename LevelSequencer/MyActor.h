#pragma once

#include "LevelSequence.h"  // May require cleaning your build before working
#include "LevelSequencePlayer.h"

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
	ALevelSequenceActor* MySequenceActor = nullptr;
};
