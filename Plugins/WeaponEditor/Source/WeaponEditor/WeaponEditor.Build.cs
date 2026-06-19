using UnrealBuildTool;

public class WeaponEditor : ModuleRules
{
	public WeaponEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[]
			{
				ModuleDirectory,
			}
		);

		PrivateIncludePaths.AddRange(
			new string[]
			{
				ModuleDirectory,
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"WeaponSystem",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"UnrealEd",
				"KismetWidgets",
				"AdvancedPreviewScene",
				"InputCore",
				"UMG",
				"AnimGraphRuntime",
				"PropertyEditor",
				"AssetTools",
				"GameplayTasks",
				"GameplayAbilities",
				"GameplayTags",
			}
		);
	}
}
