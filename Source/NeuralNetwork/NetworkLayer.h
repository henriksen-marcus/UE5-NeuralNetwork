// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NNConstructorInfo.h"
#include "UObject/NoExportTypes.h"
#include "NetworkLayer.generated.h"

struct FLayerInfo;
class UNeuron;

/**
 * 
 */
UCLASS()
class NEURALNETWORK_API UNetworkLayer : public UObject
{
	GENERATED_BODY()

public:
	UNetworkLayer();
	void Init(const FLayerInfo& LayerInfo, int32 NumNeuronInputs);

	UPROPERTY()
	TArray<UNeuron*> Neurons;
};
