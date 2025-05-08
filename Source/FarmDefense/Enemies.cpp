// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "StatsInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/PawnSensingComponent.h"



// Sets default values
AEnemies::AEnemies()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	MontagePlay = false; 

}

// Called when the game starts or when spawned
void AEnemies::BeginPlay()
{
	
	Super::BeginPlay();
	enemy_stats = FEnemyStats(100, 100);
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemies::SetActorValues);
	PawnSensingComp->OnComponentDeactivated.AddDynamic(this, &AEnemies::UnSetActorValues);
	FTimerHandle TimerHandle;
	FTimerHandle EnemyLifeSupport;
	FTimerHandle Check;
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemies::isSensingPawn, 1.f, true);
	GetWorld()->GetTimerManager().SetTimer(EnemyLifeSupport, this, &AEnemies::EnemyDeath, 1.f, true);
	Attack = FMath::RandRange(0.01f, 0.5f); 
	

}

void AEnemies::Destroyed()
{
	ACharacter::Destroyed();
	//stats interface, increment enemy kill
}

// Called every frame
void AEnemies::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//--enemy_stats.Health;

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
		Distance = FVector::Dist(GetActorLocation(), SensedPawnActor->GetActorLocation());
		if (Distance >= 800)
		{
			SensedPawnActor = nullptr;
		}
	}
}

void AEnemies::AttackPlayer()
{
	FVector Start, End;
	if (GetMesh() && GetMesh()->DoesSocketExist(FName("AttackCenter")))
	{
		Start = GetMesh()->GetSocketLocation(FName("AttackCenter"));
		End = GetMesh()->GetSocketLocation(FName("AttackCenter"));
	}
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> IgnoreActors;
	FHitResult Hit;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	if (SensedPawnActor || PlantsTarget)
	{
		if (SensedPawnActor->Implements<UStatsInterface>())
		{
			UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), Start, End, 100.f, ObjectTypes, false, IgnoreActors, EDrawDebugTrace::None, Hit, true, FColor::MakeRandomColor());
			// DO PLAYER DAMAGE
			IStatsInterface::Execute_TakeHealth(SensedPawnActor, Attack);
		}
			
	}
}

void AEnemies::PlayMontage()
{
	if (AttackAnimINstance && AttackMontage && AttackAnimINstance->Montage_IsPlaying(AttackMontage) == false)
		AttackAnimINstance->Montage_Play(AttackMontage);
}


//IStatsInterface::Execute_TakeHealth(SensedPawnActor, -(Attack));

void AEnemies::TakeDamage_Implementation(float ATK)
{
	float DamagePoint = ATK * (1.5 - enemy_stats.Defense);
	if (enemy_stats.Health > DamagePoint)
	{
		enemy_stats.Health += DamagePoint;
		if (enemy_stats.Health <= 0)
		{
			EnemyDeath(); 
		}
	}
	else
	{
		EnemyDeath(); 
	}
		
}

	