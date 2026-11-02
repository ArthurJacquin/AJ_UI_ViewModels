#include "Utilities/AJ_ViewModelsUtilities.h"

#include "Subsystems/AJ_ViewModelsSubsystem.h"

UAJ_ViewModelBase* UAJ_ViewModelsUtilities::GetViewModel(const UObject* WorldContextObject, const FGameplayTag& ViewModelTag)
{
	if (UAJ_ViewModelsSubsystem* ViewModelManager = UAJ_ViewModelsSubsystem::GetInstance(WorldContextObject))
	{
		return ViewModelManager->GetViewModelInstance(ViewModelTag);
	}

	return nullptr;
}
