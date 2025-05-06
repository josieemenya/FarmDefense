// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlantInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlantInterface : public UInterface
{
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FPlantInfo {
	
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName PlantName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FarmDefense")
	float PlantHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FarmDefense")
	float MaxPlantHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* PlantBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DaysToGrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Thumbnail = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* CurrentGrowthStage; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMesh*> GrowthStages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool hasBeenWatered; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool readyforHarvest;

	FPlantInfo() = default;

	FPlantInfo(FName PName, float plantHealth = 100.f, float MaxPHealth = 100.f, UStaticMeshComponent* Body = nullptr, int32 daysToGrowm = 3,  UTexture2D* thumbnail = nullptr, bool Watered = false, bool Harvest = false) : PlantName(PName), PlantHealth(plantHealth), MaxPlantHealth(MaxPHealth), PlantBody(Body), DaysToGrow(daysToGrowm), Thumbnail(thumbnail), hasBeenWatered(Watered), readyforHarvest(Harvest) {};
};

/**
 * 
 */
class FARMDEFENSE_API IPlantInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	void WaterPlant();

	// harvest;

	UFUNCTION(BlueprintNativeEvent)
	void GetDaysLeft();

	UFUNCTION(BlueprintNativeEvent)
	float GetHealth();

	UFUNCTION(BlueprintNativeEvent)
	float GetMaxHealth();

	UFUNCTION(BlueprintNativeEvent)
	void ChangeInHealth(float Change);

	
	
};
