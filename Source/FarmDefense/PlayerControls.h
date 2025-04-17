// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2Node_SpawnActor.h"
#include "GameFramework/PlayerController.h"
#include "Iris/ReplicationSystem/WorldLocations.h"
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
	bool bPlacemenrIsValid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	TSubclassOf<class AActor> PlaceableActorType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	TSubclassOf<class UActorComponent> ClickableComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	TSubclassOf<class UActorComponent> CanPlaceComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	TEnumAsByte<ECollisionChannel> Landscape;
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "References")
	void PlacementModeEnabled(bool isEnabled);
	
	UFUNCTION(BlueprintCallable)
	void UpdatePlacement()
	{
		
		FVector WorldLocation;
		FVector WorldDirection;
		DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, WorldLocation, (WorldLocation + (WorldDirection * 10000)), Landscape);
		
		DrawDebugPoint(GetWorld(), Hit.Location, 100.f, FColor::Red, false, 5.0f);
		if(!Hit.bBlockingHit && Hit.GetActor()){
						FString Name = *Hit.GetActor()->GetName();
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Name);
						//PlaceableActor->SetActorLocation(Hit.Location);
		}
		else
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Name");
	};

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "References")
	void SpawnBuilding();

	
	
};
