// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "InputCoreTypes.h"
#include "PlantInterface.h"
#include "Plants.generated.h"

class ADirectionalLight;
UCLASS()

class FARMDEFENSE_API APlants : public AActor, public IInteractInterface, public IPlantInterface
{
	GENERATED_BODY()
	
public:


	
	// Sets default values for this actor's properties
	APlants();

	// sets cost for watering  plant
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StaminaCost; 
	
	// i don't think i've ever used this delete
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interact)
	FText DaysLeft; 

	// i think this was for.. nah, can't think of anything. delete
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDay;


	// implememted in bp because i couldn't hack it in cpp
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateStamina(); 

	// okay i think this runs. okay it's kinda trash. delete
	UFUNCTION(BlueprintCallable)
	void bIsDaytime();

	// key function, basically all plant growing functionality is in here
	UFUNCTION(BlueprintCallable)
	void bCanGrow();

	// i think this was an experiment. delete soon
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FarmDefense")
	FColor LightColour;

	// debateable on whether this is useful yet
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FarmDefense")
	bool bIsDamaged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FarmDefense")
	float DaytimeManager;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FarmDefense")
	float NightManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FPlantInfo PlantInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FarmDefense")
	class UBoxComponent* BoxOverlap;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FarmDefense")
	int32 howManyTimes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FarmDefense")
	TSubclassOf<AActor> AllEnemies;

	UFUNCTION(BlueprintCallable)
	static FPlantInfo CreateDefaultPlantInfo();

	UFUNCTION(BlueprintPure)
	static FPlantInfo CreateSpecialPlanInfo(FName PlantName);

	UFUNCTION(BlueprintImplementableEvent)
	void Harvest();


	UFUNCTION(BlueprintCallable)
	virtual void ChangeInHealth_Implementation(float Change) override;

	UFUNCTION(BlueprintCallable)
	virtual void WaterPlant_Implementation() override;

	UFUNCTION(BlueprintCallable)
	void GetDaysLeft_Implementation() override;
	

	
	public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SellPrice;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxSellPrince;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ADirectionalLight> SunLightClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ADirectionalLight* SunLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* GetCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorCharacterClass;

	AActor* OverlappingActor;

	FORCEINLINE AActor* GetOverlappingActor() const {return  OverlappingActor;}
	FORCEINLINE void SetOverlappingActor (AActor* v) {OverlappingActor = v;}
	

	public:
	//UFUNCTION(BlueprintCallable, Category = "FarmDefense")
	//float GetSellPrince() const { return SellPrice; } // should have many factors for sell price

	UFUNCTION(BlueprintCallable)
	virtual void Action_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UUserWidget* PlantActionMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> PlantActionMenuContext;



	
protected:
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ChangeBody(float Percentage);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DayCounter; 

};
