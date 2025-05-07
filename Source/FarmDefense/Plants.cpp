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
#include "Editor/Documentation/Private/UDNParser.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnitConversion.h"
// Sets default values
APlants::APlants()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// setting default values
	PlantInfo = CreateDefaultPlantInfo();
	PlantInfo.PlantBody = CreateDefaultSubobject<UStaticMeshComponent>("PlantBody");
	RootComponent = PlantInfo.PlantBody;
	//PlantInfo.PlantBody->SetupAttachment(GetRootComponent());
	OverlappingActor = nullptr;
	BoxOverlap = CreateDefaultSubobject<UBoxComponent>("BoxOverlap");
	BoxOverlap->SetupAttachment(PlantInfo.PlantBody);
	StaminaCost = -12;
	howManyTimes = 0;
	//BoxOverlap->size
	PlantInfo.GrowthStages.SetNum(3);
	

}


FPlantInfo APlants::CreateDefaultPlantInfo() // tbh i don't think i actually use this
{
	return FPlantInfo();
}

FPlantInfo APlants::CreateSpecialPlanInfo(FName PlantName) // uunused
{
	return FPlantInfo(PlantName);
}

void APlants::ChangeInHealth_Implementation(float Change) // yet ti be used but will be used
{
	this->PlantInfo.MaxPlantHealth += Change;
}

void APlants::GetDaysLeft_Implementation()
{
	DaysLeft = (FText::AsNumber(this->PlantInfo.DaysToGrow)); // unuased
}

void APlants::WaterPlant_Implementation()
{
	++howManyTimes;
	this->PlantInfo.hasBeenWatered = true;
}

void APlants::Action_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Plant Action Test"));

	if (PlantInfo.hasBeenWatered && howManyTimes == 1 && PlantInfo.DaysToGrow > 0)
	{
		if ((GetOverlappingActor() == nullptr))
		{
			GetCharacter = UGameplayStatics::GetActorOfClass(GetWorld(), ActorCharacterClass); 
			SetOverlappingActor(GetCharacter); 
		}// if days to grow == 0 - harvest;
	} else if (howManyTimes >= 0)
	{
		FString Message = "You have already watered "+ FString(this->GetName());
		GEngine->AddOnScreenDebugMessage(1, 10.f, FColor::MakeRandomColor(), Message); // playtest and ad return; if neccessary.
	} 

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
	DayCounter = PlantInfo.DaysToGrow;
	SetActorScale3D(FVector(2, 2, 2));
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlants::bIsDaytime, 60.f, true); // checks for daytime, i think we can potentially get rid of this
	GetWorld()->GetTimerManager().SetTimer(TimerHandle2, this, &APlants::bCanGrow, 5.f, true); // growth functionality
	GetWorld()->GetTimerManager().SetTimer(TimerHandle3, this, &APlants::GetDaysLeft_Implementation, 45.f, true); // unused

	
	
	if (BoxOverlap)
	{
		BoxOverlap->OnComponentBeginOverlap.AddDynamic(this, &APlants::OnOverlap);
		BoxOverlap->OnComponentBeginOverlap.AddDynamic(this, &APlants::OnOverlap);
	}
	
	for (TActorIterator<ADirectionalLight> DirectionalLightIter(GetWorld()); DirectionalLightIter; ++DirectionalLightIter)
	{

		if (ADirectionalLight* DirectionalLight = Cast<ADirectionalLight>(*DirectionalLightIter))
		{
		// replace with UE_LOG	GEngine->AddOnScreenDebugMessage(1, 10.f, FColor::MakeRandomColor(), TEXT("Found Sunlight"));
			SunLight = DirectionalLight;
		
		} else
		{	// replace with ue_log
			GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::MakeRandomColor(), TEXT("No Sunlight"));
		}
	}
	if (!PlantInfo.GrowthStages.IsEmpty() && PlantInfo.GrowthStages.IsValidIndex(0))
		PlantInfo.PlantBody->SetStaticMesh(PlantInfo.GrowthStages[0]);
}



void APlants::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);
	GEngine->AddOnScreenDebugMessage(12, 10.f, FColor::MakeRandomColor(), TEXT("I've been clicked")); // remove
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

void APlants::ChangeBody(float Percentage)
{
	// checking if the graowth stages aren't empty
	if (PlantInfo.GrowthStages.IsEmpty())
	{
		return; 
	}

	// checking if each static mesh is valid
	for (auto c : PlantInfo.GrowthStages)
	{
		if (!IsValid(c))
		{
			return; 
		}
	}

	// changing plant body based on Percentage
	if (Percentage < 0.33f)
	{
		PlantInfo.PlantBody->SetStaticMesh(PlantInfo.GrowthStages[2]);
	} else if (Percentage < 0.67f)
	{
		PlantInfo.PlantBody->SetStaticMesh(PlantInfo.GrowthStages[1]);
	}else
	{
		PlantInfo.PlantBody->SetStaticMesh(PlantInfo.GrowthStages[0]);
	}
	UE_LOG(LogTemp, Warning, TEXT("Percentage: %f"), Percentage);
	UE_LOG(LogTemp, Warning, TEXT("DaysLeft : %d"), PlantInfo.DaysToGrow);
}


void APlants::bCanGrow()
{
	ChangeBody(PlantInfo.DaysToGrow/(float)DayCounter);
	TArray<AActor*> EnemyActos;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AllEnemies, EnemyActos);
	if (SunLight->GetBrightness() <  0.5f && !bIsDamaged && PlantInfo.hasBeenWatered)
	{
		howManyTimes = 0; 
		if (PlantInfo.DaysToGrow > 0)
		{
			if (EnemyActos.IsEmpty())
			{
				--PlantInfo.DaysToGrow;
				SunLight->SetBrightness(10.f); //sets it back to day
				SunLight->SetLightColor(FColor(1.0, 1.0, 1.0)); // white
				PlantInfo.hasBeenWatered = false;
				
				
			}
		}	
		else
			Harvest(); 
		
	}
	UE_LOG(LogTemp, Warning, TEXT("DaysLeft : %d"), PlantInfo.DaysToGrow);
}

