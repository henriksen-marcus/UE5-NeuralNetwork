// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActivationFunction.h"
#include "Neuron.generated.h"

class UNetworkLayer;

/**
 * 
 */
UCLASS()
class NEURALNETWORK_API UNeuron : public UObject
{
	GENERATED_BODY()

public:
	UNeuron();
	void Init(int32 NumInputs, double LearningRate_, NeuralNetwork::EActivationFunction ActivationFunction_);
	void CalculateOutputGradient(double TargetOutput);
	void CalculateHiddenGradient(UNetworkLayer* LayerToTheRight, int32 Index);
	void FeedForward(const TArray<UNeuron*>& NeuronsOfPreviousLayer);
	void UpdateWeights(const TArray<UNeuron*>& NeuronsOfPreviousLayer, bool bIsOutputLayer);
	void UpdateBias();
	
	double Output;
	double ErrorDelta;
	
protected:
	double Activate(double Input) const;
	double ActivateDerivative(double Input) const;
	
	double OriginalOutput;
	double ErrorGradient;
	double Bias;
	double LearningRate;
	NeuralNetwork::EActivationFunction ActivationFunction;
	TArray<double> Weights;
};
