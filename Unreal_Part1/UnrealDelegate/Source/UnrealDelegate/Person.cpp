// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"
#include "Card.h"

UPerson::UPerson()
{
	Name = TEXT("홍길동");
	Card = CreateDefaultSubobject<UCard>(TEXT("NAME_Card"));//string이 아니고 FName임을 명시하기 위해서 NAME_을 출력
}