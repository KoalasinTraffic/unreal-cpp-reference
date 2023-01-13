// Tested on UE 4.27.2

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Steam.generated.h"

UCLASS()
class EXAMPLE_API USteam : public UObject
{
	GENERATED_BODY()
	
public:
	USteam(const FObjectInitializer& ObjectInitializer);

	bool Init(UWorld* InWorld);

	void UpdateLeaderboard(FName& InLevelName, int InScore);
	
private:
	UGameInstance* GameInstance = nullptr;
	TSharedPtr<const FUniqueNetId> UserId = nullptr;
};