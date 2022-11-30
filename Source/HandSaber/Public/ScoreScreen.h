// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuInterface.h"
#include "MenuWidget.h"
#include "Blueprint/UserWidget.h"
#include "ScoreScreen.generated.h"

class UTextBlock;

UCLASS()
class HANDSABER_API UScoreScreen : public UMenuWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreText;
	void SendScreen(int score);
	IMenuInterface* MainMenuInterface = nullptr;

	UFUNCTION()
	void SetScoreColor(float progress);
	
private:
	int Score = 0;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};