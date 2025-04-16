// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "InputCoreTypes.h"
#include "CanPlaceInterface.h"
#include "Plants.generated.h"

UCLASS()
class FARMDEFENSE_API APlants : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlants();

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FarmDefense")
	float PlantHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FarmDefense")
	float MaxPlantHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* PlantBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DaysToGrow; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool hasBeenWatered; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool readyforHarvest;

	public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SellPrice;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxSellPrince;

	public:
	//UFUNCTION(BlueprintCallable, Category = "FarmDefense")
	//float GetSellPrince() const { return SellPrice; } // should have many factors for sell price

	UFUNCTION(BlueprintCallable)
	virtual void Action_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UUserWidget* PlantActionMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> PlantActionMenuContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanBePlaced;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterial* M_CanPlaceMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterial* M_CannotPlaceMaterial;

	
protected:
	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
