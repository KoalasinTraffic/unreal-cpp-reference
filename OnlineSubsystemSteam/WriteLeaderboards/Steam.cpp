// Tested on UE 4.27.2

#include "Steam.h"
#include "ExampleGameInstance.h"

#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineAchievementsInterface.h"
#include "Interfaces/OnlineLeaderboardInterface.h"

USteam::USteam(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

// Must be called after every creation of USteam object
bool USteam::Init(UWorld* InWorld)
{
	GameInstance = InWorld->GetGameInstance();
	if (UExampleGameInstance* MyGameInstance = Cast<UExampleGameInstance>(GameInstance))
	{
		// Attempt to initialize OnlineSubsystem when not connected
		if (!MyGameInstance->OnlineSubsystem)
			MyGameInstance->OnlineSubsystem = IOnlineSubsystem::Get();

		if (MyGameInstance->OnlineSubsystem)
		{
			IOnlineIdentityPtr Identity = MyGameInstance->OnlineSubsystem->GetIdentityInterface();
			if (Identity.IsValid())
			{
				// All other variable initializations should go here
				UserId = Identity->GetUniquePlayerId(0);
				MyGameInstance->Username = Identity->GetPlayerNickname(*UserId.Get());

				UE_LOG(LogTemp, Display, TEXT("USteam: Successful login"));
				return true;
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("USteam: UserId invalid"));
				MyGameInstance->OnlineSubsystem = nullptr;
				return false;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("USteam: OnlineSubsystem disabled"));
			MyGameInstance->OnlineSubsystem = nullptr;
			return false;
		}
	}
	UE_LOG(LogTemp, Error, TEXT("USteam: MyGameInstance invalid"));
	return false;
}

void USteam::UpdateLeaderboard(FName& InStatName, int InScore)
{
	if (UExampleGameInstance* MyGameInstance = Cast<UExampleGameInstance>(GameInstance))
	{
		if (MyGameInstance->OnlineSubsystem)
		{
			IOnlineLeaderboardsPtr Leaderboards = MyGameInstance->OnlineSubsystem->GetLeaderboardsInterface();
			if (Leaderboards.IsValid())
			{
				FOnlineLeaderboardWrite WritePtr;
				WritePtr.SortMethod = ELeaderboardSort::Descending;
				WritePtr.DisplayFormat = ELeaderboardFormat::Number;
				WritePtr.UpdateMethod = ELeaderboardUpdateMethod::KeepBest;
				WritePtr.LeaderboardNames = { InStatName };
				WritePtr.RatedStat = InStatName;
				WritePtr.SetIntStat(InStatName, InScore); // StatName within Steamworks must be named InStatName_InStateName
				Leaderboards->WriteLeaderboards(InStatName, *UserId.Get(), WritePtr);
				UE_LOG(LogTemp, Display, TEXT("USteam: Writing %s = %i"), *InStatName.ToString(), InScore);
			}
			else
				UE_LOG(LogTemp, Error, TEXT("USteam: UpdateLeaderboard invalid"));
		}
	}
}