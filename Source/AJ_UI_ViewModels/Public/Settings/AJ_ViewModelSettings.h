#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "AJ_ViewModelSettings.generated.h"

/**
 * Project settings for the plugin
 */
UCLASS(config = Plugins, DefaultConfig)
class AJ_UI_VIEWMODELS_API UAJ_ViewModelSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	virtual FName GetCategoryName() const override { return FName("Plugins"); }
	virtual FName GetSectionName() const override { return FName("AJ View Models"); }
	
	UPROPERTY(config, EditAnywhere, meta=(AllowedClasses="/Script/AJ_UI_ViewModels.AJ_ViewModelConfig"))
	FSoftObjectPath ViewModelsConfig;
};
