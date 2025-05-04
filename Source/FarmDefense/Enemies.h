// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyInterface.h"
#include "Enemies.generated.h"

UCLASS()
class FARMDEFENSE_API AEnemies : public ACharacter, public  IEnemyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemies();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SetActorValues(APawn* SensedPawn);

	UFUNCTION(BlueprintCallable)
	void UnSetActorValues(UActorComponent* Component); 
	
	UPROPERTY(EditAnywhere)
	FEnemyStats enemy_stats;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> Plants;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Distance;  

	UFUNCTION(BlueprintPure)
	float GetHealth() { return enemy_stats.Health; }

	UFUNCTION(BlueprintCallable)
	void TakeDamage_Implementation(float ATK) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ai Comp")
	class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ai Comp")
	APawn* SensedPawnActor;

	UFUNCTION(BlueprintCallable)
	void isSensingPawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ai Comp")
	class UAnimInstance* AttackAnimINstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ai Comp")
	class UAnimMontage* AttackMontage;

	UFUNCTION(BlueprintCallable)
	void AttackPlayer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ai Comp")
	AActor* PlantsTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ai Comp")
	float Attack;

	UFUNCTION(BlueprintCallable)
	void PlayMontage();
};



