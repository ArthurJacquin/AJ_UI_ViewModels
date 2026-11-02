#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MVVMViewModelBase.h"

#include "AJ_ViewModelBase.generated.h"

/**
 * Base class for all view models
 */
UCLASS()
class AJ_UI_VIEWMODELS_API UAJ_ViewModelBase : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	virtual void InitializeViewModel(FSubsystemCollectionBase& Collection) {}
	virtual void InitializeViewModelForOwner(UObject* Owner) {}
	virtual void DeinitializeViewModel() {}
	virtual bool AsBlueprintData() const { return false; }
	
	virtual FGameplayTag GetViewModelTag() const { PURE_VIRTUAL("GetViewModelTag needs to be implemented") return FGameplayTag::EmptyTag; }
};
