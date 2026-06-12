// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuUI.generated.h"

/**
 * 
 */
UCLASS()
class FARMDEFENSE_API UMenuUI : public UUserWidget
{
	GENERATED_BODY()
	
	public:


protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* CloseButton;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* OpenButton;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UEditableTextBox* OpenTextBox;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UEditableTextBox* CloseTextBox;
	
	UPROPERTY(EditAnywhere)
	FString TargetLevel; 
	
	UFUNCTION()
	void CloseButtonClicked();
	
	UFUNCTION()
	void OpenButtonClicked();
};
