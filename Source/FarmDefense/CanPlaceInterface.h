// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CanPlaceInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCanPlaceInterface : public UInterface
{
	GENERATED_BODY()
	
};

/**
 * 
 */
class FARMDEFENSE_API ICanPlaceInterface
{
	GENERATED_BODY()



public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Can place interface")
	void UpdateState(bool bIsPlacementAvailable, UMaterial* PlaceableMaterial, UMaterial* UnplaceableMaterial);

	
	
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
