// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayFeedSlot.generated.h"

UCLASS()
class HANDSABER_API UPlayFeedSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* OpenSongListButton;

	UFUNCTION()
	void OpenPlayFeedSlot();
	UFUNCTION()
	void SendOpenRequest();
	
	virtual bool Initialize() override;

	UFUNCTION(BlueprintCallable)
	void FadeInAnim();
	UFUNCTION(BlueprintCallable)
	void FadeOutAnim();

private:
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
