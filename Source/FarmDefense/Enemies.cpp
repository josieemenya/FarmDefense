// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies.h"
#include "Perception/PawnSensingComponent.h"



// Sets default values
AEnemies::AEnemies()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	

}

// Called when the game starts or when spawned
void AEnemies::BeginPlay()
{
	Super::BeginPlay();
	enemy_stats = FEnemyStats(100, 100);
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemies::SetActorValues);
	PawnSensingComp->OnComponentDeactivated.AddDynamic(this, &AEnemies::UnSetActorValues);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemies::isSensingPawn, 1.f, true);
}

// Called every frame
void AEnemies::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemies::SetActorValues(APawn* SensedPawn)
{
	//SetActorScale3D(FVector(6, 6, 6));
	SensedPawnActor = SensedPawn;
}

void AEnemies::UnSetActorValues(UActorComponent* Component)
{
	SetActorScale3D(FVector(1, 1, 1));
}


// Called to bind functionality to input
void AEnemies::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemies::isSensingPawn()
{
	if (SensedPawnActor)
	{
		float Distance = FVector::Dist(GetActorLocation(), SensedPawnActor->GetActorLocation());
		if (Distance >= 500)
		{
			SensedPawnActor = nullptr;
		}
	}
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

