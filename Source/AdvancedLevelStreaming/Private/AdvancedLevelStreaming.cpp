// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AdvancedLevelStreaming.h"
#include "ALSConfig.h"

#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"
#define LOCTEXT_NAMESPACE "FAdancedLevelStreamingModule"

void FAdvancedLevelStreamingModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		// Create the new category
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");

		SettingsContainer->DescribeCategory("AdvancedLevelStreaming",
			LOCTEXT("RuntimeWDCategoryName", "Plugins"),
			LOCTEXT("RuntimeWDCategoryDescription", "Base configuration for Advanced Level Streaming"));

		// Register the settings
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "ALS Settings",
			LOCTEXT("RuntimeGeneralSettingsName", "ALS Settings"),
			LOCTEXT("RuntimeGeneralSettingsDescription", "Base configuration for Advanced Level Streaming"),
			GetMutableDefault<UALSConfig>()
		);
	}
}

void FAdvancedLevelStreamingModule::ShutdownModule()
{
	if (UObjectInitialized())
	{
		if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
		{
			SettingsModule->UnregisterSettings("Project", "Plugins", "ALS Settings");
		}
	}
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAdvancedLevelStreamingModule, AdvancedLevelStreaming)
