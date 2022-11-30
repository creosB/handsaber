// Fill out your copyright notice in the Description page of Project Settings.


#include "SongList.h"
#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

bool USongList::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) { return false; }

	if (!ensure(SongName != nullptr)) { return false; }
	if (!ensure(AuthorName != nullptr)) { return false; }
	if (!ensure(Difficulty != nullptr)) { return false; }
	if (!ensure(SelectButton != nullptr)) { return false; }
	SelectButton->OnClicked.AddDynamic(this, &USongList::OnClicked);
	SelectButton->OnHovered.AddDynamic(this, &USongList::HoveredAnim);
	SelectButton->OnUnhovered.AddDynamic(this, &USongList::UnHoveredAnim);
	return true;
}

void USongList::Setup(UMainMenu* InParent, uint32 InIndex)
{
	Parent = InParent;
	Index = InIndex;
}

// return pressed button index
void USongList::OnClicked()
{
	FTimerHandle Timer;
	FadeOutAnim();
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &USongList::SendSelectedIndex, 1.0f, false,
	                                       FadeOut->GetEndTime() - 0.7f);
}

void USongList::SendSelectedIndex()
{
	Parent->SelectIndex(Index);
	FadeInAnim();
}


void USongList::HoveredAnim()
{
	PlayAnimation(Hovered, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.f, false);
}

void USongList::UnHoveredAnim()
{
	PlayAnimation(UnHovered, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.f, false);
}

void USongList::FadeInAnim()
{
	PlayAnimation(FadeIn, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.f, false);
}

void USongList::FadeOutAnim()
{
	PlayAnimation(FadeOut, 0.0f, 1, EUMGSequencePlayMode::Forward, 3.f, false);
}
