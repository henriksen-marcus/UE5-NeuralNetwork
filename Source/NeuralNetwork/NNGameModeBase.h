// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NNConstructorInfo.h"
#include "Printer.h"
#include "NNGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class NEURALNETWORK_API ANNGameModeBase : public AGameModeBase, public Printer
{
	GENERATED_BODY()

public:
	ANNGameModeBase() = default;
	
	void BeginPlay() override;
};
