#pragma once

#include "CoreMinimal.h"
#include "SettingsDataStruct.h"
#include "GameFramework/SaveGame.h"
#include "HandSaberSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class HANDSABER_API UHandSaberSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	// Spawner Configuration
	UPROPERTY(VisibleDefaultsOnly, Category = "Save Game Data")
	FSettingsDataStruct SettingsData;
	//SCORES
	UPROPERTY(VisibleAnywhere, Category = "Saved Game Data")
	int LastScore;
	UPROPERTY(VisibleAnywhere, Category = "Saved Game Data")
	int BestScore;
};
