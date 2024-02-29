// Fill out your copyright notice in the Description page of Project Settings.


#include "Neuron.h"

#include "NetworkLayer.h"
#include "Printer.h"

UNeuron::UNeuron() : Output(0), ErrorDelta(0), OriginalOutput(0), ErrorGradient(0), Bias(0), LearningRate(0),
                    ActivationFunction(NeuralNetwork::EActivationFunction::Sigmoid)
{
}

void UNeuron::Init(int32 NumInputs, double LearningRate_, NeuralNetwork::EActivationFunction ActivationFunction_)
{
	Weights.Reserve(NumInputs);
	for (int32 i = 0; i < NumInputs; i++)
	{
		Weights.Add(FMath::FRandRange(-1.0, 1.0));
	}

	Bias = FMath::FRandRange(-1.0, 1.0);
	this->LearningRate = LearningRate_;
	this->ActivationFunction = ActivationFunction_;
}

void UNeuron::CalculateOutputGradient(double TargetOutput)
{
	ErrorDelta = TargetOutput - Output;
	ErrorGradient = ErrorDelta * ActivateDerivative(Output);
}

void UNeuron::CalculateHiddenGradient(UNetworkLayer* LayerToTheRight, int32 Index)
{
	double Sum = 0.0;
	for (const auto& Neuron : LayerToTheRight->Neurons)
		Sum += Neuron->ErrorGradient * Neuron->Weights[Index];

	ErrorGradient = Sum * ActivateDerivative(Output);
}

void UNeuron::FeedForward(const TArray<UNeuron*>& NeuronsOfPreviousLayer)
{
	double Sum = 0.0;

	for (int32 i = 0; i < NeuronsOfPreviousLayer.Num(); i++)
	{
		Sum += NeuronsOfPreviousLayer[i]->Output * Weights[i];
	}

	Sum += Bias;
	OriginalOutput = Sum;
	Output = Activate(Sum);
}

void UNeuron::UpdateWeights(const TArray<UNeuron*>& NeuronsOfPreviousLayer, bool bIsOutputLayer)
{
	if (bIsOutputLayer)
	{
		for (int32 i = 0; i < Weights.Num(); i++)
			Weights[i] += LearningRate * NeuronsOfPreviousLayer[i]->Output * ErrorDelta;
		return;
	}

	for (int32 i = 0; i < Weights.Num(); i++)
		Weights[i] += LearningRate * NeuronsOfPreviousLayer[i]->Output * ErrorGradient;
}

void UNeuron::UpdateBias()
{
	Bias += LearningRate * ErrorGradient;
}

double UNeuron::Activate(double Input) const
{
	switch (ActivationFunction)
	{
	case NeuralNetwork::EActivationFunction::Sigmoid:
		return 1 / (1 + FMath::Exp(-Input));
	case NeuralNetwork::EActivationFunction::ReLU:
		return Input > 0 ? Input : 0;
	case NeuralNetwork::EActivationFunction::Tanh:
		return FMath::Tanh(Input);
	default:
		Printer::printError("Neuron::Activate: Unknown activation function.\n");
		return 0;
	}
}

double UNeuron::ActivateDerivative(double Input) const
{
	switch (ActivationFunction)
	{
	case NeuralNetwork::EActivationFunction::Sigmoid:
		return Input * (1 - Input); // Derivative of the sigmoid activation function
	case NeuralNetwork::EActivationFunction::ReLU:
		return Input > 0 ? 1 : 0;
	case NeuralNetwork::EActivationFunction::Tanh:
		return 1 - Input * Input; // Derivative of the tanh activation function
	default:
		Printer::printError("Neuron::ActivateDerivative: Unknown activation function.\n");
		return 0;
	}
}
