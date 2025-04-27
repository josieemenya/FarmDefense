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
#include "Components/BoxComponent.h"
#include "StatsInterface.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
APlants::APlants()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlantInfo = CreateDefaultPlantInfo();
	PlantInfo.PlantBody = CreateDefaultSubobject<UStaticMeshComponent>("PlantBody");
	PlantInfo.PlantBody->SetupAttachment(GetRootComponent());
	OverlappingActor = nullptr;
	BoxOverlap = CreateDefaultSubobject<UBoxComponent>("BoxOverlap");
	BoxOverlap->SetupAttachment(RootComponent);
	StaminaCost = -12;
	howManyTimes = 0;
	//BoxOverlap->size

}


FPlantInfo APlants::CreateDefaultPlantInfo()
{
	return FPlantInfo();
}

FPlantInfo APlants::CreateSpecialPlanInfo(FName PlantName)
{
	return FPlantInfo(PlantName);
}

void APlants::ChangeInHealth_Implementation(float Change)
{
	this->PlantInfo.MaxPlantHealth += Change;
}

void APlants::GetDaysLeft_Implementation()
{
	DaysLeft = (FText::AsNumber(this->PlantInfo.DaysToGrow));
}

void APlants::WaterPlant_Implementation()
{
	++howManyTimes;
	this->PlantInfo.hasBeenWatered = true;
}

void APlants::Action_Implementation()
{
	if (PlantInfo.hasBeenWatered && howManyTimes == 1 && PlantInfo.DaysToGrow > 0)
	{
		--PlantInfo.DaysToGrow;
		if ((GetOverlappingActor() == nullptr))
		{
			TooMuchWork = CmonMan->GetDefaultObject<AActor>();
			SetOverlappingActor(TooMuchWork);
		}// if days to grow == 0 - harvest;
	} else if (howManyTimes != 1 || howManyTimes == 0)
	{
		char* prefix = "You have already watered ";
		char* temp = new char [50];
		for (char c : this->GetName())
			temp += c;
		const char* suffix = temp;
		GEngine->AddOnScreenDebugMessage(1, 10.f, FColor::MakeRandomColor(), std::strcat(prefix , suffix));
	}
	GEngine->AddOnScreenDebugMessage(1, 10.f, FColor::MakeRandomColor(), TEXT("OverlappingPlant"));
	UpdateStamina();
}

void APlants::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}


void APlants::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this)
		return;
	
	if (OtherActor)
	{
		SetOverlappingActor(OtherActor);
	}
}

void APlants::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (OtherActor == this)
		return;
	if (OtherActor)
	{
		SetOverlappingActor(nullptr);
	}
}

// Called when the game starts or when spawned
void APlants::BeginPlay()
{
	Super::BeginPlay();
	PlantInfo.PlantHealth = PlantInfo.MaxPlantHealth;
	LightColour = FColor(38, 58, 150);
	GEngine->AddOnScreenDebugMessage(10, 10.f, LightColour, TEXT("Testing Light Colour"));
	FTimerHandle TimerHandle;
	FTimerHandle TimerHandle2;
	FTimerHandle TimerHandle3;
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlants::bIsDaytime, 60.f, true);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle2, this, &APlants::bCanGrow, 45.f, true);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle3, this, &APlants::GetDaysLeft_Implementation, 45.f, true);
	
	if (BoxOverlap)
	{
		BoxOverlap->OnComponentBeginOverlap.AddDynamic(this, &APlants::OnOverlap);
		BoxOverlap->OnComponentBeginOverlap.AddDynamic(this, &APlants::OnOverlap);
	}
	
	for (TActorIterator<ADirectionalLight> DirectionalLightIter(GetWorld()); DirectionalLightIter; ++DirectionalLightIter)
	{

		if (ADirectionalLight* DirectionalLight = Cast<ADirectionalLight>(*DirectionalLightIter))
		{
			GEngine->AddOnScreenDebugMessage(1, 10.f, FColor::MakeRandomColor(), TEXT("Found Sunlight"));
			SunLight = DirectionalLight;
			//SunLight->SetBrightness(0.08f);
			//SunLight->SetLightColor(LightColour);
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
		GEngine->AddOnScreenDebugMessage(12, 4.f, FColor::MakeRandomColor(), TEXT("daylight"));
	}
}

void APlants::bCanGrow()
{
	if (SunLight->GetBrightness() <  0.5f && !bIsDamaged && PlantInfo.hasBeenWatered)
	{
		if (PlantInfo.DaysToGrow > 0)
			--PlantInfo.DaysToGrow;
		else
			PlantInfo.readyforHarvest = true;
		PlantInfo.hasBeenWatered = false;
	}

}

