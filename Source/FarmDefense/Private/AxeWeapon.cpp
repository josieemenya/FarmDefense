// Fill out your copyright notice in the Description page of Project Settings.


#include "AxeWeapon.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AAxeWeapon::AAxeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(GetRootComponent());
	AxeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AxeMesh"));
	AxeMesh->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AAxeWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAxeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	CurrentLocation.Z += FMath::Sin(DeltaTime * 2 * 100.f); 

	SetActorLocation(CurrentLocation);
	

}

