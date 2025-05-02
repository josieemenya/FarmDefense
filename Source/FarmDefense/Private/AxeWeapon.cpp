// Fill out your copyright notice in the Description page of Project Settings.


#include "AxeWeapon.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "ReplayHelper.h"
#include "FarmDefense/EnemyInterface.h"
#include "GameFramework/Character.h"


// Sets default values
AAxeWeapon::AAxeWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(GetRootComponent());
}


// Called when the game starts or when spawned
void AAxeWeapon::BeginPlay()
{
	Super::BeginPlay();
	BaseZ = GetActorLocation().Z;
	FTimerHandle CheckBlockingHitActor;
	GetWorld()->GetTimerManager().SetTimer(CheckBlockingHitActor, this, &AAxeWeapon::DrawALine_Implementation, 1.0f, true);
	
}

void AAxeWeapon::DrawALine_Implementation()
{
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + (GetActorForwardVector() * 1000), FColor::Red, false, 1, 0, 2);
	GetWorld()->LineTraceSingleByChannel(AxeStructure.LineHit, AxeStructure.Start, AxeStructure.End, AxeStructure.CollisionChannel);
	isHittingEnemy_Implementation(AxeStructure.LineHit.GetActor() && AxeStructure.LineHit.GetActor()->Implements<UEnemyInterface>()); 
}


// Called every frame
void AAxeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AxeStructure.End = GetActorLocation() + (GetActorForwardVector() * 1000);
	AxeStructure.Start = GetActorLocation();

	//FVector CurrentLocation = GetActorLocation();
	//CurrentLocation.Z =  BaseZ + FMath::Sin(DeltaTime * 2 * 1000.f); 

}

bool AAxeWeapon::isHittingEnemy_Implementation(bool x)
{
	if (x == true)
		this->SetActorScale3D(FVector(10, 10, 10));
	else this->SetActorScale3D(FVector(1, 1, 1));
	return x;
}


