#include <SDL2/SDL.h>

#define MAX_ROUNDS 1
class Round
{
	public:
		Round ();
		void start();
		void end();
		void update();
		bool isActive();
		typedef void (*FunctionPointer)();
		typedef bool (*FunctionPointerB)();

		void setRoundStart(FunctionPointer ptr) 
		{
			roundStart = ptr;
		}

		void callRoundStart() 
		{
			if (roundStart != nullptr) 
				roundStart();
		}

		bool callRoundUpdate() 
		{
			if (roundUpdate != nullptr) 
				return roundUpdate();
			else
				return false;
		}

		void setRoundUpdate (FunctionPointerB ptr) 
		{
			roundUpdate = ptr;
		}

	private:
		Uint32 duration;
		FunctionPointer roundStart;
		FunctionPointer roundEnd;
		FunctionPointerB roundUpdate;
};

extern Round rnd;
