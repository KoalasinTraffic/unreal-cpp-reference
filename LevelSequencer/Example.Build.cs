// Tested on UE 4.27.2

using UnrealBuildTool;

public class Example : ModuleRules
{
	public Example(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",

			"LevelSequence",  // Required module for playing Level Sequences
			"MovieScene",  // Required module for playing Level Sequences
		});
	}
}
