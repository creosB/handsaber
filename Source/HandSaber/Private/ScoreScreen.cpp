// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreScreen.h"
#include "Components/TextBlock.h"

void UScoreScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UScoreScreen::SendScreen(int score)
{
	Score += score;
	UE_LOG(LogTemp, Warning, TEXT("Added Amount: %d"), score);
	ScoreText->SetText(FText::FromString(FString::FromInt(Score)));
}

void UScoreScreen::SetScoreColor(float progress)
{
	FLinearColor LinearColor = FLinearColor::LerpUsingHSV(FLinearColor::White, FLinearColor(1, 0, 0), progress);
	ScoreText->SetColorAndOpacity(FSlateColor(LinearColor));
}
