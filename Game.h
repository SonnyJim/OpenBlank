enum GameState
{
	STATE_GAMEOVER,
	STATE_ROUND_START,
	STATE_ROUND_ACTIVE,
	STATE_ROUND_END,
};

class Game
{
	public:
		void start();
		void end();
		void update();
		GameState getState();
		void setState(GameState s);
		int getRound();
		void setRound(int value);
	private:
		GameState state;
		int round; //Which round are we on
};

extern Game game;
