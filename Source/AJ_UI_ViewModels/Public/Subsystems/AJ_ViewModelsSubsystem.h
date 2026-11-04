#pragma once

#include "CoreMinimal.h"
#include "Engine/StreamableManager.h"
#include "GameplayTagContainer.h"
#include "Subsystems/WorldSubsystem.h"

#include "AJ_ViewModelsSubsystem.generated.h"

class UMVVMViewModelCollectionObject;
class UViewModelBase;

/**
 * Subsystem to manage and request registered view models
 */
UCLASS()
class AJ_UI_VIEWMODELS_API UAJ_ViewModelsSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	static UAJ_ViewModelsSubsystem* GetInstance(const UObject* WorldContextObject);
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	UFUNCTION(BlueprintCallable)
	UAJ_ViewModelBase* GetViewModelInstance(UPARAM(meta=(Categories="UI.ViewModel"))const FGameplayTag& ViewModelTag);

private:
	void ValidateAndAddNewViewModel(const FGameplayTag& ViewModelTag, const TSubclassOf<UAJ_ViewModelBase>& ViewModelClass, FSubsystemCollectionBase& SubsystemCollection, UMVVMViewModelCollectionObject* ViewModelCollection);

	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<UAJ_ViewModelBase>> RegisteredViewModels;
	
	FStreamableManager AssetStreamableManager;
	TArray<TSharedPtr<FStreamableHandle>> LoadedAssetHandles;
};
