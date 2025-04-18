// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlaceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FARMDEFENSE_API UPlaceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlaceComponent();

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlaceComponent")
	APawn* Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlaceComponent")
	TSubclassOf<class UStaticMeshComponent> MeshRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	FTransform Transform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMesh* NewMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UMaterial* PerfectMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UMaterial* BadMaterial;
	
	UFUNCTION(BlueprintCallable)
	void PreviewLoop();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	AActor* TheGround;

	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool CanBuild(TArray<AActor*> GetOverlaps);

	


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
