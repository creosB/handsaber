// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SongFeed.generated.h"

UCLASS()
class HANDSABER_API USongFeed : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UPanelWidget* SongList;

	virtual bool Initialize() override;
};
