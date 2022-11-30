#pragma once

#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "CoreMinimal.h"
#include "SongStruct.generated.h"

USTRUCT()
struct FSong
{
	GENERATED_BODY()

	UPROPERTY()
	FString songName;

	UPROPERTY()
	FString songAuthorName;

	UPROPERTY()
	int32 previewStartTime;

	UPROPERTY()
	int32 previewDuration;

	UPROPERTY()
	FString difficulty;

	FSong()
	{
	};

	FSong(FString _songName, FString _songAuthorName, int32 _previewStartTime, int32 _previewDuration,
	      FString _difficulty)
	{
		songName = _songName;
		songAuthorName = _songAuthorName;
		previewStartTime = _previewStartTime;
		previewDuration = _previewDuration;
		difficulty = _difficulty;
	}
};

USTRUCT()
struct FSongStruct
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FSong> songs;

	FSongStruct()
	{
	};

	FSongStruct(TArray<FSong> _songs)
	{
		songs = _songs;
	}

	FSongStruct(FString _json_)
	{
		FSongStruct _tmpMyStruct;

		FJsonObjectConverter::JsonObjectStringToUStruct<FSongStruct>(
			_json_,
			&_tmpMyStruct,
			0, 0);

		songs = _tmpMyStruct.songs;
	}
};
