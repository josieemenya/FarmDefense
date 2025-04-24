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
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStamina;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TotalWealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TotalDays;

	FPlayerInfo() = default;
	FPlayerInfo(float PHealth, float PMaxHealth, float PStamina, float PMaxStamina, float TWealth, int32 TDays) : Health(PHealth), MaxHealth(PMaxHealth), Stamina(PStamina), MaxStamina(PMaxStamina), TotalWealth(TWealth), TotalDays(TDays) {};
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

	UFUNCTION(BlueprintNativeEvent)
	float GetHealth();

	UFUNCTION(BlueprintNativeEvent)
	float GetMaxHealth();

	UFUNCTION(BlueprintNativeEvent)
	float GetStamina();

	UFUNCTION(BlueprintNativeEvent)
	float GetMaxStamina();

	UFUNCTION(BlueprintNativeEvent)
	void ChangeInHealth(float Change);

	UFUNCTION(BlueprintNativeEvent)
	void HealHealth(float HealPoint);

	UFUNCTION(BlueprintNativeEvent)
	void TakeHealth(float DamagePoint);

	UFUNCTION(BlueprintNativeEvent)
	void ChangeInStamina(float Cost);

	UFUNCTION(BlueprintNativeEvent)
	void HealStamina(float HealPoint);

	UFUNCTION(BlueprintNativeEvent)
	void TakeStamina(float DamagePoint);
	

	
};
