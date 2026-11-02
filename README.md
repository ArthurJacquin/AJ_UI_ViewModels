This plugin provides utilities to implement and use Unreal Engine's MVVM plugin (ModelViewViewModel). It allows an easy way to register View Models and access from a Gameplay Tag defined by each View Model.

# View Model Creation Guide

## Create a C++ View Model

1. Create a class derived from `UAJ_ViewModelBase`.
2. Implement `GetViewModelTag()` using a unique tag for this View Model. The tags should be child of `UI.ViewModel`.

## Create a Blueprint View Model

### If you don't have any Blueprint View Model yet:

1. Create a new Data Asset of type `UAJ_ViewModelConfig`.
2. Go to **Project Settings > AJ View Models**.
3. Assign the newly created Data Asset to **View Models Config**.

### Add Blueprint View Model to Data Asset

Once you have a Data Asset created:
1. Open your config Data Asset (of type `UAJ_ViewModelConfig`).
2. Add a new element to **View Model Configs**.
3. Specify the **Tag** and **Class** of your Blueprint View Model.

The view model will be initialized and registered automatically.

## Access Registered View Model

Call `UAJ_ViewModelsUtilities::GetViewModel()` in Blueprint or C++ and pass the tag of the desired view model.
