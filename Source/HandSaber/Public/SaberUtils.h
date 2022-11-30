// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

struct HANDSABER_API SaberUtils
{
	static FVector GetOrthogonalVectorPointToPlane(FVector Point, FVector PointOnPlane, FVector PlaneNormal);
	FORCEINLINE static float SignedDistancePointToPlane(FVector Point, FVector PointOnPlane, FVector PlaneNormal)
	{
		return FVector::DotProduct(PlaneNormal, Point - PointOnPlane);
	}
};
