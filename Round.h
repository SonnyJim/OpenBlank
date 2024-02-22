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
		void setTarget(int value);
		void setTimeout (int seconds);
		int getTimeout ();
		int getDuration ();
		int getTarget(); //How many targets are needed to finish the round
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
		Uint32 mTickStart;
		int mTimeout; //How long in seconds the round should be
		int mDuration; //How long we've been running for
		FunctionPointer roundStart;
		FunctionPointer roundEnd;
		FunctionPointerB roundUpdate;
		int target; //How many targets we need to hit to clear the round
		bool mActive;
		bool hurryUpActive;
};

extern Round rnd;
