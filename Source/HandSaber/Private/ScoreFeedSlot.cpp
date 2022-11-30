#include "ScoreFeedSlot.h"
#include "HandSaberGameInstance.h"
#include "HandSaberSaveGame.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UScoreFeedSlot::NativeConstruct()
{
	Super::NativeConstruct();
	
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

	if (SaveGameData != nullptr)
	{
		// check save
		UE_LOG(LogTemp, Warning, TEXT("%d"), SaveGameData->BestScore);
		UE_LOG(LogTemp, Warning, TEXT("%d"), SaveGameData->LastScore);
	}
	else
	{
		// couldn't load save game
		UE_LOG(LogTemp, Warning, TEXT("Save coludn't load"));
	}
}

bool UScoreFeedSlot::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) { return false; }

	if (!ensure(ScoreText != nullptr)) { return false; }
	SaveGameData = Cast<UHandSaberSaveGame>(UGameplayStatics::LoadGameFromSlot("HandSaberSaveSlot", 0));
	if (SaveGameData != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ScoreText"));
		ScoreText->SetText(FText::FromString(FString::FromInt(SaveGameData->BestScore)));
		ScoreText->SetVisibility(ESlateVisibility::Visible);
	}
	return true;
}

void UScoreFeedSlot::HoveredAnim()
{
	PlayAnimation(Hovered, 0.0f, 1, EUMGSequencePlayMode::Forward, 0.9f, false);
}

void UScoreFeedSlot::UnHoveredAnim()
{
	PlayAnimation(UnHovered, 0.0f, 1, EUMGSequencePlayMode::Forward, 0.9f, false);
}
void UScoreFeedSlot::FadeInAnim()
{
	PlayAnimation(FadeIn, 0.0f, 1, EUMGSequencePlayMode::Forward, 0.9f, false);
}
void UScoreFeedSlot::FadeOutAnim()
{
	PlayAnimation(FadeOut, 0.0f, 1, EUMGSequencePlayMode::Forward, 3.f, false);
}
