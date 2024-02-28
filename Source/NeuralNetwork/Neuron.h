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
	void Init(uint32 NumInputs, double LearningRate_, NeuralNetwork::EActivationFunction ActivationFunction_);
	void CalculateOutputGradient(double TargetOutput);
	void CalculateHiddenGradient(const UNetworkLayer& LayerToTheRight, uint32 Index);
	void FeedForward(const TArray<UNeuron>& NeuronsOfPreviousLayer);
	void UpdateWeights(const TArray<UNeuron>& NeuronsOfPreviousLayer, bool bIsOutputLayer);
	void UpdateBias();
	
protected:
	double Activate(double Input) const;
	double ActivateDerivative(double Input) const;
	
	double OriginalOutput;
	double Output;
	double ErrorGradient;
	double ErrorDelta;
	double Bias;
	double LearningRate;
	NeuralNetwork::EActivationFunction ActivationFunction;
	TArray<double> Weights;
};
