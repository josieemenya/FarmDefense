// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BarnInterface.generated.h"

USTRUCT(BlueprintType)
struct FBarnStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	double Health;
	
	UPROPERTY(EditAnywhere)
	double MaxHealth;
	
	UPROPERTY()
	double AttackRange;

	FBarnStats() = default;
	FBarnStats(double x, double y, double z) : Health(x), MaxHealth(y), AttackRange(z) {};
	
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBarnInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FARMDEFENSE_API IBarnInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	int32 GetHealth(const FBarnStats &Stats);

	UFUNCTION(BlueprintNativeEvent)
	bool CanAttack(float Range, const FBarnStats &Stats);
};
