#include "MainMenu.h"

#include "HandSaberGameInstance.h"
#include "HandSaberSaveGame.h"
#include "SongFeed.h"
#include "SongList.h"
#include "Components/Button.h"
#include "Components/ScaleBox.h"
#include "Components/SizeBox.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
{
	// find menu widget class and define to MenuClass.
	ConstructorHelpers::FClassFinder<UUserWidget> SongListBPClass(
		TEXT("/Game/Blueprints/Widgets/WBP_SongList"));
	if (!ensure(SongListBPClass.Class != nullptr)) return;
	SongListClass = SongListBPClass.Class;
	// find menu widget class and define to MenuClass.
	ConstructorHelpers::FClassFinder<UUserWidget> SongFeedBPClass(
		TEXT("/Game/Blueprints/Widgets/WBP_SongFeed"));
	if (!ensure(SongFeedBPClass.Class != nullptr)) return;
	SongFeedClass = SongFeedBPClass.Class;
	if (UGameplayStatics::DoesSaveGameExist("HandSaberSaveSlot", 0))
	{
		SaveGameData = Cast<UHandSaberSaveGame>(UGameplayStatics::LoadGameFromSlot("HandSaberSaveSlot", 0));
	}
	else
	{
		// couldn't load saved game
		SaveGameData = Cast<UHandSaberSaveGame>(
			UGameplayStatics::CreateSaveGameObject(UHandSaberSaveGame::StaticClass()));
	}

	if (SaveGameData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SaveGameSlot not found"));
	}
}

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) { return false; }

	// NavBar Buttons
	if (!ensure(PlayFeedButton!= nullptr)) { return false; }
	PlayFeedButton->OnClicked.AddDynamic(this, &UMainMenu::PlayFeed);
	PlayFeedButton->OnHovered.AddDynamic(this, &UMainMenu::PlayHover);
	PlayFeedButton->OnUnhovered.AddDynamic(this, &UMainMenu::PlayUnHover);
	if (!ensure(OptionsButton != nullptr)) { return false; }
	OptionsButton->OnClicked.AddDynamic(this, &UMainMenu::OptionsFeed);
	OptionsButton->OnHovered.AddDynamic(this, &UMainMenu::OptionsHover);
	OptionsButton->OnUnhovered.AddDynamic(this, &UMainMenu::OptionsUnHover);
	if (!ensure(CreditsButton != nullptr)) { return false; }
	CreditsButton->OnClicked.AddDynamic(this, &UMainMenu::Credits);
	CreditsButton->OnHovered.AddDynamic(this, &UMainMenu::CreditsHover);
	CreditsButton->OnUnhovered.AddDynamic(this, &UMainMenu::CreditsUnHover);

	// Bottom Buttons
	if (!ensure(QuitButton != nullptr)) { return false; }
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitWarning);
	if (!ensure(BackButton != nullptr)) { return false; }
	BackButton->SetVisibility(ESlateVisibility::Collapsed);
	BackButton->OnClicked.AddDynamic(this, &UMainMenu::Back);

	// START WARNING
	if (!ensure(StartButton != nullptr)) { return false; }
	StartButton->OnClicked.AddDynamic(this, &UMainMenu::StartWarningYes);
	if (!ensure(BackWarningButton != nullptr)) { return false; }
	BackWarningButton->OnClicked.AddDynamic(this, &UMainMenu::StartWarningNo);

	// QUIT WARNING
	if (!ensure(YesButton != nullptr)) { return false; }
	YesButton->OnClicked.AddDynamic(this, &UMainMenu::QuitWarningYes);
	if (!ensure(NoButton != nullptr)) { return false; }
	NoButton->OnClicked.AddDynamic(this, &UMainMenu::QuitWarningNo);
	if (!ensure(SongFeedBox != nullptr)) { return false; }

	// PatchNote WARNING
	if (!ensure(CloseButton != nullptr)) { return false; }
	CloseButton->OnClicked.AddDynamic(this, &UMainMenu::ClosePatchNotes);

	// Intro
	if (!ensure(IntroStartButton != nullptr)) { return false; }
	IntroStartButton->OnClicked.AddDynamic(this, &UMainMenu::IntroStart);

	SaveGameData = Cast<UHandSaberSaveGame>(UGameplayStatics::LoadGameFromSlot("HandSaberSaveSlot", 0));
	if (SaveGameData != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Main Menu successfully reached save game data"));
	}

	UGameplayStatics::SaveGameToSlot(SaveGameData, "HandSaberSaveSlot", 0);
	
	return true;
}

void UMainMenu::NativeConstruct()
{
	WidgetSwitch->SetActiveWidgetIndex(0);
	MainContentSwitcher->SetActiveWidgetIndex(0);
	IntroFadeInAnim();
}


// Get all song names from game instance
void UMainMenu::SetSongList(TArray<FSong> SongNames)
{
	if (!ensure(SongFeedClass != nullptr)) return;
	WBP_SongFeed = CreateWidget<USongFeed>(this, SongFeedClass);
	if (!ensure(SongFeedClass != nullptr)) return;
	SongFeedBox->AddChild(WBP_SongFeed);

	UWorld* World = this->GetWorld();
	if (!ensure(World != nullptr)) { return; }
	if (!ensure(WBP_SongFeed != nullptr)) { return; }
	RefreshList();

	// song index
	uint32 i = 0;
	UE_LOG(LogTemp, Warning, TEXT("Names Num: %s"), *FString::FromInt(SongNames.Num()));
	for (const FSong& SongData : SongNames)
	{
		USongList* SongListWidget = CreateWidget<USongList>(this, SongListClass);

		if (!ensure(SongListWidget != nullptr)) { return; }
		UE_LOG(LogTemp, Warning, TEXT("%s"), *SongData.songName);
		SongListWidget->SongName->SetText(FText::FromString(SongData.songName));
		SongListWidget->AuthorName->SetText(FText::FromString(SongData.songAuthorName));
		SongListWidget->Difficulty->SetText(FText::FromString(SongData.difficulty));

		SongListWidget->Setup(this, i);
		++i;
		WBP_SongFeed->SongList->AddChild(SongListWidget); // add to scroll box
	}
}

void UMainMenu::UpdateChildren()
{
	if (WBP_SongFeed == nullptr) { return; }
	for (int32 i = 0; i < WBP_SongFeed->SongList->GetChildrenCount(); ++i)
	{
		auto List = Cast<USongList>(WBP_SongFeed->SongList->GetChildAt(i));
		if (List != nullptr)
		{
			List->Selected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i);
		}
	}
}

void UMainMenu::ReturnChosenSong(uint32 Index)
{
	MainMenuInterface->ReturnChosenSong(Index);
}

// when you choose one song, it will get the selected index
void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
	UE_LOG(LogTemp, Warning, TEXT("Index: %s"), *FString::FromInt(Index));
	ReturnChosenSong(Index);
	UpdateChildren();
	StartWarning(); // open warning screen
}

// Clear old song list
void UMainMenu::RefreshList() const
{
	WBP_SongFeed->SongList->ClearChildren();
}


/*
 * Play Feed
 */
// Play
void UMainMenu::OpenSongList()
{
	MainMenuWidgetSwitcher->SetActiveWidgetIndex(1);
	ChangedMainMenuWidgetMenu(1);
}

void UMainMenu::PatchNotes()
{
	FadeInAnim();
	MainContentSwitcher->SetActiveWidgetIndex(5);
	ChangedMainContentWidgetMenu(5);
}

/*
 * Option Feed
 */

void UMainMenu::GraphicOptions()
{
	BackButton->SetVisibility(ESlateVisibility::Visible);
	BackButtonBox->SetVisibility(ESlateVisibility::Visible);
	MainContentSwitcher->SetActiveWidgetIndex(2);
	ChangedMainContentWidgetMenu(2);
}

void UMainMenu::AudioOptions()
{
	BackButton->SetVisibility(ESlateVisibility::Visible);
	BackButtonBox->SetVisibility(ESlateVisibility::Visible);
	MainContentSwitcher->SetActiveWidgetIndex(3);
	ChangedMainContentWidgetMenu(3);
}

/*
 * Nav Bar
 */

void UMainMenu::PlayFeed()
{
	MainMenuWidgetSwitcher->SetActiveWidgetIndex(0);
	ChangedMainMenuWidgetMenu(0);
}

void UMainMenu::OptionsFeed()
{
	MainMenuWidgetSwitcher->SetActiveWidgetIndex(2);
	ChangedMainMenuWidgetMenu(2);
}

void UMainMenu::Credits()
{
	MainMenuWidgetSwitcher->SetActiveWidgetIndex(3);
	ChangedMainMenuWidgetMenu(3);
}

/*
 * BottomButtons
 */

// Quit button will open the Quit Warning
void UMainMenu::QuitWarning()
{
	FadeInAnim();
	MainContentSwitcher->SetActiveWidgetIndex(1);
	ChangedMainContentWidgetMenu(1);
}

// Back button it will visible on options menu
void UMainMenu::Back()
{
	FTimerHandle Timer;
	FadeInAnim();
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &UMainMenu::GoBack, 1.0f, false,
	                                       FadeIn->GetEndTime() - 0.5);
}

void UMainMenu::GoBack()
{
	if (IsSaved)
	{
		if (GEngine)
		{
			bool Applied = false;;
			GEngine->GameUserSettings->ApplySettings(Applied);
			if (Applied)
			{
				if(auto const GameInstance = Cast<UHandSaberGameInstance>(GetGameInstance()))
				{
					//GameInstance->SaveGame();
				}
				UGameplayStatics::SaveGameToSlot(SaveGameData, "HandSaberSaveSlot", 0);
				UE_LOG(LogTemp, Warning, TEXT("Saved"));
			}
		}
	}

	BackButton->SetVisibility(ESlateVisibility::Collapsed);
	BackButtonBox->SetVisibility(ESlateVisibility::Collapsed);
	MainContentSwitcher->SetActiveWidgetIndex(0);
	ChangedMainContentWidgetMenu(0);
	IsSaved = false;
}


/*
 * Warning Screen
 */
void UMainMenu::StartWarning()
{
	FadeInAnim();
	MainContentSwitcher->SetActiveWidgetIndex(4);
	ChangedMainContentWidgetMenu(4);
}

/*
 * Quit Warning Screen
 */

void UMainMenu::QuitWarningYes()
{
	// Exit to the game
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) { return; }

	PlayerController = World->GetFirstPlayerController(); // call player controller
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}

void UMainMenu::QuitWarningNo()
{
	FadeInAnim();
	MainContentSwitcher->SetActiveWidgetIndex(0);
	ChangedMainContentWidgetMenu(0);
}

/*
 * Start Warning Screen
 * call start game func. from interface (when you pressed yes at start warning screen) 
 */

void UMainMenu::StartWarningYes()
{
	MainMenuInterface->StartGame();
}




void UMainMenu::StartWarningNo()
{
	FadeInAnim();
	MainContentSwitcher->SetActiveWidgetIndex(0);
	ChangedMainContentWidgetMenu(0);
}

void UMainMenu::NativeDestruct()
{
	Super::NativeDestruct();

	// MAIN MENU
	StartButton->OnClicked.RemoveAll(this);
	QuitButton->OnClicked.RemoveAll(this);
}

/*
 * Intro
 */
void UMainMenu::IntroStart()
{
	WidgetSwitch->SetActiveWidgetIndex(1);
	ChangedMenuWidgetMenu(1);
}

/*
 * Patch Note Warning
 */
void UMainMenu::ClosePatchNotes()
{
	FadeInAnim();
	MainContentSwitcher->SetActiveWidgetIndex(0);
	ChangedMainContentWidgetMenu(0);
}

/*
 * Animations
 */

void UMainMenu::PlayHover()
{
	PlayAnimation(PlayHovered, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}

void UMainMenu::PlayUnHover()
{
	PlayAnimation(PlayUnHovered, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}

void UMainMenu::OptionsHover()
{
	PlayAnimation(OptionsHovered, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}

void UMainMenu::OptionsUnHover()
{
	PlayAnimation(OptionsUnHovered, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}

void UMainMenu::CreditsHover()
{
	PlayAnimation(CreditsHovered, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}

void UMainMenu::CreditsUnHover()
{
	PlayAnimation(CreditsUnHovered, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}

void UMainMenu::SwitchAnimation()
{
	PlayAnimation(SwitchAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}

void UMainMenu::FadeInAnim()
{
	PlayAnimation(FadeIn, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}

void UMainMenu::IntroFadeInAnim()
{
	PlayAnimation(IntroFadeIn, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}
