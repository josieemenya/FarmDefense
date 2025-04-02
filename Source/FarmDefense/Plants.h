// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plants.generated.h"

UCLASS()
class FARMDEFENSE_API APlants : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlants();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* PlantBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DaysToGrow; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool hasBeenWatered; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool readyforHarvest;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void Grow() { (hasBeenWatered)? --DaysToGrow : DaysToGrow; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
