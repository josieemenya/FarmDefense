// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */

class AFarmDefenseCharacter;
class UScaleBox;
class UBorder;
class UEditableTextBox;
class UCanvasPanel;
class UButton;
class UImage; 
class UProgressBar;
struct FSlateFontInfo; 

UCLASS()
class FARMDEFENSE_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;
	
	// Currency / Gold UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBorder> GoldBorder; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UScaleBox> GoldScaleBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> GoldImage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEditableTextBox> GoldTextBox;
	
	// Health + Stamina UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> StaminaBar; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEditableTextBox> HealthTextBox; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEditableTextBox> StaminaTextBox;
	
	// Gameplay Stats UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEditableTextBox> DaysSpentText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UEditableTextBox> DaysSpentTextNumber;
	
	// axe equip
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UScaleBox> EquipButtonScaleBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> EquipButtonImage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> EquipButton;
	
	// non UI, non Binding variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UFont> TextFont; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AFarmDefenseCharacter> FarmDefenseCharacter; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> EquipAxeIcon; 
	
	// functions
	
	UFUNCTION(BlueprintPure)
	float GetHealthBar() const; 
	
	UFUNCTION(BlueprintPure)
	float GetStaminaBar() const;
	
	UFUNCTION(BlueprintPure)
	FText GetDaysSpentTextNumber() const;
	
	UFUNCTION(BlueprintPure)
	FText WealthText() const; 
	
	UFUNCTION()
	void EquipAxeAction(); 
};
