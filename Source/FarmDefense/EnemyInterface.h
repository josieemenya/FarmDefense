// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

USTRUCT(BlueprintType)
struct FEnemyStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Defense; 

	

	FEnemyStats() = default;
	FEnemyStats(double x, double y = 100.f, int32 z = 10) : Health(x), MaxHealth(y), Defense(z) {};

	
};


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FARMDEFENSE_API IEnemyInterface
{
	GENERATED_BODY()

	

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent)
	void TakeDamage(float ATK);
};
