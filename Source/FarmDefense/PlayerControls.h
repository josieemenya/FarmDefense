// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2Node_SpawnActor.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControls.generated.h"

/**
 * 
 */
 
UCLASS()
class FARMDEFENSE_API APlayerControls : public APlayerController
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	AActor* PlaceableActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	bool bPlacementModeEnabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	TSubclassOf<class AActor> PlaceableActorType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	TSubclassOf<class UActorComponent> ClickableComponent;
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "References")
	void PlacementModeEnabled(bool isEnabled);
	
	UFUNCTION(BlueprintCallable)
	void UpdatePlacement(){};

	UFUNCTION(BlueprintCallable)
	void SpawnBuilding(){};


	
};
