// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BarnInterface.h"
#include "TheBarn.generated.h"

UCLASS()
class FARMDEFENSE_API ATheBarn : public AActor, public IBarnInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATheBarn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FBarnStats GetBarnStats;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* BarnMesh;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HealthBarClass;

	UPROPERTY(EditAnywhere)
	class UUserWidget* HealthBar;

	UFUNCTION(BlueprintCallable)
	virtual int32 GetHealth_Implementation(const FBarnStats &Stats) override;

	UFUNCTION(BlueprintCallable)
	bool CanAttack_Implementation(float Range, const FBarnStats& Stats) override;

};
