// Fill out your copyright notice in the Description page of Project Settings.


#include "HandSaberGameInstance.h"
#include "HandSaberSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "HandSaber/data/SongStruct.h"

UHandSaberGameInstance::UHandSaberGameInstance(const FObjectInitializer& ObjectInitializer)
{
	// find menu widget class and define to MenuClass.
	const ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/Blueprints/Widgets/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;
	MenuClass = MenuBPClass.Class;

	// find pause menu widget class and define to PauseMenuClass.
	const ConstructorHelpers::FClassFinder<UUserWidget> PauseMenuBPClass(
		TEXT("/Game/Blueprints/Widgets/WBP_PauseMenu"));
	if (!ensure(PauseMenuBPClass.Class != nullptr)) return;
	PauseMenuClass = PauseMenuBPClass.Class;

	// find pause menu widget class and define to DeadScreenBPClass.
	const ConstructorHelpers::FClassFinder<UUserWidget> DeadScreenBPClass(
		TEXT("/Game/Blueprints/Widgets/WBP_DeadScreen"));
	if (!ensure(DeadScreenBPClass.Class != nullptr)) return;
	DeadScreenClass = DeadScreenBPClass.Class;

	// find pause menu widget class and define to ScoreScreenBPClass.
	ConstructorHelpers::FClassFinder<UUserWidget> ScoreScreenBPClass(
		TEXT("/Game/Blueprints/Widgets/WBP_Score"));
	if (!ensure(ScoreScreenBPClass.Class != nullptr)) return;
	ScoreScreenClass = ScoreScreenBPClass.Class;
}

void UHandSaberGameInstance::Init()
{
	Super::Init();
}

void UHandSaberGameInstance::ReadSongList(FString FilePath)
{
	TSharedPtr<FJsonObject> JsonObject;
	FString JsonString; //Json converted to FString

	FFileHelper::LoadFileToString(JsonString, *(FPaths::ProjectDir() + FilePath));

	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	SongList = FSongStruct(JsonString);


	if (SongList.songs.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Instance Music Num %s"), *FString::FromInt(SongList.songs.Num()));
		Menu->SetSongList(SongList.songs);
	}
}


void UHandSaberGameInstance::ReturnChosenSong(uint32 Index)
{
	ChosenSong = SongList.songs[Index];
}

// Start Game
void UHandSaberGameInstance::StartGame()
{
	SaveGame();
	// load to the main map
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) { return; }
	UGameplayStatics::OpenLevel(World,TEXT("/Game/Maps/Level1"), false);
}

// Restart Game
void UHandSaberGameInstance::RestartGame()
{
	// load to the main map
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) { return; }
	UGameplayStatics::OpenLevel(World,TEXT("/Game/Maps/Level1"), TRAVEL_Absolute);
}

// create main dead screen widget
void UHandSaberGameInstance::DeadScreen()
{
	if (!ensure(DeadScreenClass != nullptr)) return;
	DeadMenu = CreateWidget<UDeadScreen>(this, DeadScreenClass); // create menu widget with MenuClass
	if (!ensure(DeadMenu != nullptr)) { return; }
	DeadMenu->Setup(true); // add to viewport and show cursor
	DeadMenu->SetMenuInterface(this);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

// create main menu widget
void UHandSaberGameInstance::LoadMenu()
{
	// Create menu widget
	if (!ensure(MenuClass != nullptr)) return;
	Menu = CreateWidget<UMainMenu>(this, MenuClass); // create menu widget with MenuClass
	if (!ensure(Menu != nullptr)) return;

	Menu->Setup(true); // add to viewport and show cursor
	Menu->SetMenuInterface(this);
}

// create pause menu widget
void UHandSaberGameInstance::PauseLoadMenu()
{
	if (!ensure(PauseMenuClass != nullptr)) return;
	PauseMenu = CreateWidget<UPauseMenu>(this, PauseMenuClass); // create menu widget with MenuClass
	if (!ensure(PauseMenu != nullptr)) return;
	PauseMenu->Setup(true); // add to viewport and show cursor
	PauseMenu->SetMenuInterface(this);
}

// open the main menu
void UHandSaberGameInstance::LoadMainMenu()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) { return; }
	UGameplayStatics::OpenLevel(World,TEXT("/Game/Maps/Level0"), TRAVEL_Absolute);
}

// create score widget
void UHandSaberGameInstance::ScoreScreenWidget()
{
	if (!ensure(ScoreScreenClass != nullptr)) return;
	ScoreScreen = CreateWidget<UScoreScreen>(this, ScoreScreenClass); // create menu widget with MenuClass
	if (!ensure(ScoreScreen != nullptr)) return;
	ScoreScreen->Setup(false); // add to viewport and show cursor
	ScoreScreen->SetMenuInterface(this);
}

// add score to score screen
void UHandSaberGameInstance::AddScore(int score)
{
	if (Score + score < 0)
	{
		Score = 0;
		ScoreScreen->SendScreen(0);
	}
	else
	{
		Score += score;
		ScoreScreen->SendScreen(score);
	}
}

void UHandSaberGameInstance::GetSongPercent(float percent)
{
	ScoreScreen->SetScoreColor(percent);
}

void UHandSaberGameInstance::SaveGame()
{
	if (UGameplayStatics::DoesSaveGameExist("HandSaberSaveSlot", 0))
	{
		SaveGameSlot = Cast<UHandSaberSaveGame>(UGameplayStatics::LoadGameFromSlot("HandSaberSaveSlot", 0));
	}
	else
	{
		// couldn't load saved game
		SaveGameSlot = Cast<UHandSaberSaveGame>(
			UGameplayStatics::CreateSaveGameObject(UHandSaberSaveGame::StaticClass()));
	}


	if (SaveGameSlot != nullptr)
	{
		if (SaveGameSlot->BestScore < Score)
		{
			SaveGameSlot->BestScore = Score;
			UE_LOG(LogTemp, Warning, TEXT("Best Score Saved"));
		}
		SaveGameSlot->LastScore = Score;
		UGameplayStatics::SaveGameToSlot(SaveGameSlot, "HandSaberSaveSlot", 0);
		// check save
		UE_LOG(LogTemp, Warning, TEXT("Game Saved Hud %d"), SaveGameSlot->BestScore);
		UE_LOG(LogTemp, Warning, TEXT("Game Saved Hud %d"), SaveGameSlot->LastScore);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SaveGameSlot not found"));
	}
}
