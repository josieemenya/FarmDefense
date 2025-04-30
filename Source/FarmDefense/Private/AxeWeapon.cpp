// Fill out your copyright notice in the Description page of Project Settings.


#include "AxeWeapon.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AAxeWeapon::AAxeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Axe = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	Axe->SetupAttachment(GetRootComponent());
	Axe->SetWorldScale3D(FVector(100, 100, 100)); 

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

}

