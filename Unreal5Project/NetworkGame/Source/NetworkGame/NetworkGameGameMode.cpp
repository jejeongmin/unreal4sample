// Copyright Epic Games, Inc. All Rights Reserved.

#include "NetworkGameGameMode.h"
#include "NetworkGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

ANetworkGameGameMode::ANetworkGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	Http = &FHttpModule::Get();
}

void ANetworkGameGameMode::HttpCall(const FString& InURL, const FString& InVerb)
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &ANetworkGameGameMode::OnResponseReceived);

	//This is the url on which to process the request

	Request->SetURL(InURL);
	Request->SetVerb(InVerb);
	Request->SetHeader("Content-Type", TEXT("application/json"));

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("input", "obj");
	RequestObj->SetStringField("voice", "obj");


	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->SetContentAsString(RequestBody);

	Request->ProcessRequest();

	UE_LOG(LogTemp, Warning, TEXT("HttpCall   url : %s\nrequestBody : %s"), *InURL, *RequestBody);
}


void ANetworkGameGameMode::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("OnResponseReceived   url : %s\nrecv : %s"), *Request->GetURL(), *Response->GetContentAsString());

	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObject;

	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		//Get the value of the json object by field name
		int32 recievedInt = JsonObject->GetIntegerField("customInt");

		UE_LOG(LogTemp, Warning, TEXT("HTTP request result   customInt : %d"), recievedInt);
	}
}

void ANetworkGameGameMode::StartPlay()
{
	Super::StartPlay();

	ResponseHandle = APIHandler.OnResponseSample.AddUObject(
		this, &ANetworkGameGameMode::OnResponse);

}

void ANetworkGameGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	APIHandler.OnResponseSample.Remove(ResponseHandle);

	Super::EndPlay(EndPlayReason);
}

// tests
void ANetworkGameGameMode::TestRequest(const FSampleRequestBody& InRequestBody)
{
	APIHandler.RequestSample(InRequestBody);
}




void ANetworkGameGameMode::OnResponse(const FSampleResponseBody& InResponseBody)
{
}