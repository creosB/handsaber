// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PatchNotesSlot.generated.h"

UCLASS()
class HANDSABER_API UPatchNotesSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void FadeInAnim();
	UFUNCTION(BlueprintCallable)
	void FadeOutAnim();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* NotesButton;

	UFUNCTION()
	void PatchNotesSlot();
	UFUNCTION()
	void OpenNotesRequest();

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

	virtual bool Initialize() override;
};
