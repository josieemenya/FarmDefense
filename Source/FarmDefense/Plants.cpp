// Fill out your copyright notice in the Description page of Project Settings.


#include "Plants.h"
#include "Materials/Material.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/DirectionalLight.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
APlants::APlants()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MaxPlantHealth = 100;
	PlantBody = CreateDefaultSubobject<UStaticMeshComponent>("PlantBody");
	PlantBody->SetupAttachment(GetRootComponent());
	FTimerHandle TimerHandle;
	FTimerHandle TimerHandle2;
	
//	GetWorld()->GetTimerManager().SetTimer(TimerHandle2, this, &APlants::bIsNighttime, 2.f, true);

}


void APlants::Action_Implementation()
{
	(hasBeenWatered) ? --DaysToGrow : DaysToGrow;
	GEngine->AddOnScreenDebugMessage(1, 10.f, FColor::MakeRandomColor(), TEXT("OverlappingPlant"));
}

void APlants::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}



// Called when the game starts or when spawned
void APlants::BeginPlay()
{
	Super::BeginPlay();
	PlantHealth = MaxPlantHealth;
	LightColour = FColor(0.019382, 0.031896, 0.074214);
	for (TActorIterator<ADirectionalLight> DirectionalLightIter(GetWorld()); DirectionalLightIter; ++DirectionalLightIter)
	{

		if (ADirectionalLight* DirectionalLight = Cast<ADirectionalLight>(*DirectionalLightIter))
		{
			GEngine->AddOnScreenDebugMessage(1, 10.f, FColor::MakeRandomColor(), TEXT("Found Sunlight"));
			SunLight = DirectionalLight;
		} else
		{
			GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::MakeRandomColor(), TEXT("No Sunlight"));
		}
	}
}



void APlants::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);
	GEngine->AddOnScreenDebugMessage(12, 10.f, FColor::MakeRandomColor(), TEXT("I've been clicked"));
}

// Called every frame
void APlants::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//((SunLight->GetBrightness() == 0.f)) ? Nighttime = true : Nighttime = false;
	
}

void APlants::bIsDaytime()
{
	if (SunLight->GetBrightness() > 0.5f)
	{
		bIsDay = true;
	}
}

void APlants::bIsNighttime()
{
	if (SunLight->GetBrightness() <  0.5f)
	{
		//SunLight->SetLightColor(LightColour);
		bIsNight = true;
	}

}

