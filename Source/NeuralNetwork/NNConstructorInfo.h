#pragma once

#include "CoreMinimal.h"
#include "ActivationFunction.h"
#include "UObject/NoExportTypes.h"

struct FLayerInfo
{
	int32 NumNeurons;
	double LearningRate;
	NeuralNetwork::EActivationFunction ActivationFunction;

	FLayerInfo(int32 NumNeurons_ = 0, double LearningRate_ = 0.0, NeuralNetwork::EActivationFunction ActivationFunction_ = NeuralNetwork::EActivationFunction::Sigmoid)
		: NumNeurons(NumNeurons_), LearningRate(LearningRate_), ActivationFunction(ActivationFunction_)
	{}
};

struct FNNConstructorInfo
{
	TArray<FLayerInfo> Topology;

	FNNConstructorInfo(int32 InputLayerNumNeurons, const FLayerInfo& OutputLayer)
	{
		Topology.Emplace(InputLayerNumNeurons);
		Topology.Add(OutputLayer);
	}

	void AddHiddenLayer(const FLayerInfo& LayerInfo)
	{
		Topology.Insert(LayerInfo, Topology.Num() - 1);
	}
};