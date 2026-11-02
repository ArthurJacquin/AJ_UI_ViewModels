#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "AJ_ViewModelsUtilities.generated.h"

class UAJ_ViewModelBase;

/**
 * Utility function for View Models
 */
UCLASS()
class AJ_UI_VIEWMODELS_API UAJ_ViewModelsUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static UAJ_ViewModelBase* GetViewModel(const UObject* WorldContextObject, const FGameplayTag& ViewModelTag);
};
