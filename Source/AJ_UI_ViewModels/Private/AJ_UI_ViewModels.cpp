// Copyright Epic Games, Inc. All Rights Reserved.

#include "AJ_UI_ViewModels.h"

#define LOCTEXT_NAMESPACE "FAJ_UI_ViewModelsModule"

void FAJ_UI_ViewModelsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FAJ_UI_ViewModelsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAJ_UI_ViewModelsModule, AJ_UI_ViewModels)