// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies.h"



// Sets default values
AEnemies::AEnemies()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

}

// Called when the game starts or when spawned
void AEnemies::BeginPlay()
{
	Super::BeginPlay();
	enemy_stats = FEnemyStats(100, 100);

}

// Called every frame
void AEnemies::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemies::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemies::TakeDamage_Implementation(float ATK)
{
	float DamagePoint = ATK * (1.5 - enemy_stats.Defense);
	if (enemy_stats.Health > DamagePoint)
	{
		enemy_stats.Health += DamagePoint;
		if (enemy_stats.Health <= 0)
			Destroy();
	}
	else
		Destroy();
}

