// Tested on UE 4.27.2

#include "MyActor.h"

AMyActor::AMyActor()
{
	// Reference path to Level Sequence copied from unreal
	static ConstructorHelpers::FObjectFinder<ULevelSequence> LevelSequenceAsset(TEXT("/Game/Blueprints/TutorialLevelSequence"));
	if (LevelSequenceAsset.Succeeded())
		MySequence = LevelSequenceAsset.Object;
}

void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	// This portion can be put anywhere including overlaps, conditionals, etc
	if (MySequence)
	{
		// Creates a sequence actor with a player to handle playback
		if (ULevelSequencePlayer* MySequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), MySequence, FMovieSceneSequencePlaybackSettings(), MySequenceActor))
		{
			//MySequencePlayer->PlayLooping(NumLoops);  // Defaults to no loops
			//MySequencePlayer->SetPlayRate(PlayRate);  // Defaults to 1.0x playback speed
			MySequencePlayer->Play();
			
			// Equivalent to Get Level Sequence Length where GetLowerBoundValue should be zero
			//float SequenceLength = MySequence->MovieScene->GetPlaybackRange().GetUpperBoundValue().Value / MySequence->MovieScene->GetTickResolution().AsDecimal();
		}
	}
}
