#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HANDSABER_API IMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// pure virtual function - no implementation
	virtual void StartGame() PURE_VIRTUAL(UHandSaberGameInstance::StartGame);
	virtual void ReturnChosenSong(uint32 Index) PURE_VIRTUAL(UHandSaberGameInstance::ReturnChosenSong; uint32 Index);
	virtual void RestartGame() PURE_VIRTUAL(UHandSaberGameInstance::RestartGame);
	virtual void LoadMainMenu() PURE_VIRTUAL(UHandSaberGameInstance::LoadMainMenu);
	virtual void AddScore(int score) PURE_VIRTUAL(UHandSaberGameInstance::AddScore; int score);
};
