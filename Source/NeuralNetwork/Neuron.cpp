// Fill out your copyright notice in the Description page of Project Settings.


#include "Neuron.h"

UNeuron::UNeuron()
{
	
}

void UNeuron::Init(uint32 NumInputs, double LearningRate_, NeuralNetwork::EActivationFunction ActivationFunction_)
{
	Weights.Reserve(NumInputs);
	for (uint32 i = 0; i < NumInputs; i++)
	{
		Weights.Add(FMath::FRandRange(-1.0, 1.0));
	}

	Bias = FMath::FRandRange(-1.0, 1.0);
	this->LearningRate = LearningRate_;
	this->ActivationFunction = ActivationFunction_;
}


void UNeuron::CalculateOutputGradient(double TargetOutput)
{
}

void UNeuron::CalculateHiddenGradient(const UNetworkLayer& LayerToTheRight, uint32 Index)
{
}

void UNeuron::FeedForward(const TArray<UNeuron>& NeuronsOfPreviousLayer)
{
}

void UNeuron::UpdateWeights(const TArray<UNeuron>& NeuronsOfPreviousLayer, bool bIsOutputLayer)
{
}

void UNeuron::UpdateBias()
{
}

double UNeuron::Activate(double Input) const
{
	return {};
}

double UNeuron::ActivateDerivative(double Input) const
{
	return {};
}
