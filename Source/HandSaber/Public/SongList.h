// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SongList.generated.h"

class UTextBlock;

UCLASS()
class HANDSABER_API USongList : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SongName; // server name text block widget
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AuthorName;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Difficulty;

	UPROPERTY(BlueprintReadOnly)
	bool Selected = false; // selection logic
	UFUNCTION()
	void Setup(class UMainMenu* Parent, uint32 Index);

	UFUNCTION(BlueprintCallable)
	void FadeInAnim();
	UFUNCTION(BlueprintCallable)
	void FadeOutAnim();
private:
	virtual bool Initialize() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* SelectButton;

	UFUNCTION()
	void OnClicked();
	UFUNCTION()
	void SendSelectedIndex();

	UPROPERTY()
	UMainMenu* Parent;
	uint32 Index;

	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
	UWidgetAnimation* FadeIn;
	UPROPERTY(Transient, meta=(BindWidgetAnim, AllowPrivateAccess = true))
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
