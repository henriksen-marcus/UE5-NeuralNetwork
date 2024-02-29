// Fill out your copyright notice in the Description page of Project Settings.

#include "NetworkLayer.h"
#include "Neuron.h"

UNetworkLayer::UNetworkLayer()
{
}

void UNetworkLayer::Init(const FLayerInfo& LayerInfo, int32 NumNeuronInputs)
{
	Neurons.Reserve(LayerInfo.NumNeurons);
	for (int32 i = 0; i < LayerInfo.NumNeurons; i++)
	{
		UNeuron* Neuron = NewObject<UNeuron>();
		Neuron->Init(NumNeuronInputs, LayerInfo.LearningRate, LayerInfo.ActivationFunction);
		Neurons.Add(Neuron);
	}
}
