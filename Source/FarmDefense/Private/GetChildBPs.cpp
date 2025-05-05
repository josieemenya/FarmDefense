// Fill out your copyright notice in the Description page of Project Settings.


#include "GetChildBPs.h"
#include "UObject/UObjectIterator.h"

TArray<UClass*> UGetChildBPs::GetChildrenOfClass(TSubclassOf<UObject> ParentClass, bool includeCPP, bool includeBP)
{
    TArray<UClass*> Sublasses;
    
    for(TObjectIterator< UClass > ClassIt; ClassIt; ++ClassIt)
    {
        UClass* Class = *ClassIt;
 
        // Only interested in relevant classes
        if (Class->IsNative() && !includeCPP) continue;
        if (!Class->IsNative() && !includeBP) continue;
 
 
        // Ignore deprecated
        if(Class->HasAnyClassFlags(CLASS_Deprecated | CLASS_NewerVersionExists))
            continue;
 
 
        if (Class->HasAnyFlags(RF_Transient) && Class->HasAnyClassFlags(CLASS_CompiledFromBlueprint)) continue;
 
 
        // Check this class is a subclass of Base
        if(!Class->IsChildOf(ParentClass))
            
            continue;
 
        // Add this class
        Sublasses.Add(Class);
    }

    return Sublasses;
}
