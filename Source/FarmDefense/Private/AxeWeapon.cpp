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


}


// Called when the game starts or when spawned
void AAxeWeapon::BeginPlay()
{
	Super::BeginPlay();
	AxeStructure = FWeaponStructure(AxeDamage); 
	
}

float AAxeWeapon::GetWeaponDamage_Implementation()
{
	return AxeStructure.WeaponDamage; 
}


// Called every frame
void AAxeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}




