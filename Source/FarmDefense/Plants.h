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

	// i don't think this is used at all, check and delete later
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FarmDefense")
	float DaytimeManager;

	// same thing for daytime manageer
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FarmDefense")
	float NightManager;

	// i think i should change to read only
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FPlantInfo PlantInfo;

	//for overlap events
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FarmDefense")
	class UBoxComponent* BoxOverlap;
	
	//for watering functionality, to prevent rapid plant growth
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FarmDefense")
	int32 howManyTimes;

	// also for gameplay funcitonality and growth functionality
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FarmDefense")
	TSubclassOf<AActor> AllEnemies;

	// i think... we can remove this
	UFUNCTION(BlueprintCallable)
	static FPlantInfo CreateDefaultPlantInfo();

	// i also think we can remove this
	UFUNCTION(BlueprintPure)
	static FPlantInfo CreateSpecialPlanInfo(FName PlantName);

	// implemented in BP, if plant has finished growing, sell automatically, desttroy and add max sell price to player
	UFUNCTION(BlueprintImplementableEvent)
	void Harvest();

	// yet to implement 
	UFUNCTION(BlueprintCallable)
	virtual void ChangeInHealth_Implementation(float Change) override;

	// a bit buggy but half does what it's supposed to do-- water plants
	UFUNCTION(BlueprintCallable)
	virtual void WaterPlant_Implementation() override;

	// unused-> i think this was made for ui purposes
	UFUNCTION(BlueprintCallable)
	void GetDaysLeft_Implementation() override;
	

	
	public:
	
	// there is a difference between max price and sell price, if the plant was damaged, sell prce was supposed to go down by an amount between 3-7.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SellPrice;

	// gives max sell price, shop prices were based on 1/4 of the value
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxSellPrince;

	// sunlight ref.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ADirectionalLight> SunLightClass;

	// sunlight rec cont.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ADirectionalLight* SunLight;

	// character refernce holder value thing
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* GetCharacter;

	// character class refernce value holder thinf
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorCharacterClass;

	// self explanatory
	AActor* OverlappingActor;

	// used so the OnOverlap and EndOverlap code wouldn't be bloated.
	FORCEINLINE AActor* GetOverlappingActor() const {return  OverlappingActor;}

	// used so the OnOverlap and EndOverlap code wouldn't be bloated.
	FORCEINLINE void SetOverlappingActor (AActor* v) {OverlappingActor = v;}
	

	public:
	//UFUNCTION(BlueprintCallable, Category = "FarmDefense")
	//float GetSellPrince() const { return SellPrice; } // should have many factors for sell price

	// Inherited from Interact Interface Class
	UFUNCTION(BlueprintCallable)
	virtual void Action_Implementation() override;

	// Unused, delete later
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UUserWidget* PlantActionMenu;

	// the theory was that when actor was clicked you could bring up a plant meanu that showed : water, harvet and otherers
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

	// calculates progress of plant growth and sets mesh accordingly
	UFUNCTION(BlueprintCallable)
	void ChangeBody(float Percentage);

	// used in calculation for plant growth
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DayCounter; 

};
