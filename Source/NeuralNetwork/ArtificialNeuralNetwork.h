// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ArtificialNeuralNetwork.generated.h"

class UNetworkLayer;
struct FNNConstructorInfo;

/**
 * 
 */
UCLASS()
class NEURALNETWORK_API UArtificialNeuralNetwork : public UObject
{
	GENERATED_BODY()

public:
	UArtificialNeuralNetwork();
	void Init(const FNNConstructorInfo& ConstructorInfo);
	TArray<double> ForwardPropagate(const TArray<double>& Input);
	double BackPropagate(const TArray<double>& Input, const TArray<double>& TargetOutput);
	double Train(const TArray<TArray<double>>& TrainingData, const TArray<TArray<double>>& TargetOutputs);
	FORCEINLINE TArray<double> Predict(const TArray<double>& Input) { return ForwardPropagate(Input); }

protected:
	UPROPERTY()
	TArray<UNetworkLayer*> NetworkLayers;
};
