// Tested on UE 4.27.2

#include "ExampleGameInstance.h"
#include "Steam.h"

void UExampleGameInstance::Init()
{
	Super::Init();

	// Cache OnlineSubsystem for Achievements
	if (USteam* MySteam = NewObject<USteam>())
		if (MySteam->Init(GetWorld()))
			MySteam->QueryAchievements();
}