// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include "Components/EditableTextBox.h"
#include "Components/ProgressBar.h"
#include "FarmDefense/FarmDefenseCharacter.h"

void UPlayerHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	HealthBar->PercentDelegate.BindUFunction(this, "GetHealthBar"); 
	StaminaBar->PercentDelegate.BindUFunction(this, "GetStaminaBar");
	DaysSpentTextNumber->TextDelegate.BindUFunction(this, "GetDaysSpentTextNumber");; 
	GoldTextBox->TextDelegate.BindUFunction(this, "WealthText");
}

void UPlayerHUD::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerHUD::NativeDestruct()
{
	Super::NativeDestruct();
}

float UPlayerHUD::GetHealthBar() const
{
	float Proportion = 0.f;
	if (FarmDefenseCharacter)
	{
		float PlayerHealth = FarmDefenseCharacter->GetHealth_Implementation();
		float MaxHealth = FarmDefenseCharacter->GetMaxHealth_Implementation();
		
		Proportion = PlayerHealth / MaxHealth; 
	}
	return Proportion;
}

float UPlayerHUD::GetStaminaBar() const
{
	float Proportion = 0.f;
	if (FarmDefenseCharacter)
	{
		float PlayerStamina = FarmDefenseCharacter->GetStaminaP(); 
		float MaxStamina = FarmDefenseCharacter->GetMaxStamina();
		
		Proportion = PlayerStamina / MaxStamina;
	}
	return Proportion;
}

FText UPlayerHUD::GetDaysSpentTextNumber() const
{
	FText DaysSpentTextUI = FText::FromString(""); 
	if (FarmDefenseCharacter)
	{
		int32 DaysSpent = FarmDefenseCharacter->GetTotalDays();
		DaysSpentTextUI = FText::AsNumber(DaysSpent);
	}
	return DaysSpentTextUI;
}

FText UPlayerHUD::WealthText() const
{
	FText WealthText = FText::FromString("");
	
	if (FarmDefenseCharacter)
	{
		float Wealth = FarmDefenseCharacter->PlayerStatsInfo.TotalWealth;
		WealthText = FText::AsNumber(Wealth);
	}
	return WealthText;
}

void UPlayerHUD::EquipAxeAction()
{
	// detect if character is armed
	// equip axe if not, adjust damage ig and whatever
}

