// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GetChildBPs.generated.h"

/**
 * 
 */
UCLASS()
class FARMDEFENSE_API UGetChildBPs : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, meta =(DecidesOutputType = "Class"))
	static TArray<UClass*> GetChildrenOfClass(TSubclassOf<UObject> ParentClass, bool includeCPP = true, bool includeBP = true);
	
};
