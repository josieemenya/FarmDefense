// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuUI.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMenuUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	CloseButton->OnClicked.AddDynamic(this, &UMenuUI::CloseButtonClicked); 
	OpenButton->OnClicked.AddDynamic(this, &UMenuUI::OpenButtonClicked);
}

void UMenuUI::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UMenuUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMenuUI::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMenuUI::CloseButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(),0), EQuitPreference::Quit, true); 
}

void UMenuUI::OpenButtonClicked()
{
	// open level 
	if (!TargetLevel.IsEmpty())
	{
		UGameplayStatics::OpenLevel(GetWorld(), *TargetLevel); 
	}
}
