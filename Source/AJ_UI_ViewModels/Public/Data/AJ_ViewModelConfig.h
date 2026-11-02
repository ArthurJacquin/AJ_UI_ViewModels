#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"

#include "AJ_ViewModelConfig.generated.h"

USTRUCT()
struct FViewModelConfig
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FGameplayTag ViewModelTag = FGameplayTag::EmptyTag;
	
	UPROPERTY(EditAnywhere, meta=(AllowedClasses="/Script/AJ_UI_ViewModels.AJ_ViewModelBase"))
	UClass* ViewModelClass = nullptr;
};

/**
 * Data for Blueprint View Models
 * Useful for selecting View Model class and editing default values
 */
UCLASS()
class AJ_UI_VIEWMODELS_API UAJ_ViewModelConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TArray<FViewModelConfig> ViewModelConfigs;
};
