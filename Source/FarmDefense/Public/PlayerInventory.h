// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInventory.generated.h"


USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Quantity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UTexture2D* Icon;
	

	FInventoryItem() = default;
	FInventoryItem(const FString& Name, const FString& Description, int32 Quantity = 1, class UTexture2D* Icon = nullptr){};
	
	bool operator==(const FInventoryItem& Other)
	{
		return Name == Other.Name;
	}
	
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FARMDEFENSE_API UPlayerInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInventory();	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
