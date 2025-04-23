// Fill out your copyright notice in the Description page of Project Settings.


#include "Plants.h"
#include "Materials/Material.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/DirectionalLight.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
APlants::APlants()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MaxPlantHealth = 100;
	PlantBody = CreateDefaultSubobject<UStaticMeshComponent>("PlantBody");
	PlantBody->SetupAttachment(GetRootComponent());
	

}


void APlants::Action_Implementation()
{
	(hasBeenWatered) ? --DaysToGrow : DaysToGrow;
	GEngine->AddOnScreenDebugMessage(1, 10.f, FColor::MakeRandomColor(), TEXT("OverlappingPlant"));
}



// Called when the game starts or when spawned
void APlants::BeginPlay()
{
	Super::BeginPlay();
	PlantHealth = MaxPlantHealth;
	//SunLight = UGameplayStatics::GetAllActorsOfClass(GetWorld(), SunLightClass, );
	//SunLight = Cast<ADirectionalLight>(UGameplayStatics::GetActorOfClass(GetWorld(), SunLightClass));
	if (SunLight)
	{
		SunLight->SetBrightness(4.f);
	} else
	{
		GEngine->AddOnScreenDebugMessage(1, 10.f, FColor::MakeRandomColor(), TEXT("Unable To Resolve"));
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

	((SunLight->GetBrightness() == 0.f)) ? Nighttime = true : Nighttime = false;
	
}

