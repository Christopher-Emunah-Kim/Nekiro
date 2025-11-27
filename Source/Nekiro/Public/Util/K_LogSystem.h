// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nekiro.h"
#include "Misc/Paths.h"
#include "Engine/Engine.h"


//1. 로그 카테고리 선언
NEKIRO_API DECLARE_LOG_CATEGORY_EXTERN(LogKHS, Log, All);


//2. 로그 레벨 정의 
enum class EKLogLevel : uint8
{
	Trace = 0, // 세밀 추적 (개발/디버그 전용)
	Debug = 1,     // 디버그 정보 (개발/디버그 전용)
	Info  = 2,      // 중요 상태 변화 (모든 빌드 포함)
	Warn  = 3,      // 경고 상황 (모든 빌드 포함)
	Error = 4,     // 오류 상황 (모든 빌드 포함)
	Fatal = 5      // 치명적 오류 (모든 빌드 포함)
};


//3. 빌드 환경별 컴파일 타임 최적화
#if UE_BUILD_SHIPPING
	#define KHS_COMPILETIME_MIN_LEVEL EKLogLevel::Info
#else
	#define KHS_COMPILETIME_MIN_LEVEL EKLogLevel::Trace
#endif

#define KHS_LEVEL_ENABLED(Level) (static_cast<int32>(Level) >= static_cast<int32>(KHS_COMPILETIME_MIN_LEVEL))



//4. 메인 로깅 매크로
//함수 이름, 파일 이름, 라인 번호 포함
#define KHS_LOG_INTERNAL(Category, Level, Format, ...) \
	do { \
		if (KHS_LEVEL_ENABLED(Level)) \
		{ \
			switch(Level) {																					  \
                case EKLogLevel::Trace:																		  \
                    UE_LOG(Category, VeryVerbose, TEXT("[%s][%s:%d] " Format),								  \
                        TEXT(__FUNCTION__), *FPaths::GetCleanFilename(__FILE__), __LINE__, ##__VA_ARGS__);	  \
                    break;																					  \
                case EKLogLevel::Debug:																		  \
                    UE_LOG(Category, Verbose, TEXT("[%s][%s:%d] " Format),									  \
                        TEXT(__FUNCTION__), *FPaths::GetCleanFilename(__FILE__), __LINE__, ##__VA_ARGS__);    \
                    break;																					  \
                case EKLogLevel::Info:																		  \
                    UE_LOG(Category, Log, TEXT("[%s][%s:%d] " Format),										  \
                        TEXT(__FUNCTION__), *FPaths::GetCleanFilename(__FILE__), __LINE__, ##__VA_ARGS__);    \
                    break;																					  \
                case EKLogLevel::Warn:																		  \
                    UE_LOG(Category, Warning, TEXT("[%s][%s:%d] " Format),									  \
                        TEXT(__FUNCTION__), *FPaths::GetCleanFilename(__FILE__), __LINE__, ##__VA_ARGS__);    \
                    break;																					  \
                case EKLogLevel::Error:																		  \
                    UE_LOG(Category, Error, TEXT("[%s][%s:%d] " Format),									  \
                        TEXT(__FUNCTION__), *FPaths::GetCleanFilename(__FILE__), __LINE__, ##__VA_ARGS__);    \
                    break;																					  \
                case EKLogLevel::Fatal:																		  \
                    UE_LOG(Category, Fatal, TEXT("[%s][%s:%d] " Format),									  \
                        TEXT(__FUNCTION__), *FPaths::GetCleanFilename(__FILE__), __LINE__, ##__VA_ARGS__);    \
                    break;																					  \
				default:																					  \
					UE_LOG(Category, Log, TEXT("[%s][%s:%d] " Format),										  \
						TEXT(__FUNCTION__), *FPaths::GetCleanFilename(__FILE__), __LINE__, ##__VA_ARGS__);    \
				break;																						  \
            }																								  \
		} \
	} while(0)


//5. 사용자 인터페이스
#define KHS_TRACE(Format, ...) KHS_LOG_INTERNAL(LogKHS, EKLogLevel::Trace, Format, ##__VA_ARGS__)
#define KHS_DEBUG(Format, ...) KHS_LOG_INTERNAL(LogKHS, EKLogLevel::Debug, Format, ##__VA_ARGS__)
#define KHS_INFO(Format, ...)  KHS_LOG_INTERNAL(LogKHS, EKLogLevel::Info,  Format, ##__VA_ARGS__)
#define KHS_WARN(Format, ...)  KHS_LOG_INTERNAL(LogKHS, EKLogLevel::Warn,  Format, ##__VA_ARGS__)
#define KHS_ERROR(Format, ...) KHS_LOG_INTERNAL(LogKHS, EKLogLevel::Error, Format, ##__VA_ARGS__)
#define KHS_FATAL(Format, ...) KHS_LOG_INTERNAL(LogKHS, EKLogLevel::Fatal, Format, ##__VA_ARGS__)


//6. 에디터 출력용
#if WITH_EDITOR

// 에디터 모드에서만 화면에 디버그 메시지 출력
#define KHS_SCREEN_INFO(Format, ...) \
	do \
	{ \
		const FString DebugMessage = FString::Printf(Format, ##__VA_ARGS__); \
		KHS_INFO(TEXT("SCREEN: %s"), *DebugMessage); \
		if (GEngine) \
		{ \
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, DebugMessage); \
		} \
	} while(0)

#else

// 에디터가 아닌 빌드에서는 빈 매크로로 대체
#define KHS_SCREEN_INFO(Format, ...) do {} while(0)

#endif



// 추가 : 함수 진입/종료 로그
struct FKScopeTrace
{

#if UE_BUILD_SHIPPING

	// 컴파일 타임에 비활성화된 경우, 빈 생성자만 제공
	FKScopeTrace(const TCHAR* InFuncName) {}

#else
	FKScopeTrace(const TCHAR* InFuncName)
		: FuncName(InFuncName)
	{
		KHS_TRACE(TEXT(" => Enter %s"), FuncName);
	}

	~FKScopeTrace()
	{
		KHS_TRACE(TEXT(" <= Leave %s"), FuncName);
	}

	const TCHAR* FuncName;
#endif
};

// 함수 진입 시 추가해 실행흐름 추적
#define KHS_FUNC_TRACE() FKScopeTrace ScopeTrace_##__LINE__(TEXT(__FUNCTION__));

