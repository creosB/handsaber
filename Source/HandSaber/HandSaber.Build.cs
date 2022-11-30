using UnrealBuildTool;

public class HandSaber : ModuleRules
{
    public HandSaber(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "MediaPipe",
            "RuntimeAudioImporter",
            "Niagara",
            "UMG",
            "Slate",
            "SlateCore",
            "MediaAssets"
        });

        PrivateDependencyModuleNames.AddRange(new string[] {"JsonUtilities", "Json", "RuntimeAudioImporter"});
    }
}
