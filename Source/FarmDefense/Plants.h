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

	//APlants(const FObjectInitializer& ObjectInitializer, FPlantInfo);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StaminaCost; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interact)
	FText DaysLeft; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDay;


	UFUNCTION(BlueprintImplementableEvent)
	void UpdateStamina(); 

	UFUNCTION(BlueprintCallable)
	void bIsDaytime();

	UFUNCTION(BlueprintCallable)
	void bCanGrow();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FarmDefense")
	FColor LightColour;

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

	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
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
