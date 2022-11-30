// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

// Add default functionality here for any IMenuInterface functions that are not pure virtual.
void UMenuWidget::SetMenuInterface(IMenuInterface* MenuInterface)
{
	MainMenuInterface = MenuInterface;
}

// show widget on the screen
void UMenuWidget::Setup(bool bIsMenu)
{
	// Show menu widget
	this->AddToViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) { return; }

	// Show cursor on the menu for the click to button.
	PlayerController = World->GetFirstPlayerController();
	if (PlayerController == nullptr) return;
	//PlayerController->SetShowMouseCursor(true); // alternative for the show cursor

	if (bIsMenu)
	{
		FInputModeUIOnly InputModeData; // call the struct
		InputModeData.SetWidgetToFocus(this->TakeWidget()); // show in the widget
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // set lock mode
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableMouseOverEvents = true;
		PlayerController->SetInputMode(InputModeData);
	}
	else
	{
		FInputModeGameOnly InputModeData; // call the struct
		PlayerController->bShowMouseCursor = false;
		PlayerController->SetInputMode(InputModeData);
	}
}

// When switched the level, it will activate input and remove the widget.
void UMenuWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);

	RemoveFromParent();


	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) { return; }
	//PlayerController->CleanupGameViewport();
	PlayerController = World->GetFirstPlayerController(); // call player controller
	if (PlayerController == nullptr) return;
	FInputModeGameOnly InputModeData; // call the struct
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;
	PlayerController->SetShowMouseCursor(false);
}