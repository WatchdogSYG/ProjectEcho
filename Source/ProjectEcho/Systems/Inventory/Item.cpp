// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

Item::Item(FString name){
	this->name = name;
}

Item::~Item(){

}

FString Item::GetName() {
	return name;
}





