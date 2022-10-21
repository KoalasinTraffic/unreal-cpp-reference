#include "MyActor.h"

AMyActor::AMyActor()
{
	// Path to Level Sequence defined in unreal with custom tracks, keyframing, etc
	static ConstructorHelpers::FObjectFinder<ULevelSequence> LevelSequenceAsset(TEXT("/Game/Blueprints/TutorialLevelSequence"));
	if (LevelSequenceAsset.Succeeded())
		MySequence = LevelSequenceAsset.Object;
}

void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	// Sequence player can be triggered any time using overlaps, inputs, checking external variables, etc
	if (MySequence)
	{
		// Creates a sequence actor with a player to handle playback
		if (ULevelSequencePlayer* MySequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), MySequence, FMovieSceneSequencePlaybackSettings(), MySequenceActor))
		{
			//MySequencePlayer->PlayLooping(NumLoops);  // defaults to no loops
			//MySequencePlayer->SetPlayRate(PlayRate);  // defaults to 1.0x playback speed
			MySequencePlayer->Play();
		}
	}
}