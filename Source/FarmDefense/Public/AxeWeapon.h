// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponInterface.h"
#include "AxeWeapon.generated.h"

UCLASS()
class FARMDEFENSE_API AAxeWeapon : public AActor, public IWeaponInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAxeWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float BaseZ = 0.f; 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ACharacter> Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeaponStructure AxeStructure; 
	
	UFUNCTION(BlueprintPure)
	float GetWeaponDamage_Implementation() override;
	

};

