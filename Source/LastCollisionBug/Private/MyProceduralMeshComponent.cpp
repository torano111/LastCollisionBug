// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProceduralMeshComponent.h"

bool UMyProceduralMeshComponent::ContainsPhysicsTriMeshData(bool InUseAllTriData) const
{
	if (bAlwaysCookPhysics)
	{
		return true;
	}
	else
	{
		return Super::ContainsPhysicsTriMeshData(InUseAllTriData);
	}
}
