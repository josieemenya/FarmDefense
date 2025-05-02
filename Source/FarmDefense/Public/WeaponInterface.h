// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponInterface.generated.h"




USTRUCT(BlueprintType)
struct FWeaponStructure
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHitResult LineHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Start;

	// alternatively you can get the camera location
	// FVector Start = FirstPersonCameraComponent->GetComponentLocation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ForwardVector; // = FirstPersonCameraComponent->GetForwardVector();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector End; //((ForwardVector * 1000.f) + Start);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);
	
	
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FARMDEFENSE_API IWeaponInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	void DrawALine(); 
	
	UFUNCTION(BlueprintNativeEvent)
	bool isHittingEnemy(bool x); 
};
