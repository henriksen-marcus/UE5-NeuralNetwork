// Fill out your copyright notice in the Description page of Project Settings.

#include "NNGameModeBase.h"
#include "ArtificialNeuralNetwork.h"

void ANNGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Init ANN
	UArtificialNeuralNetwork* ANN = NewObject<UArtificialNeuralNetwork>();
	FNNConstructorInfo ConstructorInfo(2, FLayerInfo(1, 0.1, NeuralNetwork::EActivationFunction::Sigmoid));
	ConstructorInfo.AddHiddenLayer(FLayerInfo(100, 0.1, NeuralNetwork::EActivationFunction::Sigmoid));
	//ConstructorInfo.AddHiddenLayer(FLayerInfo(10, 0.1, NeuralNetwork::EActivationFunction::Sigmoid));
	ANN->Init(ConstructorInfo);

	// Training data
	TArray<TArray<double>> TrainingData;
	TArray<TArray<double>> TargetOutputs;
	
	TrainingData.Add({0, 0});
	TargetOutputs.Add({0});

	TrainingData.Add({1, 0});
	TargetOutputs.Add({1});

	TrainingData.Add({0, 1});
	TargetOutputs.Add({1});

	TrainingData.Add({1, 1});
	TargetOutputs.Add({0});

	for (int32 i = 0; i < 1000; i++)
	{
		printWarning(ANN->Train(TrainingData, TargetOutputs));
	}

	
	printLog(" ");
	printWarning("Predicting 0 0:");
	printWarning(ANN->Predict({0, 0})[0]);

	printLog(" ");
	printWarning("Predicting 0 1:");
	printWarning(ANN->Predict({0, 1})[0]);

	printLog(" ");
	printWarning("Predicting 1 0:");
	printWarning(ANN->Predict({1, 0})[0]);

	printLog(" ");
	printWarning("Predicting 1 1:");
	printWarning(ANN->Predict({1, 1})[0]);

	
	
	/*double MSE = ANN->Train(TrainingData, TargetOutputs);
	Printer::printWarning((float)MSE);*/
}
