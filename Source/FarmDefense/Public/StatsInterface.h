// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StatsInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UStatsInterface : public UInterface
{
	GENERATED_BODY()
};


USTRUCT(BlueprintType)
struct FPlayerInfo {
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TotalWealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TotalDays;

	FPlayerInfo(){};
	FPlayerInfo(float TWealth, int32 TDays) : TotalWealth(TWealth), TotalDays(TDays) {};
};


/**
 * 
 */
class FARMDEFENSE_API IStatsInterface
{
	GENERATED_BODY()


	

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent)
	float GetTotalWealth();

	UFUNCTION(BlueprintNativeEvent)
	void AddTotalWealth(float MoneyAdded);

	UFUNCTION(BlueprintNativeEvent)
	void TakeAwayWealth(float MoneyTakenAway);

	UFUNCTION(BlueprintNativeEvent)
	void TheNextDay();

	UFUNCTION(BlueprintNativeEvent)
	int32 GetTotalDays();

	
};
