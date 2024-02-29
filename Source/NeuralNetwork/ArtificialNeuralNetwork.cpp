// Fill out your copyright notice in the Description page of Project Settings.


#include "ArtificialNeuralNetwork.h"

#include "NetworkLayer.h"
#include "Neuron.h"
#include "NNConstructorInfo.h"
#include "Printer.h"

UArtificialNeuralNetwork::UArtificialNeuralNetwork()
{
}

void UArtificialNeuralNetwork::Init(const FNNConstructorInfo& ConstructorInfo)
{
	NetworkLayers.Reserve(ConstructorInfo.Topology.Num());
	for (int32 i = 0; i < ConstructorInfo.Topology.Num(); i++)
	{
		UNetworkLayer* Layer = NewObject<UNetworkLayer>();
		Layer->Init(ConstructorInfo.Topology[i], i == 0 ? 0 : ConstructorInfo.Topology[i - 1].NumNeurons);
		NetworkLayers.Add(Layer);
	}
}

TArray<double> UArtificialNeuralNetwork::ForwardPropagate(const TArray<double>& Input)
{
	checkf(Input.Num() == NetworkLayers[0]->Neurons.Num(),
		TEXT("UArtificialNeuralNetwork::ForwardPropagate: Input size does not match the number of neurons in the input layer."
	   " Input size: %d, Number of neurons in the input layer: %d"), Input.Num(), NetworkLayers[0]->Neurons.Num());

	for (int32 i = 0; i < Input.Num(); i++)
		NetworkLayers[0]->Neurons[i]->Output = Input[i];
	
	for (int32 i = 1; i < NetworkLayers.Num(); i++)
	{
		for (const auto Neuron : NetworkLayers[i]->Neurons)
			Neuron->FeedForward(NetworkLayers[i - 1]->Neurons);
	}

	// Prepare output array
	const TArray<UNeuron*> OutputLayer = NetworkLayers.Last()->Neurons;
	TArray<double> Output;
	Output.Reserve(OutputLayer.Num());
	
	for (const auto Neuron : OutputLayer)
		Output.Emplace(Neuron->Output);

	return Output;
}

double UArtificialNeuralNetwork::BackPropagate(const TArray<double>& Input, const TArray<double>& TargetOutput)
{
	UNetworkLayer* OutputLayer = NetworkLayers.Last();
	double ErrorSum = 0.0;

	for (int32 i = 0; i < OutputLayer->Neurons.Num(); i++)
	{
		const double NeuronDeltaError = TargetOutput[i] - OutputLayer->Neurons[i]->Output;
		OutputLayer->Neurons[i]->ErrorDelta = NeuronDeltaError;
		ErrorSum += NeuronDeltaError * NeuronDeltaError;
	}

	const double MeanSquaredError = ErrorSum / OutputLayer->Neurons.Num();

	// Calc output layer gradients
	for (int32 i = 0; i < OutputLayer->Neurons.Num(); i++)
		OutputLayer->Neurons[i]->CalculateOutputGradient(TargetOutput[i]);

	// Calc hidden layer gradients
	for (int32 i = NetworkLayers.Num() - 2; i > 0; i--)
	{
		UNetworkLayer* ThisLayer = NetworkLayers[i];
		UNetworkLayer* LayerToTheRight = NetworkLayers[i + 1];

		for (int32 k = 0; k < ThisLayer->Neurons.Num(); k++)
			ThisLayer->Neurons[k]->CalculateHiddenGradient(LayerToTheRight, k);
	}

	// Update weights and biases
	for (const auto Neuron : OutputLayer->Neurons)
		Neuron->UpdateWeights(NetworkLayers[NetworkLayers.Num() - 2]->Neurons, true);

	for (int32 i = NetworkLayers.Num() - 2; i > 0; i--)
	{
		UNetworkLayer* Layer = NetworkLayers[i];
		
		for (const auto Neuron : Layer->Neurons)
		{
			Neuron->UpdateWeights(NetworkLayers[i - 1]->Neurons, false);
			Neuron->UpdateBias();
		}
	}

	return MeanSquaredError;
}

double UArtificialNeuralNetwork::Train(const TArray<TArray<double>>& TrainingData,
	const TArray<TArray<double>>& TargetOutputs)
{
	double MSE = 0.0;
	for (int32 i = 0; i < TrainingData.Num(); i++)
	{
		ForwardPropagate(TrainingData[i]);
		MSE = BackPropagate(TrainingData[i], TargetOutputs[i]);
	}
	return MSE;
}
