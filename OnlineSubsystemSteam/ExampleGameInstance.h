// Tested on UE 4.27.2

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "ExampleGameInstance.generated.h"

UCLASS()
class EXAMPLE_API UExampleGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	IOnlineSubsystem* OnlineSubsystem = nullptr;
	FString Username = "Offline";
};