// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InteractInterface.h"
#include "StatsInterface.h"
#include "Logging/LogMacros.h"
#include "Kismet/KismetMathLibrary.h"
#include "SimpleMacros.h"
#include "FarmDefenseCharacter.generated.h"

UENUM(BlueprintType)
enum class EAxeEquippedState : uint8
{
	AxeEquipped,
	AxeUnequipped
};

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UUserWidget;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AFarmDefenseCharacter : public ACharacter, public SimpleMacros, public IStatsInterface
{
	GENERATED_BODY()

	class USkeletalMeshComponent* Mesh;
	
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TriggerAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* OpenContextMenuAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackEnemies;


public:
	AFarmDefenseCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FPlayerInfo PlayerStatsInfo; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Animation)
	class UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Animation)
	bool bAttacking;

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetStaminaP() { return this->PlayerStatsInfo.Stamina; };

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetHealthP() { return this->PlayerStatsInfo.Health; }

	UFUNCTION(BlueprintPure)
	FPlayerInfo GetPlayerStatsInfo() { return PlayerStatsInfo; };

	UFUNCTION(BlueprintCallable)
	void SetPlayerStatsInfo(FPlayerInfo PlayerStats) { PlayerStatsInfo = PlayerStats; };

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* OverlapSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TSubclassOf<class ASpectatorPawn> BuilderPawn;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Trigger(const FInputActionValue& Value);

	void OpenContextMenu(const FInputActionValue& Value);
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FarmDefense")
	int32 Actions;

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

	AActor* OverlappingActor {nullptr};

	
public:
	// interface methods, maybe i should done differently, is getting kind of tedious
	UFUNCTION(BlueprintPure)
	virtual float GetTotalWealth_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual void AddTotalWealth_Implementation(float MoneyAdded) override;

	UFUNCTION(BlueprintCallable)
	virtual void TakeAwayWealth_Implementation(float MoneyTakenAway) override;

	UFUNCTION(BlueprintPure)
	virtual int32 GetTotalDays_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual void TheNextDay_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual float GetHealth_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual float GetMaxHealth_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual float GetStamina_Implementation() override;

	UFUNCTION(BlueprintCallable)
	virtual float GetMaxStamina_Implementation() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void ChangeInStamina_Implementation(float Cost) override;

	UFUNCTION(BlueprintCallable)
	virtual void ChangeInHealth_Implementation(float Change) override;

	UFUNCTION(BlueprintCallable)
	virtual void HealHealth_Implementation(float HealPoint) override;

	UFUNCTION(BlueprintCallable)
	virtual void TakeHealth_Implementation(float DamagePoint) override;

	float time = 0; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sounds")
	class USoundBase* WaterSound;

	//UFUNCTION(BlueprintCallable)
	//void AddToInventory(FPlayerInfo& PlayerStats, AActor* InventoryActor) override;

	UFUNCTION(BlueprintCallable)
	void Attack(const FInputActionValue& Value); 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FarmDefense")
	TSubclassOf<UUserWidget> ContextMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FarmDefense")
	UUserWidget* ContextMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FarmDefense")
	TSubclassOf<UUserWidget> TheHUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FarmDefense")
	UUserWidget* TheHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FarmDefense")
	bool bBeginAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FarmDefense")
	EAxeEquippedState isAxeEquipped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FarmDefense")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FarmDefense")
	TArray<AActor*> Ignore;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FarmDefense")
	bool enlarge;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE AActor* GetOverlappingActor() const {return  OverlappingActor;}
	FORCEINLINE void SetOverlappingActor (AActor* v) {OverlappingActor = v;}

	virtual void Tick(float DeltaTime) override;
	
	
};





