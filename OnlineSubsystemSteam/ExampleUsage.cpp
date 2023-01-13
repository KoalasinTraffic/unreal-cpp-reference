// Tested on UE 4.27.2

#include "ExampleUsage.h"
#include "Steam.h"

void AExampleUsage::BeginPlay()
{
	// These can be put in any function, event, or trigger
	// It even works within UserWidget
	
	// These are just examples, don't initialize multiple instances of USteam object at once
	
	// This is for completing a single achievement
	// Don't forget to modify DefaultEngine.ini and update Achievement_0_Id definitions to match Steamworks
	if (USteam* MySteam = NewObject<USteam>())
		if (MySteam->Init(GetWorld()))
			MySteam->FinishAchievement("ACHIEVEMENT_NAME");
			
	// This is for updating progress on an achievement with a Progress Stat
	// Progress stat within Steamworks must be named LevelsComplete_LevelsComplete in this example
	int LevelsComplete = 1;
	if (USteam* MySteam = NewObject<USteam>())
		if (MySteam->Init(GetWorld()))
			MySteam->UpdateStat("LevelsComplete", LevelsComplete);
	
	// This is for updating a leaderboard (see UpdateLeaderboard for other settings)
	// Stat within Steamworks must be named HighScore_HighScore in this example
	FName StatName = "HighScore";
	int HighScore = 9001;
	if (USteam* MySteam = NewObject<USteam>())
		if (MySteam->Init(GetWorld()))
			MySteam->UpdateLeaderboard(StatName, HighScore);
}