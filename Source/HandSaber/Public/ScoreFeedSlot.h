// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreFeedSlot.generated.h"

UCLASS()
class HANDSABER_API UScoreFeedSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void FadeInAnim();
	UFUNCTION(BlueprintCallable)
	void FadeOutAnim();
private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ScoreText;

	virtual void NativeConstruct() override;

	UPROPERTY()
	class UHandSaberSaveGame* SaveGameData = nullptr;
	virtual bool Initialize() override;

	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true), BlueprintReadWrite)
	UWidgetAnimation* FadeIn;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true), BlueprintReadWrite)
	UWidgetAnimation* FadeOut;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* Hovered;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* UnHovered;

	UFUNCTION()
	void HoveredAnim();
	UFUNCTION()
	void UnHoveredAnim();
};
