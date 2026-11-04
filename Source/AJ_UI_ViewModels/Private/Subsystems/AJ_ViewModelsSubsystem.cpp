#include "Subsystems/AJ_ViewModelsSubsystem.h"

#include "MVVMGameSubsystem.h"
#include "Data/AJ_ViewModelConfig.h"
#include "Settings/AJ_ViewModelSettings.h"
#include "ViewModels/AJ_ViewModelBase.h"

UAJ_ViewModelsSubsystem* UAJ_ViewModelsSubsystem::GetInstance(const UObject* WorldContextObject)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (IsValid(World))
	{
		return World->GetSubsystem<UAJ_ViewModelsSubsystem>();
	}
	
	return nullptr;
}

void UAJ_ViewModelsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	const UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	
	const UGameInstance* GameInstance = World->GetGameInstance();
	if (!GameInstance)
	{
		return;
	}
	
	if (UMVVMGameSubsystem* MVVMSubsystem = GameInstance->GetSubsystem<UMVVMGameSubsystem>())
	{
		if (UMVVMViewModelCollectionObject* ViewModelCollection = MVVMSubsystem->GetViewModelCollection())
		{
			// Iterate through classes derived from UViewModelBase
			for (TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt)
			{
				UClass* Class = *ClassIt;
				if (Class == UAJ_ViewModelBase::StaticClass() || !Class->IsChildOf(UAJ_ViewModelBase::StaticClass()) || Class->HasAnyClassFlags(CLASS_Abstract))
				{
					continue;
				}
				
				// Register pure c++ View Models
				const UAJ_ViewModelBase* DefaultObject = GetDefault<UAJ_ViewModelBase>(Class);
				if (!DefaultObject->AsBlueprintData())
				{
					ValidateAndAddNewViewModel(DefaultObject->GetViewModelTag(), Class, Collection, ViewModelCollection);
				}
				
				// Register Blueprint View Models
				if (const UAJ_ViewModelSettings* Settings = GetDefault<UAJ_ViewModelSettings>())
				{
					if (Settings->ViewModelsConfig.IsValid())
					{
						LoadedAssetHandles.AddDefaulted();
						if (const UAJ_ViewModelConfig* ViewModelConfig = Cast<UAJ_ViewModelConfig>(AssetStreamableManager.LoadSynchronous(Settings->ViewModelsConfig)))
						{
							for (const FViewModelConfig& Config : ViewModelConfig->ViewModelConfigs)
							{
								ValidateAndAddNewViewModel(Config.ViewModelTag, Config.ViewModelClass, Collection, ViewModelCollection);
							}
						}
					}
				}
			}
		}
	}
}

void UAJ_ViewModelsSubsystem::Deinitialize()
{
	Super::Deinitialize();
	
	if (const UWorld* World = GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			if (UMVVMGameSubsystem* MVVMSubsystem = GameInstance->GetSubsystem<UMVVMGameSubsystem>())
			{
				if (UMVVMViewModelCollectionObject* ViewModelCollection = MVVMSubsystem->GetViewModelCollection())
				{
					for (auto& Pair : RegisteredViewModels)
					{
						Pair.Value->DeinitializeViewModel();

						FMVVMViewModelContext Context;
						Context.ContextClass = Pair.Value->GetClass();
						Context.ContextName = FName(Pair.Key.ToString());
						
						ViewModelCollection->RemoveViewModel(Context);
					}
				}
			}
		}
	}
	
	RegisteredViewModels.Empty();

	for (TSharedPtr<FStreamableHandle>& AssetHandle : LoadedAssetHandles)
	{
		if (AssetHandle.IsValid())
		{
			AssetHandle->ReleaseHandle();
		}
	}
	
	LoadedAssetHandles.Empty();
}

UAJ_ViewModelBase* UAJ_ViewModelsSubsystem::GetViewModelInstance(const FGameplayTag& ViewModelTag)
{
	if (!ViewModelTag.IsValid())
	{
		ensureAlwaysMsgf(false, TEXT("UAJ_ViewModelsSubsystem: Failed to find View Model instance, View Model tag is invalid."));
		return nullptr;
	}
	
	if (TObjectPtr<UAJ_ViewModelBase>* ViewModelPtr = RegisteredViewModels.Find(ViewModelTag))
	{
		return *ViewModelPtr;
	}

	ensureAlwaysMsgf(false, TEXT("UAJ_ViewModelsSubsystem: Failed to find View Model instance with tag %s, Make sure the View Model was registered before trying to access it."), *ViewModelTag.ToString());
	return nullptr;
}

void UAJ_ViewModelsSubsystem::ValidateAndAddNewViewModel(const FGameplayTag& ViewModelTag,
	const TSubclassOf<UAJ_ViewModelBase>& ViewModelClass, FSubsystemCollectionBase& SubsystemCollection,
	UMVVMViewModelCollectionObject* ViewModelCollection)
{
	if (RegisteredViewModels.Contains(ViewModelTag))
	{
		ensureAlwaysMsgf(false, TEXT("UAJ_ViewModelsSubsystem: View model %s is already registered!"), *ViewModelTag.ToString());
		return;
	}
	
	if (ViewModelClass && ViewModelTag.IsValid())
	{
		UAJ_ViewModelBase* NewViewModel = NewObject<UAJ_ViewModelBase>(ViewModelClass);
		NewViewModel->InitializeViewModel(SubsystemCollection);
		
		FMVVMViewModelContext Context;
		Context.ContextClass = ViewModelClass;
		Context.ContextName = FName(ViewModelTag.ToString());
		ViewModelCollection->AddViewModelInstance(Context, NewViewModel);
		
		RegisteredViewModels.Add(ViewModelTag, NewViewModel);
	}
	else
	{
		ensureAlwaysMsgf(false, TEXT("UAJ_ViewModelsSubsystem: View model class or View Model tag is invalid!"));
	}
}
