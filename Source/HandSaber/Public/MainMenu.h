#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "SettingsDataStruct.h"
#include "HandSaber/data/SongStruct.h"
#include "MainMenu.generated.h"


/**
 * 
 */
UCLASS()
class HANDSABER_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

public:
	UMainMenu(const FObjectInitializer& ObjectInitializer);

	void SetSongList(TArray<FSong> SongNames);
	void SelectIndex(uint32 Index);
	void RefreshList() const;
	void UpdateChildren();

	/*
 * PlayFeed
 */
	UFUNCTION()
	void OpenSongList(); // play button
	UFUNCTION()
	void PatchNotes();


	/*
	 * OptionsFeed
	 */

	UFUNCTION()
	void GraphicOptions();
	UFUNCTION()
	void AudioOptions();

	UFUNCTION(BlueprintImplementableEvent)
	void ChangedMenuWidgetMenu(int index);
	UFUNCTION(BlueprintImplementableEvent)
	void ChangedMainMenuWidgetMenu(int index);
	UFUNCTION(BlueprintImplementableEvent)
	void ChangedMainContentWidgetMenu(int index);

	// Settings Changed Check
	bool IsSaved = false;
private:
	// Nav Bar
	UPROPERTY(meta = (BindWidget))
	class UButton* PlayFeedButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* OptionsButton; // it will open the options
	UPROPERTY(meta = (BindWidget))
	class UButton* CreditsButton; // it will open the options

	// Bottom Buttons
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton; // back button in join menu
	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton; // it will change widget with num 0
	UPROPERTY(meta = (BindWidget))
	class UScaleBox* BackButtonBox;

	// Start Warning
	UPROPERTY(meta = (BindWidget))
	class UButton* BackWarningButton; // (no button)
	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton; // it will start the game (yes button)

	// Quit Warning
	UPROPERTY(meta = (BindWidget))
	class UButton* NoButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* YesButton;

	// PatchNote WARNING
	UPROPERTY(meta = (BindWidget))
	class UButton* CloseButton;
	UFUNCTION()
	void ClosePatchNotes();

	// SongList
	UPROPERTY()
	class USongFeed* WBP_SongFeed;
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true), BlueprintReadWrite)
	class USizeBox* SongFeedBox;
	TSubclassOf<class UUserWidget> SongFeedClass = nullptr;
	TSubclassOf<class UUserWidget> SongListClass = nullptr;

	// Intro
	UPROPERTY(meta = (BindWidget))
	class UButton* IntroStartButton;

	/*
	 * NavBar
	 */
	UFUNCTION()
	void PlayFeed();
	UFUNCTION()
	void OptionsFeed();
	UFUNCTION()
	void Credits();

	/*
	 * Quit Warning
	 */
	UFUNCTION()
	void QuitWarningYes();
	UFUNCTION()
	void QuitWarningNo();

	/*
	 *Start Warning
	 */
	UFUNCTION()
	void StartWarning();
	UFUNCTION()
	void StartWarningYes();
	UFUNCTION()
	void StartWarningNo();
	
	/*
	 * Bottom Buttons
	 */

	// Quit Warning
	UFUNCTION()
	void QuitWarning();
	UFUNCTION()
	void Back();
	UFUNCTION()
	void GoBack();


	// Song List
	UFUNCTION()
	void ReturnChosenSong(uint32 Index);

	// Intro
	UFUNCTION()
	void IntroStart();

	// WIDGET SWITCHER
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true), BlueprintReadWrite)
	class UWidgetSwitcher* WidgetSwitch; // wrap with widget switcher on the editor
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true), BlueprintReadWrite)
	class UWidgetSwitcher* MainContentSwitcher; // wrap with widget switcher on the editor
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = true), BlueprintReadWrite)
	class UWidgetSwitcher* MainMenuWidgetSwitcher; // wrap with widget switcher on the editor

	// WIDGET ANIMATION
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* PlayHovered;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* PlayUnHovered;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* OptionsHovered;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* OptionsUnHovered;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* CreditsHovered;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* CreditsUnHovered;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* SwitchAnim;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true), BlueprintReadWrite)
	UWidgetAnimation* IntroFadeIn;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true), BlueprintReadWrite)
	UWidgetAnimation* FadeIn;

	TOptional<uint32> SelectedIndex;

	/*
	 * ANIMATIONS
	 */
	UFUNCTION()
	void PlayHover();
	UFUNCTION()
	void PlayUnHover();
	UFUNCTION()
	void OptionsHover();
	UFUNCTION()
	void OptionsUnHover();
	UFUNCTION()
	void CreditsHover();
	UFUNCTION()
	void CreditsUnHover();
	UFUNCTION()
	void SwitchAnimation();
	UFUNCTION()
	void IntroFadeInAnim();
	UFUNCTION()
	void FadeInAnim();

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual bool Initialize() override;
protected:
	UPROPERTY()
	class UHandSaberSaveGame* SaveGameData;
};
