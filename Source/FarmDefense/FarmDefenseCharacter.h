// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InteractInterface.h"

#include "Logging/LogMacros.h"
#include "Kismet/KismetMathLibrary.h"
#include "SimpleMacros.h"
#include "FarmDefenseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UUserWidget;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AFarmDefenseCharacter : public ACharacter, public SimpleMacros
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


public:
	AFarmDefenseCharacter();



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
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FarmDefense")
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

	AActor* OverlappingActor {nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FarmDefense")
	double TotalWealth {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FarmDefense")
	int32 DaysSpent;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "FarmDefense")
	FORCEINLINE float GetTotalWealth() const { return TotalWealth; }

	UFUNCTION(BlueprintCallable, Category = "FarmDefense")
	FORCEINLINE void AddToWealth(float SellPrice){ TotalWealth += SellPrice; }

	UFUNCTION(BlueprintCallable, Category = "FarmDefense")
	FORCEINLINE void RemoveFromWealth(){ TotalWealth -= GetTotalWealth(); }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FarmDefense")
	TArray<AActor*> Inventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FarmDefense")
	TSubclassOf<UUserWidget> ContextMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FarmDefense")
	UUserWidget* ContextMenuWidget;
	
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE AActor* GetOverlappingActor() const {return  OverlappingActor;}
	FORCEINLINE void SetOverlappingActor (AActor* v) {OverlappingActor = v;}

	UPROPERTY(EditAnywhere)
	class UAnimSequence* WaterPlant; 
	
	
};

