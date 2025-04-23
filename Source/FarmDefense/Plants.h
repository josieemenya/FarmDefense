// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "InputCoreTypes.h"
#include "Plants.generated.h"

class ADirectionalLight;
UCLASS()

class FARMDEFENSE_API APlants : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlants();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDay;

	UFUNCTION(BlueprintCallable)
	void bIsDaytime();

	UFUNCTION(BlueprintCallable)
	void bCanGrow();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FarmDefense")
	FColor LightColour;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FarmDefense")
	bool bIsDamaged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FarmDefense")
	float DaytimeManager;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FarmDefense")
	float NightManager;
	
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ADirectionalLight> SunLightClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ADirectionalLight* SunLight;
	

	public:
	//UFUNCTION(BlueprintCallable, Category = "FarmDefense")
	//float GetSellPrince() const { return SellPrice; } // should have many factors for sell price

	UFUNCTION(BlueprintCallable)
	virtual void Action_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UUserWidget* PlantActionMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> PlantActionMenuContext;



	
protected:
	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
