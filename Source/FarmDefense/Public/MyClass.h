// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "MyClass.generated.h"

/**
 * 
 */
UCLASS()
class FARMDEFENSE_API UMyClass : public UUserDefinedStruct
{
	GENERATED_BODY()

	UMyClass() = default;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	int32 BUF_StructuredBuffe;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float BUF_StructuredValue;
	
};
